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

#define CPLD2_PATH I2C_SYSFS_DEV_DIR(26-0015)"/hwmon"

IdInfoMap_Psu psu_info = {
    {
        1,
        {
            .pmbusSuid = "25-005b",
            .eepromSuid = "25-0053",
            .presentPath = CPLD2_PATH,
            .presentAttr = "fm_present_psu1_n",
            .pwrgdPath = CPLD2_PATH,
            .pwrgdAttr = "fm_pwrok_psu1",
        }
    },
    {
        2,
        {
            .pmbusSuid = "24-0059",
            .eepromSuid = "24-0051",
            .presentPath = CPLD2_PATH,
            .presentAttr = "fm_present_psu2_n",
            .pwrgdPath = CPLD2_PATH,
            .pwrgdAttr = "fm_pwrok_psu2",
        }
    },
};
