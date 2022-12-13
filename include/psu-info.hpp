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

#pragma once

/* Define present and power ok value which are read from CPLD */
#define PSU_PRESENT_ACTIVE NULL
#define PSU_PWROK_ACTIVE   NULL

/* Define PSU PMBus MFR length */
enum psu_mfr_length {
    PSU_MFR_REV_LENGTH = 0,
    PSU_MFR_ID_LENGTH = 0,
    PSU_MFR_MODEL_LENGTH = 0,
    PSU_MFR_SERIAL_LENGTH = 0,
};
