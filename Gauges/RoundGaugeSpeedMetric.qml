import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle {
    id: gauge
    width: 300
    height: width
    color: "transparent"


       CircularGauge {
            height: parent.height / 1.5
            width: height
            id: speedometer
            anchors.fill: parent
            value: Dashboard.speed
            anchors.verticalCenter: parent.verticalCenter
            maximumValue: 320

            style: DashboardGaugeStyle {}
        }

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


