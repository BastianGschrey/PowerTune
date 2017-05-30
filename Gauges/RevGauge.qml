import QtQuick 2.4
import QtGraphicalEffects 1.0

Rectangle {
    color: "transparent"
    height: (parent.height -10)
    width: (parent.height -10)
    x: (parent.width / 2) - (width / 2)
    y: (parent.height / 2) - (height / 2)
              RevGaugeNeedle {
                  id: revNeedle

                       anchors.verticalCenterOffset: 0
                       anchors.centerIn: parent

                       focus: true
                       Keys.onPressed: {
                                if (event.key == Qt.Key_Shift && !event.isAutoRepeat) {
                                    revNeedle.value = 100 // percentage (gauge has a span of 300 deg)

                                }
                       }
                       Keys.onReleased: {
                               if (event.key == Qt.Key_Shift && !event.isAutoRepeat) {
                                   revNeedle.value = 0

                               }}}



              RevGaugeInnerRing   {
                id: revinnerring
                revolutions: (Math.round(revNeedle.revcurrentValue, 0) + 360) * 10
              }


 }



