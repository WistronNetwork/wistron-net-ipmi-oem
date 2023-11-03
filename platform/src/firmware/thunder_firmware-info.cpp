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

#define FPGA_PATH I2C_SYSFS_DEV_DIR(29-0020)"/hwmon"
#define CPLD0_PATH I2C_SYSFS_DEV_DIR(1-0066)"/hwmon"
#define CPLD1_PATH I2C_SYSFS_DEV_DIR(30-0061)"/hwmon"
#define CPLD2_PATH I2C_SYSFS_DEV_DIR(31-0062)"/hwmon"
#define CPLD3_PATH I2C_SYSFS_DEV_DIR(31-0063)"/hwmon"
#define FANCPLD_PATH I2C_SYSFS_DEV_DIR(22-0027)"/hwmon"

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
        3, /* For FPGA */
        {
            .majorPath = FPGA_PATH,
            .majorAttr = "fpga_major_version",
            .minorPath = FPGA_PATH,
            .minorAttr = "fpga_minor_version",
        }
    },
    {
        4, /* For SYSTEMCPLD */
        {
            .majorPath = CPLD0_PATH,
            .majorAttr = "syscpld_major_version",
            .minorPath = CPLD0_PATH,
            .minorAttr = "syscpld_minor_version",
        }
    },
    {
        5, /* For LED CPLD */
        {
            .majorPath = CPLD1_PATH,
            .majorAttr = "ledcpld_major_version",
            .minorPath = CPLD1_PATH,
            .minorAttr = "ledcpld_minor_version",
        }
    },
    {
        6, /* For PORT CPLD 1 */
        {
            .majorPath = CPLD2_PATH,
            .majorAttr = "portcpld1_major_version",
            .minorPath = CPLD2_PATH,
            .minorAttr = "portcpld1_minor_version",
        }
    },
    {
        7, /* For PORT CPLD 2 */
        {
            .majorPath = CPLD3_PATH,
            .majorAttr = "portcpld2_major_version",
            .minorPath = CPLD3_PATH,
            .minorAttr = "portcpld2_minor_version",
        }
    },
    {
        8, /* For FANCPLD */
        {
            .majorPath = FANCPLD_PATH,
            .majorAttr = "fancpld_major_version",
            .minorPath = FANCPLD_PATH,
            .minorAttr = "fancpld_minor_version",
        }
    },
};
