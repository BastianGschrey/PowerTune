//Dashboard in style of a fueltech ecu Dashboard

import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "../Gauges"
import "qrc:/Gauges/createsquaregauge.js" as CreateSquareGaugeScript


Item {
    id: fueltechDash
    anchors.fill: parent

    property var val1: false
    property var val2: false
    property var val3: false
    property double val4 : 20000
    property int val5 : -20000


      Image
      {
        id:groove1
        source:"qrc:/graphics/fueltechempty.png"
        anchors.top:parent.top
        anchors.left:parent.left
        smooth: true

        Item{
              id: displayWindow1
              height: parent.height
              width: (800*(Dashboard.rpm)/Dashboard.maxRPM)
              clip: true

                anchors.bottom: parent.bottom
                anchors.left: parent.left

              Image
              {
                id:speedarcfill
                anchors.top:parent.top
                anchors.left:parent.left
                source:"qrc:/graphics/fueltechfill.png"
                smooth: true
                z: 1
              }
            }

      PathInterpolator {
        id: motionPath
        property int value

           path: Path {
           startX: 0; startY: 189
           PathLine { x: 800; y: 480 }
         }
        progress: Dashboard.rpm / Dashboard.maxRPM
      }
}
//
        ShiftLights{}


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
            if (dashvalue.textAt(14) != "") {val4 = dashvalue.textAt(14),console.log("Hello " + dashvalue.textAt(14));}else {val4 = 20000;}
            if (dashvalue.textAt(15) != "") {val5 = dashvalue.textAt(15),console.log("Hello2 " + dashvalue.textAt(15));}else {val5 = -20000;}

            CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13),val4,val5);

            //call script without setting MaxValue
            //CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
        }
    }
    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup
        visible:false
        Component.onCompleted: Connect.readdashsetup()
    }

    Rectangle{
    anchors.fill: parent
    z:100 //This makes the Rectangle appear in front of the bar gauges
    color: "transparent"
    WarningLoader{}
    }

}






