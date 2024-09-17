#pragma once

#include "HardwareData/HardwareType.h"

#include <unordered_map>
#include <QString>

class SensorFormatter
{
public:
   static const std::pair<QString, int>& getFormat(HardwareType hardwareType);

private:
   static const std::unordered_map<HardwareType, std::pair<QString, int>> m_formats;
};