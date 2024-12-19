import QtQuick
import QtQuick.Controls

Repeater {
    id: root
    property var hardwarePageModel
    model: hardwarePageModel.getHardwareList().rowCount()

    property int selectedSensorTableIndex

    delegate: Column {
        property int localIndex: index

        visible: localIndex === selectedSensorTableIndex

        HeaderOfSensorTableView
        {
            id: headerOfSensorTableView
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            model: [qsTr("Sensor"), qsTr("Value"), qsTr("Min"), qsTr("Max")]
            syncView: sensorTableView
        }

        SensorTableView
        {
            id: sensorTableView
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            model: hardwarePageModel.getSensorTable(localIndex)
        }
    }
}
