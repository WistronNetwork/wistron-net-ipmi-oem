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

#include <ipmid/api.hpp>
#include <sdbusplus/message/types.hpp>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <phosphor-logging/log.hpp>
#include <gpiod.h>
#include <openbmc/obmc-i2c.h>
#include <openbmc/libgpio.h>
#include <openbmc/misc-utils.h>
#include <openbmc/psu.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <ipmid/utils.hpp>
#include <oem_types.hpp>
#include <psu-info.hpp>
#include <fan-info.hpp>
#include <led-info.hpp>

#define PMBUS_BLOCK_MAX 32

using namespace phosphor::logging;

enum psu_info_id
{
    PSU_INFO = 1,
    PSU_MFR_REV,
    PSU_MFR_ID,
    PSU_MFR_MODEL,
    PSU_MFR_SERIAL,
};

enum firmware_info_id
{
    BMC_PRIMARY_VER = 1,
    BMC_BACKUP_VER,
    CPLD0_VER,
    CPLD1_VER,
    CPLD2_VER,
    FANCPLD_VER,
    FPGA_VER,
};

enum fan_info_id
{
    FAN_INFO = 1,
    FAN_PWM_DUTY,
};

class OemCommon
{
    public:
        std::string i2c_mux_sel;
        std::string i2c_mux_sel_path;

        uint8_t i2c_mux_sel_cpu;
        uint8_t i2c_mux_sel_bmc;

        OemCommon()
        {
            i2c_mux_sel = "NULL";
            i2c_mux_sel_path = "NULL";
            i2c_mux_sel_cpu = 1;
            i2c_mux_sel_bmc = 0;
        }

        virtual ~OemCommon() = default;

        /** @brief Combine multiple bytes to one value
         *
         *  @returns No return
         */
        virtual void sensorMergeValue(std::list<uint8_t>& valueList,
                                      double* value)
        {
            /* One dbus property only matches one parameter,
             * so the size is always 1.
             * If there is a property that needs to be combined by
             * more than one byte, we need to override
             * the function in platform layer.
             */

            *value = (double)(valueList.front());
            valueList.pop_front();
        }

        /** @brief Get I2C mux master select
         *
         *  @returns
         *  -2: No I2C MUX select
         *  -1: Get I2C MUX select value fail
         *   0: BMC
         *   1: CPU
         */
        virtual int getI2cMuxSel()
        {
            int value;
            gpio_value_t value_shadow;

            if (!strcmp(i2c_mux_sel.c_str(), "NULL"))
                return -2;

            if (path_exists(i2c_mux_sel_path.c_str())) {
                if (device_read(i2c_mux_sel_path.c_str(), &value))
                    return -1;
            } else if (gpio_export_by_name(GPIO_CHIP_ASPEED,
                                           i2c_mux_sel.c_str(),
                                           i2c_mux_sel.c_str()) == 0) {
                value_shadow = gpio_get_value_by_shadow(i2c_mux_sel.c_str());

                if (value_shadow == GPIO_VALUE_INVALID)
                    return -1;

                value = (int) value_shadow;
                gpio_unexport(i2c_mux_sel.c_str());
            } else {
                return -1;
            }

            if (value == i2c_mux_sel_cpu)
                return 1;
            else
                return 0;
        }

        /** @brief Get PSU fan direction
         *
         *  @returns
         *  -1: Fail
         *   0: AFO
         *   1: AFI
         */
        virtual int getPSUFanDirection(uint8_t psu, IdInfoMap_Psu::iterator iter)
        {
            (void)psu;
            (void)iter;
            return -1;
        }

        /** @brief Get PSU present status
         *
         *  @returns
         *  -1: Fail
         *   0: Not present
         *   1: Present
         */
        virtual int getPSUPresent(uint8_t psu, IdInfoMap_Psu::iterator iter)
        {
            char path_real[PATH_MAX];
            char path[PATH_MAX];
            int value;

            if (getI2cMuxSel() > 0) {
                log<level::ERR>("getI2cMuxSel - PSU", entry("%d fail", psu));
                return -1;
            }

            try {
                auto presentPath = iter->second.presentPath;
                if (path_realpath(presentPath.c_str(), path_real))
                    return -1;

                snprintf(path, sizeof(path), "%s/%s",
                            path_real, iter->second.presentAttr.c_str());
                if (device_read(path, &value))
                    return -1;

                if (value == PSU_PRESENT_ACTIVE)
                    return 1;
                else
                    return 0;
            }
            catch (const std::exception& e) {
                return -1;
            }
        }

