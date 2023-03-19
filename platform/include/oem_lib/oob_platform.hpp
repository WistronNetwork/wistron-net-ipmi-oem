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
#include <oem-common.hpp>

namespace ipmi
{

enum wistron_oem_cmds
{
    WIS_CMD_GET_FIRMWARE_INFO = 0x20,
    WIS_CMD_SET_FAN_SPEED_CONTROL = 0x21,
    WIS_CMD_GET_FAN_SPEED_CONTROL = 0x22,
    WIS_CMD_SET_HW_WATCHDOG = 0x22,
    WIS_CMD_GET_HW_WATCHDOG = 0x24,
    WIS_CMD_I2C_READ_WRITE = 0x25,
    WIS_CMD_SET_GPIO = 0x26,
    WIS_CMD_GET_GPIO = 0x27,
    WIS_CMD_GET_ALL_GPIO = 0x28,
    WIS_CMD_SET_LED_STATUS = 0x29,
    WIS_CMD_GET_LED_STATUS = 0x2a,
    WIS_CMD_SET_FRU_MFG_DATE = 0x3f,
    WIS_CMD_SET_CMIS_INFORMATION = 0x40,
    WIS_CMD_GET_CMIS_INFORMATION = 0x41,
    WIS_CMD_GET_INTERNAL_SENSOR_THRESHOLD_READING = 0x7c,
    WIS_CMD_GET_PSU_SENSOR_READING = 0x7d,
    WIS_CMD_GET_PSU_SENSOR_THRESHOLD_READING = 0x7e,
    WIS_CMD_GET_FAN_INFORMATION = 0x7f,
    WIS_CMD_SET_I2C_MUX_MASTER = 0x80,
    WIS_CMD_GET_I2C_MUX_MASTER = 0x81,
    WIS_CMD_SET_INTERNAL_SENSOR_READING = 0x82,
    WIS_CMD_SET_UART_MUX_MASTER = 0x83,
    WIS_CMD_GET_UART_MUX_MASTER = 0x84,
    WIS_CMD_SET_LEGACY_CHANNEL_TO_CPU = 0x85,
    WIS_CMD_SET_LEGACY_CHANNEL_TO_BMC = 0x86,
    WIS_CMD_GET_INTERNAL_SENSOR_READING = 0x87,
    WIS_CMD_GET_PSU_INFORMATION = 0x88,
    WIS_CMD_GET_PSU_EEPROM_INFORMATION = 0x89,
    WIS_CMD_GET_PSU_MFR_INFORMATION = 0x8a,
    WIS_CMD_SET_SYSTEM_LED = 0x8b,
    WIS_CMD_GET_SYSTEM_LED = 0x8c,
    WIS_CMD_I2C_WRITE_REQUEST = 0x8d,
    WIS_CMD_I2C_READ_REQUEST = 0x8e,
    WIS_CMD_I2C_READ_WRITE_STATUS = 0x8f,
    WIS_CMD_FORCE_STOP_OEM_TASK_RUNNING = 0x90,
    WIS_CMD_ENABLE_OEM_BMC_TASK_RUNNING = 0x91,
};

enum wistron_net_oem_cmds
{
    WIS_CMD_READ_DIAG_LOG = 0x80,
};

} // namespace ipmi

class OemPlatform : public OemCommon
{
  public:

    OemPlatform() : OemCommon()
    {}
};
