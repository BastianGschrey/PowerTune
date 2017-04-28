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
/*
    Rectangle {
        width: parent.width /8
        height: width
        color: "blue"
        Column {
            spacing: 2
            anchors.centerIn: parent
            Text {
                color: "yellow"
                text: "Boost inhg / kgcm2"
                 }
            Text {
                color: "yellow"
                text: Dashboard.pim
            }
        }
    }
    */

    Rectangle {
        CircularGauge {
            id: speedometer
            height: parent.height
            width: height
            value: Dashboard.speed
            anchors.verticalCenter: parent.verticalCenter
            maximumValue: 320

            style: DashboardGaugeStyle {}
        }

        color: "transparent"
        id: speedo
        height: parent.height / 1.5
        width: height

        x: 20
        y: (parent.height / 5)
/*
        GaugeNeedle {
            id: speedoNeedle

            anchors.verticalCenterOffset: 0
            anchors.centerIn: parent
            value: innerring.speed / 3.8
        }
*/


        SpeedGaugeInnerRing   {
            id: innerring
            speed: Dashboard.speed
        }
    }


     Rectangle {
         CircularGauge {
             id: tachometer
             height: parent.height
             width: height
             value: Dashboard.revs / 1000
             maximumValue: 10
             anchors.centerIn: parent

             style: TachometerStyle {}
         }

         color: "transparent"
         //color: "blue"
        height: parent.height / 1.5
        width: height
        y: (parent.height / 5)
        x: ((parent.width - parent.height / 1.5 )-20)
        // anchors.right:parent.right
/*
        GaugeNeedle {
            id: revNeedle
            anchors.verticalCenterOffset: 0
            anchors.centerIn: parent
            value: 40//Dashboard.revs / 118.9 //* 0.00839 + 0.049

        }
*/
        RevGaugeInnerRing   {
            id: revinnerring
            revolutions: Dashboard.revs
        }
    }


}
