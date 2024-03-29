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
#define FRU_MAX 0

const char* frulist[FRU_MAX] = {
};

/** @example
 *  IdInfoMap_External_Sensor oem_externalsensors = {
 *    {1,{.size = 2, .path = "/xyz/openbmc_project/sensors/temperature/CPU_DDR_DIMM_tmp"}},
 *    {2,{.size = 1, .path = "/xyz/openbmc_project/sensors/temperature/PHY3_temp"}},
 *  };
 */

IdInfoMap_External_Sensor oem_externalsensors = {
    {1,{.size = 1, .path = "NULL"}},
};
