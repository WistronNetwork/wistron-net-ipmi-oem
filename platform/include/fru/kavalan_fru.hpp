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
#include <oem_types.hpp>

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

IdInfoMap_External_Sensor oem_externalsensors = {
    {1,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/CPU_TMP"}},
    {2,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/M2_SATA_TMP"}},
    {3,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/M2_NVME_TMP"}},
    {4,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/DIMM_TMP"}},
    {5,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P1_TMP"}},
    {6,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P2_TMP"}},
    {7,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P3_TMP"}},
    {8,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P4_TMP"}},
    {9,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P5_TMP"}},
    {10,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P6_TMP"}},
    {11,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P7_TMP"}},
    {12,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P8_TMP"}},
    {13,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P9_TMP"}},
    {14,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P10_TMP"}},
    {15,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P11_TMP"}},
    {16,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P12_TMP"}},
    {17,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P13_TMP"}},
    {18,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P14_TMP"}},
    {19,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P15_TMP"}},
    {20,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P16_TMP"}},
    {21,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P17_TMP"}},
    {22,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P18_TMP"}},
    {23,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P19_TMP"}},
    {24,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P20_TMP"}},
    {25,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P21_TMP"}},
    {26,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P22_TMP"}},
    {27,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P23_TMP"}},
    {28,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P24_TMP"}},
    {29,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P25_TMP"}},
    {30,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P26_TMP"}},
    {31,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P27_TMP"}},
    {32,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P28_TMP"}},
    {33,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P29_TMP"}},
    {34,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P30_TMP"}},
    {35,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P31_TMP"}},
    {36,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P32_TMP"}},
    {37,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/MAC_DIE_TMP"}},
};
