#include "SensorLogTask.h"
#include "DataBase/Database.h"

#include <QDateTime>
#include <ranges>
#include <QRegularExpression>

SensorLogTask::SensorLogTask(Database* database, GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo)
    : m_database(std::move(database))
{
    for (const auto& hardwareInfo : hardwareListInfo->hardwareInfos())
    {
        QString tableName = hardwareInfo.name();
        tableName.replace(QRegularExpression("[ \\(\\)]"), "_");
        m_hardwaredNames.append(tableName);

        QList<QString> sensorNames;
        for (const auto& sensorInfo : hardwareInfo.sensorInfos())
            sensorNames.append(sensorInfo.name());

        m_sensorTableNames.append(sensorNames);
    }
}

void SensorLogTask::onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList)
{
    auto currentTime = QDateTime::currentDateTime().toString(Qt::ISODate);

    for (auto&& [hardwareIndex, hardware]: std::views::enumerate(hardwareList.hardwares()))
    {
        QString tableName = m_hardwaredNames[hardwareIndex];
        const auto& sensorNames = m_sensorTableNames[hardwareIndex];

        QString insertQuery = QString("INSERT OR IGNORE INTO %1 (timestamp, sensor_name, value) VALUES ").arg(tableName);
        QStringList valueList;

        for (auto&& [sensorIndex, sensor]:  std::views::enumerate(hardware.sensors()))
        {
            QString entry = QString("('%1', '%2', %3)").arg(currentTime)
            .arg(sensorNames[sensorIndex])
                .arg(sensor.value());
            valueList.append(entry);
        }

        insertQuery += valueList.join(", ");
        m_database->execute(insertQuery.toStdString());
    }
}

