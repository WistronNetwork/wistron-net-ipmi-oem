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

#include <ipmid/api.hpp>
#include <sdbusplus/message/types.hpp>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <oem_platform.hpp>
#include <led-info.hpp>
#include <openbmc/misc-utils.h>

using namespace phosphor::logging;

#define LED_COLOR_MAX 3
#define LED_BLINK_MAX 1

namespace ipmi
{

static int setLedStatus(uint8_t led, uint8_t color, uint8_t blink, 
                        std::list<uint8_t> valueList)
{
    auto iter = dalmore_led_info.find(led);
    char path_real[PATH_MAX];
    char ColorPath[PATH_MAX];
    char BlinkPath[PATH_MAX];
    char str_value[10] = {0};
    std::string empty ("NULL");

    auto ledColorPath = iter->second.ledColorPath;
    auto ledColorAttr = iter->second.ledColorAttr;
    auto ledBlinkPath = iter->second.ledBlinkPath;
    auto ledBlinkAttr = iter->second.ledBlinkAttr;

    try {
        if (ledColorPath.compare(empty) == 0 || ledBlinkPath.compare(empty) == 0)
            return ccCommandNotAvailable;

        if (valueList.size() != 2 ||
            valueList.front() != 1 || /* Byte for LED force mode, always 1 */
            valueList.back() > LED_STATUS_MAX)
            return ccParmOutOfRange;
        if (path_realpath(ledColorPath.c_str(), path_real))
            return ccDestinationUnavailable;
        
        snprintf(ColorPath, sizeof(ColorPath), "%s/%s",
                    path_real, ledColorAttr.c_str());
        sprintf(str_value, "%u", color);

        if (device_write_buff(ColorPath, str_value))
            return ccUnspecifiedError;
        
        /* Set Blink */
        if (path_realpath(ledBlinkPath.c_str(), path_real))
            return ccDestinationUnavailable;

        snprintf(BlinkPath, sizeof(BlinkPath), "%s/%s",
                    path_real, ledBlinkAttr.c_str());
        sprintf(str_value, "%u", blink);

        if (device_write_buff(BlinkPath, str_value))
            return ccUnspecifiedError;
    }
    catch (const std::exception& e) {
        return ccUnspecifiedError;
    }
    return ccSuccess;
}

ipmi::RspType<uint8_t> ipmiOemSetLEDStatus(uint8_t led, 
                                           std::vector<uint8_t> valueVec)
{
    uint8_t IpmiCcStatus;
    std::list<uint8_t> valueList(valueVec.begin(), valueVec.end());

    try {
        switch (valueList.back())
        {
            case 0: /* LED off */
                IpmiCcStatus = setLedStatus(led, LED_OFF, LED_NOT_BLINK, valueList);
                break;
            case 1: /* LED on */
            case 2:
            case 3:
                IpmiCcStatus = setLedStatus(led, valueList.back() - 1,
                                            LED_NOT_BLINK, valueList);
                break;
            case 4: /* LED blink */
            case 5:
            case 6:
                IpmiCcStatus = setLedStatus(led, valueList.back() - 4,
                                            LED_BLINK, valueList);
                break;
            default:
                return ipmi::responseParmOutOfRange();
        }
    }
    catch (const std::exception& e) {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::response(IpmiCcStatus);
}

ipmi::RspType<std::vector<uint8_t>> ipmiOemGetLEDStatus(uint8_t led)
{
    int color_value = 0xff;
    int blink_value = 0xff;
    auto iter = dalmore_led_info.find(led);
    char path_real[PATH_MAX];
    char ColorPath[PATH_MAX];
    char BlinkPath[PATH_MAX];
    std::vector<uint8_t> values;
    std::string empty ("NULL");
    
    try {
        auto ledColorPath = iter->second.ledColorPath;
        auto ledColorAttr = iter->second.ledColorAttr;
        auto ledBlinkPath = iter->second.ledBlinkPath;
        auto ledBlinkAttr = iter->second.ledBlinkAttr;

        if (ledColorPath.compare(empty) == 0 || ledBlinkPath.compare(empty) == 0) {
            values.push_back(0);
            return ipmi::responseSuccess(values);
        }
        else {
            if (path_realpath(ledColorPath.c_str(), path_real))
                 color_value = 0xff;

            snprintf(ColorPath, sizeof(ColorPath), "%s/%s",
                     path_real, ledColorAttr.c_str());
            if (device_read(ColorPath, &color_value))
                 color_value = 0xff;
            
            if (path_realpath(ledBlinkPath.c_str(), path_real))
                 blink_value = 0xff;

            snprintf(BlinkPath, sizeof(BlinkPath), "%s/%s",
                     path_real, ledBlinkAttr.c_str());
            if (device_read(BlinkPath, &blink_value))
                 blink_value = 0xff;
        }
    }
    catch (const std::exception& e) {
        values.push_back(0xff);
    }

    if (color_value == LED_OFF)
        values.push_back(0x00);
    else if (color_value == LED_RED && blink_value == LED_NOT_BLINK)
        values.push_back(0x01);
    else if (color_value == LED_GREEN && blink_value == LED_NOT_BLINK)
        values.push_back(0x02);
    else if (color_value == LED_BLUE && blink_value == LED_NOT_BLINK)
        values.push_back(0x03);
    else if (color_value == LED_RED && blink_value == LED_BLINK)
        values.push_back(0x04);
    else if (color_value == LED_RED && blink_value == LED_BLINK)
        values.push_back(0x05);
    else if (color_value == LED_RED && blink_value == LED_BLINK)
        values.push_back(0x06);
    else
        values.push_back(0xff);

    return ipmi::responseSuccess(values);
}
}
