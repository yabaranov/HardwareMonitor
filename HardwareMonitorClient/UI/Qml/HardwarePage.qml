import QtQuick
import QtQuick.Controls

import HardwarePageModel
import SensorDatabase

Page {
    id: root
    property var hardwareListInfo

    SplitView {
        anchors.fill: parent

        HardwarePageModel {
            id: hardwarePageModel

            Component.onCompleted: {
                hardwarePageModel.initialize(hardwareListInfo);
                netClient.sensorTablesChanged.connect(hardwarePageModel.onSensorTablesChanged);
                hardwareView.hardwareList = hardwarePageModel.getHardwareList();
                sensorTableRepeater.hardwarePageModel = hardwarePageModel;
            }
        }

        SensorDatabase {
            id: sensorDatabase

            Component.onCompleted: {
                var dbPath = "SensorLogs/" + AppSettings.serverAddress + "_" + AppSettings.portNumber + ".db";
                sensorDatabase.open(dbPath, hardwareListInfo);
                if(AppSettings.logSensors)
                    netClient.sensorTablesChanged.connect(sensorDatabase.sensorTablesChanged);
            }
        }

        Connections {
            target: AppSettings

            function onLogSensorsModified() {
                if(AppSettings.logSensors)
                    netClient.sensorTablesChanged.connect(sensorDatabase.sensorTablesChanged);
                else
                    netClient.sensorTablesChanged.disconnect(sensorDatabase.sensorTablesChanged);
            }

            function onResetMinAndMax() {
                hardwarePageModel.resetMinAndMax();
            }
        }

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
