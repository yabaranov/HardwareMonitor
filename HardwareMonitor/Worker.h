#pragma once
#include <QObject>
#include <QTimer>
#include "HardwareMonitorLib.h"

class Worker : public QObject {
   Q_OBJECT

public slots:
   void process();
signals:
   void sensorDataUpdated(std::shared_ptr<Hardware> rootItem);
};

