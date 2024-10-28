import QtQuick
import QtQuick.Controls

Repeater {
    id: root
    model: parent.visible && modelManager ? modelManager.getHardwareModel().rowCount() : 0

    property int selectedSensorTableIndex

    delegate: Column {
        property int localIndex: index

        visible: localIndex === selectedSensorTableIndex

        HeaderOfSensorTableView
        {
            id: headerOfSensorTableView
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            model: root.visible ? [qsTr("Sensor"), qsTr("Value"), qsTr("Min"), qsTr("Max")] : null
            syncView: sensorTableView
        }

        SensorTableView
        {
            id: sensorTableView
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            model: root.visible && modelManager ? modelManager.getSensorTable(localIndex) : null
        }
    }
}
