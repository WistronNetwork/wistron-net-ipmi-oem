#pragma once

#include <stdint.h>
#include <string>
#include <map>

/*
 *  This struct is for external sensor.
 *  If there is no external sensor in the project, please keep struct empty.
 */
struct SensorParams
{
    /** @brief The sensor path quantity */
    uint8_t size;
    /** @brief dbus path */
    std::string path;
};

using IdInfoMap_External_Sensor = std::map<uint8_t, SensorParams>;

extern IdInfoMap_External_Sensor oem_externalsensors;

struct Oem_Info
{
    std::string sensorPath;
};

using IdInfoMap_oem = std::map<uint8_t, Oem_Info>;

extern IdInfoMap_oem oem_internalsensors;
