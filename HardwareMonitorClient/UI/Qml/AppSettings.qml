pragma Singleton
import QtCore
import QtQuick.Controls.Universal

Settings {
    property int theme: Universal.System
    property string serverAddress: "localhost"
    property string portNumber: "65000"
    property string languageCode: "en"

    property bool logSensors: false
    signal logSensorsModified()
    function setLogSensors(value) {
        if (logSensors !== value) {
            logSensors = value;
            logSensorsModified();
        }
    }

    property list<bool> columnVisibility: [true, true, true]
    signal columnVisibilityModified()
    function setColumnVisibility(index, value) {
        if (columnVisibility[index] !== value) {
            columnVisibility[index] = value;
            columnVisibilityModified();
        }
    }

    signal resetMinAndMax()

}
