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
#include <led-info.hpp>

#define CPLD0_PATH I2C_SYSFS_DEV_DIR(1-0033)"/hwmon"

Hibiki_IdInfoMap_LED hibiki_led_info = {
    {
        1, /* For System LED */
        {
            .ledColorPath = CPLD0_PATH,
            .ledColorAttr = "sys_led_color_control",
            .ledForceModePath = CPLD0_PATH,
            .ledForceModeAttr = "led_force_control",
        }
    },
    {
        2, /* For Fan LED */
        {
            .ledColorPath = CPLD0_PATH,
            .ledColorAttr = "fan_led_color_control",
            .ledForceModePath = CPLD0_PATH,
            .ledForceModeAttr = "led_force_control",
        }
    },
    {
        3, /* For PSU LED */
        {
            .ledColorPath = CPLD0_PATH,
            .ledColorAttr = "psu_led_color_control",
            .ledForceModePath = CPLD0_PATH,
            .ledForceModeAttr = "led_force_control",
        }
    },
    {
        4, /* For LOC LED */
        {
            .ledColorPath = CPLD0_PATH,
            .ledColorAttr = "loc_led_color_control",
            .ledForceModePath = CPLD0_PATH,
            .ledForceModeAttr = "led_force_control",
        }
    },
};