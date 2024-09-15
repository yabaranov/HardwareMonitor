#include "UpdateVisitor.h"

void UpdateVisitor::VisitComputer(LibreHardwareMonitor::Hardware::IComputer^ computer)
{
   computer->Traverse(this);
}

void UpdateVisitor::VisitHardware(LibreHardwareMonitor::Hardware::IHardware^ hardware)
{
   hardware->Update();
   for each (LibreHardwareMonitor::Hardware::IHardware ^ subHardware in hardware->SubHardware)
   {
      subHardware->Accept(this);
   }
}

void UpdateVisitor::VisitSensor(LibreHardwareMonitor::Hardware::ISensor^ sensor)
{
}

void UpdateVisitor::VisitParameter(LibreHardwareMonitor::Hardware::IParameter^ parameter)
{
}