#include "HardwarePageModel.h"
#include "Logger/Logger.h"

#include <ranges>

void HardwarePageModel::initialize(GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo)
{
    m_hardwareModel = std::make_unique<HardwareListModel>(hardwareListInfo->hardwareInfos());

    for(auto& hardware: hardwareListInfo->hardwareInfos())
        m_sensorTables.push_back(std::make_unique<SensorTableModel>(hardware.sensorInfos()));
    Logger::instance().info("Create models");
}

HardwarePageModel::~HardwarePageModel()
{
    Logger::instance().info("Destroy models");
}

HardwareListModel* HardwarePageModel::getHardwareList()
{
    return m_hardwareModel.get();
}

SensorTableModel* HardwarePageModel::getSensorTable(int index)
{
    return m_sensorTables[index].get();
}

void HardwarePageModel::onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList)
{
    for(auto&& [i, hardware]: std::views::enumerate(hardwareList.hardwares()))
        m_sensorTables[i]->changeSensorTable(hardware.sensors());
}

void HardwarePageModel::resetMinAndMax()
{
    for(auto& sensorTable: m_sensorTables)
        sensorTable->resetMinAndMax();
}