        /** @brief Get PSU power good status
         *
         *  @returns
         *  -1: Fail
         *   0: Power Fail
         *   1: Power OK
         */
        virtual int getPSUPowerGood(uint8_t psu, IdInfoMap_Psu::iterator iter)
        {
            char path_real[PATH_MAX];
            char path[PATH_MAX];
            int value;

            if (getI2cMuxSel() > 0) {
                log<level::ERR>("getI2cMuxSel - PSU", entry("%d fail", psu));
                return -1;
            }

            try {
                auto pwrgdPath = iter->second.pwrgdPath;
                if (path_realpath(pwrgdPath.c_str(), path_real))
                    return -1;

                snprintf(path, sizeof(path), "%s/%s",
                            path_real, iter->second.pwrgdAttr.c_str());
                if (device_read(path, &value))
                    return -1;

                if (value == PSU_PWROK_ACTIVE)
                    return 1;
                else
                    return 0;
            }
            catch (const std::exception& e) {
                return -1;
            }
        }

        /** @brief Get PSU MFR data
         *
         *  @returns
         *  MFR info arry. If all of data are 0xa, it means can't get anything.
         */
        virtual std::vector<uint8_t> getPSUMfrData(uint8_t psu,
                                                   IdInfoMap_Psu::iterator iter,
                                                   uint8_t reg, uint8_t length)
        {
            char data[PMBUS_BLOCK_MAX];
            std::vector<uint8_t> mfr_rev;

            memset(data, 0xa, sizeof(data)); /* Init all value with LF char */

            if (getI2cMuxSel() > 0) {
                log<level::ERR>("getI2cMuxSel - PSU", entry("%d fail", psu));
                goto exit;
            }

            try {
                auto pmbusSuid = iter->second.pmbusSuid;

                if (psu_block_read(pmbusSuid.c_str(), reg, length, data))
                    memset(data, 0xa, sizeof(data));
            }
            catch (const std::exception& e) {
                memset(data, 0xa, sizeof(data));
            }

        exit:
            for (int i = 0; i < length; i++)
                mfr_rev.push_back(data[i]);

            return mfr_rev;
        }

        /** @brief Get system fan direction
         *
         *  @returns
         *  -1: Fail
         *   0: AFO
         *   1: AFI
         */
        virtual int getFanDirection(uint8_t fan, IdInfoMap_Fan::iterator iter)
        {
            char path_real[PATH_MAX];
            char path[PATH_MAX];
            int value;

            if (getI2cMuxSel() > 0) {
                log<level::ERR>("getI2cMuxSel - Fan", entry("%d fail", fan));
                return -1;
            }

            try {
                auto directionPath = iter->second.directionPath;
                auto directionAttr = iter->second.directionAttr;
                if (path_realpath(directionPath.c_str(), path_real))
                    return -1;

                snprintf(path, sizeof(path), "%s/%s", path_real,
                         directionAttr.c_str());
                if (device_read(path, &value))
                    return -1;

                if (value == FAN_AFI_ACTIVE)
                    return 1;
                else
                    return 0;
            }
            catch (const std::exception& e) {
                return -1;
            }
        }

        /** @brief Get system fan present status
         *
         *  @returns
         *  -1: Fail
         *   0: Not present
         *   1: Present
         */
        virtual int getFanPresent(uint8_t fan, IdInfoMap_Fan::iterator iter)
        {
            char path_real[PATH_MAX];
            char path[PATH_MAX];
            int value;

            if (getI2cMuxSel() > 0) {
                log<level::ERR>("getI2cMuxSel - Fan", entry("%d fail", fan));
                return -1;
            }

            try {
                auto presentPath = iter->second.presentPath;
                auto presentAttr = iter->second.presentAttr;
                if (path_realpath(presentPath.c_str(), path_real))
                    return -1;

                snprintf(path, sizeof(path), "%s/%s", path_real,
                         presentAttr.c_str());
                if (device_read(path, &value))
                    return -1;

                if (value == FAN_PRESENT_ACTIVE)
                    return 1;
                else
                    return 0;
            }
            catch (const std::exception& e) {
                return -1;
            }
        }

        /** @brief Get system fan pwm value
         *
         *  @returns
         *        -1: Fail
         *   0 - 100: Duty cycle
         */
        virtual int getFanPwm(uint8_t fan, IdInfoMap_Fan::iterator iter)
        {
            char path_real[PATH_MAX];
            char path[PATH_MAX];
            int value;

            if (getI2cMuxSel() > 0) {
                log<level::ERR>("getI2cMuxSel - Fan", entry("%d fail", fan));
                return -1;
            }

            try {
                auto pwmPath = iter->second.pwmPath;
                auto pwmAttr = iter->second.pwmAttr;
                if (path_realpath(pwmPath.c_str(), path_real))
                    return -1;

                snprintf(path, sizeof(path), "%s/%s",
                         path_real, pwmAttr.c_str());
                if (device_read(path, &value))
                    return -1;

                if (value < 0 || value > 100 )
                    return -1;

            }
            catch (const std::exception& e) {
                return -1;
            }

            return value;
        }
}; // class OemCommon
