import QtQuick 2.8
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
            text: "Boosttp %" + Dashboard.Boosttp

        }
        Text {
            color: "yellow"
            text: "Boostwg %" +Dashboard.Boostwg

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
            text: Dashboard.Flag1 +" "+ Dashboard.FlagString1

        }
        Text {
            color: "yellow"
            text: Dashboard.Flag2 +" "+ Dashboard.FlagString2

        }
        Text {
            color: "yellow"
            text: Dashboard.Flag3 +" "+ Dashboard.FlagString3

        }
        Text {
            color: "yellow"
            text: Dashboard.Flag4 +" "+ Dashboard.FlagString4

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag5 +" "+ Dashboard.FlagString5

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag6 +" "+ Dashboard.FlagString6

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag7 +" "+ Dashboard.FlagString7

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag8 +" "+ Dashboard.FlagString8

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag9 +" "+ Dashboard.FlagString9

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag10 +" "+ Dashboard.FlagString10

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag11 +" "+ Dashboard.FlagString11

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag12 +" "+ Dashboard.FlagString12

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag13 +" "+ Dashboard.FlagString13

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag14 +" "+ Dashboard.FlagString14

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag15 +" "+ Dashboard.FlagString15

        }

        Text {
            color: "yellow"
            text: Dashboard.Flag16 +" "+ Dashboard.FlagString16

        }

}
}


