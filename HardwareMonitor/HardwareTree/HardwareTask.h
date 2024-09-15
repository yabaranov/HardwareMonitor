#pragma once
#include <QObject>
#include <QTimer>
#include "HardwareDataExtractor.h"

class HardwareTask : public QObject 
{
   Q_OBJECT
   HardwareDataExtractor m_hardwareDataExtractor;

public slots:
   void process();
signals:
   void sensorDataUpdated(std::shared_ptr<Hardware> rootItem);
};

