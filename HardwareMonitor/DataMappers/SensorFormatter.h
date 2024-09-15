#pragma once
#include <unordered_map>
#include <string>

class SensorFormatter
{
public:
   static std::wstring_view getFormat(std::wstring_view sensorName);

private:
   static const std::unordered_map<std::wstring, std::wstring> m_formats;
};