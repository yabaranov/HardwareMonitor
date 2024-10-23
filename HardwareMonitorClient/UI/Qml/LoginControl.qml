import QtQuick
import QtQuick.Controls

import NetState
import NetEngine
import ModelManager

Column {
    id: loginControl
    spacing: 5
    enabled: NetState.currentState === NetState.Disconnected
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
        Label {
            id: enterText
            text: qsTr("Enter")
            font.pointSize: 14
            anchors.centerIn: parent
        }
        onClicked: {
            NetState.currentState = NetState.Connecting
            NetEngine.login("http://" + AppSettings.serverAddress + ":" + AppSettings.portNumber, loginField.text, passwordField.text)
        }
    }
    ProgressBar {
        id: connecting
        visible: NetState.currentState === NetState.Connecting
        anchors.horizontalCenter: parent.horizontalCenter
        indeterminate: true
    }   
    ErrorText {
        id: errorText
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Connections {
        target: NetEngine
        function onAuth(state) {
            if(state)
            {
                ModelManager.createModels(NetEngine.getHardwareStructure());
                NetState.currentState = NetState.Connected;
                NetEngine.startSensorThread();
            }
            else
            {
                errorText.text = qsTr("This username with this password doesn't exists.")
                errorText.visible = true;
                NetState.currentState = NetState.Disconnected;
            }
        }
        function onNetworkError(errorString) {
            errorText.text = errorString;
            errorText.visible = true;
            NetState.currentState = NetState.Disconnected;
        }
    }

}
