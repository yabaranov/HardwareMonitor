#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

struct Sensor 
{
   std::wstring name;
   std::wstring value;
   std::wstring min;
   std::wstring max;
};

struct Hardware 
{
   std::wstring name;
   std::weak_ptr<Hardware> parent;
   Sensor sensor;
   std::vector<std::shared_ptr<Hardware>> children;
   int position() const
   {
      auto sharedParent = parent.lock();

      if (sharedParent)
      {
         auto parentChildren = sharedParent->children;
         auto it = std::find_if(parentChildren.begin(), parentChildren.end(), [this](const std::shared_ptr<Hardware>& ptr) {
            return ptr.get() == this;
            });

         return static_cast<int>(std::distance(parentChildren.begin(), it));
      }

      return 0;
   }

   Hardware(const std::wstring& name, std::shared_ptr<Hardware> parent = nullptr,
      const Sensor& sensor = {}, const std::vector<std::shared_ptr<Hardware>>& children = {}) :
      name(name), parent(parent), sensor(sensor), children(children) {}
};