import QtQuick 2.8
import QtQuick.Controls 1.4 as Quick1
import QtQuick.Controls 2.1
import Qt.labs.settings 1.0
import QtSensors 5.0
import QtQuick.Controls.Styles 1.4

import QtMultimedia 5.8
import "qrc:/Gauges/"
import DLM 1.0
import QtQuick.VirtualKeyboard 2.1

Quick1.TabView {
    id: tabView
    anchors.fill: parent

    property int lastdashamount

    DLM
    {
        id:downloadManager
    }

    Rectangle{
        id: keyboardcontainer
        color: "darkgrey"
        visible: false
        width :500
        height:180
        z:220

        MouseArea {
            id: touchAkeyboardcontainer
            anchors.fill:parent
            drag.target: keyboardcontainer
        }
        InputPanel {
            id: keyboard
            anchors.fill: parent
            visible: false
            states: State {
                name: "visible";
                when: keyboard.active;
                PropertyChanges {
                    target: keyboard;
                    visible: true
                }
                PropertyChanges {
                    target: keyboardcontainer;
                    visible: true;
                    x:300
                    y:200
                }
            }
        }
    }

    style: TabViewStyle {
        frameOverlap: 1
        tab: Rectangle {
            id:tabrect
            color: styleData.selected ? "grey" :"lightgrey"
            border.color:  "steelblue"
            implicitWidth: Math.max(text.width + 4, 80)
            implicitHeight: 50
            radius: 2
            Text {
                id: text
                anchors.centerIn: parent
                font.pixelSize: tabView.width / 55
                text: styleData.title
                color: styleData.selected ? "white" : "black"
            }
        }
        frame: Rectangle { color: "steelblue" }
    }
    Quick1.Tab {
        title: "Main"
        anchors.fill: parent
        Rectangle {
            id: windowbackround
            anchors.fill: parent
            color: "grey"
            property  int test1: 0
            property  int connected: 0
            property  var gpscom
            property int hexstring;
            property int hexstring2;
            Item {
                id: powerTuneSettings
                Settings {
                    //property alias brightnessselect: brightness.value
                    // property alias connectAtStartUp: connectAtStart.checked
                    property alias connectECUAtStartup: connectButton.enabled
                    property alias connectGPSAtStartup: connectButtonGPS.enabled
                    //property alias gpsswitch: gpsswitch.checked
                    property alias serialPortName: serialName.currentText
                    property alias gpsPortName: serialNameGPS.currentText
                    property alias gpsPortNameindex: serialNameGPS.currentIndex
                    //property alias gpsBaud: serialGPSBaud.currentText
                    //property alias gpsBaudindex: serialGPSBaud.currentIndex
                    property alias ecuType: ecuSelect.currentText
                    property alias auxunit1: unitaux1.text
                    property alias aux1: an1V0.text
                    property alias aux2: an2V5.text
                    property alias auxunit2: unitaux2.text
                    property alias aux3: an3V0.text
                    property alias aux4: an4V5.text
                    property alias goProVariant: goProSelect.currentIndex
                    property alias password: goPropass.text
                    property alias vehicleweight: weight.text
                    property alias unitSelector1: unitSelect1.currentIndex
                    property alias unitSelector: unitSelect.currentIndex
                    property alias unitSelector2: unitSelect2.currentIndex
                    property alias odometervalue: odometer.text
                    property alias tripmetervalue: tripmeter.text
                    //property alias protocol : protocol.currentIndex
                    property alias smoothingrpm : smoothrpm.currentIndex
                    property alias smoothingspeed : smoothspeed.currentIndex
                    property alias extendercanbase: baseadresstext.text
                    property alias shiftlightcanbase: shiftlightbaseadresstext.text


                }
                SoundEffect {
                    id: warnsound
                    source: "qrc:/Sounds/alarm.wav"
                }

                Connections{
                    target: Dashboard
                    onWifiStatChanged:{wifistatus.text = Dashboard.WifiStat}
                    onEthernetStatChanged:{ethernetstatus.text = Dashboard.EthernetStat}

                    onOdoChanged:{odometer.text = (Dashboard.Odo).toFixed(0) }
                    onTripChanged:{tripmeter.text = (Dashboard.Trip).toFixed(1) }
                    onWatertempChanged: { if (Dashboard.Watertemp > Dashboard.waterwarn) {playwarning.start()};}
                    onRpmChanged: { if (Dashboard.rpm > Dashboard.rpmwarn) {playwarning.start()};}
                    onKnockChanged: { if (Dashboard.Knock > Dashboard.knockwarn) {playwarning.start()};}
                    onBoostPresChanged: { if (Dashboard.BoostPres > Dashboard.boostwarn) {playwarning.start()};}
                }


                Row {
                    x: windowbackround.width /150
                    y: windowbackround.width /150
                    spacing: windowbackround.width /150
                    Grid {
                        anchors.top :parent.top
                        anchors.topMargin: parent.height / 20
                        rows: 13
                        columns: 2
                        spacing: windowbackround.width /150
                        // [0]
                        Text {
                            text: "ECU Serial Port: "
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                            visible: { (ecuSelect.currentIndex != "1") ? false: true; }
                        }
                        ComboBox {
                            id: serialName
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: Connect.portsNames
                            visible: { (ecuSelect.currentIndex != "1") ? false: true; }
                            property bool initialized: false
                            onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                            Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true; autoconnect.auto(); }
                            delegate: ItemDelegate {
                                width: serialName.width
                                text: serialName.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: serialName.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: serialName.font.family
                                font.pixelSize: serialName.font.pixelSize
                                highlighted: serialName.highlightedIndex == index
                                hoverEnabled: serialName.hoverEnabled
                            }
                        }
                        Text {
                            text: "GPS Port: "
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                            //visible: { (gpsswitch.checked == true ) ? true:false; }
                        }
                        ComboBox {
                            id: serialNameGPS
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: Connect.portsNames
                            // visible: { (gpsswitch.checked == true ) ? true:false; }
                            delegate: ItemDelegate {
                                width: serialNameGPS.width
                                text: serialNameGPS.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: serialNameGPS.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: serialNameGPS.font.family
                                font.pixelSize: serialNameGPS.font.pixelSize
                                highlighted: serialNameGPS.highlightedIndex == index
                                hoverEnabled: serialNameGPS.hoverEnabled
                            }
                        }
                        Text {
                            text: "Speed units:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        ComboBox {
                            id: unitSelect1
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: [ "Metric","Imperial"]
                            property bool initialized: false
                            Component.onCompleted: { Connect.setSpeedUnits(currentIndex);changeweighttext.changetext()}
                            onCurrentIndexChanged: { Connect.setSpeedUnits(currentIndex);changeweighttext.changetext()}
                            delegate: ItemDelegate {
                                width: unitSelect1.width
                                text: unitSelect1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: unitSelect1.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: unitSelect1.font.family
                                font.pixelSize: unitSelect1.font.pixelSize
                                highlighted: unitSelect1.highlightedIndex == index
                                hoverEnabled: unitSelect1.hoverEnabled
                            }

                        }
                        Text {
                            text: "Temp units:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        ComboBox {
                            id: unitSelect
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: [ "Metric","Imperial"]
                            property bool initialized: false
                            Component.onCompleted: { Connect.setUnits(currentIndex);changeweighttext.changetext()}
                            onCurrentIndexChanged: { Connect.setUnits(currentIndex);changeweighttext.changetext()}
                            delegate: ItemDelegate {
                                width: unitSelect.width
                                text: unitSelect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: unitSelect.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: unitSelect.font.family
                                font.pixelSize: unitSelect.font.pixelSize
                                highlighted: unitSelect.highlightedIndex == index
                                hoverEnabled: unitSelect.hoverEnabled
                            }

                        }
                        Text {
                            text: "Pressure units:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        ComboBox {
                            id: unitSelect2
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: [ "kPa","PSI"]
                            property bool initialized: false
                            Component.onCompleted: { Connect.setPressUnits(currentIndex);}
                            onCurrentIndexChanged: { Connect.setPressUnits(currentIndex);}
                            delegate: ItemDelegate {
                                width: unitSelect.width
                                text: unitSelect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: unitSelect.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: unitSelect.font.family
                                font.pixelSize: unitSelect.font.pixelSize
                                highlighted: unitSelect.highlightedIndex == index
                                hoverEnabled: unitSelect.hoverEnabled
                            }

                        }
                        Text {
                            text: "ECU Selection:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        ComboBox {
                            id: ecuSelect
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            //model: [ "PowerFC","UDP","None","CAN Adaptronic Modular","Consult","HaltechV1","HaltechV2","OBD2"]
                            model: [ "CAN","PowerFC","Consult","OBD2"]
                            property bool initialized: false
                            onCurrentIndexChanged: {if (initialized) AppSettings.setECU( currentIndex ),Dashboard.setecu(ecuSelect.currentIndex);}
                            Component.onCompleted: { currentIndex = AppSettings.getECU(),Dashboard.setecu(ecuSelect.currentIndex),initialized = true; }
                            delegate: ItemDelegate {
                                width: ecuSelect.width
                                text: ecuSelect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: ecuSelect.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: ecuSelect.font.family
                                font.pixelSize: ecuSelect.font.pixelSize
                                highlighted: ecuSelect.highlightedIndex == index
                                hoverEnabled: ecuSelect.hoverEnabled
                            }
                        }
                        Text {
                            text: "GoPro Variant :"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        ComboBox {
                            id: goProSelect
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: [ "Hero", "Hero2","Hero3"]
                            delegate: ItemDelegate {
                                width: goProSelect.width
                                text: goProSelect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: goProSelect.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: goProSelect.font.family
                                font.pixelSize: goProSelect.font.pixelSize
                                highlighted: goProSelect.highlightedIndex == index
                                hoverEnabled: goProSelect.hoverEnabled
                            }

                        }
                        Text {
                            text: "GoPro Password :"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        TextField {
                            id: goPropass
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            placeholderText: qsTr("GoPro Password")
                            //InputMethod:Qt.
                            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                            Component.onCompleted: {transferSettings.sendSettings() }
                        }
                        Text
                        {
                            text: "Logfile name:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        TextField {
                            id: logfilenameSelect
                            text: qsTr("DataLog")
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                            //enterKeyAction: EnterKeyAction.Next
                        }
                        Text
                        {
                            text: "Odo:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        TextField {
                            id: odometer
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            text: qsTr("0")
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            //enterKeyAction: EnterKeyAction.Next
                        }
                        Text
                        {
                            text: "Trip:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"

                        }
                        TextField{
                            id: tripmeter
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            readOnly: true
                            text: "0"
                            Component.onCompleted: Dashboard.setTrip(tripmeter.text)
                        }

                        Text
                        {
                            id: weighttext
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                            text: "Weight:"
                        }
                        TextField {
                            id: weight
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            inputMethodHints: Qt.ImhFormattedNumbersOnly

                        }
                        Text
                        {
                            text: "Serial Status:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                        }
                        TextField {
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            text: qsTr(Dashboard.SerialStat)


                        }
                    }

                    Grid {
                        rows: 13
                        columns: 2
                        spacing: windowbackround.width / 150
                        anchors.top :parent.top
                        anchors.topMargin: parent.height / 20
                        id:middlegrid
                        Button {
                            id: connectButton
                            text: "Connect"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            onClicked: {
                                functconnect.connectfunc();
                                connectButton.enabled =false;
                                ecuSelect.enabled = false;
                                disconnectButton.enabled = true;
                                //consultset.enabled = false;
                            }
                        }
                        Button {
                            id: disconnectButton
                            text: "Disconnect"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            enabled: false
                            onClicked: {
                                connectButton.enabled = true;
                                disconnectButton.enabled = false;
                                ecuSelect.enabled = true;
                                // consultset.enabled = true;
                                functdisconnect.disconnectfunc();
                            }
                        }
                        Button {
                            id: connectButtonGPS
                            text: "GPS Connect"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            Component.onCompleted: autoconnectGPS.auto()
                            onClicked: {

                                //console.log("clicked GPS")
                                connectButtonGPS.enabled=false
                                disconnectButtonGPS.enabled=true
                                autoconnectGPS.auto()
                                //console.log("gps disconnect enabled")
                            }
                        }
                        Button {
                            id: disconnectButtonGPS
                            text: "GPS Disconnect"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            enabled: false
                            onClicked: {
                                connectButtonGPS.enabled = true
                                disconnectButtonGPS.enabled = false
                                Gps.closeConnection()

                            }
                        }

                        Button {
                            id: resettrip
                            text: "Trip Reset"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            onClicked: {Calculations.resettrip()}
                        }


                        //for official raspberry Pi image only !!!!
                        /*
                Button {
                    id: updateButton
                    text: "Pi Update "
                    onClicked: { updateButton.enabled =false,Connect.update();
                    }
                }
*/
                        Button {
                            text: "Quit"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            onClicked: { Qt.quit();}
                        }
                        Button {
                            text: "Shutdown"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            onClicked: {Connect.shutdown();}
                        }
                        Button {
                            text: "Reboot"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            onClicked: {
                                //GPS.closeConnection();
                                Connect.reboot();
                            }
                        }


                        Text  { text: "RPM Smoothing :";color: "white";font.pixelSize: windowbackround.width / 55}
                        ComboBox {
                            id: smoothrpm
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: ["OFF","2","3","4","5","6","7","8","9","10"]
                            //property bool initialized: true
                            onCurrentIndexChanged:{Dashboard.setsmoothrpm(smoothrpm.currentIndex);}
                            Component.onCompleted: {Dashboard.setsmoothrpm(smoothrpm.currentIndex);}
                            delegate: ItemDelegate {
                                width: smoothrpm.width
                                text: smoothrpm.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: smoothrpm.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: smoothrpm.font.family
                                font.pixelSize: smoothrpm.font.pixelSize
                                highlighted: smoothrpm.highlightedIndex == index
                                hoverEnabled: smoothrpm.hoverEnabled
                            }
                        }

                        Text  { text: "Speed Smoothing :";color: "white";font.pixelSize: windowbackround.width / 55}
                        ComboBox {
                            id: smoothspeed
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: ["OFF","2","3","4","5","6","7","8","9","10"]
                            property bool initialized: true
                            onCurrentIndexChanged:{Dashboard.setsmoothspeed(smoothspeed.currentIndex)}
                            Component.onCompleted: {Dashboard.setsmoothspeed(smoothspeed.currentIndex)}
                            delegate: ItemDelegate {
                                width: smoothspeed.width
                                text: smoothspeed.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: smoothspeed.currentIndex == index ? Font.DemiBold : Font.Normal
                                font.family: smoothspeed.font.family
                                font.pixelSize: smoothspeed.font.pixelSize
                                highlighted: smoothspeed.highlightedIndex == index
                                hoverEnabled: smoothspeed.hoverEnabled
                            }
                        }
                        Switch {
                            id: loggerswitch
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            text: qsTr("Data Logger")
                            Component.onCompleted: {logger.datalogger()}
                            onCheckedChanged: logger.datalogger()
                        }

                        Switch {
                            id: record
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            text: qsTr("GoPro rec")
                            onCheckedChanged: {transferSettings.sendSettings(),goproRec.rec()}
                            Component.onCompleted: tabView.currentIndex = 1; // opens the 2nd tab
                        }
                        Text  { text: " V 1.96u " + Dashboard.Platform ;color: "white";font.pixelSize: windowbackround.width / 55} //spacer


                    }
                    Grid {
                        rows: 10
                        columns:1
                        spacing: windowbackround.width / 150
                        anchors.top :parent.top
                        anchors.topMargin: parent.height / 20

                        Text  { text: "     CAN Extender";color: "white";font.pixelSize: windowbackround.width / 55}
                        Text  { text: "      base adress ";color: "white";font.pixelSize: windowbackround.width / 55}
                        Text  { text: "       (decimal) :";color: "white";font.pixelSize: windowbackround.width / 55}
                        TextField {
                            id: baseadresstext
                            enabled: connectButton.enabled == false ? false : true
                            width: windowbackround.width /5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            validator: IntValidator {bottom: 0; top: 4000;}
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            placeholderText: qsTr("1024")
                            onTextChanged: hexstring = baseadresstext.text;
                        }
                        Text  { text: "      HEX: 0x"+(hexstring+0x1000).toString(16).substr(-3).toUpperCase();color: "white";font.pixelSize: windowbackround.width / 55}
                        Text  { text: "     Shiftlight CAN";color: "white";font.pixelSize: windowbackround.width / 55}
                        Text  { text: "      base adress ";color: "white";font.pixelSize: windowbackround.width / 55}
                        Text  { text: "       (decimal) :";color: "white";font.pixelSize: windowbackround.width / 55}
                        TextField {
                            id: shiftlightbaseadresstext
                            enabled: connectButton.enabled == false ? false : true
                            width: windowbackround.width /5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            validator: IntValidator {bottom: 0; top: 4000;}
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            placeholderText: qsTr("1024")
                            onTextChanged: hexstring2 = shiftlightbaseadresstext.text;
                        }
                        Text  { text: "      HEX: 0x"+(hexstring2+0x1000).toString(16).substr(-3).toUpperCase();color: "white";font.pixelSize: windowbackround.width / 55}

                }

                }

                Grid {
                    visible: { (ecuSelect.currentIndex != "1") ? false: true; }
                    rows: 3
                    columns: 4
                    spacing: windowbackround.width / 150
                    x:350
                    y:290
                  //  anchors.right: windowbackround.right
                 //   anchors.bottom: windowbackround.bottom
  /*                  //Just a spacer for now still need to do it properly
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    //Spacer end
*/

                    Text  { text: "";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "0V";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "5V";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "Name";font.pixelSize: windowbackround.width / 55}
                    Text  { text: "    ";font.pixelSize: windowbackround.width / 55}
                    TextField {
                        id: an1V0
                        width: windowbackround.width / 10
                        height: windowbackround.height /15
                        font.pixelSize: windowbackround.width / 55
                        //validator: DoubleValidator {bottom: -1000.0; top: 1000.0;notation : DoubleValidator.StandardNotation ; decimals : 1}
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        placeholderText: qsTr("9")
                    }
                    TextField {
                        id: an2V5
                        width: windowbackround.width / 10
                        height: windowbackround.height /15
                        font.pixelSize: windowbackround.width / 55
                        // validator: DoubleValidator {bottom: -1000.0; top: 1000.0;notation : DoubleValidator.StandardNotation ; decimals : 1}
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        placeholderText: qsTr("16")
                    }

                    TextField {
                        id: unitaux1
                        width: windowbackround.width / 10
                        height: windowbackround.height /15
                        font.pixelSize: windowbackround.width / 55
                        placeholderText: qsTr("AFR")
                    }
                    Text  { text: "AN1-2";font.pixelSize: windowbackround.width / 55}
                    TextField {
                        id: an3V0
                        width: windowbackround.width / 10
                        height: windowbackround.height /15
                        font.pixelSize: windowbackround.width / 55
                        //validator: DoubleValidator {bottom: -1000.0; top: 1000.0;notation : DoubleValidator.StandardNotation ; decimals : 1}
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        placeholderText: qsTr("0")

                    }
                    TextField {
                        id: an4V5
                        width: windowbackround.width / 10
                        height: windowbackround.height /15
                        font.pixelSize: windowbackround.width / 55
                        //validator: DoubleValidator {bottom: -1000.0; top: 1000.0;notation : DoubleValidator.StandardNotation ; decimals : 1}
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        placeholderText: qsTr("5")
                    }
                    TextField {
                        id: unitaux2
                        width: windowbackround.width / 10
                        height: windowbackround.height /15
                        font.pixelSize: windowbackround.width / 55
                        placeholderText: qsTr("AFR")
                    }
                    Text  { text: "AN3-4";font.pixelSize: windowbackround.width / 55}
                }
            }

            //Functions

            Item {
                //Function to automatically connect at Startup , function is called from COmbobox Serialname component.oncompleted
                id: autoconnect
                function auto()
                {
                    // if (connectAtStart.checked == true) Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, interfaceSelect.currentIndex, loggerSelect.currentIndex);
                    if (connectButton.enabled == false) functconnect.connectfunc(),ecuSelect.enabled = false,disconnectButton.enabled = true;//Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, loggerSelect.currentIndex,logger.datalogger()),
                }
            }
            Item {
                //Function to connect and disconnect GPS
                id: autoconnectGPS
                function auto()
                {

                    // if (gpsswitch.checked == true)GPS.startGPScom(serialNameGPS.currentText,serialGPSBaud.currentText);
                    if (connectButtonGPS.enabled == false)
                    {
                        Gps.openConnection(serialNameGPS.currentText,"9600")
                        disconnectButtonGPS.enabled=true
                    }
                    //if (connectButtonGPS.enabled == true)GPS.openConnection(serialNameGPS.currentText,"9600"),disconnectButtonGPS.enabled=false;
                    //if (gpsswitch.checked == false)GPS.closeConnection(),console.log("GPS CLOSED BY QML");
                }
            }
            Item {
                id: changeweighttext
                function changetext()
                {
                    if  (unitSelect.currentIndex == 0) weighttext.text = "Weight kg";
                    if  (unitSelect.currentIndex == 1) weighttext.text = "Weight lbs";
                }
            }
            Item {

                //Function to transmit GoPro rec status on off

                id: goproRec

                property var recording: 0

                function rec()

                {

                    if (record.checked == true) goproRec.recording = 1, GoPro.goprorec(recording.valueOf());
                    if (record.checked == false) goproRec.recording = 0,GoPro.goprorec(recording.valueOf());
                }

            }
            Item {
                //Logger on off function
                id: logger
                property var loggeron: 0
                function datalogger()
                {
                    if (loggerswitch.checked == true) logger.loggeron = 1, Logger.startLog(logfilenameSelect.text);
                    if (loggerswitch.checked == false) logger.loggeron = 0,Logger.stopLog();
                }
            }
            Item {
                //Function to transmit GoPro variant and GoPro Password
                id: transferSettings
                function sendSettings()
                {
                    GoPro.goProSettings(goProSelect.currentIndex,goPropass.text);
                }
            }
            Item {
                //function to Connect
                id: functconnect
                function connectfunc()
                {
                    Connect.openConnection(serialName.currentText, ecuSelect.currentIndex ,baseadresstext.text,shiftlightbaseadresstext.text);
                    Connect.setOdometer(odometer.text);
                    Connect.setWeight(weight.text);
                    Apexi.calculatorAux(an1V0.text,an2V5.text,an3V0.text,an4V5.text,unitaux1.text,unitaux2.text);
                    connected = 1;
                }
            }

            //function to Disconnect
            Item {

                id: functdisconnect
                function disconnectfunc()
                {
                    Connect.closeConnection()
                    connected = 0;
                }
            }


            Item {
                //Function to play warning sound
                id: playwarning
                function start()
                {
                    if (warnsound.playing == false) warnsound.play();
                }
            }

        }
    }
    Quick1.Tab {
        id :dash
        title: "Dash Sel."
        Rectangle{

            id: dashselector
            anchors.fill : parent
            color: "grey"

            Item {
                id: dashSettings
                Settings {

                    property alias dashselect1 : dash1.currentIndex
                    property alias dashselect2 : dash2.currentIndex
                    property alias dashselect3 : dash3.currentIndex
                    property alias dashselect4 : dash4.currentIndex
                    property alias numberofdash : numberofdashes.currentIndex


                }
            }
                /*
                Rectangle{
                    id: firstgrid
                    width: 800
                    height: 100
                    color:"grey"



                }*/
                Grid {
                    id: dashselectorgrid
                    rows: 2
                    columns: 1
                    anchors.centerIn: parent
                   // x: 100
                   // y: 100

                    Text { text: "Active Dashboards"

                        font.pixelSize: dashselector.width / 55 }

                    ComboBox {
                        id: numberofdashes

                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["1","2","3","4"]
                        currentIndex: -1
                        onCurrentIndexChanged:{addremovedashpage.adremove()}

                        delegate: ItemDelegate {
                            width: numberofdashes.width
                            text: numberofdashes.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: numberofdashes.currentIndex == index ? Font.DemiBold : Font.Normal
                            font.family: numberofdashes.font.family
                            font.pixelSize: numberofdashes.font.pixelSize
                            highlighted: numberofdashes.highlightedIndex == index
                            hoverEnabled: numberofdashes.hoverEnabled
                        }
                    }
                }

                Grid {
                    id: dash1grid
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins:dashselector.width / 60
                    rows: 2
                    columns: 1

                    Text { text: "Dash1"
                        font.pixelSize: dashselector.width / 55 }

                    ComboBox {
                        id: dash1
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash","GPS", "Laptimer", "PowerFC Sensors","User Dash 1","User Dash 2","User Dash 3","G-Force","Mediaplayer","Screen Toggle","Drag Timer"]
                        //currentIndex: 1
                        onCurrentIndexChanged:{select1.selDash1() }
                        //Component.onCompleted: {select1.selDash1() }
                        delegate: ItemDelegate {
                            width: dash1.width
                            text: dash1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash1.currentIndex == index ? Font.DemiBold : Font.Normal
                            font.family: dash1.font.family
                            font.pixelSize: dash1.font.pixelSize
                            highlighted: dash1.highlightedIndex == index
                            hoverEnabled: dash1.hoverEnabled
                        }
                    }
                }
                Grid {
                    id: dash2grid
                    anchors.top: parent.top
                    anchors.left: dash1grid.right
                    anchors.margins:dashselector.width / 60
                    rows: 2
                    columns: 1
                    Text { text: "Dash2"
                        visible: Dashboard.Visibledashes >1
                        font.pixelSize: dashselector.width / 55}

                    ComboBox {
                        id: dash2
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash","GPS", "Laptimer", "PowerFC Sensors","User Dash 1","User Dash 2","User Dash 3","G-Force","Mediaplayer","Screen Toggle","Drag Timer"]
                        //currentIndex: 1
                        //onCurrentIndexChanged:{select2.selDash2() }
                        visible: Dashboard.Visibledashes >1
                        onCurrentIndexChanged:{if (dash2.visible == true){select2.selDash2()} }
                        onVisibleChanged:{if (dash2.visible == true){select2.selDash2()} }
                        delegate: ItemDelegate {
                            width: dash2.width
                            text: dash2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash2.currentIndex == index ? Font.DemiBold : Font.Normal
                            font.family: dash2.font.family
                            font.pixelSize: dash2.font.pixelSize
                            highlighted: dash2.highlightedIndex == index
                            hoverEnabled: dash2.hoverEnabled
                        }
                    }
                }
                Grid {
                    id: dash3grid
                    anchors.top: parent.top
                    anchors.left: dash2grid.right
                    anchors.margins:dashselector.width / 60
                    rows: 2
                    columns: 1
                    Text { text: "Dash3"
                        visible: Dashboard.Visibledashes >2
                        font.pixelSize: dashselector.width / 55}
                    ComboBox {
                        id: dash3
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash","GPS", "Laptimer", "PowerFC Sensors","User Dash 1","User Dash 2","User Dash 3","G-Force","Mediaplayer","Screen Toggle","Drag Timer"]
                        visible: Dashboard.Visibledashes >2
                        onCurrentIndexChanged:{if (dash3.visible == true){select3.selDash3()} }
                        onVisibleChanged: {if (dash3.visible == true){select3.selDash3()} }
                        delegate: ItemDelegate {
                            width: dash3.width
                            text: dash3.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash3.currentIndex == index ? Font.DemiBold : Font.Normal
                            font.family: dash3.font.family
                            font.pixelSize: dash3.font.pixelSize
                            highlighted: dash3.highlightedIndex == index
                            hoverEnabled: dash3.hoverEnabled
                        }
                    }
                }
                Grid {
                    id: dash4grid
                    anchors.top: parent.top
                    anchors.left: dash3grid.right
                    anchors.margins:dashselector.width / 60
                    rows: 2
                    columns: 1
                    Text { text: "Dash4"
                        visible: Dashboard.Visibledashes >3
                        font.pixelSize: dashselector.width / 55}

                    ComboBox {
                        id: dash4
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash","GPS", "Laptimer", "PowerFC Sensors","User Dash 1","User Dash 2","User Dash 3","G-Force","Mediaplayer","Screen Toggle","Drag Timer"]
                        visible: Dashboard.Visibledashes >3
                        onCurrentIndexChanged:{if (dash4.visible == true){select4.selDash4()} }
                        onVisibleChanged: {if (dash4.visible == true){select4.selDash4()} }
                        delegate: ItemDelegate {
                            width: dash4.width
                            text: dash4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash4.currentIndex == index ? Font.DemiBold : Font.Normal
                            font.family: dash4.font.family
                            font.pixelSize: dash4.font.pixelSize
                            highlighted: dash4.highlightedIndex == index
                            hoverEnabled: dash4.hoverEnabled
                        }
                    }





                Item {
                    id: addremovedashpage
                    function adremove()
                    {
                      //Setting amount of Active Dashes loaded
                       Dashboard.Visibledashes = numberofdashes.currentIndex +1;

                      while (dashView.count > numberofdashes.currentIndex +2)
                      {
                      dashView.takeItem(dashView.count -2)
                      //console.log("removing", dashView.count -2)
                      }

                      //Adding Dashes back
                      while (dashView.count < numberofdashes.currentIndex +2)
                      {
                         // console.log("We have currently ", dashView.count)
                      switch (dashView.count) {

                          case 2: {
                              dashView.insertItem(1,secondPageLoader)
                             // console.log("add second page")
                              break;
                          }
                          case 3: {
                              dashView.insertItem(2,thirdPageLoader)
                              //console.log("add 3rd page", dashView.count)
                              break;
                          }
                          case 4: {
                              dashView.insertItem(3,fourthPageLoader)
                             // console.log("add 4th page", dashView.count)
                              break;
                          }
                      }

                      }
                    }
                    }

                //Function to select Dash1
                Item {
                    id: select1
                    function selDash1()
                    {
                        if (dash1.currentIndex == "0") {firstPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                        if (dash1.currentIndex == "1") {firstPageLoader.source = "qrc:/Gauges/GPS.qml"};
                        if (dash1.currentIndex == "2") {firstPageLoader.source = "qrc:/GPSTracks/Laptimer.qml"};
                        if (dash1.currentIndex == "3") {firstPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                        if (dash1.currentIndex == "4") {firstPageLoader.source = "qrc:/Gauges/Userdash1.qml"};
                        if (dash1.currentIndex == "5") {firstPageLoader.source = "qrc:/Gauges/Userdash2.qml"};
                        if (dash1.currentIndex == "6") {firstPageLoader.source = "qrc:/Gauges/Userdash3.qml"};
                        if (dash1.currentIndex == "7") {firstPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                        //if (dash1.currentIndex == "8") {firstPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                        if (dash1.currentIndex == "8"){firstPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                        if (dash1.currentIndex == "9"){firstPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};
                        if (dash1.currentIndex == "10") {firstPageLoader.source = "qrc:/Gauges/SpeedMeasurements.qml"};

                    }
                }
                Item {
                    id: select2
                    function selDash2()
                    {

                        if (dash2.currentIndex == "0") {secondPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                        if (dash2.currentIndex == "1") {secondPageLoader.source = "qrc:/Gauges/GPS.qml"};
                        if (dash2.currentIndex == "2") {secondPageLoader.source = "qrc:/GPSTracks/Laptimer.qml"};
                        if (dash2.currentIndex == "3") {secondPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                        if (dash2.currentIndex == "4") {secondPageLoader.source = "qrc:/Gauges/Userdash1.qml"};
                        if (dash2.currentIndex == "5") {secondPageLoader.source = "qrc:/Gauges/Userdash2.qml"};
                        if (dash2.currentIndex == "6") {secondPageLoader.source = "qrc:/Gauges/Userdash3.qml"};
                        if (dash2.currentIndex == "7") {secondPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                        //if (dash2.currentIndex == "8") {secondPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                        if (dash2.currentIndex == "8"){secondPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                        if (dash2.currentIndex == "9"){secondPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};
                        if (dash2.currentIndex == "10") {secondPageLoader.source = "qrc:/Gauges/SpeedMeasurements.qml"};


                    }
                }
                Item {
                    id: select3
                    function selDash3()
                    {
                        if (dash3.currentIndex == "0") {thirdPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                        if (dash3.currentIndex == "1") {thirdPageLoader.source = "qrc:/Gauges/GPS.qml"};
                        if (dash3.currentIndex == "2") {thirdPageLoader.source = "qrc:/GPSTracks/Laptimer.qml"};
                        if (dash3.currentIndex == "3") {thirdPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                        if (dash3.currentIndex == "4") {thirdPageLoader.source = "qrc:/Gauges/Userdash1.qml"};
                        if (dash3.currentIndex == "5") {thirdPageLoader.source = "qrc:/Gauges/Userdash2.qml"};
                        if (dash3.currentIndex == "6") {thirdPageLoader.source = "qrc:/Gauges/Userdash3.qml"};
                        if (dash3.currentIndex == "7") {thirdPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                        //if (dash3.currentIndex == "8") {thirdPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                        if (dash3.currentIndex == "8"){thirdPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                        if (dash3.currentIndex == "9"){thirdPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};
                        if (dash3.currentIndex == "10") {thirdPageLoader.source = "qrc:/Gauges/SpeedMeasurements.qml"};


                    }
                }
                Item {
                    id: select4
                    function selDash4()
                    {
                        if (dash4.currentIndex == "0") {fourthPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                        if (dash4.currentIndex == "1") {fourthPageLoader.source = "qrc:/Gauges/GPS.qml"};
                        if (dash4.currentIndex == "2") {fourthPageLoader.source = "qrc:/GPSTracks/Laptimer.qml"};
                        if (dash4.currentIndex == "3") {fourthPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                        if (dash4.currentIndex == "4") {fourthPageLoader.source = "qrc:/Gauges/Userdash1.qml"};
                        if (dash4.currentIndex == "5") {fourthPageLoader.source = "qrc:/Gauges/Userdash2.qml"};
                        if (dash4.currentIndex == "6") {fourthPageLoader.source = "qrc:/Gauges/Userdash3.qml"};
                        if (dash4.currentIndex == "7") {fourthPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                        //if (dash4.currentIndex == "8") {fourthPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                        if (dash4.currentIndex == "8") {fourthPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                        if (dash4.currentIndex == "9") {fourthPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};
                        if (dash4.currentIndex == "10") {fourthPageLoader.source = "qrc:/Gauges/SpeedMeasurements.qml"};
"Main Dash","GPS", "Laptimer", "PowerFC Sensors","User Dash 1","User Dash 2","User Dash 3","G-Force","Mediaplayer","Screen Toggle","Drag Timer"
                    }
                    Component.onCompleted: tabView.currentIndex = 2 // opens the 3rd tab
                }
            }
        }
    }

    Quick1.Tab {
        title: "Sensehat" // Tab index 2
        //Sensehat Sensors
        Rectangle{

            id: senhatselector
            anchors.fill: parent
            color: "grey"

            Item {
                id: sensehatsettings
                Settings {

                    property alias accelswitch: accelsens.checked
                    property alias gyrowitch:  gyrosense.checked
                    property alias compassswitch: compass.checked
                    property alias tempswitch: tempsense.checked
                    property alias pressureswitch:pressuresens.checked

                }

                Grid {
                    rows: 6
                    columns: 2
                    spacing: senhatselector.width / 150
                    anchors.top :parent.top
                    anchors.topMargin: parent.height / 20
                    Switch {
                        id: accelsens
                        text: qsTr("Accelerometer")
                        onCheckedChanged:
                        {if (accelsens.checked == true){Sens.Accel()};
                        }

                    }
                    Switch {
                        id: gyrosense
                        text: qsTr("Gyro Sensor")
                        onCheckedChanged:
                        {

                            if (gyrosense.checked == true){Sens.Gyro()};
                        }
                    }
                    Switch {
                        id: compass
                        text: qsTr("Compass")
                        onCheckedChanged:{
                            if (compass.checked == true){Sens.Comp()};
                        }
                    }
                    Switch {
                        id: pressuresens
                        text: qsTr("Pressure Sensor")
                        onCheckedChanged:{

                            if (pressuresens.checked == true){Sens.Pressure()};
                        }
                    }
                    Switch {
                        id: tempsense
                        text: qsTr("Temperature Sensor")
                        onCheckedChanged:{

                            if (tempsense.checked == true){Sens.Temperature()};
                        }
                        Component.onCompleted: tabView.currentIndex = 3 // opens the 4th tab
                    }


                }
            }

        }
    }
    Quick1.Tab {
        title: "Warn / Gear" // Tab index 3
        //Warning Settings by Craig Shoesmith
        Rectangle{

            id: warningsettings
            anchors.fill: parent
            color: "black"

            Item {
                id: warnettings
                Settings {
                    property alias watertempwarning: watertempwarn.text
                    property alias boostwarning: boostwarn.text
                    property alias rpmwarning: rpmwarn.text
                    property alias knockwarning: knockwarn.text
                    property alias lambdamultiplier: lambdamultiply.text
                    property alias gearcalcselectswitch: gearcalcselect.checked
                    property alias gearval1: valgear1.text
                    property alias gearval2: valgear2.text
                    property alias gearval3: valgear3.text
                    property alias gearval4: valgear4.text
                    property alias gearval5: valgear5.text
                    property alias gearval6: valgear6.text
                }


                Grid {
                    id: speedcorrgrid
                    rows:3
                    columns: 5
                    spacing: warningsettings.height /150
                    Text { text: "WaterTemp"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Boost"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Revs"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Knock"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Lamda multiply"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    TextField {
                        id: watertempwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        text:  "110"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
                        onEditingFinished: Dashboard.setwaterwarn(watertempwarn.text)
                        Component.onCompleted: Dashboard.setwaterwarn(watertempwarn.text)

                    }
                    TextField {
                        id: boostwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "0.9"
                        onEditingFinished: Dashboard.setboostwarn(boostwarn.text)
                        Component.onCompleted: Dashboard.setboostwarn(boostwarn.text)
                    }
                    TextField {
                        id: rpmwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "10000"
                        onEditingFinished: Dashboard.setrpmwarn(rpmwarn.text)
                        Component.onCompleted: Dashboard.setrpmwarn(rpmwarn.text)
                    }
                    TextField {
                        id: knockwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "80"
                        onEditingFinished: Dashboard.setknockwarn(knockwarn.text)

                    }
                        TextField {
                            id: lambdamultiply
                            width: warningsettings.width / 7
                            height: warningsettings.height /15
                            font.pixelSize: warningsettings.width / 55
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            text:  "14.7"
                            onEditingFinished: Dashboard.setLambdamultiply(lambdamultiply.text)
                            Component.onCompleted: Dashboard.setLambdamultiply(lambdamultiply.text),tabView.currentIndex = 4; // opens the 5th tab
                        }

                }

            }
            Rectangle{
                id: gearsettings
                width: parent.width
                height: parent.height /2
                y:parent.height /5
                color: "transparent"
                Grid {
                    id: geargrid
                    rows:3
                    columns: 7
                    spacing: warningsettings.height /150

                    Text {id: switchtext
                        text: "Gear Calc"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Gear1"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Gear2"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Gear3"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Gear4"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Gear5"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Gear6"
                        font.pixelSize: warningsettings.width / 55;color:"white"}


                    Switch {
                        id: gearcalcselect
                        width: warningsettings.width / 5
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55

                        Component.onCompleted: if (gearcalcselect.checked == true){Dashboard.setgearcalcactivation(1),switchtext.text = "Gear Calulation ON";}else{Dashboard.setgearcalcactivation(0),switchtext.text = "Gear Calulation OFF";}
                        onCheckedChanged: if (gearcalcselect.checked == true){Dashboard.setgearcalcactivation(1),switchtext.text = "Gear Calulation ON";}else{Dashboard.setgearcalcactivation(0),switchtext.text = "Gear Calulation OFF";}
                    }

                    TextField {
                        id: valgear1
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "120"
                        onEditingFinished: Dashboard.setgearcalc1(valgear1.text)
                        Component.onCompleted: Dashboard.setgearcalc1(valgear1.text)
                    }
                    TextField {
                        id: valgear2
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "74"
                        onEditingFinished: Dashboard.setgearcalc2(valgear2.text)
                        Component.onCompleted: Dashboard.setgearcalc2(valgear2.text)
                    }
                    TextField {
                        id: valgear3
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "54"
                        onEditingFinished: Dashboard.setgearcalc3(valgear3.text)
                        Component.onCompleted: Dashboard.setgearcalc3(valgear3.text)
                    }
                    TextField {
                        id: valgear4
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "37"
                        onEditingFinished: Dashboard.setgearcalc4(valgear4.text)
                        Component.onCompleted: Dashboard.setgearcalc4(valgear4.text)
                    }
                    TextField {
                        id: valgear5
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  "28"
                        onEditingFinished: Dashboard.setgearcalc5(valgear5.text)
                        Component.onCompleted: Dashboard.setgearcalc5(valgear5.text)
                    }
                    TextField {
                        id: valgear6
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        text:  ""
                        onEditingFinished: Dashboard.setgearcalc6(valgear6.text)
                        Component.onCompleted: Dashboard.setgearcalc6(valgear6.text)
                    }

                }
            }
        }
    }
    Quick1.Tab {
        title: "Speed" // Tab index 4
        Rectangle{
            id: calcs
            anchors.fill : parent
            color: "grey"

            Item {
                id: speedcorretionsettings
                Settings {
                    property alias speedpercentsetting: speedpercent.text
                }
            }
            Grid {
                rows:2
                columns: 1
                id: grid
                spacing: calcs.height /150
                Text { text: "Speed Correction %"
                    font.pixelSize: calcs.width / 55;color:"white"}
                TextField {
                    id: speedpercent
                    width: calcs.width / 5
                    height: calcs.height /15
                    font.pixelSize: calcs.width / 55
                    text:  "100"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
                    Component.onCompleted: {Dashboard.setspeedpercent(speedpercent.text /100);
                                            tabView.currentIndex = 5;}
                    onEditingFinished: Dashboard.setspeedpercent(speedpercent.text /100)
                }
            }
        }
    }

    Quick1.Tab {
        id:regtab
        title: ""// Tab index 5
        visible: false
        Rectangle {
            id: backround1
            anchors.fill: parent
            Loader {anchors.fill: backround1
                id: pageLoader }

            function loadersource()
            {
                //console.log(Dashboard.ecu)
                if(Dashboard.ecu == "0"){
                    pageLoader.source = "qrc:/AnalogInputs.qml"
                    //pageLoader.source ="qrc:/ExBoardAnalog.qml"
                    regtab.title = "Analog";}
                if(Dashboard.ecu == "1"){
                    pageLoader.source = "qrc:/AnalogInputs.qml"
                    //pageLoader.source ="qrc:/ExBoardAnalog.qml"
                    regtab.title = "Analog";}
                if(Dashboard.ecu == "2"){
                    pageLoader.source = "qrc:/ConsultRegs.qml"
                    regtab.title = "Consult";}
                if(Dashboard.ecu == "3"){
                pageLoader.source = "qrc:/OBDPIDS.qml"
                regtab.title = "OBD";}
                //else pageLoader.source = "qrc:/AnalogInputs.qml",regtab.title = "Analog";
            }
            Component.onCompleted: {
                loadersource()
                tabView.currentIndex++;
            }
            Connections{
                target: Dashboard
                onEcuChanged :{loadersource()}
            }
        }


    }
    Quick1.Tab {
        title: "RPM" //
        Rectangle{
            id: rpmSettings
            anchors.fill : parent
            color: "grey"

            Item {
                Settings {
                    property alias maxrpm: maxRPM.text
                    property alias shift1: stage1.text
                    property alias shift2: stage2.text
                    property alias shift3: stage3.text
                    property alias shift4: stage4.text

                }

            }

            Grid {

                rows:2
                columns: 5
                spacing: 5
                Text { text: "MAX RPM"
                    font.pixelSize: rpmSettings.width / 55;color:"white"}
                Text { text: "Shift Light 1 (g)"
                    font.pixelSize: rpmSettings.width / 55;color:"white"}
                Text { text: "Shift Light 2 (g)"
                    font.pixelSize: rpmSettings.width / 55;color:"white"}
                Text { text: "Shift Light 3 (y)"
                    font.pixelSize: rpmSettings.width / 55;color:"white"}
                Text { text: "Shift Light 4 (r)"
                    font.pixelSize: rpmSettings.width / 55;color:"white"}
                TextField {
                    id: maxRPM
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "10000"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
                    onEditingFinished: Dashboard.setmaxRPM(maxRPM.text)
                    Component.onCompleted: Dashboard.setmaxRPM(maxRPM.text)
                }
                TextField {
                    id: stage1
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "3000"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onEditingFinished:Dashboard.setrpmStage1(stage1.text)
                    Component.onCompleted:Dashboard.setrpmStage1(stage1.text)
                }
                TextField {
                    id: stage2
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "5500"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onEditingFinished:Dashboard.setrpmStage2(stage2.text)
                    Component.onCompleted:Dashboard.setrpmStage2(stage2.text)
                }
                TextField {
                    id: stage3
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "5500"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onEditingFinished:Dashboard.setrpmStage3(stage3.text)
                    Component.onCompleted:Dashboard.setrpmStage3(stage3.text)

                }
                TextField {
                    id: stage4
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "7500"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onEditingFinished: Dashboard.setrpmStage4(stage4.text)
                    Component.onCompleted: Dashboard.setrpmStage4(stage4.text),tabView.currentIndex++;
                }
            }
        }
    }

    Quick1.Tab {
        title: "EX Board" // Tab index 6
        Rectangle{
            id: exboard
            anchors.fill : parent
            color: "grey"
            ExBoardAnalog{}
            Component.onCompleted: {

            tabView.currentIndex++;
           // console.log("switch tab index ")
            }
        }


    }



    Quick1.Tab {
        title: "Startup"// Tab index 8

        Rectangle{
            id: daemons
            anchors.fill: parent
            color: "grey"

            Item {
                id: startupsettings
                Settings {
                    property alias mainspeedsource : mainspeedsource.currentIndex
                    property alias daemonselect : daemonselect.currentIndex
                    property alias bitrateselect :canbitrateselect.currentIndex
                }
            }

            Grid {
                id:startupgrid
                anchors.top :parent.top
                anchors.topMargin: parent.height / 20
                anchors.right: parent.right
                rows: 10
                columns: 2
                spacing: parent.width /150
                Text { text: "Apply Settings :"
                    font.pixelSize: daemons.width / 55 }
                Button {
                    id: apply
                    width: daemons.width / 3
                    height: daemons.height /15
                    text: "apply"
                    onClicked: {Connect.daemonstartup(daemonselect.currentIndex)
                                Connect.canbitratesetup(canbitrateselect.currentIndex)
                                }


                }


                /*
                Text { text: "Remove screen rotate :"
                    font.pixelSize: daemons.width / 55 }
                Button {
                    id: rotate
                    width: daemons.width / 5
                    height: daemons.height /15
                    text: "screen fix"
                    onClicked: Connect.turnscreen();
                }*/
                Text { text: "Start up Daemon :"
                    font.pixelSize: daemons.width / 55 }
                ComboBox {
                    id: daemonselect
                    width: daemons.width / 3
                    height: daemons.height /15
                    font.pixelSize: daemons.width / 55
                    model: [ "None","HaltechV2","Link Generic Dash","Microtech","Consult","M800 Set1","OBD2","Hondata (KPRO)","Adaptronic CAN","Motec M1","AEM V2","AUDI B7","BRZ FRS 86","ECU Masters","Audi B8","Emtron","Holley","MaxxECU","Ford FG MK1","Ford FG MK1 + OBD Polling","Ford BA+BF ","Ford BA+BF + OBD Polling","Ford FG2x","Ford FG2x + OBD Polling","EVO X","Blackbox M3","NISSAN 370Z","GM: LS2-LS7 CAN","NISSAN 350Z","Megasquirt CAN Simplified","EMTECH EMS CAN","WRX 2008-2015","Motec Set3 ADL","Testdaemon","Ecoboost","Emerald ECU","Wolf","GM OBD-CAN","Extension Board","Hondata (S300)","11-Bit CAN","Motorsport Electronics","Fueltech","Delta","Bigstuff AFR","Bigstuff Lamda","R35","Prado","WRX 2016","LifeRacing beta","DTAFast","ProEFI","TeslaSDU","NeuroBasic"]
                    delegate: ItemDelegate {
                        width: daemonselect.width
                        text: daemonselect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: daemonselect.currentIndex == index ? Font.DemiBold : Font.Normal
                        font.family: daemonselect.font.family
                        font.pixelSize: daemonselect.font.pixelSize
                        highlighted: daemonselect.highlightedIndex == index
                        hoverEnabled: daemonselect.hoverEnabled
                    }
                    onCurrentIndexChanged: autochangecanspeed.start();
                    //Component.onCompleted: tabView.currentIndex = 0;
                }
                Text { text: "CAN Bitrate :"
                    font.pixelSize: daemons.width / 55 }
                ComboBox {
                    id: canbitrateselect
                     width: daemons.width / 3
                    height: daemons.height /15
                    font.pixelSize: daemons.width / 55
                    model: [ "250 kbit/s","500 kbit/s","1 Mbit/s"]
                    delegate: ItemDelegate {
                        width: canbitrateselect.width
                        text: canbitrateselect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: canbitrateselect.currentIndex == index ? Font.DemiBold : Font.Normal
                        font.family: canbitrateselect.font.family
                        font.pixelSize: canbitrateselect.font.pixelSize
                        highlighted: canbitrateselect.highlightedIndex == index
                        hoverEnabled: canbitrateselect.hoverEnabled
                    }
                    //Component.onCompleted: tabView.currentIndex = 0;
                }
                Item {
                    //Function to automatically change can speeds
                    id: autochangecanspeed
                    function start()
                    {
                        //if (daemonselect.textAt(daemonselect.currentIndex) == "OBD2"|| daemonselect.textAt(daemonselect.currentIndex) == "AUDI B7"|| daemonselect.textAt(daemonselect.currentIndex) == "BRZ FRS 86"|| daemonselect.textAt(daemonselect.currentIndex) =="Audi B8"|| daemonselect.textAt(daemonselect.currentIndex) == "Barra FG MK1"|| daemonselect.textAt(daemonselect.currentIndex) =="Barra FG MK1 + OBD Polling"||daemonselect.textAt(daemonselect.currentIndex) =="Barra BX "||daemonselect.textAt(daemonselect.currentIndex) =="Barra BX + OBD Polling"||daemonselect.textAt(daemonselect.currentIndex) =="Barra FG2x" || daemonselect.textAt(daemonselect.currentIndex) =="Barra FG2x + OBD Polling"||daemonselect.textAt(daemonselect.currentIndex)== "EVO X Test"||"NISSAN 370Z Test"||daemonselect.textAt(daemonselect.currentIndex) =="GM: LS2-LS7 CAN"||daemonselect.textAt(daemonselect.currentIndex) == "NISSAN 350Z Test")
                        //if (daemonselect.textAt(daemonselect.currentIndex) == "OBD2")
                        switch(daemonselect.textAt(daemonselect.currentIndex))
                        {
                        case "OBD2":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "AUDI B7":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "BRZ FRS 86":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Audi B8":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Ford FG MK1":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Ford FG MK1 + OBD Polling":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Ford BX ":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Ford BX + OBD Polling":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Ford FG2x":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Ford FG2x + OBD Polling":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "EVO X Test":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "NISSAN 370Z Test":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "GM: LS2-LS7 CAN":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "NISSAN 350Z Test":canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Subaru Test":canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "11-Bit CAN":
                            canbitrateselect.currentIndex = 1 // 500 Kbs
                            break;
                        case "Motorsport Electronics":
                            canbitrateselect.currentIndex = 2 // 1Mbit
                            break;
                        case "Fueltech":
                            canbitrateselect.currentIndex = 2 // 1Mbit
                            break;
                        default:
                        canbitrateselect.currentIndex = 2 // 1Mbit
                        break;
                        }
                    }
                }
                Text { text: "Main Speed Source :"
                    font.pixelSize: daemons.width / 55 }
                ComboBox {
                    id: mainspeedsource
                    width: daemons.width / 3
                    height: daemons.height /15
                    font.pixelSize: daemons.width / 55
                    model: ["ECU Speed","LF Wheelspeed","RF Wheelspeed","LR Wheelspeed","RR Wheelspeed","GPS"]
                    onCurrentIndexChanged: Dashboard.setExternalSpeed(mainspeedsource.currentIndex)//,console.log("Setting SPeed")
                    property bool initialized: false
                    Component.onCompleted: tabView.currentIndex = 0;
                    delegate: ItemDelegate {
                        width: mainspeedsource.width
                        text: mainspeedsource.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: mainspeedsource.currentIndex == index ? Font.DemiBold : Font.Normal
                        font.family: mainspeedsource.font.family
                        font.pixelSize: mainspeedsource.font.pixelSize
                        highlighted: mainspeedsource.highlightedIndex == index
                        hoverEnabled: mainspeedsource.hoverEnabled
                    }
                }

            }
            Text {
                id:warningtext
                text: "DO NOT SELECT ANY START UP DAEMON THAT INCLUDES OBD/OBD2 WHILST TUNING YOUR VEHICLE or working with the ECU/PCM. PowerTune Digital users MUST disable OBD polling when tuning or performing any task related to the ECU/PCM by changing the start up daemon above to a NON OBD/OBD2 option and pressing apply, or disconnecting the dash entirely whilst tuning or working with any vehicle electronics. PowerTune Digital assumes no liability for damage to your vehicle/ECU/PCM if polling OBD data at the same time as another device causes an interruption, or for any other reason. Refer to our warranty at https://www.powertunedigital.com/pages/manual "
                font.pixelSize: daemons.width / 55
                font.bold: true
                width: parent.width /1.5
                horizontalAlignment: Text.AlignHCenter
                anchors.top: startupgrid.bottom
                anchors.horizontalCenter: daemons.horizontalCenter
                color: "red"
                wrapMode: Text.WordWrap
                //visible: { (daemonselect.currentIndex == 19 || daemonselect.currentIndex == 21 || daemonselect.currentIndex == 23 ) ? true:false; }
            }
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////
    Quick1.Tab {
        title: "Network"// Tab index 9

        Rectangle{
            id: extrarect
            anchors.fill: parent
            color: "grey"
            Connections{
                target: Dashboard
                onSerialStatChanged : {
                    consoleText.append(Dashboard.SerialStat);
                    //console.log(Dashboard.SerialStat);
                 scrollBar.increase();
                }
            }
            WifiCountryList{id: wificountrynames}

            Settings {
                property alias wificountryindex: wificountrycbx.currentIndex
                      }

            Flickable {
                id: flickable
                width: 450
                height: 400

                TextArea.flickable: TextArea {
                    id : consoleText
                    wrapMode: TextArea.Wrap
                    readOnly: true
                    color: "green"
                    font.pixelSize: 15
                    background: Rectangle {
                        height:flickable.height
                        width: flickable.width
                        color: "black"
                    }
                }

                ScrollBar.vertical: ScrollBar { id:scrollBar
                policy: ScrollBar.AlwaysOn}
            }

            Grid {
                id:extragrid
                anchors.top :parent.top
                anchors.topMargin: parent.height / 20
                anchors.right: parent.right
                rows: 12
                columns: 2
                spacing: parent.width /150


                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }
                Button {
                    id: btnScanNetwork
                   // visible: false
                    text: "Scan WIFI"
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    onClicked: {
                                consoleText.clear();
                                Wifiscanner.initializeWifiscanner();
                                //btnScanNetwork.enabled =false;
                        }
                }
                Text { text: "WIFI Country :"
                    font.pixelSize: extrarect.width / 55 }
                ComboBox {
                    id: wificountrycbx
                    //visible: false
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    model: wificountrynames
                    textRole: "name"
                    property bool initialized: true
                }
                Text { text: "Wifi 1 :"
                    font.pixelSize: extrarect.width / 55 }
                ComboBox {
                    id: wifilistbox
                    //visible: false
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    model: Dashboard.wifi
                    onCountChanged: btnScanNetwork.enabled =true;
                    property bool initialized: false
                    delegate: ItemDelegate {
                        width: wifilistbox.width
                        text: wifilistbox.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: wifilistbox.currentIndex == index ? Font.DemiBold : Font.Normal
                        font.family: wifilistbox.font.family
                        font.pixelSize: wifilistbox.font.pixelSize
                        highlighted: wifilistbox.highlightedIndex == index
                        hoverEnabled: wifilistbox.hoverEnabled
                    }
                }
                Text {

                    text: "Password 1:"
                    font.pixelSize: extrarect.width / 55 }
                TextField {
                    id: pw1
                    placeholderText: qsTr("Passphrase")
                    width: extrarect.width / 5
                    font.pixelSize: extrarect.width / 55 }
                /*
                Text { text: "Wifi 2 :"
                    //visible: false
                    font.pixelSize: extrarect.width / 55 }
                ComboBox {
                    id: wifilistbox2
                    //visible: false
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    model: Dashboard.wifi
                    onCountChanged: btnScanNetwork.enabled =true;
                    property bool initialized: false
                    delegate: ItemDelegate {
                        width: wifilistbox2.width
                        text: wifilistbox2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: wifilistbox2.currentIndex == index ? Font.DemiBold : Font.Normal
                        font.family: wifilistbox2.font.family
                        font.pixelSize: wifilistbox2.font.pixelSize
                        highlighted: wifilistbox2.highlightedIndex == index
                        hoverEnabled: wifilistbox2.hoverEnabled
                    }
                }
                Text {
                    text: "Password :"
                    font.pixelSize: extrarect.width / 55 }
                TextField {
                    id: pw2
                    placeholderText: qsTr("Passphrase")
                    width: extrarect.width / 5
                    font.pixelSize: extrarect.width / 55 }*/

                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }

                Button {
                    id: applyWifiSettings
                    text: "Connect WIFI"
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    Component.onCompleted: {

                        //Wifiscanner.findActiveWirelesses();
                        Wifiscanner.initializeWifiscanner();
                    }
                    onClicked: {
                        //Wifiscanner.setwifi(wificountrynames.get(wificountrycbx.currentIndex).countryname,wifilistbox.textAt(wifilistbox.currentIndex),pw1.text,wifilistbox2.textAt(wifilistbox2.currentIndex),pw2.text );
                        Wifiscanner.setwifi(wificountrynames.get(wificountrycbx.currentIndex).countryname,wifilistbox.textAt(wifilistbox.currentIndex),pw1.text,"placeholder","placeholder" );
                        Connect.reboot();
                    }
                }

                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }
                Button {
                    id: updateBtn
                    text: "Update"
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    onClicked: {
                                Connect.update();
                                updateBtn.enabled =false;
                        }
                }


                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }

                Button {
                    id: develtest
                    text: "Restart daemon"
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55

                    onClicked: {

                    //Arduino.openConnection("COM11");
                    Connect.restartDaemon();
                    //develtest.enabled = false;
                    }
                }
                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }
                Button {
                    id: trackUpdate
                    text: "Update Tracks"
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    onClicked: {
                    downloadManager.append(""); // needed as a workarround
                    downloadManager.append("https://gitlab.com/PowerTuneDigital/PowertuneTracks/-/raw/main/repo.txt");
                    downloadManager.append(""); // needed as a workarround
                    consoleText.append("Downloading Tracks for Laptimer :");
                    trackUpdate.enabled = false;
                    downloadprogress.indeterminate = true;
                    }
                }
                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }
                Quick1.ProgressBar {
                    id: downloadprogress
                    width: extrarect.width / 5
                    height: extrarect.height /15

                }
                Text {
                    id: ethernetip
                    text: "Ethernet IP adress :"
                    font.pixelSize: extrarect.width / 55
                    visible: true

                    }

                Quick1.Button {
                    id: ethernetstatus
                    text: Dashboard.EthernetStat
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    style: ButtonStyle {
                        label: Label {
                            text: ethernetstatus.text
                            color: "black"
                            font.pixelSize: extrarect.width / 55
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: { (ethernetstatus.text == "NOT CONNECTED") ? "red": "green"; }
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"

                            }
                        }
                    }

                Text {
                    id: wlanip
                    text: "WLAN IP adress :"
                    font.pixelSize: extrarect.width / 55
                    visible: true

                    }
                Quick1.Button {
                    id: wifistatus
                    text: Dashboard.WifiStat
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    style: ButtonStyle {
                        label: Label {
                            text: wifistatus.text
                            color: "black"
                            font.pixelSize: extrarect.width / 55
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: { (wifistatus.text == "NOT CONNECTED") ? "red": "green"; }
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#888"
                            }
                        }
                    }
                Text { text: " "
                    font.pixelSize: extrarect.width / 55 }
                Text {
                    id: downloadspeedtext
                    text: downloadManager.downloadStatus
                    font.pixelSize: extrarect.width / 55
                    onTextChanged: {
                        if(downloadspeedtext.text == "Finished")
                        {
                            //trackUpdate.enabled = true;
                            downloadprogress.indeterminate = false;
                            downloadspeedtext.text = " ";
                            Connect.changefolderpermission();

                        }
                    }
                    }
                Text {
                    id: downloadfilenametext
                    text: downloadManager.downloadFilename
                    font.pixelSize: extrarect.width / 55
                    visible: false
                    onTextChanged: consoleText.append(downloadManager.downloadFilename);
                    }

/*

                Button {
                    id: develtest1
                    text: "Development dont click"
                    width: extrarect.width / 5
                    height: extrarect.height /15
                    font.pixelSize: extrarect.width / 55
                    onClicked: Connect.canbitratesetup(0)

                }*/
            }
        }
    }

}
