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
    Gauge {
        id: gauge
        height: 200
        width: parent.width
        anchors.left: parent.left
        minorTickmarkCount: 0
        tickmarkStepSize : 9000
        orientation : Qt.Horizontal
        minimumValue: 0
        maximumValue: 9000
        value: Dashboard.rpm

         style: GaugeStyle {
             valueBar: Rectangle {
                width:  200
                color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
             }
             tickmarkLabel: Text {
                visible: false
             }
             tickmark: Item {
                visible: false
             }


        }
    }
        Image {
            id: coverimage
            height: 200
            width: fueltechDash.width
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
            CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
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



}






