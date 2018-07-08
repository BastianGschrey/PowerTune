import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "../Gauges"
import ".."
import "qrc:/Gauges/createsquaregaugeracedasgh.js" as CreateSquareGaugeScript1

Item {
    id: raceDash
    anchors.fill: parent

    property var val1: false
    property var val2: false
    property var val3: false

    Connections{
        target: Dashboard
        onDashsetup1Changed: {
            //Need to do this nicer but it works
            if (dashvalue.textAt(8) == "true") {val1 = true};
            if (dashvalue.textAt(8) == "false") {val1 = false};
            if (dashvalue.textAt(9) == "true") {val2 = true};
            if (dashvalue.textAt(9) == "false") {val2 = false};
            if (dashvalue.textAt(10) == "true") {val3 = true};
            if (dashvalue.textAt(10) == "false") {val3 = false};
            CreateSquareGaugeScript1.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
            //call script without setting MaxValue
            //CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
        }
    }
    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup1
        visible:false
        Component.onCompleted: Connect.readdashsetupApexi()
    }

  Rectangle {
        id:racedashwindow
        width: parent.width
        height:parent.height
        color:"black"

        RPMBarStyle1{}
        //RPMbar{}
        ShiftLights{}






    // Sensor Status ON/OFF
        Rectangle{
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height: parent.height /2.2
        width: parent.width /2.7
        color: "transparent"
        PFCSensors{sizeoftext : racedashwindow.width /54 }
        }

    }

  Rectangle{
  anchors.fill: parent
  color: "transparent"
  WarningLoader{}
  }

    }



