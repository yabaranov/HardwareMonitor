pragma Singleton
import QtCore
import QtQuick
import QtQuick.Controls.Universal

Settings {
    property int theme: Universal.Dark
    property string serverAddress: "localhost"
    property string portNumber: "65000"
}
