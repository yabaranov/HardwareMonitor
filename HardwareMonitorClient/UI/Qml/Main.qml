import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Universal

import UI

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 320
    minimumHeight: 240

    title: "Hardware monitor client"

    Universal.theme: AppSettings.theme

    menuBar: AppMenuBar {
        id: appMenuBar
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: loginPage
    }

    LoginPage {
        id: loginPage
        header: ToolBar {
            CustomLabel {
                anchors.centerIn: parent
                text: qsTr("Login")
            }
        }
    }

    HardwarePage {
        id: hardwarePage
        visible: false
        header: ToolBar {
            ToolButton {
                id: buttonBack
                anchors.left: parent.left
                text: "<"
                onClicked: {
                    logger.info("Click back button")
                    stackView.pop();
                    netEngine.stopSensorThread();
                    sensorLogDatabase.close();
                    modelManager.destroyModels();
                    logger.info("Pop hardware page")
                }
            }

            CustomLabel {
                anchors.centerIn: parent
                text: qsTr("Hardwares")
            }
        }
    }

    Connections {
        target: netEngine

        function onAuth() {
            logger.info("Successful authentication")
            loginPage.connectingBar.visible = false;
            modelManager.createModels(netEngine.getHardwareListInfo());
            sensorLogDatabase.open("SensorLogs/" + AppSettings.serverAddress + "_" + AppSettings.portNumber + ".db");
            sensorLogDatabase.createTables(netEngine.getHardwareListInfo());
            netEngine.startSensorThread();
            stackView.push(hardwarePage);
            logger.info("Push hardware page")
        }
    }

    Component.onCompleted: {
        languageChooser.setLanguage(AppSettings.languageCode);
    }
}
