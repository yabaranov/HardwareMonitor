import QtQuick
import QtQuick.Controls

Page {
    id: root

    property alias connectingBar: connectingBar
    property alias error: error

    Column {
        id: loginControl       
        spacing: 10
        anchors.centerIn: parent

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

            CustomLabel {
                id: enterText
                text: qsTr("Enter")
                anchors.centerIn: parent
            }

            onClicked: {
                connectingBar.visible = true;
                netEngine.login("http://" + AppSettings.serverAddress + ":" + AppSettings.portNumber, loginField.text, passwordField.text);
            }
        }

        ProgressBar {
            id: connectingBar
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            indeterminate: true
        }

        Error {
            id: error
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter          
        }
    }
}
