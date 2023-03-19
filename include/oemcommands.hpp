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
#include <sdbusplus/bus.hpp>
#include <sdbusplus/exception.hpp>
#include <oem_platform.hpp>
#include <oem_types.hpp>

#define INTF_SENSORVAL "xyz.openbmc_project.Sensor.Value"
#define INTF_THRESH(type) "xyz.openbmc_project.Sensor.Threshold."#type

enum threshold_type
{
    LowerNonCritical = 1,
    LowerCritical,
    LowerNonRecoverable,
    UpperNonCritical,
    UpperCritical,
    UpperNonRecoverable,
};

enum psu_num
{
    VIN_AC = 1,
    VOUT_DC = 2,
    PIN_AC = 3,
    POUT_DC = 4,
    IIN_AC = 5,
    IOUT_DC = 6,
    TMP = 7,
    TMP2 = 8,
    TMP3 = 9,
    FAN_TACH1 = 10,
    FAN_PWM1 = 11,
    FAN_TACH2 = 12,
    FAN_PWM2 = 13,
};

enum fan_direction
{
    FAN_AFO = 0,
    FAN_AFI = 1,
};

enum device_present
{
    PRESENT = 1,
    NOT_PRESENT = 0,
};

enum device_power_good
{
    POWER_OK = 1,
    POWER_FAIL = 0,
};

#ifndef PSUn_FAN_PWM1
#define PSUn_FAN_PWM1 ""
#endif

#ifndef PSUn_FAN_PWM2
#define PSUn_FAN_PWM2 ""
#endif
