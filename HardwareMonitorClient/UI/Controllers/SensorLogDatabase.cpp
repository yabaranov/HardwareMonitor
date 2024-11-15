#include "SensorLogDatabase.h"
#include "NetEngine.h"

#include <ranges>
#include <QDateTime>

bool SensorLogDatabase::open(const QString& dbPath)
{
    return m_database.open(dbPath.toStdString());
}

void SensorLogDatabase::close()
{
    m_database.close();
}

void SensorLogDatabase::createTables(const GrpcHardwareMonitor::HardwareListInfo& hardwareListInfo)
{
    for (const auto& hardwareInfo : hardwareListInfo.hardwareInfos())
    {
        QString tableName = hardwareInfo.name();
        m_hardwaredNames.append(tableName);

        QList<QString> sensorNames;
        for (const auto& sensorInfo : hardwareInfo.sensorInfos())
            sensorNames.append(sensorInfo.name());

        m_sensorsNames.append(sensorNames);
    }

    createTables();
}

void SensorLogDatabase::onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList)
{
    auto currentTime = QDateTime::currentDateTime().toString(Qt::ISODate);

    for (auto&& [hardwareIndex, hardware]: std::views::enumerate(hardwareList.hardwares()))
    {
        QString tableName = m_hardwaredNames[hardwareIndex];
        const auto& sensorNames = m_sensorsNames[hardwareIndex];

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
        m_database.execute(insertQuery.toStdString());
    }
}

void SensorLogDatabase::connectToQObject(QObject* qObject)
{
    if (qObject)
    {
        auto netEngine = dynamic_cast<NetEngine*>(qObject);
        if(netEngine)
            QObject::connect(netEngine, &NetEngine::sensorTablesChanged,
                         this, &SensorLogDatabase::onSensorTablesChanged);
    }
}

void SensorLogDatabase::disconnectFromQObject(QObject* qObject)
{
    if (qObject)
    {
        auto netEngine = dynamic_cast<NetEngine*>(qObject);
        if(netEngine)
            QObject::disconnect(netEngine, &NetEngine::sensorTablesChanged,
                            this, &SensorLogDatabase::onSensorTablesChanged);
    }
}

void SensorLogDatabase::createTables()
{
    for (const auto& tableName : m_hardwaredNames)
    {
        QString createTableQuery = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                           "timestamp DATETIME, "
                                           "sensor_name TEXT, "
                                           "value REAL, "
                                           "UNIQUE(timestamp, sensor_name))").arg(tableName);

        m_database.execute(createTableQuery.toStdString());
    }
}
