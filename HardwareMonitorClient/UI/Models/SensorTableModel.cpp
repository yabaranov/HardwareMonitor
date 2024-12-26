#include "SensorTableModel.h"

#include "DataMappers/SensorPrecisionProvider.h"
#include "DataMappers/SensorUnitProvider.h"

#include <ranges>

SensorTableModel::SensorTableModel(const GrpcHardwareMonitor::SensorInfoRepeated& sensorInfos)
{
    for(auto& sensorInfo: sensorInfos)
        m_sensors.append(Sensor{.name = sensorInfo.name(),
                                .unit = SensorUnitProvider::getUnit(sensorInfo.type()),
                                .precision = SensorPrecisionProvider::getPrecision(sensorInfo.type())});
}

int SensorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_sensors.size());
}

int SensorTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return NUMBER_OF_COLUMNS;
}

QVariant SensorTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto& sensor = m_sensors.at(index.row());

    if (role == Qt::DisplayRole)   
        role = Qt::UserRole + index.column();

    auto sensorFormatter = [&sensor](auto&& hasValueFunc, auto&& valueFunc)
    {
        return hasValueFunc() ?
            sensor.getUnit().arg(valueFunc(), 0, 'f', sensor.getPrecision()) : "-";
    };

    switch (role)
    {
        case Name:
            return sensor.name;
        case Value:               
            return sensorFormatter([&sensor]() { return sensor.hasValue(); },
                                   [&sensor]() { return sensor.getValue(); });
        case Min:
            return sensorFormatter([&sensor]() { return sensor.hasMin(); },
                                   [&sensor]() { return sensor.getMin(); });
        case Max:
            return sensorFormatter([&sensor]() { return sensor.hasMax(); },
                                   [&sensor]() { return sensor.getMax(); });
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> SensorTableModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[Name] = "name";
    roles[Value] = "value";
    roles[Min] = "min";
    roles[Max] = "max";

    return roles;
}

void SensorTableModel::changeSensorTable(const GrpcHardwareMonitor::SensorRepeated& sensors)
{
    for(auto&& [i, sensor] : std::views::enumerate(sensors))
    {
        m_sensors[i].value = sensor.value();
        QModelIndex valueIndex = index(static_cast<int>(i), 1);
        emit dataChanged(valueIndex, valueIndex);

        if(sensor.value() < (m_sensors[i].hasMin() ? m_sensors[i].getMin() : std::numeric_limits<float>::max()))
        {
            m_sensors[i].min = sensor.value();
            QModelIndex minIndex = index(static_cast<int>(i), 2);
            emit dataChanged(minIndex, minIndex);
        }

        if(sensor.value() > (m_sensors[i].hasMax() ? m_sensors[i].getMax() : -std::numeric_limits<float>::max()))
        {
            m_sensors[i].max = sensor.value();
            QModelIndex maxIndex = index(static_cast<int>(i), 3);
            emit dataChanged(maxIndex, maxIndex);
        }
    }
}

void SensorTableModel::resetMinAndMax()
{
    for(auto&& [i, sensor] : std::views::enumerate(m_sensors))
    {
        sensor.min = std::nullopt;
        sensor.max = std::nullopt;

        QModelIndex minIndex = index(static_cast<int>(i), 2);
        emit dataChanged(minIndex, minIndex);
        QModelIndex maxIndex = index(static_cast<int>(i), 3);
        emit dataChanged(maxIndex, maxIndex);
    }
}
