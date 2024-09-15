#pragma once

#include <unordered_map>
#include <string>

class IconRegistry
{
public:
   static std::wstring_view getIconPath(std::wstring_view sensorName);

private:
   static const std::unordered_map<std::wstring, std::wstring> m_iconPaths;
};