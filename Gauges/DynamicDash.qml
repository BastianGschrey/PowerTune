import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0



Rectangle {
    width: parent.width
    height: parent.height
    color: "black"

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton

        onClicked: pieMenu.popup(mouseX, mouseY)
    }

    Item {
        id: dynamicDashSettings
        Settings {
            property alias gauge1: gauge1.source
            property alias gauge2: gauge2.source
            property alias gauge3: gauge3.source
            property alias gauge4: gauge4.source
            property alias gauge5: gauge5.source
            property alias gauge6: gauge6.source
            property alias gauge7: gauge7.source
            property alias gauge8: gauge8.source
            property alias gauge9: gauge9.source
            property alias gauge10: gauge10.source
            property alias gauge11: gauge11.source
            property alias gauge12: gauge12.source
            property alias gauge13: gauge13.source
            property alias gauge14: gauge14.source
            property alias gauge15: gauge15.source
            property alias gauge16: gauge16.source
            property alias gauge17: gauge17.source
            property alias gauge18: gauge18.source
            property alias gauge19: gauge19.source
            property alias gauge20: gauge20.source


        }
    }

    Loader { id: gauge1 }
    Loader { id: gauge2 }
    Loader { id: gauge3 }
    Loader { id: gauge4 }
    Loader { id: gauge5 }
    Loader { id: gauge6 }
    Loader { id: gauge7 }
    Loader { id: gauge8 }
    Loader { id: gauge9 }
    Loader { id: gauge10}
    Loader { id: gauge11}
    Loader { id: gauge12}
    Loader { id: gauge13}
    Loader { id: gauge14}
    Loader { id: gauge15}
    Loader { id: gauge16}
    Loader { id: gauge17}
    Loader { id: gauge18}
    Loader { id: gauge19}
    Loader { id: gauge20}




    PieMenu {
        id: pieMenu

        MenuItem {
            text: "Horizontal Bar Gauge"
            onTriggered: gauge1.setSource("qrc:/Gauges/HalfGaugeWaterDegC.qml");
        }

        MenuItem {
            text: "Vertical Bar Gauge"
            onTriggered: gauge2.setSource("qrc:/Gauges/BarGauge.qml", { "title" : "MAP", "type" : "Dashboard.MAP", "gaugetype" : Qt.Vertical });

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

