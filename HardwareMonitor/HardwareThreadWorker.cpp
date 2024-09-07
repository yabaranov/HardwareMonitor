#include "HardwareThreadWorker.h"
#include <QThread>

void HardwareThreadWorker::process()
{
   SystemMonitorWrapper systemMonitorWrapper;
   auto rootItem = systemMonitorWrapper.GetHardwareData();
   emit sensorDataUpdated(rootItem);
}

