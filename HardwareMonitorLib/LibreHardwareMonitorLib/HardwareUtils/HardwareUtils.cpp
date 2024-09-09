#include "HardwareUtils.h"
#include <map>

std::shared_ptr<Hardware> convertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent)
{
   auto hardware = std::make_shared<Hardware>(msclr::interop::marshal_as<std::wstring>(hw->Name));
   hardware->parent = parent;

   for each (LibreHardwareMonitor::Hardware::IHardware ^ subHardware in hw->SubHardware)
   {
      hardware->children.push_back(convertHardware(subHardware, hardware));
   }

   populateSensors(hw, hardware);

   return hardware;
}

void populateSensors(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent)
{
   std::map<std::wstring, std::vector<Hardware>> hardwareMap;

   for each (LibreHardwareMonitor::Hardware::ISensor ^ sr in hw->Sensors)
   {
      auto hardware = convertSensor(sr);

      hardwareMap[msclr::interop::marshal_as<std::wstring>(sr->SensorType.ToString())].push_back(hardware);
   }

   for (auto& hardwareList : hardwareMap)
   {
      parent->children.push_back(std::make_shared<Hardware>(hardwareList.first, parent));

      for (auto& hardware : hardwareList.second)
      {
         auto lastChild = parent->children.back();

         lastChild->children.push_back(std::make_shared<Hardware>(hardware.name, lastChild, hardware.values));
      }
   }
}

Hardware convertSensor(LibreHardwareMonitor::Hardware::ISensor^ sr)
{
   Hardware hardware;

   hardware.name = msclr::interop::marshal_as<std::wstring>(sr->Name);
   hardware.values.push_back(sr->Value.HasValue ? std::optional<float>(sr->Value.Value) : std::nullopt);
   hardware.values.push_back(sr->Min.HasValue ? std::optional<float>(sr->Min.Value) : std::nullopt);
   hardware.values.push_back(sr->Max.HasValue ? std::optional<float>(sr->Max.Value) : std::nullopt);

   return hardware;
}
