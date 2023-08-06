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

#include <openbmc/obmc-i2c.h>
#include <oem_types.hpp>

#define CPLD1_PATH   I2C_SYSFS_DEV_DIR(3-0011)"/hwmon"
#define CPLD2_PATH   I2C_SYSFS_DEV_DIR(3-0012)"/hwmon"
#define FANCPLD_PATH I2C_SYSFS_DEV_DIR(3-0016)"/hwmon"

IdInfoMap_Firmware firmware_info = {
    {
        1, /* For BMC Primary Flash */
        {
            .majorPath = "/etc",
            .majorAttr = "os-release",
            .minorPath = "/etc",
            .minorAttr = "os-release",
        }
    },
    {
        2, /* For BMC Backup Flash */
        {
            .majorPath = "/run/media/rofs-alt/etc",
            .majorAttr = "os-release",
            .minorPath = "/run/media/rofs-alt/etc",
            .minorAttr = "os-release",
        }
    },
    {
        3, /* For CPLD0 */
        {
            .majorPath = "NULL",
            .majorAttr = "NULL",
            .minorPath = "NULL",
            .minorAttr = "NULL",
        }
    },
    {
        4, /* For CPLD1 */
        {
            .majorPath = CPLD1_PATH,
            .majorAttr = "cpld1_major_version",
            .minorPath = CPLD1_PATH,
            .minorAttr = "cpld1_minor_version",
        }
    },
    {
        5, /* For CPLD2 */
        {
            .majorPath = CPLD2_PATH,
            .majorAttr = "cpld2_major_version",
            .minorPath = CPLD2_PATH,
            .minorAttr = "cpld2_minor_version",
        }
    },
    {
        6, /* For FANCPLD */
        {
            .majorPath = FANCPLD_PATH,
            .majorAttr = "fancpld_major_version",
            .minorPath = FANCPLD_PATH,
            .minorAttr = "fancpld_minor_version",
        }
    },
};
