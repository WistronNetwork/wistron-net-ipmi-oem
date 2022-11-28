#pragma once

#include <stdint.h>
#include <string>
#include <map>

struct Oem_Info
{
    std::string sensorPath;
};

using IdInfoMap_oem = std::map<uint8_t, Oem_Info>;

extern IdInfoMap_oem oem_internalsensors;
