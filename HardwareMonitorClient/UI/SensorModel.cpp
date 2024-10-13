#include "SensorModel.h"

SensorModel::SensorModel(QObject* parent)
{

}

void SensorModel:: setSensors(const GrpcHardwareMonitor::SensorRepeated& sensors)
{
    m_sensors = sensors;
}

int SensorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_sensors.size());
}

int SensorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant SensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto& sensor = m_sensors.at(index.row());

    if (role == Qt::DisplayRole)
    {
        role = Qt::UserRole + index.column();
    }

    switch (role)
    {
    case Name:
        return sensor.name();
    case Value:
        return sensor.hasValue() ? sensor.value(): 0;
    case IconSrc:
        return "-";
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[Name] = "name";
    roles[Value] = "value";
    roles[IconSrc] = "iconSrc";

    return roles;
}

void SensorModel::changeSensorValue(const GrpcHardwareMonitor::SensorInfo& sensorInfo)
{
    qsizetype i = 0;
    for(; i < m_sensors.size(); i++)
    {
        if(sensorInfo.sensorName()==m_sensors[i].name())
            break;
    }

    m_sensors[i].setValue(sensorInfo.value());

    QModelIndex sensorIndex = index(static_cast<int>(i), 1);
    emit dataChanged(sensorIndex, sensorIndex);

}
