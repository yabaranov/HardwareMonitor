#include "SensorModel.h"

#include "DataMappers/SensorPrecisionProvider.h"
#include "DataMappers/SensorUnitProvider.h"

#include <ranges>

SensorModel::SensorModel(const GrpcHardwareMonitor::SensorRepeated& sensors, QObject* parent) : QAbstractTableModel(parent), m_sensors(sensors)
{
}

int SensorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_sensors.size());
}

int SensorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return NUMBER_OF_COLUMNS;
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

    auto sensorFormatter = [&sensor](auto&& hasValueFunc, auto&& valueFunc)
    {
        auto sensorType = sensor.type();
        auto precision = SensorPrecisionProvider::getPrecision(sensorType);
        return hasValueFunc() ?
            SensorUnitProvider::getUnit(sensorType).arg(valueFunc(), 0, 'f', precision) : "-";
    };

    switch (role)
    {
        case Name:
            return sensor.name();
        case Value:               
            return sensorFormatter([&sensor]() { return sensor.hasValue(); },
                                   [&sensor]() { return sensor.value(); });
        case Min:
            return sensorFormatter([&sensor]() { return sensor.hasMin(); },
                                   [&sensor]() { return sensor.min(); });
        case Max:
            return sensorFormatter([&sensor]() { return sensor.hasMax(); },
                                   [&sensor]() { return sensor.max(); });
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[Name] = "name";
    roles[Value] = "value";
    roles[Min] = "min";
    roles[Max] = "max";

    return roles;
}

void SensorModel::changeSensorValue(const GrpcHardwareMonitor::SensorInfo& sensorInfo)
{
    qsizetype i = 0;
    for(; i < m_sensors.size(); i++)
    {
        if(sensorInfo.sensorName() == m_sensors[i].name())
            break;
    }

    if(sensorInfo.hasValue())
    {
        m_sensors[i].setValue(sensorInfo.value());
        m_sensors[i].setMax(std::max(m_sensors[i].hasMax() ? m_sensors[i].max() : -std::numeric_limits<float>::max(), sensorInfo.value()));
        m_sensors[i].setMin(std::min(m_sensors[i].hasMin() ? m_sensors[i].min() : std::numeric_limits<float>::max(), sensorInfo.value()));
    }
    else
    {
        m_sensors[i].clearValue();
        m_sensors[i].clearMin();
        m_sensors[i].clearMax();
    }

    for(qsizetype j = 1; j < NUMBER_OF_COLUMNS; j++)
    {
        QModelIndex sensorIndex = index(static_cast<int>(i), j);
        emit dataChanged(sensorIndex, sensorIndex);
    }
}

void SensorModel::resetMinAndMax()
{
    for(auto&& [i, sensor] : std::views::enumerate(m_sensors))
    {
        sensor.clearMin();
        QModelIndex sensorIndex = index(static_cast<int>(i), 2);
        emit dataChanged(sensorIndex, sensorIndex);
    }

    for(auto&& [i, sensor] : std::views::enumerate(m_sensors))
    {
        sensor.clearMax();
        QModelIndex sensorIndex = index(static_cast<int>(i), 3);
        emit dataChanged(sensorIndex, sensorIndex);
    }
}

void swap(SensorModel& lhs, SensorModel& rhs) noexcept
{
    using std::swap;
    swap(lhs.m_sensors, rhs.m_sensors);
}
