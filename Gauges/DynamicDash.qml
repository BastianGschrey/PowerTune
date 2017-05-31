import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4



Rectangle {
    width: parent.width
    height: parent.height
    color: "black"

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton

        onClicked: pieMenu.popup(mouseX, mouseY)
    }


    Loader { id: gaugeLoader }


    PieMenu {
        id: pieMenu

        MenuItem {
            text: "Horizontal Bar Gauge"
            onTriggered: gaugeLoader.setSource("qrc:/Gauges/BarGauge.qml", { "title" : "MAP", "type" : "Dashboard.MAP", "gaugetype" : Qt.Horizontal });
        }

        MenuItem {
            text: "Vertical Bar Gauge"
            onTriggered: gaugeLoader.setSource("qrc:/Gauges/BarGauge.qml", { "title" : "MAP", "type" : "Dashboard.MAP", "gaugetype" : Qt.Vertical });

        }
        MenuItem {
            text: "Dial Gauge"
            onTriggered: print("Action 3")

        }       
        MenuItem {
            text: "Flag Gauge"
            onTriggered: print("Action 3")
        }
    }


}

