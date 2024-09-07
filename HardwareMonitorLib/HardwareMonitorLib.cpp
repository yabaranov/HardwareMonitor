#include "HardwareMonitorLib.h"
#include "LibreHardwareMonitorLib/ComputerWrapper.h"
#include "LibreHardwareMonitorLib/UpdateVisitor/UpdateVisitorWrapper.h"
#include "LibreHardwareMonitorLib/HardwareUtils/HardwareUtils.h"

SystemMonitorWrapper::SystemMonitorWrapper() : m_computer(std::make_unique<ComputerWrapper>()), m_updateVisitor(std::make_unique<UpdateVisitorWrapper>())
{
   m_updateVisitor->API = gcnew UpdateVisitor();

   m_computer->API = gcnew LibreHardwareMonitor::Hardware::Computer(); 
   m_computer->API->IsCpuEnabled = true;
   m_computer->API->IsGpuEnabled = true;
   m_computer->API->IsMemoryEnabled = true;
   m_computer->API->IsMotherboardEnabled = true;
   m_computer->API->IsControllerEnabled = true;
   m_computer->API->IsNetworkEnabled = true;
   m_computer->API->IsStorageEnabled = true;
   m_computer->API->Open();
}

SystemMonitorWrapper::~SystemMonitorWrapper() 
{
   m_computer->API->Close();
}
std::shared_ptr<Hardware> SystemMonitorWrapper::GetHardwareData() 
{
   m_computer->API->Accept(m_updateVisitor->API.get());
   auto hardwareRoot = std::make_shared<Hardware>(L"RootItem");

   for each (LibreHardwareMonitor::Hardware::IHardware ^ hw in m_computer->API->Hardware) 
   {
      hardwareRoot->children.push_back(ConvertHardware(hw, hardwareRoot));
   }

   return hardwareRoot;
}