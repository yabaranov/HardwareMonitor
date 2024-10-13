#include "ModelManager.h"

ModelManager::ModelManager(QObject* parent) : QObject(parent)
{
}

void ModelManager::setHardwareStructure(const GrpcHardwareMonitor::HardwareStructure& hardwareStructure)
{
    m_hardwareStructure = hardwareStructure;
    m_hardwareModel.setHardwareStructure(hardwareStructure);

    for(auto& hardware: m_hardwareStructure.hardwares())
    {
        m_sensorTables.append(std::make_shared<SensorModel>());
        m_sensorTables.back()->setSensors(hardware.sensors());
    }
}

HardwareModel* ModelManager::getHardwareModel()
{
    return &m_hardwareModel;
}

SensorModel* ModelManager::getSensorTable(int i)
{
    return m_sensorTables[i].get();
}

void ModelManager::onSensorChanged(const GrpcHardwareMonitor::SensorInfo& sensorInfo)
{
    auto& hardwares = m_hardwareStructure.hardwares();
    qsizetype i = 0;
    for(; i < m_hardwareStructure.hardwares().size(); i++)
    {
        if(hardwares[i].name() == sensorInfo.hardwareName())
            break;
    }

    m_sensorTables[i]->changeSensorValue(sensorInfo);

}
