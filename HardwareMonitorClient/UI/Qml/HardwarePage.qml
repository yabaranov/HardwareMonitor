import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal

Page {
    id: root

    property int selectedHardwareIndex: 0

    SplitView {
        anchors.fill: parent

        ListView {
            id: hardwareList
            height: parent.height
            highlight: Rectangle { color: Universal.accent; radius: 5 }
            highlightResizeDuration: 0
            focus: true
            SplitView.preferredWidth: parent.width * 0.2
            model: root.visible && modelManager ? modelManager.getHardwareModel() : null

            delegate: Item {
                width: parent.width
                height: 50

                CustomLabel {
                    text: model.name
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        hardwareList.currentIndex = model.index;
                        root.selectedHardwareIndex = model.index
                    }
                }
            }
        }

        Repeater {
            id: repeater
            model: root.visible && modelManager ? modelManager.getHardwareModel().rowCount() : 0

            delegate: Column {
                property int localIndex: index
                height: parent.height
                SplitView.preferredWidth: parent.width * 0.8

                visible: localIndex === root.selectedHardwareIndex

                HorizontalHeaderView {
                    id: horizontalHeaderOfSensorTable
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    model: root.visible ? [qsTr("Sensor"), qsTr("Value"), qsTr("Min"), qsTr("Max")] : null
                    syncView: sensorTable
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

                TableView {
                    id: sensorTable
                    model: modelManager ? modelManager.getSensorTable(localIndex) : null
                    width: parent.width
                    height: parent.height
                    anchors.horizontalCenter: parent.horizontalCenter

                    columnWidthProvider: function (column) {

                        var numberOfVisibleColumns = 1;

                        for (var i = 0; i < AppSettings.columnVisibility.length; i++)
                            if (AppSettings.columnVisibility[i] === true)
                                numberOfVisibleColumns++;

                        if(column === 0)
                            return sensorTable.width / numberOfVisibleColumns;
                        else
                        {
                            if(AppSettings.columnVisibility[column - 1]  === true)
                                return sensorTable.width / numberOfVisibleColumns;
                            else
                                return 0;
                        }
                    }

                    Connections {
                        target: AppSettings

                        function onColumnVisibilityModified() {
                            sensorTable.forceLayout();
                        }
                    }

                    delegate: Item {
                        implicitWidth: 100
                        implicitHeight: 50

                        CustomLabel {
                            text: model.display
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AsNeeded
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
}
