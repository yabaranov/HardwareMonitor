import QtQuick
import QtQuick.Controls

import ModelManager
import NetState

Item {
    anchors.fill: parent
    visible: NetState.currentState === NetState.Connected

    property int selectedHardwareIndex: 0

    SplitView {
        anchors.fill: parent
        ListView {
            id: hardwareMenu
            height: parent.height
            highlight: Rectangle { color: Universal.accent; radius: 5 }
            focus: true
            SplitView.minimumWidth: 100
            SplitView.preferredWidth: 200
            SplitView.maximumWidth: parent.width * 0.2
            model: NetState.currentState === NetState.Connected ? ModelManager.getHardwareModel() : null
            delegate: Item {
                width: parent.width
                height: 50
                Label {
                    text: model.name
                    font.pointSize: 14
                    anchors.centerIn: parent
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
                model: NetState.currentState === NetState.Connected ? [qsTr("Sensor"), qsTr("Value")] : null
                syncView: tableView
                delegate: Item {
                    implicitWidth: 200
                    implicitHeight: 50

                    Label {
                       anchors.fill: parent
                       text: modelData
                       font.pointSize: 14
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            TableView {
                id: tableView
                model: NetState.currentState === NetState.Connected ? ModelManager.getSensorTable(selectedHardwareIndex) : null
                width: parent.width
                height: parent.height
                delegate: Item {
                    implicitWidth: 100
                    implicitHeight: 50
                    Label {
                        text: model.display
                        font.pointSize: 14
                        anchors.centerIn: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                    smooth: true
                }

                   ScrollBar.horizontal: ScrollBar {
                    policy: ScrollBar.AsNeeded
                    smooth: true
                }
            }
        }
    }

}
