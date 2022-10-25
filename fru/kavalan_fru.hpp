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

#pragma once

#include <ipmid/api-types.hpp>

#define FRU_MAX 9

const char* frulist[FRU_MAX] = {
    "/sys/bus/i2c/devices/0-0054/eeprom",  // fru 0: BMC
    "/sys/bus/i2c/devices/1-0056/eeprom",  // fru 1: MB
    "/sys/bus/i2c/devices/38-0051/eeprom", // fru 2: FAN1
    "/sys/bus/i2c/devices/37-0055/eeprom", // fru 3: FAN2
    "/sys/bus/i2c/devices/37-0053/eeprom", // fru 4: FAN3
    "/sys/bus/i2c/devices/37-0051/eeprom", // fru 5: FAN4
    "/sys/bus/i2c/devices/36-0055/eeprom", // fru 6: FAN5
    "/sys/bus/i2c/devices/36-0053/eeprom", // fru 7: FAN6
    "/sys/bus/i2c/devices/36-0051/eeprom"  // fru 8: FAN7
};

/*
 *  This struct is for external sensor.
 *  If there is no external sensor in the project, please keep struct empty.
 */
struct SensorParams
{
    /** @brief The sensor path quantity */
    int size;
    /** @brief dbus path */
    std::string path;
};

struct SensorParams sensorparams[] = {
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/CPU_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/M2_SATA_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/M2_NVME_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/DIMM_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P1_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P2_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P3_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P4_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P5_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P6_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P7_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P8_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P9_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P10_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P11_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P12_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P13_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P14_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P15_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P16_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P17_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P18_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P19_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P20_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P21_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P22_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P23_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P24_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P25_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P26_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P27_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P28_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P29_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P30_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P31_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P32_TMP"},
    {.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/MAC_DIE_TMP"},
};
