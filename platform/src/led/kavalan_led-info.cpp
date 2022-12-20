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

#define CPLD2_PATH I2C_SYSFS_DEV_DIR(26-0015)"/hwmon"

IdInfoMap_LED led_info = {
    {
        1, /* For System LED */
        {
            .ledStatusPath = CPLD2_PATH,
            .ledStatusrAttr = "sys_led_status",
            .ledControlPath = CPLD2_PATH,
            .ledControlAttr = "sys_led_force_control",
            .ledForceModePath = CPLD2_PATH,
            .ledForceModeAttr = "sys_led_force_enable",
        }
    },
    {
        2, /* For PSU LED */
        {
            .ledStatusPath = CPLD2_PATH,
            .ledStatusrAttr = "psu_led_status",
            .ledControlPath = CPLD2_PATH,
            .ledControlAttr = "psu_led_force_control",
            .ledForceModePath = CPLD2_PATH,
            .ledForceModeAttr = "psu_led_force_enable",
        }
    },
    {
        3, /* For Fan LED */
        {
            .ledStatusPath = CPLD2_PATH,
            .ledStatusrAttr = "fan_led_status",
            .ledControlPath = CPLD2_PATH,
            .ledControlAttr = "fan_led_force_control",
            .ledForceModePath = CPLD2_PATH,
            .ledForceModeAttr = "fan_led_force_enable",
        }
    },
    {
        4, /* For LOC LED */
        {
            .ledStatusPath = CPLD2_PATH,
            .ledStatusrAttr = "loc_led_status",
            .ledControlPath = CPLD2_PATH,
            .ledControlAttr = "loc_led_force_control",
            .ledForceModePath = CPLD2_PATH,
            .ledForceModeAttr = "loc_led_force_enable",
        }
    },
};
