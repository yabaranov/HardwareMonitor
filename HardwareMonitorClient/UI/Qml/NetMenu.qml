import QtQuick
import QtQuick.Controls

Menu {
    id: root
    title: "Net"

    MenuItem {
        text: "Server"
        onTriggered: serverDialog.open()

        Dialog {
            id: serverDialog
            modal: true
            standardButtons: Dialog.Ok | Dialog.Cancel

            Column {
                anchors.centerIn: parent
                spacing: 10

                CustomLabel {
                    text: "Enter server"
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
            }
        }
    }

    MenuItem {
        text: "Port"
        onTriggered: portDialog.open()

        Dialog {
            id: portDialog
            modal: true
            standardButtons: Dialog.Ok | Dialog.Cancel

            Column {
                anchors.centerIn: parent
                spacing: 10

                CustomLabel {
                    text: "Enter port"
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
            }
        }
    }
}
