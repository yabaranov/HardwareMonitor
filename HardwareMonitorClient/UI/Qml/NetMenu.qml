import QtQuick
import QtQuick.Controls

Menu {
    id: root
    title: qsTr("Net")

    MenuItem {
        text: qsTr("Server")
        onTriggered: serverDialog.open()

        Dialog {
            id: serverDialog
            modal: true
            standardButtons: Dialog.Ok | Dialog.Cancel

            Column {
                anchors.centerIn: parent
                spacing: 10

                CustomLabel {
                    text: qsTr("Enter server")
                }

                InputField {
                    id: serverInputField
                    text: AppSettings.serverAddress
                    onVisibleChanged: {
                        if (serverDialog.visible) {
                            serverInputField.forceActiveFocus()
                        }
                    }
                }
            }

            onAccepted: {
                AppSettings.serverAddress = serverInputField.text
                logger.info("New server address is %1", [AppSettings.serverAddress])
            }
        }
    }

    MenuItem {
        text: qsTr("Port")
        onTriggered: portDialog.open()

        Dialog {
            id: portDialog
            modal: true
            standardButtons: Dialog.Ok | Dialog.Cancel

            Column {
                anchors.centerIn: parent
                spacing: 10

                CustomLabel {
                    text: qsTr("Enter port")
                }

                InputField {
                    id: portInputField
                    text: AppSettings.portNumber
                    onVisibleChanged: {
                        if (portDialog.visible) {
                            portInputField.forceActiveFocus()
                        }
                    }
                }
            }

            onAccepted: {
                AppSettings.portNumber = portInputField.text
                logger.info("New port number is %1", [AppSettings.portNumber])
            }
        }
    }
}
