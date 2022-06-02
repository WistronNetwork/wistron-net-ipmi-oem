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

#include <ipmid/api.hpp>
#include <sdbusplus/message/types.hpp>
#include <oemcommands.hpp>
#include <vector>
#include <fstream> 
#include <filesystem>
#include <string>
#include <phosphor-logging/log.hpp>
#include <openbmc/obmc-i2c.h>

namespace ipmi
{
static void registerOEMFunctions() __attribute__((constructor));

ipmi::RspType<std::vector<uint8_t>> ipmiOemReadDiagLog()
{
    std::vector<uint8_t> rsp;
    char b;
    int count=0, MAX_COUNT=1024;
    char log1[] = "/tmp/ipmi_log";
    char log2[] = "/tmp/ipmi_log_tmp";
    std::string line;
    std::ifstream f1(log1);
    
    if(!f1.good()) 
        return ipmi::responseSuccess();

    while(!f1.eof() && count < MAX_COUNT){
        count++;
        f1.read(&b, 1);
        rsp.push_back(b);
    }

    if(!f1.eof()){
        std::ofstream f2;
        f2.open(log2);
        while (getline(f1, line)) {
            f2 << line << "\n";
        }
        f2.close();
        remove(log1);
        std::filesystem::copy(log2, log1);
        remove(log2);
    } else {
        remove(log1);
    }

    f1.close();
    return ipmi::responseSuccess(rsp);
}

ipmi::RspType<std::vector<uint8_t>> ipmiOemI2cReadWrite(uint8_t bus, uint8_t addr,
                                                        uint8_t rd_cnt, std::vector<uint8_t> wdata)
{
    int dev;
    char i2c_bus[20];
    uint8_t *wbuf = &wdata[0];
    sprintf(i2c_bus, "/dev/i2c-%d", bus);

    dev = open(i2c_bus, O_RDWR);
    if(dev < 0) {
        std::fprintf(stderr, "%s: open() failed\n", __func__);
        return ipmi::responseUnspecifiedError();
    }

    uint8_t *rbuf = (uint8_t *) malloc(rd_cnt * sizeof(uint8_t));
    i2c_rdwr_msg_transfer(dev, addr << 1, wbuf, wdata.size(), rbuf, rd_cnt);
    std::vector<uint8_t> rdata(rbuf, rbuf + rd_cnt);
    
    close(dev);
    free(rbuf);
    return ipmi::responseSuccess(rdata);
}

void registerOEMFunctions()
{
    phosphor::logging::log<phosphor::logging::level::INFO>(
        "Registering OEM commands");
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemThree, WIS_CMD_READ_DIAG_LOG,
            ipmi::Privilege::User, ipmiOemReadDiagLog);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemThree, WIS_CMD_I2C_READ_WRITE,
            ipmi::Privilege::User, ipmiOemI2cReadWrite);
}
}