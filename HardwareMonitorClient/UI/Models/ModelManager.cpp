#include "ModelManager.h"
#include "Logger/Logger.h"

#include <ranges>

ModelManager::ModelManager(QObject* parent) : QObject(parent)
{
}

void ModelManager::createModels(const GrpcHardwareMonitor::HardwareListInfo& hardwareListInfo)
{
    m_hardwareModel = std::make_unique<HardwareModel>(hardwareListInfo.hardwareInfos());

    for(auto& hardware: hardwareListInfo.hardwareInfos())
        m_sensorTables.push_back(std::make_unique<SensorModel>(hardware.sensorInfos()));
    Logger::instance().info("Create models");
}

void ModelManager::destroyModels()
{
    m_hardwareModel.reset();
    m_sensorTables.clear();
    Logger::instance().info("Destroy models");
}

HardwareModel* ModelManager::getHardwareModel()
{
    return m_hardwareModel.get();
}

SensorModel* ModelManager::getSensorTable(int index)
{
    return m_sensorTables[index].get();
}

void ModelManager::onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList)
{
   auto& hardwares = hardwareList.hardwares();

    for(auto&& [i, hardware]: std::views::enumerate(hardwareList.hardwares()))
        m_sensorTables[i]->changeSensorTable(hardware.sensors());
}

void ModelManager::resetMinAndMax()
{
    for(auto& sensorTable: m_sensorTables)
        sensorTable->resetMinAndMax();
}
