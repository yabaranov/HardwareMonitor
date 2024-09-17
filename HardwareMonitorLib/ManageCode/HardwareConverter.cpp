#include "HardwareConverter.h"
#include <map>

std::shared_ptr<Hardware> HardwareConverter::convertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent)
{
   auto hardware = std::make_shared<Hardware>(msclr::interop::marshal_as<std::wstring>(hw->Name), static_cast<HardwareType>(hw->HardwareType));
   hardware->parent = parent;

   for each (LibreHardwareMonitor::Hardware::IHardware ^ subHardware in hw->SubHardware)
   {
      hardware->children.push_back(convertHardware(subHardware, hardware));
   }

   mapSensorsToHardware(hw, hardware);

   return hardware;
}

void HardwareConverter::mapSensorsToHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent)
{
   std::map<std::pair<std::wstring, HardwareType>, std::vector<Hardware>> hardwareMap;

   for each (LibreHardwareMonitor::Hardware::ISensor ^ sr in hw->Sensors)
   {
      auto hardware = convertSensor(sr);
      auto nameAndType = std::make_pair<std::wstring, HardwareType>(msclr::interop::marshal_as<std::wstring>(sr->SensorType.ToString()),
         static_cast<HardwareType>(static_cast<int>(HardwareType::Voltage) + static_cast<int>(sr->SensorType)));
      hardwareMap[nameAndType].push_back(hardware);
   }

   for (auto& hardwareList : hardwareMap)
   {
      auto nameAndType = hardwareList.first;
      parent->children.push_back(std::make_shared<Hardware>(nameAndType.first, nameAndType.second, parent));

      for (auto& hardware : hardwareList.second)
      {
         auto lastChild = parent->children.back();

         lastChild->children.push_back(std::make_shared<Hardware>(hardware.name, hardware.type, lastChild, hardware.values));
      }
   }
}

Hardware HardwareConverter::convertSensor(LibreHardwareMonitor::Hardware::ISensor^ sr)
{
   Hardware hardware;

   hardware.name = msclr::interop::marshal_as<std::wstring>(sr->Name);
   hardware.type = HardwareType::Unknown;
   hardware.values.push_back(sr->Value.HasValue ? std::optional<float>(sr->Value.Value) : std::nullopt);
   hardware.values.push_back(sr->Min.HasValue ? std::optional<float>(sr->Min.Value) : std::nullopt);
   hardware.values.push_back(sr->Max.HasValue ? std::optional<float>(sr->Max.Value) : std::nullopt);

   return hardware;
}
