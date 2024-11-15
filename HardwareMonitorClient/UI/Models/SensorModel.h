#pragma once

#include <QAbstractTableModel>
#include "Types/Sensor.h"

#include "HardwareService.qpb.h"

class SensorModel : public QAbstractTableModel
{
public:
    explicit SensorModel(const GrpcHardwareMonitor::SensorInfoRepeated& sensorInfos = {}, QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void resetMinAndMax();

    void changeSensorTable(const GrpcHardwareMonitor::SensorRepeated& sensors);

    void swap(SensorModel& rhs) noexcept;

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

void swap(SensorModel& lhs, SensorModel& rhs) noexcept;
