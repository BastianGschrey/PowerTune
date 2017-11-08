import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

    Rectangle {
        id: gauge
        width: 300
        height: width
        color: "transparent"
        CircularGauge {
            id: tachometer
            height: parent.height
            width: height
            value: Dashboard.revs / 1000
            maximumValue: 10
            anchors.centerIn: parent

            style: TachometerStyle {}
        }


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
