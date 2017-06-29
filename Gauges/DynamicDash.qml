import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0
import "CreateBarGaugeScript.js" as BarGaugeScript




Rectangle {
    id: mainrectangle
    width: parent.width
    height: parent.height
    color: "black"

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        //onClicked: pieMenu.popup(mouseX, mouseY)

    }


    PieMenu {
        id: pieMenu

        MenuItem {
            text: "Add gauge"

            //onTriggered: BarGaugeScript.createbarGaugeObjects();
        }

        MenuItem {
            text: "remove gauge"

        }



    }

    /*ListModel {
        id: listModelSourceSelect
        ListElement {
            title: "RPM"
        }
        ListElement {
            title: "Speed"
        }
        ListElement {
            title: "MAP"
        }
        ListElement {
            title: "Watertemp"
        }
    }

    ListView {
        id: listViewSourceSelect
        model: listModelSourceSelect
    }*/
}
