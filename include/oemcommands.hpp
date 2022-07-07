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

namespace ipmi
{

enum wistron_oem_cmds
{
    WIS_CMD_SET_FAN_SPEED_CONTROL = 0x21,
    WIS_CMD_GET_FAN_SPEED_CONTROL = 0x22,
    WIS_CMD_I2C_READ_WRITE = 0x25,
    WIS_CMD_SET_GPIO = 0x26,
    WIS_CMD_GET_GPIO = 0x27,
    WIS_CMD_GET_ALL_GPIO = 0x28,
    WIS_CMD_READ_DIAG_LOG = 0x80,
};

} // namespace ipmi
