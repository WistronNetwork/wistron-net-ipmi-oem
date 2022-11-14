/*
 * Copyright (c)  2018 Intel Corporation.
 * Copyright (c)  2018-present Facebook.
 * Copyright (c)  2022-present Wistron-net.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ipmid/api.h>

#include <boost/container/flat_map.hpp>
#include <commandutils.hpp>
#include <ipmid/utils.hpp>
#include <phosphor-logging/log.hpp>
#include <sdbusplus/message/types.hpp>
#include <sdbusplus/timer.hpp>
#include <storagecommands.hpp>

#include <iostream>

namespace ipmi
{

namespace storage
{
void registerStorageFunctions() __attribute__((constructor));

constexpr static const size_t maxMessageSize = 64;

using ManagedObjectType = boost::container::flat_map<
    sdbusplus::message::object_path,
    boost::container::flat_map<
        std::string, boost::container::flat_map<std::string, DbusVariant>>>;
using ManagedEntry = std::pair<
    sdbusplus::message::object_path,
    boost::container::flat_map<
        std::string, boost::container::flat_map<std::string, DbusVariant>>>;

constexpr static const char* fruDeviceServiceName =
    "xyz.openbmc_project.FruDevice";
constexpr static const size_t cacheTimeoutSeconds = 10;

static std::vector<uint8_t> fruCache;
static uint8_t cacheBus = 0xFF;
static uint8_t cacheAddr = 0XFF;

std::unique_ptr<phosphor::Timer> cacheTimer = nullptr;

// we unfortunately have to build a map of hashes in case there is a
// collision to verify our dev-id
boost::container::flat_map<uint8_t, std::pair<uint8_t, uint8_t>> deviceHashes;

static sdbusplus::bus::bus dbus(ipmid_get_sd_bus_connection());

bool writeFru()
{
    sdbusplus::message::message writeFru = dbus.new_method_call(
        fruDeviceServiceName, "/xyz/openbmc_project/FruDevice",
        "xyz.openbmc_project.FruDeviceManager", "WriteFru");
    writeFru.append(cacheBus, cacheAddr, fruCache);
    try
    {
        sdbusplus::message::message writeFruResp = dbus.call(writeFru);
    }
    catch (const sdbusplus::exception_t&)
    {
        // todo: log sel?
        phosphor::logging::log<phosphor::logging::level::ERR>(
            "error writing fru");
        return false;
    }
    return true;
}

void createTimer()
{
    if (cacheTimer == nullptr)
    {
        cacheTimer = std::make_unique<phosphor::Timer>(writeFru);
    }
}

ipmi_ret_t replaceCacheFru(uint8_t devId)
{
    static uint8_t lastDevId = 0xFF;

    bool timerRunning = (cacheTimer != nullptr) && !cacheTimer->isExpired();
    if (lastDevId == devId && timerRunning)
    {
        return IPMI_CC_OK; // cache already up to date
    }
    // if timer is running, stop it and writeFru manually
    else if (timerRunning)
    {
        cacheTimer->stop();
        writeFru();
    }

    sdbusplus::message::message getObjects = dbus.new_method_call(
        fruDeviceServiceName, "/", "org.freedesktop.DBus.ObjectManager",
        "GetManagedObjects");
    ManagedObjectType frus;
    try
    {
        sdbusplus::message::message resp = dbus.call(getObjects);
        resp.read(frus);
    }
    catch (const sdbusplus::exception_t&)
    {
        phosphor::logging::log<phosphor::logging::level::ERR>(
            "replaceCacheFru: error getting managed objects");
        return IPMI_CC_RESPONSE_ERROR;
    }

    deviceHashes.clear();
    // hash the object paths to create unique device id's. increment on
    // collision
    [[maybe_unused]] std::hash<std::string> hasher;
    for (const auto& fru : frus)
    {
        auto fruIface = fru.second.find("xyz.openbmc_project.FruDevice");
        if (fruIface == fru.second.end())
        {
            continue;
        }
        auto fruidFind = fruIface->second.find("FRUID");
        auto busFind = fruIface->second.find("BUS");
        auto addrFind = fruIface->second.find("ADDRESS");
        if (busFind == fruIface->second.end() ||
            addrFind == fruIface->second.end())
        {
            phosphor::logging::log<phosphor::logging::level::INFO>(
                "fru device missing Bus or Address",
                phosphor::logging::entry("FRU=%s", fru.first.str.c_str()));
            continue;
        }
        uint8_t fruID = std::get<int>(fruidFind->second);
        uint8_t fruBus = std::get<uint32_t>(busFind->second);
        uint8_t fruAddr = std::get<uint32_t>(addrFind->second);
        std::pair<uint8_t, uint8_t> newDev(fruBus, fruAddr);

        deviceHashes.emplace(fruID, newDev);
    }
    auto deviceFind = deviceHashes.find(devId);
    if (deviceFind == deviceHashes.end())
    {
        return IPMI_CC_SENSOR_INVALID;
    }

    fruCache.clear();
    sdbusplus::message::message getRawFru = dbus.new_method_call(
        fruDeviceServiceName, "/xyz/openbmc_project/FruDevice",
        "xyz.openbmc_project.FruDeviceManager", "GetRawFru");
    cacheBus = deviceFind->second.first;
    cacheAddr = deviceFind->second.second;
    getRawFru.append(cacheBus, cacheAddr);
    try
    {
        sdbusplus::message::message getRawResp = dbus.call(getRawFru);
        getRawResp.read(fruCache);
    }
    catch (const sdbusplus::exception_t&)
    {
        lastDevId = 0xFF;
        cacheBus = 0xFF;
        cacheAddr = 0xFF;
        return IPMI_CC_RESPONSE_ERROR;
    }

    lastDevId = devId;
    return IPMI_CC_OK;
}

ipmi_ret_t ipmiStorageReadFRUData(ipmi_netfn_t, ipmi_cmd_t,
                                  ipmi_request_t request,
                                  ipmi_response_t response,
                                  ipmi_data_len_t dataLen, ipmi_context_t)
{
    if (*dataLen != 4)
    {
        *dataLen = 0;
        return IPMI_CC_REQ_DATA_LEN_INVALID;
    }
    *dataLen = 0; // default to 0 in case of an error

    auto req = static_cast<GetFRUAreaReq*>(request);

    if (req->countToRead > maxMessageSize - 1)
    {
        return IPMI_CC_INVALID_FIELD_REQUEST;
    }
    ipmi_ret_t status = replaceCacheFru(req->fruDeviceID);

    if (status != IPMI_CC_OK)
    {
        return status;
    }

    size_t fromFRUByteLen = 0;
    if (req->countToRead + req->fruInventoryOffset < fruCache.size())
    {
        fromFRUByteLen = req->countToRead;
    }
    else if (fruCache.size() > req->fruInventoryOffset)
    {
        fromFRUByteLen = fruCache.size() - req->fruInventoryOffset;
    }
    size_t padByteLen = req->countToRead - fromFRUByteLen;
    uint8_t* respPtr = static_cast<uint8_t*>(response);
    *respPtr = req->countToRead;
    std::copy(fruCache.begin() + req->fruInventoryOffset,
              fruCache.begin() + req->fruInventoryOffset + fromFRUByteLen,
              ++respPtr);
    // if longer than the fru is requested, fill with 0xFF
    if (padByteLen)
    {
        respPtr += fromFRUByteLen;
        std::fill(respPtr, respPtr + padByteLen, 0xFF);
    }
    *dataLen = fromFRUByteLen + 1;

    return IPMI_CC_OK;
}

ipmi_ret_t ipmiStorageWriteFRUData(ipmi_netfn_t, ipmi_cmd_t,
                                   ipmi_request_t request,
                                   ipmi_response_t response,
                                   ipmi_data_len_t dataLen, ipmi_context_t)
{
    if (*dataLen < 4 ||
        *dataLen >=
            0xFF + 3) // count written return is one byte, so limit to one
                      // byte of data after the three request data bytes
    {
        *dataLen = 0;
        return IPMI_CC_REQ_DATA_LEN_INVALID;
    }

    auto req = static_cast<WriteFRUDataReq*>(request);
    size_t writeLen = *dataLen - 3;
    *dataLen = 0; // default to 0 in case of an error

    ipmi_ret_t status = replaceCacheFru(req->fruDeviceID);
    if (status != IPMI_CC_OK)
    {
        return status;
    }
    size_t lastWriteAddr = req->fruInventoryOffset + writeLen;
    if (fruCache.size() < lastWriteAddr)
    {
        fruCache.resize(req->fruInventoryOffset + writeLen);
    }

    std::copy(req->data, req->data + writeLen,
              fruCache.begin() + req->fruInventoryOffset);

    bool atEnd = false;

    if (fruCache.size() >= sizeof(FRUHeader))
    {

        FRUHeader* header = reinterpret_cast<FRUHeader*>(fruCache.data());

        size_t lastRecordStart = std::max(
            header->internalOffset,
            std::max(header->chassisOffset,
                     std::max(header->boardOffset, header->productOffset)));
        // TODO: Handle Multi-Record FRUs?

        lastRecordStart *= 8; // header starts in are multiples of 8 bytes

        // get the length of the area in multiples of 8 bytes
        if (lastWriteAddr > (lastRecordStart + 1))
        {
            // second byte in record area is the length
            int areaLength(fruCache[lastRecordStart + 1]);
            areaLength *= 8; // it is in multiples of 8 bytes

            if (lastWriteAddr >= (areaLength + lastRecordStart))
            {
                atEnd = true;
            }
        }
    }
    uint8_t* respPtr = static_cast<uint8_t*>(response);
    if (atEnd)
    {
        // cancel timer, we're at the end so might as well send it
        cacheTimer->stop();
        if (!writeFru())
        {
            return IPMI_CC_INVALID_FIELD_REQUEST;
        }
        *respPtr = std::min(fruCache.size(), static_cast<size_t>(0xFF));
    }
    else
    {
        // start a timer, if no further data is sent in cacheTimeoutSeconds
        // seconds, check to see if it is valid
        createTimer();
        cacheTimer->start(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::seconds(cacheTimeoutSeconds)));
        *respPtr = 0;
    }

    *dataLen = 1;

    return IPMI_CC_OK;
}

ipmi_ret_t ipmiStorageGetFRUInvAreaInfo(ipmi_netfn_t, ipmi_cmd_t,
                                        ipmi_request_t request,
                                        ipmi_response_t response,
                                        ipmi_data_len_t dataLen, ipmi_context_t)
{
    if (*dataLen != 1)
    {
        *dataLen = 0;
        return IPMI_CC_REQ_DATA_LEN_INVALID;
    }
    *dataLen = 0; // default to 0 in case of an error

    uint8_t reqDev = *(static_cast<uint8_t*>(request));
    if (reqDev == 0xFF)
    {
        return IPMI_CC_INVALID_FIELD_REQUEST;
    }
    ipmi_ret_t status = replaceCacheFru(reqDev);

    if (status != IPMI_CC_OK)
    {
        return status;
    }

    GetFRUAreaResp* respPtr = static_cast<GetFRUAreaResp*>(response);
    respPtr->inventorySizeLSB = fruCache.size() & 0xFF;
    respPtr->inventorySizeMSB = fruCache.size() >> 8;
    respPtr->accessType = static_cast<uint8_t>(GetFRUAreaAccessType::byte);

    *dataLen = sizeof(GetFRUAreaResp);
    return IPMI_CC_OK;
}

void registerStorageFunctions()
{
    // <Get FRU Inventory Area Info>
    ipmiPrintAndRegister(
        NETFUN_STORAGE,
        static_cast<ipmi_cmd_t>(IPMINetfnStorageCmds::ipmiCmdGetFRUInvAreaInfo),
        NULL, ipmiStorageGetFRUInvAreaInfo, PRIVILEGE_OPERATOR);

    // <READ FRU Data>
    ipmiPrintAndRegister(
        NETFUN_STORAGE,
        static_cast<ipmi_cmd_t>(IPMINetfnStorageCmds::ipmiCmdReadFRUData), NULL,
        ipmiStorageReadFRUData, PRIVILEGE_OPERATOR);

    // <WRITE FRU Data>
    ipmiPrintAndRegister(
        NETFUN_STORAGE,
        static_cast<ipmi_cmd_t>(IPMINetfnStorageCmds::ipmiCmdWriteFRUData),
        NULL, ipmiStorageWriteFRUData, PRIVILEGE_OPERATOR);

    return;
}
} // namespace storage
} // namespace ipmi
