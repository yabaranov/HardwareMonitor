import QtQuick
import QtQuick.Controls

TableView {
    id: root

    columnWidthProvider: function (column) {

        var numberOfVisibleColumns = 1;

        for (var i = 0; i < AppSettings.columnVisibility.length; i++)
            if (AppSettings.columnVisibility[i] === true)
                numberOfVisibleColumns++;

        if(column === 0)
            return root.width / numberOfVisibleColumns;
        else
        {
            if(AppSettings.columnVisibility[column - 1]  === true)
                return root.width / numberOfVisibleColumns;
            else
                return 0;
        }
    }

    Connections {
        target: AppSettings

        function onColumnVisibilityModified() {
            root.forceLayout();
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
