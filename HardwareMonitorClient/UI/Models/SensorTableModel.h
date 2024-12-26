#pragma once

#include <QAbstractTableModel>
#include "Types/Sensor.h"

#include "HardwareService.qpb.h"

class SensorTableModel : public QAbstractTableModel
{
public:
    explicit SensorTableModel(const GrpcHardwareMonitor::SensorInfoRepeated& sensorInfos);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void resetMinAndMax();

    void changeSensorTable(const GrpcHardwareMonitor::SensorRepeated& sensors);

private:
    const quint32 NUMBER_OF_COLUMNS = 4;

    enum SensorRoles
    {
        Name = Qt::UserRole,
        Value,
        Min,
        Max
    };

    QList<Sensor> m_sensors;
};
