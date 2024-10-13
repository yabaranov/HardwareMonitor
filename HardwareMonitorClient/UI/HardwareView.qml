import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import ModelManager
import NetState

Rectangle {
    anchors.fill: parent
    color: "#09102b"
    visible: currentState === NetState.Connected

    property int selectedHardwareIndex: 0


    SplitView {
        anchors.fill: parent
        ListView {
            id: hardwareMenu
            height: parent.height
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
            SplitView.minimumWidth: 100
            SplitView.preferredWidth: 200
            SplitView.maximumWidth: parent.width * 0.2
            model: currentState === NetState.Connected ? ModelManager.getHardwareModel() : null
            delegate: Item {
                width: parent.width
                height: 50

                Text {
                    text: model.name
                    anchors.centerIn: parent
                    font.pointSize: 14
                    color: "#f3f3f4"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        selectedHardwareIndex = index;
                        hardwareMenu.currentIndex = index;
                    }
                }
            }
        }

        Column
        {
            height: parent.height
            SplitView.minimumWidth: 200
            SplitView.preferredWidth: parent.width * 0.8

            HorizontalHeaderView {
                id: horizontalHeader
                width: parent.width
                model: currentState === NetState.Connected ? [qsTr("Sensor"), qsTr("Value")] : null
                syncView: tableView
                delegate: Rectangle {
                    color: "#09102b"
                    implicitWidth: 200
                    implicitHeight: 50

                    Label {
                       anchors.fill: parent
                       text: modelData
                       color: "#f3f3f4"
                       font.pointSize: 14
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            TableView {
                id: tableView
                model: currentState === NetState.Connected ? ModelManager.getSensorTable(selectedHardwareIndex) : null
                width: parent.width
                height: parent.height
                delegate: Rectangle {
                    color: "#09102b"
                    implicitWidth: 100
                    implicitHeight: 50
                    Text {
                        text: display
                        anchors.centerIn: parent
                        font.pointSize: 14
                        color: "#f3f3f4"
                    }
                }
            }
        }
    }

}
