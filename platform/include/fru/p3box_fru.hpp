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

#define FRU_MAX 10

const char* frulist[FRU_MAX] = {
    "/sys/bus/i2c/devices/8-0051/eeprom",   // fru 0: BMC
    "/sys/bus/i2c/devices/18-0050/eeprom",  // fru 1: MB
    "/sys/bus/i2c/devices/24-0051/eeprom",  // fru 2: FAN1
    "/sys/bus/i2c/devices/24-0053/eeprom",  // fru 3: FAN2
    "/sys/bus/i2c/devices/24-0055/eeprom",  // fru 4: FAN3
    "/sys/bus/i2c/devices/26-0051/eeprom",  // fru 5: FAN4
    "/sys/bus/i2c/devices/26-0053/eeprom",  // fru 6: FAN5
    "/sys/bus/i2c/devices/26-0055/eeprom",  // fru 7: FAN6
};

IdInfoMap_External_Sensor oem_externalsensors = {
    {1,{.size = 1, .path = "NULL"}},
};
