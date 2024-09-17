#pragma once

#include "HardwareType.h"

#include <unordered_map>
#include <QString>

class IconRegistry
{
public:
   static const QString& getIconPath(HardwareType hardwareType);

private:
   static const std::unordered_map<HardwareType, QString> m_iconPaths;
};