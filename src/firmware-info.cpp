/*
 * Copyright (c) 2022 Wistron Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <openbmc/psu.h>
#include <openbmc/obmc-i2c.h>
#include <oem_types.hpp>

IdInfoMap_Firmware firmware_info = {
    {
        1, /* For BMC Primary Flash*/
        {
            .majorPath = "/etc",
            .majorAttr = "os-release",
            .minorPath = "/etc",
            .minorAttr = "os-release",
        }
    },
    {
        2, /* For BMC Backup Flash*/
        {
            .majorPath = "/run/media/rofs-alt/etc",
            .majorAttr = "os-release",
            .minorPath = "/run/media/rofs-alt/etc",
            .minorAttr = "os-release",
        }
    },
};
