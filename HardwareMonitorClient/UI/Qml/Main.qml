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

    Component {
        id: hardwarePageComponent

        HardwarePage {
            header: ToolBar {
                ToolButton {
                    id: buttonBack
                    anchors.left: parent.left
                    text: "<"
                    onClicked: {
                        logger.info("Click back button")
                        stackView.pop();
                        logger.info("Pop hardware page")
                        netClient.logout();                   
                    }
                }

                CustomLabel {
                    anchors.centerIn: parent
                    text: qsTr("Hardwares")
                }
            }

            Connections {
                target: netClient

                function onNetworkError(errorString) {
                    netClient.logout();
                    stackView.pop();
                }
            }
        }
    }

    Connections {
        target: netClient

        function onAuth(hardwareListInfo) {
            loginPage.connectingBar.visible = false;
            stackView.push(hardwarePageComponent, {"hardwareListInfo": hardwareListInfo});
            logger.info("Push hardware page")
        }
    }

    Component.onCompleted: {
        languageChooser.setLanguage(AppSettings.languageCode);
    }
}
