#include "ModelManager.h"

ModelManager::ModelManager(QObject* parent) : QObject(parent)
{
}

void ModelManager::createModels(const GrpcHardwareMonitor::HardwareStructure& hardwareStructure)
{
    m_hardwareModel = std::make_unique<HardwareModel>(hardwareStructure.hardwares());

    for(auto& hardware: hardwareStructure.hardwares())
        m_sensorTables.push_back(std::make_unique<SensorModel>(hardware.sensors()));
}

void ModelManager::destroyModels()
{
    HardwareModel().swap(*m_hardwareModel);
    m_sensorTables.clear();
}

HardwareModel* ModelManager::getHardwareModel()
{
    return m_hardwareModel.get();
}

SensorModel* ModelManager::getSensorTable(int i)
{
    return m_sensorTables[i].get();
}

void ModelManager::onSensorChanged(const GrpcHardwareMonitor::SensorInfo& sensorInfo)
{
    auto& hardwares = m_hardwareModel->getHardwareList();
    qsizetype i = 0;
    for(; i < hardwares.size(); i++)
    {
        if(hardwares[i].name() == sensorInfo.hardwareName())
            break;
    }

    m_sensorTables[i]->changeSensorValue(sensorInfo);

}

void ModelManager::resetMinAndMax()
{
    for(auto& sensorTable: m_sensorTables)
        sensorTable->resetMinAndMax();
}
