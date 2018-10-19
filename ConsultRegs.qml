import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Item {
    id: consultrequestselect
    anchors.fill : parent

    Connections{
        target: Dashboard
        onSupportedRegChanged: {functsupportedRegs.supportedRegs() }
    }
    Grid {
        rows: 10
        columns: 3

        Button {
            id: supportedRegs
            text: "Check"
            width: consultrequestselect.width / 10
            height: consultrequestselect.height /15
            font.pixelSize: consultrequestselect.width / 55
            onClicked: {Connect.checkReg(),closeconsultsettings.visible = true ,supportedRegs.visible = false ;}
        }
        Button {
            id: closeconsultsettings
            text: "Save & Reboot"
            width: consultrequestselect.width / 7
            height: consultrequestselect.height /15
            font.pixelSize: consultrequestselect.width / 55
            visible:false
            onClicked: {
                //supportedRegs.enabled = true;
                Connect.LiveReqMsg(consRPM.checkState,consRPMREF.checkState,consMAFVolt.checkState,consRHMAFVolt.checkState,consCoolantTemp.checkState,consLHO2Volt.checkState,consRHO2Volt.checkState,consSpeed.checkState,consBattvolt.checkState,consTPS.checkState,consFuelTemp.checkState,consIAT.checkState,consEGT.checkState,consDigitalBitReg.checkState,consInjectTimeLH.checkState,consIGNTiming.checkState,consAACValve.checkState,consAFALPHALH.checkState,consAFALPHARH.checkState,consAFALPHASELFLEARNLH.checkState,consAFALPHASELFLEARNRH.checkState,consDigitalControlReg1.checkState,consDigitalControlReg2.checkState,consMRFCMNT.checkState,consInjecttimeRH.checkState,consWasteGate.checkState,consMAPVolt.checkState,consEngineMount.checkState,consPositionCounter.checkState,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
            }
        }
        CheckBox {
            id: consRPM
            visible: false;
            text: qsTr("RPM")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consRPMREF
            visible: false;
            text: qsTr("RPMREF")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consMAFVolt
            visible: false;
            text: qsTr("MAF Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consRHMAFVolt
            visible: false;
            text: qsTr("RH MAF Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consCoolantTemp
            visible: false;
            text: qsTr("Coolant Temp")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consLHO2Volt
            visible: false;
            text: qsTr("LH O2 Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consRHO2Volt
            visible: false;
            text: qsTr("RH O2 Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consSpeed
            visible: false;
            text: qsTr("Speed")
            font.pixelSize: consultrequestselect.width / 55
        }
        //
        CheckBox {
            id: consBattvolt
            visible: false;
            text: qsTr("Battery Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consTPS
            visible: false;
            text: qsTr("TPS")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consFuelTemp
            visible: false;
            text: qsTr("Fuel Temp.")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consIAT
            visible: false;
            text: qsTr("Intake Air Temp.")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consEGT
            visible: false;
            text: qsTr("EGT")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consDigitalBitReg
            visible: false;
            text: qsTr("Digital Bit Register")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consInjectTimeLH
            visible: false;
            text: qsTr("Inj Time LH")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consIGNTiming
            visible: false;
            text: qsTr("IgnitionTiming")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAACValve
            visible: false;
            text: qsTr("AACValve")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAFALPHALH
            visible: false;
            text: qsTr("AF ALPHA LH")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAFALPHARH
            visible: false;
            text: qsTr("AF ALPHA RH")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAFALPHASELFLEARNLH
            visible: false;
            text: qsTr("AF ALPHA SELFLEARN LH")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAFALPHASELFLEARNRH
            visible: false;
            text: qsTr("AF ALPHA SELFLEARN RH")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consDigitalControlReg1
            visible: false;
            text: qsTr("Digital Control Reg1")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consDigitalControlReg2
            visible: false;
            text: qsTr("Digital Control Reg2")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consMRFCMNT
            visible: false;
            text: qsTr("MRFCMNT")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consInjecttimeRH
            visible: false;
            text: qsTr("Injector Time RH")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consWasteGate
            visible: false;
            text: qsTr("WasteGate")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consMAPVolt
            visible: false;
            text: qsTr("MAP Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consEngineMount
            visible: false;
            text: qsTr("EngineMount")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consPositionCounter
            visible: false;
            text: qsTr("Position Counter")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consPurgeContValve
            visible: false;
            text: qsTr("Purg. Vol. Control Valve")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consFuelTankTemp
            visible: false;
            text: qsTr("Fuel Tank Temp")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consDPCMDRVolt
            visible: false;
            text: qsTr("FPCM DR, Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consFuelGaugeVolt
            visible: false;
            text: qsTr("Fuel Gauge, Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consFRO2HeatB1
            visible: false;
            text: qsTr("FR O2 Heater-B1")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consFRO2HeatB2
            visible: false;
            text: qsTr("FR O2 Heater-B2")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consIGNsw
            visible: false;
            text: qsTr("Ignition Switch")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consCALLD
            visible: false;
            text: qsTr("CAL/LD Value, %")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consBFuelSched
            visible: false;
            text: qsTr("B/Fuel Schedule,ms")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consRRO2SensVolt
            visible: false;
            text: qsTr("RR O2 Sensor Volt")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consRRO2SensB2Volt
            visible: false;
            text: qsTr("RR O2 Sensor B2 Volt")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAbsTPSVolt
            visible: false;
            text: qsTr("Absolute TPS Volt")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consMAFgmS
            visible: false;
            text: qsTr("MAF gm/S")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consEvapSysPressVolt
            visible: false;
            text: qsTr("Evap System Press Volt")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consAbsPressSensVolt
            visible: false;
            text: qsTr("Abs. Press. Sens. Volt")
            font.pixelSize: consultrequestselect.width / 55
        }
        CheckBox {
            id: consFPCMFPVolt
            visible: false;
            text: qsTr("FPCM F/P Voltage")
            font.pixelSize: consultrequestselect.width / 55
        }

            Item {   //Function for Consult to show only supported Regs
                id: functsupportedRegs
                function supportedRegs()
                {
                    //console.log("QML"+Dashboard.supportedReg)
                    switch (Dashboard.supportedReg) {
                    case 1: {
                        consRPM.visible = true;
                        break;
                    }

                    case 3: {
                        consRPMREF.visible = true;
                        break;
                    }
                    case 5: {
                        consMAFVolt.visible = true;
                        break;
                    }
                    case 7: {
                        consRHMAFVolt.visible = true;
                        break;
                    }
                    case 8: {
                        consCoolantTemp.visible = true;
                        break;
                    }
                    case 9: {
                        consLHO2Volt.visible = true;
                        break;
                    }
                    case 10: {
                        consRHO2Volt.visible = true;
                        break;
                    }
                    case 11: {
                        consSpeed.visible = true;
                        break;
                    }
                    case 12: {
                        consBattvolt.visible = true;
                        break;
                    }
                    case 13: {
                        consTPS.visible = true;
                        break;
                    }
                    case 14: {
                        consFuelTemp.visible = true;
                        break;
                    }
                    case 15: {
                        consIAT.visible = true;
                        break;
                    }
                    case 16: {
                        consEGT.visible = true;
                        break;
                    }
                    case 17: {
                        consDigitalBitReg.visible = true;
                        break;
                    }
                    case 19: {
                        consInjectTimeLH.visible = true;
                        break;
                    }
                    case 20: {
                        consIGNTiming.visible = true;
                        break;
                    }
                    case 21: {
                        consAACValve.visible = true;
                        break;
                    }
                    case 22: {
                        consAFALPHALH.visible = true;
                        break;
                    }
                    case 23: {
                        consAFALPHARH.visible = true;
                        break;
                    }
                    case 24: {
                        consAFALPHASELFLEARNLH.visible = true;
                        break;
                    }
                    case 25: {
                        consAFALPHASELFLEARNRH.visible = true;
                        break;
                    }
                    case 26: {
                        consDigitalControlReg1.visible = true;
                        break;
                    }
                    case 27: {
                        consDigitalControlReg2.visible = true;
                        break;
                    }
                    case 28: {
                        consMRFCMNT.visible = true;
                        break;
                    }
                    case 30: {
                        consInjecttimeRH.visible = true;
                        break;
                    }
                    case 31: {
                        consWasteGate.visible = true;
                        break;
                    }
                    case 32: {
                        consMAPVolt.visible = true;
                        break;
                    }
                    case 33: {
                        consEngineMount.visible = true;
                        break;
                    }
                    case 34: {
                        consPositionCounter.visible = true;
                        break;
                    }
                    case 35: {
                        consPurgeContValve.visible = true;
                        break;
                    }
                    case 36: {
                        consFuelTankTemp.visible = true;
                        break;
                    }
                    case 37: {
                        consDPCMDRVolt.visible = true;
                        break;
                    }
                    case 38: {
                        consFuelGaugeVolt.visible = true;
                        break;
                    }
                    case 39: {
                        consFRO2HeatB1.visible = true;
                        break;
                    }
                    case 40: {
                        consFRO2HeatB2.visible = true;
                        break;
                    }
                    case 41: {
                        consIGNsw.visible = true;
                        break;
                    }
                    case 42: {
                        consCALLD.visible = true;
                        break;
                    }
                    case 43: {
                        consBFuelSched.visible = true;
                        break;
                    }
                    case 44: {
                        consRRO2SensVolt.visible = true;
                        break;
                    }
                    case 45: {
                        consRRO2SensB2Volt.visible = true;
                        break;
                    }
                    case 46: {
                        consAbsTPSVolt.visible = true;
                        break;
                    }
                    case 47: {
                        consMAFgmS.visible = true;
                        break;
                    }
                    case 48: {
                        consEvapSysPressVolt.visible = true;
                        break;
                    }
                    case 50: {
                        consAbsPressSensVolt.visible = true;
                        break;
                    }
                    case 52: {
                        consFPCMFPVolt.visible = true;
                        break;
                    }
                    default: {
                        break;
                    }
                    }
                }
            }

        }
    }

