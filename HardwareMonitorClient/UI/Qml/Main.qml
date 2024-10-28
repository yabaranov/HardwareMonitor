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

    title: qsTr("Hardware monitor client")

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
                text: "Login"
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
                    stackView.pop();
                    netEngine.stopSensorThread();
                    modelManager.destroyModels();
                }
            }

            CustomLabel {
                anchors.centerIn: parent
                text: "Hardwares"
            }
        }     
    }

    Connections {
        target: netEngine

        function onAuth() {
            loginPage.connectingBar.visible = false;
            modelManager.createModels(netEngine.getHardwareStructure());
            netEngine.startSensorThread();
            stackView.push(hardwarePage);
        }
        function onNetworkError(errorString) {
            loginPage.connectingBar.visible = false;
            loginPage.error.text = errorString;
            loginPage.error.visible = true;
        }
    }

}
