/*
// Copyright (c) 2023 Jarvis Chen
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

#define FRU_MAX 6

const char* frulist[FRU_MAX] = {
    "/sys/bus/i2c/devices/0-0054/eeprom",  // fru 0: BMC
    "/sys/bus/i2c/devices/1-0057/eeprom",  // fru 1: MB
    "/sys/bus/i2c/devices/20-0052/eeprom", // fru 2: FAN1
    "/sys/bus/i2c/devices/20-0053/eeprom", // fru 3: FAN2
    "/sys/bus/i2c/devices/21-0054/eeprom", // fru 4: FAN3
    "/sys/bus/i2c/devices/21-0055/eeprom"  // fru 5: FAN4
};

IdInfoMap_External_Sensor oem_externalsensors = {
    {1,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/MAC_DIE_TMP"}},
    {2,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/M2_SATA_TMP"}},
    {3,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/M2_NVME_TMP"}},
    {4,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P1_TMP"}},
    {5,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P2_TMP"}},
    {6,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P3_TMP"}},
    {7,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P4_TMP"}},
    {8,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P5_TMP"}},
    {9,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P6_TMP"}},
    {10,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P7_TMP"}},
    {11,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P8_TMP"}},
    {12,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P9_TMP"}},
    {13,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P10_TMP"}},
    {14,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P11_TMP"}},
    {15,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P12_TMP"}},
    {16,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P13_TMP"}},
    {17,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P14_TMP"}},
    {18,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P15_TMP"}},
    {19,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P16_TMP"}},
    {20,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P17_TMP"}},
    {21,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P18_TMP"}},
    {22,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P19_TMP"}},
    {23,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P20_TMP"}},
    {24,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P21_TMP"}},
    {25,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P22_TMP"}},
    {26,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P23_TMP"}},
    {27,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P24_TMP"}},
    {28,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P25_TMP"}},
    {29,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P26_TMP"}},
    {30,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P27_TMP"}},
    {31,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P28_TMP"}},
    {32,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P29_TMP"}},
    {33,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P30_TMP"}},
    {34,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P31_TMP"}},
    {35,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P32_TMP"}},
    {36,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P33_TMP"}},
    {37,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P34_TMP"}},
    {38,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P35_TMP"}},
    {39,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P36_TMP"}},
    {40,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P37_TMP"}},
    {41,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P38_TMP"}},
    {42,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P39_TMP"}},
    {43,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P40_TMP"}},
    {44,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P41_TMP"}},
    {45,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P42_TMP"}},
    {46,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P43_TMP"}},
    {47,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P44_TMP"}},
    {48,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P45_TMP"}},
    {49,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P46_TMP"}},
    {50,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P47_TMP"}},
    {51,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P48_TMP"}},
    {52,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P49_TMP"}},
    {53,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P50_TMP"}},
    {54,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P51_TMP"}},
    {55,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P52_TMP"}},
    {56,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P53_TMP"}},
    {57,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P54_TMP"}},
    {58,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P55_TMP"}},
    {59,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P56_TMP"}},
    {60,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P57_TMP"}},
    {61,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P58_TMP"}},
    {62,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P59_TMP"}},
    {63,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P60_TMP"}},
    {64,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P61_TMP"}},
    {65,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P62_TMP"}},
    {66,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P63_TMP"}},
    {67,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/QSFP_P64_TMP"}},
};
