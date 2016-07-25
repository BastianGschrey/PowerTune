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
                       //this is just to animate the needles via keyboard button and can be deleted once C++ interface is working
                       focus: true
                       Keys.onPressed: {
                                if (event.key == Qt.Key_0 && !event.isAutoRepeat) {
                                    speedoNeedle.value = 100 // percentage (gauge has a radius of 100 = 300 deg)
                                    revNeedle.value = 100
                                }
                                //once C++ works
                                //speedo.Needle.value = speed from C ++ /3  //Speedgauge 0-300 = 300 degrees
                                //revNeedle.value = Rev from C++ /100      //Rev gauge has 0-10.000 RPM = 300 degrees
                       }
                       Keys.onReleased: {
                               if (event.key == Qt.Key_0 && !event.isAutoRepeat) {
                                   speedoNeedle.value = 0
                                   revNeedle.value = 0
                               }}}


               //revolutions can be replaced with Speed value from C++ no formula needed
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

               }


               //revolutions can be replaced with Rev value from C++ no formula needed
              RevGaugeInnerRing   {
                id: revinnerring
                revolutions: (Math.round(revNeedle.revcurrentValue, 0) + 360) * 33.333333333
              }


 }
}

