import QtQuick
import QtQuick.Controls

Item {
    id: root

    property alias text: errorText.text

    onVisibleChanged: {
        if (root.visible)
            errorDialog.open();
    }

    Dialog {
        id: errorDialog
        modal: true
        anchors.centerIn: parent

        Column {
            spacing: 10

            CustomLabel {
                id: errorText
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width / 2
                height: 40

                CustomLabel {
                    id: enterText
                    text: qsTr("Close")
                    anchors.centerIn: parent
                }

                onClicked: {
                    errorDialog.close();
                    root.visible = false;
                }
            }
        }
    }
}
