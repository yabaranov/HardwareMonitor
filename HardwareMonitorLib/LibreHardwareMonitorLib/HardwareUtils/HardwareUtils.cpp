#include "HardwareUtils.h"

Hardware ConvertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw)
{
   Hardware hardware;
   hardware.name = msclr::interop::marshal_as<std::wstring>(hw->Name);
   hardware.parent = hw->Parent != nullptr ? msclr::interop::marshal_as<std::wstring>(hw->Parent->Name) : L"";

   for each (LibreHardwareMonitor::Hardware::ISensor ^ sr in hw->Sensors)
   {
      Sensor sensor;
      sensor.name = msclr::interop::marshal_as<std::wstring>(sr->Name);
      sensor.value = sr->Value.HasValue ? sr->Value.Value : 0.0f;
      sensor.min = sr->Min.HasValue ? sr->Min.Value : 0.0f;
      sensor.max = sr->Max.HasValue ? sr->Max.Value : 0.0f;

      hardware.sensors[msclr::interop::marshal_as<std::wstring>(sr->SensorType.ToString())].push_back(sensor);
   }

   for each (LibreHardwareMonitor::Hardware::IHardware ^ subHardware in hw->SubHardware)
   {
      hardware.children.push_back(ConvertHardware(subHardware));
   }

   return hardware;
}