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

struct PsuInfo
{
    /** @brief PSU PMBus bus and address suid, ex. 24-0059 */
    std::string pmbusSuid;
    /** @brief PSU eeprom bus and address suid, ex. 24-0051 */
    std::string eepromSuid;
    /** @brief Sysfs for PSU present driver path */
    std::string presentPath;
    /** @brief Sysfs for PSU present attributes */
    std::string presentAttr;
    /** @brief Sysfs for PSU power ok driver path */
    std::string pwrgdPath;
    /** @brief Sysfs for PSU power ok attributes */
    std::string pwrgdAttr;
};

using IdInfoMap_Psu = std::map<uint8_t, PsuInfo>;

extern IdInfoMap_Psu psu_info;

struct Oem_Info
{
    std::string sensorPath;
};

using IdInfoMap_oem = std::map<uint8_t, Oem_Info>;

extern IdInfoMap_oem oem_internalsensors;
