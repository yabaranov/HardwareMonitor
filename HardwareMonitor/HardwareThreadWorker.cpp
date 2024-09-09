#include "HardwareThreadWorker.h"
#include <QThread>

void HardwareThreadWorker::process()
{
   HardwareMonitorLib hardwareMonitorLib;
   auto rootItem = hardwareMonitorLib.getHardwareData();
   emit sensorDataUpdated(rootItem);
}

