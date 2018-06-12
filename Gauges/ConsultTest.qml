import QtQuick 2.8
import QtQuick.Controls 2.1

Rectangle {
    id: view
    anchors.fill: parent
    color: "grey"
    Grid {
        rows: 15
        columns: 4
        spacing: view.width/ 30
    Text {
        text: Dashboard.Flag1 + " AC SW   "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag2 + " PS SW   "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag3 + " N  SW   "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag4 + " Cranking"
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag5 + " CLSD/THL"
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag6 + " AC Relay"
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag7 + " Fuel Rel"
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag8 + " VTC SOL "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag9 + " FAN Hi  "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag10 + " FAN Low "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag11 + " P/Reg Va"
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag12 + " WG Sol  "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag13 + " IAC Sol "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag14 + " EGR Sol "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag15 + " LH Bank "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: Dashboard.Flag16 + " RH Bank "
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "RPM     " + Dashboard.rpm
        font.pixelSize: view.width/ 55
    }
    Text {
        text:"RPM Ref " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "MAF V.  " + Dashboard.MAF1V
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "RH MAFV " + Dashboard.MAF2V
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "Water T " + Dashboard.Watertemp
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "LH 02 V " + Dashboard.O2volt
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "RH 02 V " + Dashboard.O2volt_2
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "Speed   " + Dashboard.speed
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "Batt V  " + Dashboard.BatteryV
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "TPS  V  " + Dashboard.TPS
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "Fuel T  " + Dashboard.Fueltemp
        font.pixelSize: view.width/ 55
    }

    Text {
        text: "IAT     " + Dashboard.Intaketemp
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "EGT V   " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "Inj T L " + Dashboard.Inj
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "IGN T   " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "AAC Val " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "A/F LH  " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "A/F RH  " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "A/F LH S" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "A/F RH S" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "M/R FC M" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }		Text {
        text: "Inj T RH" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "WG %    " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "MAP Volt" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "MAF gm/s" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }		Text {
        text: "Evap V  " //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "ABS Pr.V" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
    Text {
        text: "FPCMF/PV" //+ Dashboard.
        font.pixelSize: view.width/ 55
    }
}
}
