import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0
import "CreateBarGaugeScript.js" as BarGaugeScript




Rectangle {
    id: mainrectangle
    width: parent.width
    height: parent.height
    color: "black"

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        //onClicked: pieMenu.popup(mouseX, mouseY)

    }


    PieMenu {
        id: pieMenu

        MenuItem {
            text: "Add gauge"

            //onTriggered: BarGaugeScript.createbarGaugeObjects();
        }

        MenuItem {
            text: "remove gauge"

        }



    }
/*
    ListModel {
        id: sourceList
        ListElement {title:"m_revs" }
        ListElement {title:"m_Intakepress" }
        ListElement {title:"m_PressureV" }
        ListElement {title:"m_ThrottleV" }
        ListElement {title:"m_Primaryinp" }
        ListElement {title:"m_Fuelc" }
        ListElement {title:"m_Leadingign" }
        ListElement {title:"m_Trailingign" }
        ListElement {title:"m_Fueltemp" }
        ListElement {title:"m_Moilp" }
        ListElement {title:"m_Boosttp" }
        ListElement {title:"m_Boostwg" }
        ListElement {title:"m_Watertemp" }
        ListElement {title:"m_Intaketemp" }
        ListElement {title:"m_Knock" }
        ListElement {title:"m_BatteryV" }
        ListElement {title:"m_speed" }
        ListElement {title:"m_Iscvduty" }
        ListElement {title:"m_O2volt" }
        ListElement {title:"m_na1" }
        ListElement {title:"m_Secinjpulse" }
        ListElement {title:"m_na2" }
        ListElement {title:"m_InjDuty" }
        ListElement {title:"m_EngLoad" }
        ListElement {title:"m_MAF1V" }
        ListElement {title:"m_MAF2V" }
        ListElement {title:"m_injms" }
        ListElement {title:"m_Inj" }
        ListElement {title:"m_Ign" }
        ListElement {title:"m_Dwell" }
        ListElement {title:"m_BoostPres" }
        ListElement {title:"m_BoostDuty" }
        ListElement {title:"m_MAFactivity" }
        ListElement {title:"m_O2volt_2" }


        //Relative Boost

        ListElement {title:"m_pim" }

        //Aux Inputs
        ListElement {title:"m_auxcalc1" }
        ListElement {title:"m_auxcalc2" }
        ListElement {title:"m_auxcalc3" }
        ListElement {title:"m_auxcalc4" }

        // Sensor Info FD3S
        ListElement {title:"m_sens1" }
        ListElement {title:"m_sens2" }
        ListElement {title:"m_sens3" }
        ListElement {title:"m_sens4" }
        ListElement {title:"m_sens5" }
        ListElement {title:"m_sens6" }
        ListElement {title:"m_sens7" }
        ListElement {title:"m_sens8" }

        //Flag Strings

        ListElement {title:"m_FlagString1" }
        ListElement {title:"m_FlagString2" }
        ListElement {title:"m_FlagString3" }
        ListElement {title:"m_FlagString4" }
        ListElement {title:"m_FlagString5" }
        ListElement {title:"m_FlagString6" }
        ListElement {title:"m_FlagString7" }
        ListElement {title:"m_FlagString8" }
        ListElement {title:"m_FlagString9" }
        ListElement {title:"m_FlagString10" }
        ListElement {title:"m_FlagString11" }
        ListElement {title:"m_FlagString12" }
        ListElement {title:"m_FlagString13" }
        ListElement {title:"m_FlagString14" }
        ListElement {title:"m_FlagString15" }
        ListElement {title:"m_FlagString16" }

        //Sensor Srings

        ListElement {title:"m_SensorString1" }
        ListElement {title:"m_SensorString2" }
        ListElement {title:"m_SensorString3" }
        ListElement {title:"m_SensorString4" }
        ListElement {title:"m_SensorString5" }
        ListElement {title:"m_SensorString6" }
        ListElement {title:"m_SensorString7" }
        ListElement {title:"m_SensorString8" }



        //Bit Flags for Sensors
        ListElement {title:"m_Flag1" }
        ListElement {title:"m_Flag2" }
        ListElement {title:"m_Flag3" }
        ListElement {title:"m_Flag4" }
        ListElement {title:"m_Flag5" }
        ListElement {title:"m_Flag6" }
        ListElement {title:"m_Flag7" }
        ListElement {title:"m_Flag8" }
        ListElement {title:"m_Flag9" }
        ListElement {title:"m_Flag10" }
        ListElement {title:"m_Flag11" }
        ListElement {title:"m_Flag12" }
        ListElement {title:"m_Flag13" }
        ListElement {title:"m_Flag14" }
        ListElement {title:"m_Flag15" }
        ListElement {title:"m_Flag16" }


        //Adaptronic extra
        ListElement {title:"m_MAP" }
        ListElement {title:"m_AUXT" }
        ListElement {title:"m_AFR" }
        ListElement {title:"m_TPS" }
        ListElement {title:"m_IdleValue" }
        ListElement {title:"m_MVSS" }
        ListElement {title:"m_SVSS" }
        ListElement {title:"m_Inj1" }
        ListElement {title:"m_Inj2" }
        ListElement {title:"m_Inj3" }
        ListElement {title:"m_Inj4" }
        ListElement {title:"m_Ign1" }
        ListElement {title:"m_Ign2" }
        ListElement {title:"m_Ign3" }
        ListElement {title:"m_Ign4" }
        ListElement {title:"m_TRIM" }
        //GPS Strings
        ListElement {title:"m_gpsTime" }
        ListElement {title:"m_gpsAltitude" }
        ListElement {title:"m_gpsLatitude" }
        ListElement {title:"m_gpsLongitude" }
        ListElement {title:"m_gpsSpeed" }
        ListElement {title:"m_gpsVisibleSatelites" }
    }
    */
    /*
    ListView {
        id: listViewSourceSelect
        model: listModelSourceSelect
    }*/
}
