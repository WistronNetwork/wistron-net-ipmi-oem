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

enum led_color
{
    LED_RED = 0,
    LED_GREEN = 1,
    LED_BLUE = 2,
    LED_OFF = 3,
};

enum led_blink
{
    LED_NOT_BLINK = 0,
    LED_BLINK = 1,
};

struct Dalmore_LEDInfo
{
    /** @brief Sysfs for LED color driver path */
    std::string ledColorPath;
    /** @brief Sysfs for LED color attributes */
    std::string ledColorAttr;
    /** @brief Sysfs for LED blink driver path */
    std::string ledBlinkPath;
    /** @brief Sysfs for LED blink attributes */
    std::string ledBlinkAttr;
};

using Dalmore_IdInfoMap_LED = std::map<uint8_t, Dalmore_LEDInfo>;

extern Dalmore_IdInfoMap_LED dalmore_led_info;