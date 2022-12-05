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
#include <fru.hpp>
#include <oem_types.hpp>

#define CHANNEL_NUM 1
#define PATH_ROOT "/xyz/openbmc_project/sensors/temperature"
#define PATH_SERVICE "xyz.openbmc_project.ExternalSensor"
#define INTF_SENSORVAL "xyz.openbmc_project.Sensor.Value"
#define INTF_THRESH(type) "xyz.openbmc_project.Sensor.Threshold."#type

namespace ipmi
{

enum externalsensor_errtypes
{
    SENSOR_SUCCESS = 0x00,
    SENSOR_OUT_OF_RANGE = 0x01,
    SENSOR_CONFIG_ERROR = 0x02,
};

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

#ifndef PSUn_FAN_PWM1
#define PSUn_FAN_PWM1 ""
#endif

#ifndef PSUn_FAN_PWM2
#define PSUn_FAN_PWM2 ""
#endif

IdInfoMap_oem oem_psusensors = {
    {
        VIN_AC,
        {.sensorPath = "/xyz/openbmc_project/sensors/voltage/PSUn_VIN_AC",}
    },
    {
        VOUT_DC,
        {.sensorPath = "/xyz/openbmc_project/sensors/voltage/PSUn_VOUT_DC",}
    },
    {
        PIN_AC,
        {.sensorPath = "/xyz/openbmc_project/sensors/power/PSUn_PIN_AC",}
    },
    {
        POUT_DC,
        {.sensorPath = "/xyz/openbmc_project/sensors/power/PSUn_POUT_DC",}
    },
    {
        IIN_AC,
        {.sensorPath = "/xyz/openbmc_project/sensors/current/PSUn_IIN_AC",}
    },
    {
        IOUT_DC,
        {.sensorPath = "/xyz/openbmc_project/sensors/current/PSUn_IOUT_DC",}
    },
    {
        TMP,
        {.sensorPath = "/xyz/openbmc_project/sensors/temperature/PSUn_TMP",}
    },
    {
        TMP2,
        {.sensorPath = "/xyz/openbmc_project/sensors/temperature/PSUn_TMP2",}
    },
    {
        TMP3,
        {.sensorPath = "/xyz/openbmc_project/sensors/temperature/PSUn_TMP3",}
    },
    {
        FAN_TACH1,
        {.sensorPath = "/xyz/openbmc_project/sensors/fan_tach/PSUn_FAN_TACH1",}
    },
    {
        FAN_PWM1,
        {.sensorPath = PSUn_FAN_PWM1,}
    },
    {
        FAN_TACH2,
        {.sensorPath = "/xyz/openbmc_project/sensors/fan_tach/PSUn_FAN_TACH2",}
    },
    {
        FAN_PWM2,
        {.sensorPath = PSUn_FAN_PWM2,}
    },
};

} // namespace ipmi
