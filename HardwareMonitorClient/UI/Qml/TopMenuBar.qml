import QtQuick
import QtQuick.Controls

MenuBar {
    Menu {
        title: "Net"

        MenuItem {
            text: "Server"
            onTriggered: serverDialog.open()
        }
        MenuItem {
            text: "Port"
            onTriggered: portDialog.open()
        }
    }
    Dialog {
        id: serverDialog
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        Column {
            anchors.centerIn: parent
            spacing: 10
            Label {
                text: "Enter server"
                font.pointSize: 14
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
    Dialog {
        id: portDialog
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        Column {
            anchors.centerIn: parent
            spacing: 10
            Label {
                text: "Enter port"
                font.pointSize: 14
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
    Menu {
        title: "Theme"

        MenuItem {
            text: "Dark"
            onTriggered: AppSettings.theme = Universal.Dark
        }
        MenuItem {
            text: "Light"
            onTriggered: AppSettings.theme = Universal.Light
        }
    }
}


