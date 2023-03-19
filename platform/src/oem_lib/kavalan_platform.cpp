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
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <phosphor-logging/log.hpp>
#include <openbmc/obmc-i2c.h>
#include <openbmc/misc-utils.h>
#include <openbmc/psu.h>
#include <psu-info.hpp>
#include <oem_types.hpp>

using namespace phosphor::logging;

namespace ipmi
{

int getPSUFanDirection(uint8_t psu)
{
    auto iter = psu_info.find(psu);
    char path[PATH_MAX];
    char data[32] = {0};
    int fd;

    if (iter == psu_info.end())
        return -1;
    else {
        try {
            auto eepromSuid = iter->second.eepromSuid;
            snprintf(path, sizeof(path), PSU_EEPROM, eepromSuid.c_str());
            fd = open(path, O_RDONLY);
            if (fd < 0)
                return -1;

            if (lseek(fd, 0x2E, SEEK_SET) != 0x2E)
                return -1;

            if (file_read_bytes(fd, data, 6) != 6)
                return -1;
            close(fd);

            if (strcmp(data, "FSJ041") == 0)
                return 1;
            else if (strcmp(data, "FSJ021") == 0)
                return 0;
            else
                return -1;
        }
        catch (const std::exception& e) {
            return -1;
        }
    }
}
}
