import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts

import NetEngine
import NetState
import ModelManager

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Hardware monitor client")

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#09102b"
    }

    menuBar: MenuBar {
        background: Rectangle {
            color: "#f3f3f4"  // Задаем цвет фона для MenuBar
        }
        font.pointSize: 14
        Menu {
            title: "Settings"
            MenuItem {
                text: "Server"
                font.pointSize: 12
                onTriggered: serverDialog.open()
            }
            MenuItem {
                text: "Port"
                font.pointSize: 12
                onTriggered: portDialog.open()
            }
        }
    }

        // Окно для ввода сервера
    Dialog {
        id: serverDialog
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {

            anchors.centerIn: parent
            spacing: 10
            Text {
                text: "Enter server"
                Layout.alignment: Qt.AlignHCenter
                font.pointSize: 14
            }
            InputField {
                id: serverInputField
                width: 200
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("localhost")
                placeholderText: qsTr("Server Address")
            }
        }
    }

    // Окно для ввода порта
    Dialog {
        id: portDialog
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 10
            Text {
                text: "Enter port"
                Layout.alignment: Qt.AlignHCenter
                font.pointSize: 14
            }
            InputField {
                id: portInputField
                width: 200
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("65000")
                placeholderText: qsTr("Port Number")
            }
        }
    }

    property int currentState : NetState.Disconnected

    Column {
        id: loginControl
        spacing: 5
        visible: currentState !== NetState.Connected
        anchors.centerIn: parent
        enabled: currentState === NetState.Disconnected
        InputField {
            id: loginField
            placeholderText: qsTr("Login")
            onVisibleChanged: {
                if (loginControl.visible) {
                    loginField.forceActiveFocus()
                }
            }
            Component.onCompleted: {
                if (loginControl.visible) {
                    loginField.forceActiveFocus()
                }
            }

        }
        InputField {
            id: passwordField
            echoMode: TextInput.Password
            placeholderText: qsTr("Password")         
        }
        Button {
            id: loginButton
            anchors.horizontalCenter: parent.horizontalCenter
            width: enterText.implicitWidth + 20
            height: 40
            background: Rectangle {
                radius: 5
                border {
                    width: 1
                    color: loginButton.pressed ? "#41cd52" : "#f3f3f4"
                }
                color:"#53586b"
                Text {
                    id: enterText
                    text : qsTr("Enter")
                    color: "#f3f3f4"
                    anchors.centerIn: parent
                    font.pointSize: 14
                }
            }

            onClicked: {
                currentState = NetState.Connecting
                NetEngine.login("http://" + serverInputField.text + ":" + portInputField.text, loginField.text, passwordField.text)
            }
        }
    }

    HardwareView {
        id: hardwareView
    }

    Text {
        id: connectingText
        visible: currentState === NetState.Connecting
        anchors.top: loginControl.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Connecting...")
        font.pointSize: 14
        color: "#f3f3f4"
    }

    Text {
        id: errorText
        visible: false
        anchors.top: loginControl.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 14
        color: "#f3f3f4"
        onVisibleChanged: {
            if (errorText.visible) {
                fadeOutTimer.restart()
            } else {
                fadeOutTimer.stop()
            }
        }

        Timer {
            id: fadeOutTimer
            onTriggered: {
                errorText.visible = false
            }
        }
    }

    Connections {
        target: NetEngine
        function onAuth(state) {
            if(state)
            {
                ModelManager.setHardwareStructure(NetEngine.getHardwareStructure());
                currentState = NetState.Connected;
                NetEngine.startSensorThread();
            }
            else
            {
                errorText.text = qsTr("This username with this password doesn't exists.")
                errorText.visible = true;
                currentState = NetState.Disconnected;
            }
        }

        function onNetworkError(errorString) {
            errorText.text = errorString;
            errorText.visible = true;
            currentState = NetState.Disconnected;
        }
    }

    Component.onCompleted: {
        NetEngine.sensorChanged.connect(ModelManager.onSensorChanged)
    }
}
