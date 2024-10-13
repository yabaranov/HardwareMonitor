#pragma once

#include <QAbstractTableModel>

#include "HardwareService.qpb.h"

class SensorModel : public QAbstractTableModel
{
public:
    explicit SensorModel(QObject* parent = nullptr);
    void setSensors(const GrpcHardwareMonitor::SensorRepeated& sensors);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void changeSensorValue(const GrpcHardwareMonitor::SensorInfo& sensorInfo);

private:

    enum SensorRoles
    {
        Name = Qt::UserRole,
        Value,
        IconSrc
    };

    GrpcHardwareMonitor::SensorRepeated m_sensors;
};
