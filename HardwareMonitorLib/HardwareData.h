#pragma once

#include <vector>
#include <string>
#include <map>

struct Sensor 
{
   std::wstring name;
   float value;
   float min;
   float max;
};

struct Hardware 
{
   std::wstring name;
   std::wstring parent;
   std::map<std::wstring, std::vector<Sensor>> sensors;
   std::vector<Hardware> children;
};