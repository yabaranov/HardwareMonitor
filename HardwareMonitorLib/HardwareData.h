#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <optional>

struct Hardware 
{
   std::wstring name;
   std::weak_ptr<Hardware> parent;
   std::wstring type;
   std::vector<std::optional<float>> values;
   std::vector<std::shared_ptr<Hardware>> children;

   int indexInParent() const
   {
      if (auto sharedParent = parent.lock())
      {
         auto parentChildren = sharedParent->children;
         auto it = std::find_if(parentChildren.begin(), parentChildren.end(), 
            [this](const std::shared_ptr<Hardware>& ptr) 
            {
               return ptr.get() == this;
            });
         if(it!= parentChildren.end())
            return static_cast<int>(std::distance(parentChildren.begin(), it));
      }

      return -1;
   }

   Hardware(const std::wstring& name = {}, const std::wstring& type = {}, std::shared_ptr<Hardware> parent = nullptr,
      const std::vector<std::optional<float>>& values = {},
      const std::vector<std::shared_ptr<Hardware>>& children = {}) :
      name(name), type(type), parent(parent), values(values), children(children) {}
};