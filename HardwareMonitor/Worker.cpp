#include "Worker.h"
#include <QThread>

void Worker::process()
{
   SystemMonitorWrapper work;
   auto result = work.GetHardwareData();
   emit sensorDataUpdated(result);
}

