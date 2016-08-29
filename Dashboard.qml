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
            value: innerring.speed * 0.26875 //86 % of 360 degree is the full needle range = 320 KPH
        }



        SpeedGaugeInnerRing   {
            id: innerring
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
            value: revinnerring.revolutions * 0.0086  //86 % of 360 degree is the full needle range = 10.000 RPM
            
        }
        RevGaugeInnerRing   {
            id: revinnerring
            revolutions: Dashboard.revs
        }
    }
}

