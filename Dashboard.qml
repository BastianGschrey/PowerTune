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



    Rectangle {
        width: parent.width /10
        height: parent.height /2
        color: "transparent"
        anchors.centerIn: parent

  /*      Timer {
            running: true
            repeat: true
            interval: 2000
            onTriggered: gauge.value = gauge.value == gauge.maximumValue ? 5 : gauge.maximumValue
        }
*/
        Gauge {
            id: gauge
            anchors.fill: parent
            anchors.margins: 10
            minimumValue: 0
            maximumValue: 140

            value: Dashboard.Watertemp
            Behavior on value {
                NumberAnimation {
                    duration: 10000
                }
            }

              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth: 16

                    color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                }
            }
      }
    }

    Rectangle {
        width: parent.width /8
        height: width
        color: "transparent"
        anchors.centerIn: parent

    }


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

        GaugeNeedle {
            id: speedoNeedle

                 anchors.verticalCenterOffset: 0
                 anchors.centerIn: parent
                 value: Dashboard.speed / 4.155844155844156

}


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
        height: parent.height / 1.5
        width: height
        y: (parent.height / 5)
        x: ((parent.width - parent.height / 1.5 )-20)
        // anchors.right:parent.right

        GaugeNeedle {
            id: revNeedle
            anchors.verticalCenterOffset: 0
            anchors.centerIn: parent
            value: Dashboard.revs * 0.0077

        }
        RevGaugeInnerRing   {
            id: revinnerring
            revolutions: Dashboard.revs
        }
    }


}
