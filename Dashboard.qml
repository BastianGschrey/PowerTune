import QtQuick 2.4
import QtGraphicalEffects 1.0

Rectangle {
    width: parent.width
    height: parent.height
    color: "black"

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


    Column {
        spacing: 2
        anchors.centerIn: parent
        Text {
            color: "white"
            text: "Kgcm2 " + Dashboard.Intakepress
        }
        Text {
            color: "white"
            text: "In V " + Dashboard.PressureV
        }
        Text {
            color: "white"
            text: "Thro V " + Dashboard.ThrottleV

        }
        Text {
            color: "white"
            text: "Pri Inj "+ Dashboard.Primaryinp

        }
        Text {
            color: "white"
            text: "Fuelc " + Dashboard.Fuelc

        }
        Text {
            color: "white"
            text: "Lead Ign " + Dashboard.Leadingign

        }
        Text {
            color: "white"
            text: "Trailingign " + Dashboard.Trailingign

        }
        Text {
            color: "white"
            text: "Fueltemp " + Dashboard.Fueltemp

        }
        Text {
            color: "white"
            text: "Moilp " + Dashboard.Moilp

        }
        Text {
            color: "white"
            text: "Boosttp " + Dashboard.Boosttp

        }
        Text {
            color: "white"
            text: "Boostwg " +Dashboard.Boostwg

        }
        Text {
            color: "white"
            text:"Watertemp " + Dashboard.Watertemp

        }

        Text {
            color: "white"
            text: "Intaketemp " + Dashboard.Intaketemp

        }

        Text {
            color: "white"
            text: "Knock " + Dashboard.Knock

        }

        Text {
            color: "white"
            text: "Batt V " + Dashboard.BatteryV

        }
        Text {
            color: "white"
            text: "Iscvduty " + Dashboard.Iscvduty

        }

        Text {
            color: "white"
            text: "O2volt " + Dashboard.O2volt

        }

        Text {
            color: "white"
            text: "na1 " + Dashboard.na1

        }

        Text {
            color: "white"
            text: "Secinjpulse " + Dashboard.Secinjpulse

        }
        Text {
            color: "white"
            text: "na2 " + Dashboard.na2

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

