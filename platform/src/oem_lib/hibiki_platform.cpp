/*
// Copyright (c) 2022 Wistron Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#include <oem_platform.hpp>

using namespace phosphor::logging;

#define LED_COLOR_MAX 3
#define LED_BLINK_MAX 1

namespace ipmi
{
static int setLedStatus(uint8_t led, uint8_t status)
{
    auto iter = hibiki_led_info.find(led);
    char path_real[PATH_MAX];
    char ColorPath[PATH_MAX];
    char str_value[10] = {0};
    std::string empty ("NULL");
    uint8_t led_status = status;

    auto ledColorPath = iter->second.ledColorPath;
    auto ledColorAttr = iter->second.ledColorAttr;
    if (ledColorPath.compare(empty) == 0)
        return ccCommandNotAvailable;

    try {
        if (led == 4) // LOC
        {
            if ((int)status == 0)
                led_status = LED_LOC_OFF;
            else if ((int)status == 3)
                led_status = LED_LOC_BLUE;
            else
                return ccParmOutOfRange;
        }
        if (path_realpath(ledColorPath.c_str(), path_real))
            return ccDestinationUnavailable;

        snprintf(ColorPath, sizeof(ColorPath), "%s/%s",
                    path_real, ledColorAttr.c_str());
        sprintf(str_value, "%u", led_status);

        if (device_write_buff(ColorPath, str_value))
            return ccUnspecifiedError;
    }
    catch (const std::exception& e) {
        return ccUnspecifiedError;
    }
    return ccSuccess;
}

ipmi::RspType<uint8_t> ipmiOemSetLEDStatus(uint8_t led,
                                           std::vector<uint8_t> valueVec)
{
    auto iter = hibiki_led_info.find(led);
    uint8_t IpmiCcStatus;
    char ForceModePath[PATH_MAX];
    char path_real[PATH_MAX];
    char str_value[10] = {0};
    std::string empty ("NULL");
    std::list<uint8_t> valueList(valueVec.begin(), valueVec.end());

    auto ledForceModePath = iter->second.ledForceModePath;
    auto ledForceModeAttr = iter->second.ledForceModeAttr;

    if (ledForceModePath.compare(empty) == 0)
        return ipmi::responseCommandNotAvailable();

    if (valueList.size() > 2 ||
        led < 1 || led > 4 ||
        valueList.back() > 6)
        return ipmi::responseParmOutOfRange();

    if (valueList.front() != 0 && valueList.front() != 1)
        return ipmi::responseParmOutOfRange();

    if (path_realpath(ledForceModePath.c_str(), path_real)) {
        return ipmi::responseDestinationUnavailable();
    }

    snprintf(ForceModePath, sizeof(ForceModePath), "%s/%s",
                path_real, ledForceModeAttr.c_str());
    sprintf(str_value, "%u", valueList.front() ? 0 : 1);

    if (device_write_buff(ForceModePath, str_value))
        return ipmi::responseUnspecifiedError();
    try {
        switch (led)
        {
            case 1: /* SYS */
                if (valueList.back() == 0)
                    IpmiCcStatus = setLedStatus(led, LED_OFF);
                else if (valueList.back() == 1)
                    IpmiCcStatus = setLedStatus(led, LED_RED);
                else if (valueList.back() == 2)
                    IpmiCcStatus = setLedStatus(led, LED_GREEN);
                else if (valueList.back() == 4)
                    IpmiCcStatus = setLedStatus(led, LED_GREEN_BLINK);
                else
                    return ipmi::responseParmOutOfRange();
                break;
            case 2: /* FAN and PSU */
            case 3:
                if (valueList.back() == 0)
                    IpmiCcStatus = setLedStatus(led, LED_OFF);
                else if (valueList.back() == 1)
                    IpmiCcStatus = setLedStatus(led, LED_RED);
                else if (valueList.back() == 2)
                    IpmiCcStatus = setLedStatus(led, LED_GREEN);
                else
                    return ipmi::responseParmOutOfRange();
                break;
            case 4: /* LOC needs a special rule*/
                if ((int)valueList.back() == 0)
                    IpmiCcStatus = setLedStatus(led, 0);
                else if ((int)valueList.back() == 3)
                    IpmiCcStatus = setLedStatus(led, 3);
                else
                    return ipmi::responseParmOutOfRange();
                break;
            default:
                return ipmi::responseParmOutOfRange();
        }
    }
    catch (const std::exception& e) {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::response(IpmiCcStatus);
}

ipmi::RspType<std::vector<uint8_t>> ipmiOemGetLEDStatus(uint8_t led)
{
    int color_value = 0xff;
    int forcemode_value = 0xff;
    auto iter = hibiki_led_info.find(led);
    char path_real[PATH_MAX];
    char ColorPath[PATH_MAX];
    char ForceModePath[PATH_MAX];
    std::vector<uint8_t> values;
    std::string empty ("NULL");

    try {
        auto ledColorPath = iter->second.ledColorPath;
        auto ledColorAttr = iter->second.ledColorAttr;
        auto ledForceModePath = iter->second.ledForceModePath;
        auto ledForceModeAttr = iter->second.ledForceModeAttr;

        if (ledColorPath.compare(empty) == 0 ||
            ledForceModePath.compare(empty) == 0) {
            values.push_back(0);
            return ipmi::responseSuccess(values);
        }
        else {
            if (path_realpath(ledColorPath.c_str(), path_real))
                 color_value = 0xff;

            snprintf(ColorPath, sizeof(ColorPath), "%s/%s",
                     path_real, ledColorAttr.c_str());
            if (device_read(ColorPath, &color_value))
                 color_value = 0xff;

            if (path_realpath(ledForceModePath.c_str(), path_real))
                 forcemode_value = 0xff;

            snprintf(ForceModePath, sizeof(ForceModePath), "%s/%s",
                     path_real, ledForceModeAttr.c_str());
            if (device_read(ForceModePath, &forcemode_value))
                 forcemode_value = 0xff;

            if (forcemode_value == 0)
                values.push_back(1);
            else if (forcemode_value == 1)
                values.push_back(0);
        }
    }
    catch (const std::exception& e) {
        values.push_back(0xff);
    }

    if (led == 4) {
        if (color_value == LED_LOC_OFF)
            values.push_back(0x00);
        else if (color_value == LED_LOC_BLUE)
            values.push_back(0x03);
        else
            values.push_back(0xff);
    }
    else if (led == 1){
        if (color_value == LED_OFF)
            values.push_back(0x00);
        else if (color_value == LED_RED)
            values.push_back(0x01);
        else if (color_value == LED_GREEN)
            values.push_back(0x02);
        else if (color_value == LED_GREEN_BLINK)
            values.push_back(0x04);
        else
            values.push_back(0xff);
    } else if (led == 2 || led == 3) {
        if (color_value == LED_OFF)
            values.push_back(0x00);
        else if (color_value == LED_RED)
            values.push_back(0x01);
        else if (color_value == LED_GREEN)
            values.push_back(0x02);
        else
            values.push_back(0xff);
    } else
        return ipmi::responseParmOutOfRange();

    return ipmi::responseSuccess(values);
}
}
