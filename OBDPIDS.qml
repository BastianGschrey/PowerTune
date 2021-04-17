import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4


Item {
property variant items:[]
 anchors.fill: parent
 id: obdselect

        Grid {
            rows: 10
            columns: 3

            Button {
                id: supportedRegs
                text: "Check"
                width: obdselect.width / 10
                height: obdselect.height /15
                font.pixelSize: obdselect.width / 55
                onClicked: {
                   Connect.checkOBDReg(),supportedRegs.visible = false,apply.visible = true;
                }
            }
Button {
                id: apply
                text: "Save & Reboot"
                width: obdselect.width / 7
                height: obdselect.height /15
                visible: false
                font.pixelSize: obdselect.width / 55
                onClicked: {items = [0,0,0,0,(obd4.checkState),(obd5.checkState),(obd6.checkState),(obd7.checkState),(obd8.checkState),(obd9.checkState),(obd10.checkState),(obd11.checkState),0,0,(obd14.checkState),(obd15.checkState),(obd16.checkState),(obd17.checkState),0,0,(obd20.checkState),(obd21.checkState),(obd22.checkState),(obd23.checkState),(obd24.checkState),(obd25.checkState),(obd26.checkState),(obd27.checkState),0,0,0,0,0,0,(obd34.checkState),(obd35.checkState),(obd36.checkState),(obd37.checkState),(obd38.checkState),(obd39.checkState),(obd40.checkState),(obd41.checkState),(obd42.checkState),(obd43.checkState),0,0,0,(obd47.checkState),0,0,(obd50.checkState),(obd51.checkState),(obd52.checkState),(obd53.checkState),(obd54.checkState),(obd55.checkState),(obd56.checkState),(obd57.checkState),(obd58.checkState),(obd59.checkState),(obd60.checkState),(obd61.checkState),(obd62.checkState),(obd63.checkState),(obd66.checkState)];
                            Connect.LiveReqMsgOBD(items);
                            }
            }

            CheckBox {
                id: obd4
                visible: false;
                text: qsTr("Calculated Engine LOAD")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd5
                visible: false;
                text: qsTr("Coolant Temp")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd6
                visible: false;
                text: qsTr("Short term fuel trim—Bank 1")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd7
                visible: false;
                text: qsTr("Long term fuel trim—Bank 1")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd8
                visible: false;
                text: qsTr("Short term fuel trim—Bank 2")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd9
                visible: false;
                text: qsTr("Long term fuel trim—Bank 2")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd10
                visible: false;
                text: qsTr("Fuel pressure")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd11
                visible: false;
                text: qsTr("Intake mani abs pres")
                font.pixelSize: obdselect.width / 55
            }
// 12 and 13 are RPM and speed and are polled by default
            CheckBox {
                id: obd14
                visible: false;
                text: qsTr("Timing advance")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd15
                visible: false;
                text: qsTr("Intake air temp (IAT)")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd16
                visible: false;
                text: qsTr("MAF rate")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd17
                visible: false;
                text: qsTr("Throttle pos")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd20
                visible: false;
                text: qsTr("Oxygen Sen 1")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd21
                visible: false;
                text: qsTr("Oxygen Sen 2")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd22
                visible: false;
                text: qsTr("Oxygen Sen 3")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd23
                visible: false;
                text: qsTr("Oxygen Sen 4")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd24
                visible: false;
                text: qsTr("Oxygen Sen 5")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd25
                visible: false;
                text: qsTr("Oxygen Sen 6")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd26
                visible: false;
                text: qsTr("Oxygen Sen 7")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd27
                visible: false;
                text: qsTr("Oxygen Sen 8")
                font.pixelSize: obdselect.width / 55
            }

            CheckBox {
                id: obd34
                visible: false;
                text: qsTr("Fuel Rail Rel. Pres")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd35
                visible: false;
                text: qsTr("Fuel Rail Gauge Pres")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd36
                visible: false;
                text: qsTr("Oxygen S.1 AFR /V")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd37
                visible: false;
                text: qsTr("Oxygen S.2 AFR /V")
                font.pixelSize: obdselect.width / 55
            }				CheckBox {
                id: obd38
                visible: false;
                text: qsTr("Oxygen S.3 AFR /V")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd39
                visible: false;
                text: qsTr("Oxygen S.4 AFR /V")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd40
                visible: false;
                text: qsTr("Oxygen S.5 AFR /V")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd41
                visible: false;
                text: qsTr("Oxygen S.6 AFR /V")
                font.pixelSize: obdselect.width / 55
            }				CheckBox {
                id: obd42
                visible: false;
                text: qsTr("Oxygen S.7 AFR /V")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd43
                visible: false;
                text: qsTr("Oxygen S.8 AFR /V")
                font.pixelSize: obdselect.width / 55
            }

            CheckBox {
                id: obd47
                visible: false;
                text: qsTr("Fuel Tank Level")
                font.pixelSize: obdselect.width / 55
            }


            CheckBox {
                id: obd50
                visible: false;
                text: qsTr("Evap. System Vap Pres")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd51
                visible: false;
                text: qsTr("Abs.Baro Pressure")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd52
                visible: false;
                text: qsTr("Oxygen Sensor 1")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd53
                visible: false;
                text: qsTr("Oxygen Sensor 2")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd54
                visible: false;
                text: qsTr("Oxygen Sensor 3")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd55
                visible: false;
                text: qsTr("Oxygen Sensor 4")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd56
                visible: false;
                text: qsTr("Oxygen Sensor 5")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd57
                visible: false;
                text: qsTr("Oxygen Sensor 6")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd58
                visible: false;
                text: qsTr("Oxygen Sensor 7")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd59
                visible: false;
                text: qsTr("Oxygen Sensor 8")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd60
                visible: false;
                text: qsTr("Cat Temp: Bank 1,S1")
                font.pixelSize: obdselect.width / 55
            }				CheckBox {
                id: obd61
                visible: false;
                text: qsTr("Cat Temp: Bank 2,S1")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd62
                visible: false;
                text: qsTr("Cat Temp: Bank 1,S2")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd63
                visible: false;
                text: qsTr("Cat Temp: Bank 2,S2")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd64
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd65
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd66
                visible: false;
                text: qsTr("Battery voltage")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd67
                visible: false;
                text: qsTr("Absolute load value")
                font.pixelSize: obdselect.width / 55
            }
            /*
            CheckBox {
                id: obd68
                visible: false;
                text: qsTr("Fuel–Air commanded equivalence ratio")
                font.pixelSize: obdselect.width / 55
            }*/
            CheckBox {
                id: obd69
                visible: false;
                text: qsTr("Relative throttle pos")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd70
                visible: false;
                text: qsTr("Ambient air temp")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd71
                visible: false;
                text: qsTr("Abs throttle pos B")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd72
                visible: false;
                text: qsTr("Abs throttle pos C")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd73
                visible: false;
                text: qsTr("Accel ped pos D")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd74
                visible: false;
                text: qsTr("Accel ped pos E")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd75
                visible: false;
                text: qsTr("Accel ped pos F")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd76
                visible: false;
                text: qsTr("Com. throttle act")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd77
                visible: false;
                text: qsTr("Time run with MIL on")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd78
                visible: false;
                text: qsTr("Time run with MIL on")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd79
                visible: false;
                text: qsTr("Time since errors cleared")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd80
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd81
                visible: false;
                text: qsTr("Fuel Type")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd82
                visible: false;
                text: qsTr("Ethanol fuel %")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd83
                visible: false;
                text: qsTr("Abs Evap sys Vapor Pres")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd84
                visible: false;
                text: qsTr("Evap sys Vapor Pres")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd85
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd86
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd87
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd88
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd89
                visible: false;
                text: qsTr("Fuel rail abs pres")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd90
                visible: false;
                text: qsTr("Rel accel pedal pos")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd91
                visible: false;
                text: qsTr("Hybrid batt remaining life")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd92
                visible: false;
                text: qsTr("Engine oil temp")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd93
                visible: false;
                text: qsTr("Injection timing")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd94
                visible: false;
                text: qsTr("Fuel rate")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd95
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd96
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd97
                visible: false;
                text: qsTr("Demand engine % torque")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd98
                visible: false;
                text: qsTr("Act engine % torque")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd99
                visible: false;
                text: qsTr("Engine reference torque")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd100
                visible: false;
                text: qsTr("Eng percent torque data")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd101
                visible: false;
                text: qsTr("Mass air flow sensor")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd102
                visible: false;
                text: qsTr("Engine coolant temp (ECT)")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd103
                visible: false;
                text: qsTr("Intake air temperature")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd104
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd105
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd106
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }

            CheckBox {
                id: obd107
                visible: false;
                text: qsTr("EGT")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd108
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd109
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd110
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd111
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd112
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd123
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd124
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd125
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd126
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd127
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd128
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd129
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd130
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd131
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd132
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd133
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd134
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd135
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd136
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd137
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd138
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd139
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd140
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd141
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd142
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd143
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd144
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd145
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd146
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd147
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd148
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd149
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd150
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd151
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd152
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd153
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd154
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd155
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd156
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd157
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd158
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd159
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd160
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd161
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd162
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd163
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd164
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd165
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd166
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd167
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd168
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd169
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd170
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd172
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd173
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd174
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd175
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd176
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd177
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd178
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd179
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd180
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd181
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd182
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd183
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd184
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }				CheckBox {
                id: obd185
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd186
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd187
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd188
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd189
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd190
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd191
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }				CheckBox {
                id: obd192
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd193
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd194
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd195
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }
            CheckBox {
                id: obd196
                visible: false;
                text: qsTr("")
                font.pixelSize: obdselect.width / 55
            }


        }
        Connections{
            target: Dashboard
            onSupportedRegChanged: {functsupportedRegs.supportedRegs() }
        }

        Item {   //Function for Consult to show only supported Regs
            id: functsupportedRegs
            function supportedRegs()
            {
                var Test = "obd"+Dashboard.supportedReg+".visible"
                //console.log(Test)
                switch (Dashboard.supportedReg) {

                case 4: {
                    obd4.visible = true;
                    break;
                }
                case 5: {
                    obd5.visible = true;
                    break;
                }
                case 6: {
                    obd6.visible = true;
                    break;
                }
                case 7: {
                    obd7.visible = true;
                    break;
                }
                case 8: {
                    obd8.visible = true;
                    break;
                }
                case 9: {
                    obd9.visible = true;
                    break;
                }
                case 10: {
                    obd10.visible = true;
                    break;
                }
                case 11: {
                    obd11.visible = true;
                    break;
                }
                case 14: {
                    obd14.visible = true;
                    break;
                }
                case 15: {
                    obd15.visible = true;
                    break;
                }
                case 16: {
                    obd16.visible = true;
                    break;
                }
                case 17: {
                    obd17.visible = true;
                    break;
                }
                case 20: {
                    obd20.visible = true;
                    break;
                }
                case 21: {
                    obd21.visible = true;
                    break;
                }
                case 22: {
                    obd22.visible = true;
                    break;
                }
                case 23: {
                    obd23.visible = true;
                    break;
                }
                case 24: {
                    obd24.visible = true;
                    break;
                }
                case 25: {
                    obd25.visible = true;
                    break;
                }
                case 26: {
                    obd26.visible = true;
                    break;
                }
                case 27: {
                    obd27.visible = true;
                    break;
                }
                case 34: {
                    obd34.visible = true;
                    break;
                }
                case 35: {
                    obd35.visible = true;
                    break;
                }
                case 36: {
                    obd36.visible = true;
                    break;
                }
                case 37: {
                    obd37.visible = true;
                    break;
                }
                case 38: {
                    obd38.visible = true;
                    break;
                }
                case 39: {
                    obd39.visible = true;
                    break;
                }
                case 40: {
                    obd40.visible = true;
                    break;
                }
                case 41: {
                    obd41.visible = true;
                    break;
                }
                case 42: {
                    obd42.visible = true;
                    break;
                }
                case 43: {
                    obd43.visible = true;
                    break;
                }
                case 44: {
                    obd44.visible = true;
                    break;
                }
                case 45: {
                    obd45.visible = true;
                    break;
                }
                case 46: {
                    obd46.visible = true;
                    break;
                }
                case 47: {
                    obd47.visible = true;
                    break;
                }
                case 48: {
                    obd48.visible = true;
                    break;
                }
                case 49: {
                    obd49.visible = true;
                    break;
                }
                case 50: {
                    obd50.visible = true;
                    break;
                }
                case 51: {
                    obd51.visible = true;
                    break;
                }
                case 52: {
                    obd52.visible = true;
                    break;
                }
                case 53: {
                    obd53.visible = true;
                    break;
                }
                case 54: {
                    obd54.visible = true;
                    break;
                }
                case 55: {
                    obd55.visible = true;
                    break;
                }
                case 56: {
                    obd56.visible = true;
                    break;
                }
                case 57: {
                    obd57.visible = true;
                    break;
                }
                case 58: {
                    obd58.visible = true;
                    break;
                }
                case 59: {
                    obd59.visible = true;
                    break;
                }
                case 60: {
                    obd60.visible = true;
                    break;
                }
                case 61: {
                    obd61.visible = true;
                    break;
                }
                case 62: {
                    obd62.visible = true;
                    break;
                }
                case 63: {
                    obd63.visible = true;
                    break;
                }
                case 64: {
                    obd64.visible = true;
                    break;
                }
                case 65: {
                    obd65.visible = true;
                    break;
                }
                case 66: {
                    obd66.visible = true;
                    break;
                }
                case 67: {
                    obd67.visible = true;
                    break;
                }
                case 68: {
                    obd68.visible = true;
                    break;
                }
                case 69: {
                    obd69.visible = true;
                    break;
                }
                case 70: {
                    obd70.visible = true;
                    break;
                }
                case 71: {
                    obd71.visible = true;
                    break;
                }
                case 72: {
                    obd72.visible = true;
                    break;
                }
                default: {
                    break;
                }

                }
            }
        }
    }

