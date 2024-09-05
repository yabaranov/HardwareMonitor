#include "HardwareUtils.h"
#include <map>
std::shared_ptr<Hardware> ConvertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent)
{
   auto hardware = std::make_shared<Hardware>(msclr::interop::marshal_as<std::wstring>(hw->Name));
   hardware->parent = parent;

   for each (LibreHardwareMonitor::Hardware::IHardware ^ subHardware in hw->SubHardware)
   {
      hardware->children.push_back(ConvertHardware(subHardware, hardware));
   }

   std::map<std::wstring, std::vector<Sensor>> sensors;

   for each (LibreHardwareMonitor::Hardware::ISensor ^ sr in hw->Sensors)
   {
      Sensor sensor;
      sensor.name = msclr::interop::marshal_as<std::wstring>(sr->Name);
      sensor.value = std::to_wstring(sr->Value.HasValue ? sr->Value.Value : 0.0f);
      sensor.min = std::to_wstring(sr->Min.HasValue ? sr->Min.Value : 0.0f);
      sensor.max = std::to_wstring(sr->Max.HasValue ? sr->Max.Value : 0.0f);

      sensors[msclr::interop::marshal_as<std::wstring>(sr->SensorType.ToString())].push_back(sensor);
   }

   for (auto& sensorGroup : sensors)
   {
      hardware->children.push_back(std::make_shared<Hardware>(sensorGroup.first, hardware, Sensor(), std::vector<std::shared_ptr<Hardware>>()));

      for (auto& sensor : sensorGroup.second)
      {
         hardware->children.back()->children.push_back(std::make_shared<Hardware>(sensor.name, hardware->children.back(), sensor, std::vector<std::shared_ptr<Hardware>>()));
      }
   }

   return hardware;
}