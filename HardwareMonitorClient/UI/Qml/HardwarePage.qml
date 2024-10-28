import QtQuick.Controls

Page {
    id: root

    SplitView {
        anchors.fill: parent

        HardwareView {
            id: hardwareView
            height: parent.height
            focus: true
            SplitView.preferredWidth: parent.width * 0.2
        }

        SensorTableRepeater {
            id: sensorTableRepeater
            height: parent.height
            SplitView.preferredWidth: parent.width * 0.8
            selectedSensorTableIndex: hardwareView.selectedHardwareIndex
        }
    }
}
