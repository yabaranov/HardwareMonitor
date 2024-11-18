#include "SensorDatabase.h"
#include "Logger/Logger.h"
#include "SensorLogTask.h"

SensorDatabase::~SensorDatabase()
{
    stopSensorLogThread();
}

void SensorDatabase::open(const QString& dbPath, GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo)
{
    m_database = std::make_unique<Database>(dbPath.toStdString());

    createTables(hardwareListInfo);

    startSensorLogThread(hardwareListInfo);
}

void SensorDatabase::createTables(GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo)
{
    for (const auto& hardwareInfo : hardwareListInfo->hardwareInfos())
    {
        QString createTableQuery = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                           "timestamp DATETIME, "
                                           "sensor_name TEXT, "
                                           "value REAL, "
                                           "UNIQUE(timestamp, sensor_name))").arg(hardwareInfo.name());

        m_database->execute(createTableQuery.toStdString());
    }
}

void SensorDatabase::startSensorLogThread(GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo)
{
    auto sensorLogTask = new SensorLogTask(m_database.get(), hardwareListInfo);

    m_sensorLogThread = std::make_unique<QThread>();

    sensorLogTask->moveToThread(m_sensorLogThread.get());

    connect(this, &SensorDatabase::sensorTablesChanged, sensorLogTask,
            &SensorLogTask::onSensorTablesChanged);

    connect(m_sensorLogThread.get(), &QThread::finished, sensorLogTask, &QObject::deleteLater);

    m_sensorLogThread->start();
    Logger::instance().info("Start sensor log thread");
}

void SensorDatabase::stopSensorLogThread()
{
    if (m_sensorLogThread && m_sensorLogThread->isRunning())
    {
        m_sensorLogThread->quit();
        m_sensorLogThread->wait();
    }

    Logger::instance().info("Stop sensor log thread");
}
