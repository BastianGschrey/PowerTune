import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    width: parent.width
    height: parent.height

Rectangle {
    color: "transparent"
    id: speedo
    height: parent.height / 1.5
    width: height

    x: 20
    y: (parent.height / 5)
              SpeedGaugeNeedle {
                  id: speedoNeedle

                       anchors.verticalCenterOffset: 0
                       anchors.centerIn: parent

                       focus: true
                       Keys.onPressed: {
                                if (event.key == Qt.Key_0 && !event.isAutoRepeat) {
                                    speedoNeedle.value = 100 // percentage of 360 degrees (gauge has a radius of 300 deg)
                                    revNeedle.value = 100
                                }
                       }
                       Keys.onReleased: {
                               if (event.key == Qt.Key_0 && !event.isAutoRepeat) {
                                   speedoNeedle.value = 0
                                   revNeedle.value = 0
                               }}}



              SpeedGaugeInnerRing   {
                id: innerring
                speed: (Math.round(speedoNeedle.currentValue, 0) + 360)
              }


 }

Rectangle {
    color: "transparent"
    height: parent.height / 1.5
    width: height
    y: (parent.height / 5)
    x: ((parent.width - parent.height / 1.5 )-20)
    // anchors.right:parent.right
              RevGaugeNeedle {
                  id: revNeedle

                       anchors.verticalCenterOffset: 0
                       anchors.centerIn: parent

                       /*focus: true
                       Keys.onPressed: {
                                if (event.key == Qt.Key_Shift && !event.isAutoRepeat) {
                                    revNeedle.value = 100 // percentage (gauge has a span of 300 deg)

                                }
                       }
                       Keys.onReleased: {
                               if (event.key == Qt.Key_Shift && !event.isAutoRepeat) {
                                   revNeedle.value = 0

                               }}*/}



              RevGaugeInnerRing   {
                id: revinnerring
                revolutions: (Math.round(revNeedle.revcurrentValue, 0) + 360) * 35
              }


 }
}

