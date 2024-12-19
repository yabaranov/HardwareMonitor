import QtQuick
import QtQuick.Controls

HorizontalHeaderView {
    id: root

    resizableColumns: false

    delegate: Item {
        implicitWidth: 100
        implicitHeight: 50

        CustomLabel {
           anchors.fill: parent
           text: modelData
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
        }
    }
}
