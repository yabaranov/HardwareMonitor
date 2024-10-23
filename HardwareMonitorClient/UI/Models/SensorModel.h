#pragma once

#include <QAbstractTableModel>

#include "HardwareService.qpb.h"

class SensorModel : public QAbstractTableModel
{
public:
    explicit SensorModel(const GrpcHardwareMonitor::SensorRepeated& sensors, QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void changeSensorValue(const GrpcHardwareMonitor::SensorInfo& sensorInfo);

private:
    const quint32 NUMBER_OF_COLUMNS = 2;

    enum SensorRoles
    {
        Name = Qt::UserRole,
        Value
    };

    GrpcHardwareMonitor::SensorRepeated m_sensors;
};
