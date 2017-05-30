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
            text: "Add Bar Gauge"
            onTriggered: gaugeLoader.setSource("qrc:/Gauges/horizontalBarGauge.qml", { "title" : "MAP", "type" : "Dashboard.MAP" });

        }
        MenuItem {
            text: "Action 2"
            onTriggered: print("Action 2")
        }
        MenuItem {
            text: "Action 3"
            onTriggered: print("Action 3")
        }
    }


}

