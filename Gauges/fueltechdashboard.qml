//Dashboard in style of a fueltech ecu Dashboard

import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "qrc:/Gauges/createsquaregauge.js" as CreateSquareGaugeScript


Item {
    id: fueltechDash
    anchors.fill: parent

    property var val1: false
    property var val2: false
    property var val3: false

    Connections{
        target: Dashboard
        onDashsetupChanged: {
            //Need to do this nicer but it works
            if (dashvalue.textAt(8) == "true") {val1 = true};
            if (dashvalue.textAt(8) == "false") {val1 = false};
            if (dashvalue.textAt(9) == "true") {val2 = true};
            if (dashvalue.textAt(9) == "false") {val2 = false};
            if (dashvalue.textAt(10) == "true") {val3 = true};
            if (dashvalue.textAt(10) == "false") {val3 = false};
            console.log("received");
           // CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
        }
    }
    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup
        visible:false
        Component.onCompleted: Connect.readdashsetup()
    }

    Squaregauge{}
}
/*
//Needto replace the combobox with a ListModel but this seems to work for now ( very shitty workarround)


//This slot is called every time a line from the UserDash.txt has been read
Connections{
target: Dashboard
onDashsetupChanged: {
    //Need to do this nicer but it works
    if (dashvalue.textAt(8) == "true") {val1 = true};
    if (dashvalue.textAt(8) == "false") {val1 = false};
    if (dashvalue.textAt(9) == "true") {val2 = true};
    if (dashvalue.textAt(9) == "false") {val2 = false};
    if (dashvalue.textAt(10) == "true") {val3 = true};
    if (dashvalue.textAt(10) == "false") {val3 = false};
 //   CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
}
}

//Call Connect.cpp and read the UserDash.txt file ==> Works
Item {
Component.onCompleted: Connect.readdashsetup()
}

         Gauge {
             id: revgauge
             width: 800
             height: 200

             tickmarkStepSize: 0
             minorTickmarkCount: 0
             tickmarkAlignment: Qt.AlignBottom
             orientation: Qt.Horizontal

             value: Dashboard.rpm
             minimumValue: 0
             maximumValue: 9000

             style: GaugeStyle {

                 valueBar: Rectangle {

                     width: 200
                     color: Qt.rgba(revgauge.value / revgauge.maximumValue, 0, 1 - revgauge.value / revgauge.maximumValue, 1)
                    }

                 }
             }


             Image {
                 height: 200
                 width: 800
                  source: "/graphics/vertrevcanvas.png"
             }


             Text {
                 x: 0
                 y: 43
                 font.pixelSize: 70
                 font.bold: true
                 color: "white"
                 text: Dashboard.rpm
                 horizontalAlignment: Text.AlignLeft
                 font.letterSpacing: 3
                 font.wordSpacing: 0
             }


}

*/





