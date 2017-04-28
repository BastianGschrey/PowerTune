import QtQuick 2.4
import QtGraphicalEffects 1.0



Rectangle {
    width: parent.width
    height: parent.height
    color: "black"


    Column {
        spacing: 2
        anchors.left: parent.left
        Text {
            color: "yellow"
            text: "PIM kgcm2 " + Dashboard.Intakepress
        }
        Text {
            color: "yellow"
            text: "PIM V " + Dashboard.PressureV
        }
        Text {
            color: "yellow"
            text: "Thro V " + Dashboard.ThrottleV

        }
        Text {
            color: "yellow"
            text: "Pri Inj "+ Dashboard.Primaryinp

        }
        Text {
            color: "yellow"
            text: "Fuelc " + Dashboard.Fuelc

        }
        Text {
            color: "yellow"
            text: "Lead Ign " + Dashboard.Leadingign

        }
        Text {
            color: "yellow"
            text: "Trailingign " + Dashboard.Trailingign

        }
        Text {
            color: "yellow"
            text: "Fueltemp " + Dashboard.Fueltemp

        }
        Text {
            color: "yellow"
            text: "Moilp " + Dashboard.Moilp

        }
        Text {
            color: "yellow"
            text: "Boosttp " + Dashboard.Boosttp

        }
        Text {
            color: "yellow"
            text: "Boostwg " +Dashboard.Boostwg

        }
        Text {
            color: "yellow"
            text:"Watertemp " + Dashboard.Watertemp

        }

        Text {
            color: "yellow"
            text: "Intaketemp " + Dashboard.Intaketemp

        }

        Text {
            color: "yellow"
            text: "Knock " + Dashboard.Knock

        }

        Text {
            color: "yellow"
            text: "Batt V " + Dashboard.BatteryV

        }
        Text {
            color: "yellow"
            text: "Iscvduty " + Dashboard.Iscvduty

        }

        Text {
            color: "yellow"
            text: "O2volt " + Dashboard.O2volt

        }

        Text {
            color: "yellow"
            text: "na1 " + Dashboard.na1

        }

        Text {
            color: "yellow"
            text: "Secinjpulse " + Dashboard.Secinjpulse

        }
        Text {
            color: "yellow"
            text: "na2 " + Dashboard.na2

        }
}

//Sensor Info

    Column {
        spacing: 2
        anchors.centerIn: parent
        Text {
            color: "yellow"
            text: "Boost " + Dashboard.pim
             }
        Text {
            color: "yellow"
            text: "VTA1 V " + Dashboard.vta1
        }
        Text {
            color: "yellow"
            text: "VTA2 V " + Dashboard.vta2

        }
        Text {
            color: "yellow"
            text: "Oil pump V "+ Dashboard.vmop

        }
        Text {
            color: "yellow"
            text: "Water Temp. " + Dashboard.wtrt

        }
        Text {
            color: "yellow"
            text: "Air Temp. " + Dashboard.airt

        }
        Text {
            color: "yellow"
            text: "Fuel Temp. " + Dashboard.fuelt

        }
        Text {
            color: "yellow"
            text: "O2S " + Dashboard.O2S

        }
}
        // Sensor Bit Flags
        Column {
            spacing: 2
            anchors.right: parent.right

        Text {
            color: "yellow"
            text: "STR " + Dashboard.Flag1

        }
        Text {
            color: "yellow"
            text: "A/C " + Dashboard.Flag2

        }
        Text {
            color: "yellow"
            text: "PWS " + Dashboard.Flag3

        }
        Text {
            color: "yellow"
            text: "NTR " + Dashboard.Flag4

        }

        Text {
            color: "yellow"
            text: "CLT " + Dashboard.Flag5

        }

        Text {
            color: "yellow"
            text: "STP " + Dashboard.Flag6

        }

        Text {
            color: "yellow"
            text: "CAT " + Dashboard.Flag7

        }

        Text {
            color: "yellow"
            text: "ELD " + Dashboard.Flag8

        }

        Text {
            color: "yellow"
            text: "HWL " + Dashboard.Flag9

        }

        Text {
            color: "yellow"
            text: "FPD " + Dashboard.Flag10

        }

        Text {
            color: "yellow"
            text: "FPR " + Dashboard.Flag11

        }

        Text {
            color: "yellow"
            text: "APR " + Dashboard.Flag12

        }

        Text {
            color: "yellow"
            text: "PAC " + Dashboard.Flag13

        }

        Text {
            color: "yellow"
            text: "CCN " + Dashboard.Flag14

        }

        Text {
            color: "yellow"
            text: "TCN " + Dashboard.Flag15

        }

        Text {
            color: "yellow"
            text: "PRC " + Dashboard.Flag16

        }

}
}


