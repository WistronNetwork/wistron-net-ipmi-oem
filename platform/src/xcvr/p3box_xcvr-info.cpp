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
#include <oemcommands.hpp>

#define CPLD1_PATH I2C_SYSFS_DEV_DIR(3-0011)"/hwmon"
#define CPLD2_PATH I2C_SYSFS_DEV_DIR(3-0012)"/hwmon"

IdInfoMap_Xcvr xcvr_info = {
    {
        1,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p01_present_n",
            .eepromSuid = "32-0050",
        }
    },
    {
        2,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p02_present_n",
            .eepromSuid = "33-0050",
        }
    },
    {
        3,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p03_present_n",
            .eepromSuid = "34-0050",
        }
    },
    {
        4,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p04_present_n",
            .eepromSuid = "35-0050",
        }
    },
    {
        5,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p05_present_n",
            .eepromSuid = "36-0050",
        }
    },
    {
        6,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p06_present_n",
            .eepromSuid = "37-0050",
        }
    },
    {
        7,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p07_present_n",
            .eepromSuid = "38-0050",
        }
    },
    {
        8,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p08_present_n",
            .eepromSuid = "39-0050",
        }
    },
    {
        9,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p09_present_n",
            .eepromSuid = "40-0050",
        }
    },
    {
        10,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p10_present_n",
            .eepromSuid = "41-0050",
        }
    },
    {
        11,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p11_present_n",
            .eepromSuid = "42-0050",
        }
    },
    {
        12,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p12_present_n",
            .eepromSuid = "43-0050",
        }
    },
    {
        13,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p13_present_n",
            .eepromSuid = "44-0050",
        }
    },
    {
        14,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p14_present_n",
            .eepromSuid = "45-0050",
        }
    },
    {
        15,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p15_present_n",
            .eepromSuid = "46-0050",
        }
    },
    {
        16,
        {
            .presentPath = CPLD1_PATH,
            .presentAttr = "qsfpdd_p16_present_n",
            .eepromSuid = "47-0050",
        }
    },
    {
        17,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p17_present_n",
            .eepromSuid = "48-0050",
        }
    },
    {
        18,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p18_present_n",
            .eepromSuid = "49-0050",
        }
    },
    {
        19,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p19_present_n",
            .eepromSuid = "50-0050",
        }
    },
    {
        20,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p20_present_n",
            .eepromSuid = "51-0050",
        }
    },
    {
        21,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p21_present_n",
            .eepromSuid = "52-0050",
        }
    },
    {
        22,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p22_present_n",
            .eepromSuid = "53-0050",
        }
    },
    {
        23,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p23_present_n",
            .eepromSuid = "54-0050",
        }
    },
    {
        24,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p24_present_n",
            .eepromSuid = "55-0050",
        }
    },
    {
        25,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p25_present_n",
            .eepromSuid = "56-0050",
        }
    },
    {
        26,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p26_present_n",
            .eepromSuid = "57-0050",
        }
    },
    {
        27,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p27_present_n",
            .eepromSuid = "58-0050",
        }
    },
    {
        28,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p28_present_n",
            .eepromSuid = "59-0050",
        }
    },
    {
        29,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p29_present_n",
            .eepromSuid = "60-0050",
        }
    },
    {
        30,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p30_present_n",
            .eepromSuid = "61-0050",
        }
    },
    {
        31,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p31_present_n",
            .eepromSuid = "62-0050",
        }
    },
    {
        32,
        {
            .presentPath = CPLD2_PATH,
            .presentAttr = "qsfpdd_p32_present_n",
            .eepromSuid = "63-0050",
        }
    },
};
