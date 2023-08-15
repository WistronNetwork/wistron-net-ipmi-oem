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

#include <string>
#include <map>

#pragma once

#define LED_STATUS_MAX 6

enum led_sys_psu_fan_status
{
    LED_GREEN_BLINK = 0,
    LED_RED = 1,
    LED_GREEN = 2,
    LED_OFF = 3,
};

enum led_loc_status
{
    LED_LOC_BLUE = 0,
    LED_LOC_OFF = 1,
};

enum led_forece_mode
{
    FORCE_MODE = 0,
    UNFORCE_MODE = 1,
};

struct Hibiki_LEDInfo
{
    /** @brief Sysfs for LED color driver path */
    std::string ledColorPath;
    /** @brief Sysfs for LED color attributes */
    std::string ledColorAttr;
    /** @brief Sysfs for LED blink driver path */
    std::string ledForceModePath;
    /** @brief Sysfs for LED blink attributes */
    std::string ledForceModeAttr;
};

using Hibiki_IdInfoMap_LED = std::map<uint8_t, Hibiki_LEDInfo>;

extern Hibiki_IdInfoMap_LED hibiki_led_info;