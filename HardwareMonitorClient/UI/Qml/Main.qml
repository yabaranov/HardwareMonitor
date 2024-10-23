import QtQuick
import QtQuick.Controls

import NetEngine
import NetState
import ModelManager

import UI

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Hardware monitor client")

    Universal.theme: AppSettings.theme
    Universal.accent: Universal.Violet

    menuBar: TopMenuBar {
        id: topMenuBar
    }

    LoginControl {
        id: loginControl
        visible: NetState.currentState !== NetState.Connected
        anchors.centerIn: parent
    }

    HardwareView {
        id: hardwareView
    }

    Connections {
        target: NetEngine
        function onSensorChanged(sensorInfo){
            ModelManager.onSensorChanged(sensorInfo);
        }
    }
}
