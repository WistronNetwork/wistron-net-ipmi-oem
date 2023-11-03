/*
 * Copyright (c) 2023 Jarvis Chen
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

#define FANCPLD_PATH I2C_SYSFS_DEV_DIR(16-0027)"/hwmon"

IdInfoMap_Fan fan_info = {
    {
        1,
        {
            .presentPath = FANCPLD_PATH,
            .presentAttr = "fm_det_fan1_n",
            .directionPath = FANCPLD_PATH,
            .directionAttr = "fm_judgement_fan1",
            .pwmPath = FANCPLD_PATH,
            .pwmAttr = "pwm1",
        }
    },
    {
        2,
        {
            .presentPath = FANCPLD_PATH,
            .presentAttr = "fm_det_fan2_n",
            .directionPath = FANCPLD_PATH,
            .directionAttr = "fm_judgement_fan2",
            .pwmPath = FANCPLD_PATH,
            .pwmAttr = "pwm2",
        }
    },
    {
        3,
        {
            .presentPath = FANCPLD_PATH,
            .presentAttr = "fm_det_fan3_n",
            .directionPath = FANCPLD_PATH,
            .directionAttr = "fm_judgement_fan3",
            .pwmPath = FANCPLD_PATH,
            .pwmAttr = "pwm3",
        }
    },
    {
        4,
        {
            .presentPath = FANCPLD_PATH,
            .presentAttr = "fm_det_fan4_n",
            .directionPath = FANCPLD_PATH,
            .directionAttr = "fm_judgement_fan4",
            .pwmPath = FANCPLD_PATH,
            .pwmAttr = "pwm4",
        }
    },
};
