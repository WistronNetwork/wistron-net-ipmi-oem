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

#define CHANNEL_NUM 1
#define PATH_ROOT "/xyz/openbmc_project/sensors/temperature"
#define PATH_SERVICE "xyz.openbmc_project.ExternalSensor"
#define INTF_SENSORVAL "xyz.openbmc_project.Sensor.Value"

namespace ipmi
{

enum externalsensor_errtypes
{
    SENSOR_SUCCESS = 0x00,
    SENSOR_OUT_OF_RANGE = 0x01,
    SENSOR_CONFIG_ERROR = 0x02,
};

} // namespace ipmi
