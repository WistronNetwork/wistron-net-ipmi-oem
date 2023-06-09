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
extern IdInfoMap_oem oem_psusensors;

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

struct FanInfo
{
    /** @brief Sysfs for FAN present driver path */
    std::string presentPath;
    /** @brief Sysfs for FAN present attributes */
    std::string presentAttr;
    /** @brief Sysfs for FAN direction driver path */
    std::string directionPath;
    /** @brief Sysfs for FAN direction attributes */
    std::string directionAttr;
    /** @brief Sysfs for FAN pwm driver path */
    std::string pwmPath;
    /** @brief Sysfs for FAN pwm attributes */
    std::string pwmAttr;
};

using IdInfoMap_Fan = std::map<uint8_t, FanInfo>;

extern IdInfoMap_Fan fan_info;

struct FirmwareInfo
{
    /** @brief Sysfs for major version driver path */
    std::string majorPath;
    /** @brief Sysfs for major version attributes */
    std::string majorAttr;
    /** @brief Sysfs for major version driver path */
    std::string minorPath;
    /** @brief Sysfs for major version attributes */
    std::string minorAttr;
};

using IdInfoMap_Firmware = std::map<uint8_t, FirmwareInfo>;

extern IdInfoMap_Firmware firmware_info;

struct LEDInfo
{
    /** @brief Sysfs for LED status driver path */
    std::string ledStatusPath;
    /** @brief Sysfs for LED status attributes */
    std::string ledStatusrAttr;
    /** @brief Sysfs for LED control driver path */
    std::string ledControlPath;
    /** @brief Sysfs for LED control attributes */
    std::string ledControlAttr;
    /** @brief Sysfs for LED force mode driver path */
    std::string ledForceModePath;
    /** @brief Sysfs for LED force mode attributes */
    std::string ledForceModeAttr;
};

using IdInfoMap_LED = std::map<uint8_t, LEDInfo>;

extern IdInfoMap_LED led_info;

struct XcvrInfo
{
    /** @brief Sysfs for XCVR present driver path */
    std::string presentPath;
    /** @brief Sysfs for XCVR present attributes */
    std::string presentAttr;
    /** @brief XCVR eeprom bus and address suid, ex. 24-0051 */
    std::string eepromSuid;
};

using IdInfoMap_Xcvr = std::map<uint8_t, XcvrInfo>;

extern IdInfoMap_Xcvr xcvr_info;
