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
        standardButtons: Dialog.Ok
        anchors.centerIn: parent
        spacing: 10

        CustomLabel {
            id: errorText
        }

        onClosed: {
            root.visible = false;
        }
    }
}
