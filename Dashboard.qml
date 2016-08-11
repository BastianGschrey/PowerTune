import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    width: parent.width
    height: parent.height
    //property qint16 value : 0

    Rectangle {
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
            value: innerring.speed

            // once c++ interface works
            //speedoNeedle.value =  packageADV[16] *0.26875 // max speedo 320 KMH = 86


            /*
                        this is just to animate the needles via keyboard button
                        and can be deleted once C++ interface is working

                       focus: true
                       Keys.onPressed: {
                                if (event.key == Qt.Key_0 && !event.isAutoRepeat) {

                                    speedoNeedle.value = 86 // 86 = 300 degrees 3.488 = 1 degree
                                    revNeedle.value = 86    // 86 = 300 degrees 3.488 = 1 degree
                                }

                       }
                       Keys.onReleased: {
                               if (event.key == Qt.Key_0 && !event.isAutoRepeat) {
                                   speedoNeedle.value = 0
                                   revNeedle.value = 0
                               }}
*/
        }



        SpeedGaugeInnerRing   {
            id: innerring
            // speed: (Math.round(speedoNeedle.currentValue, 0) + 360) * 1.066666666666667
            // speed: packageADV[16]
            speed: Dashboard.speed
        }


    }

    Rectangle {
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
            value: revinnerring.revolutions
            //RevNeedle.value = packageADV[0] * 0.03        // max rev 10000 RPM = 86
        }
        //revolutions can be replaced with Rev value from C++ no formula needed
        RevGaugeInnerRing   {
            id: revinnerring
            // revolutions:(Math.round(revNeedle.currentValue, 0) + 360) * 33.33333333333334
            // revolutions: packageADV[0]
            revolutions: Dashboard.revs
        }
    }
}

