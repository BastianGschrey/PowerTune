import QtQuick 2.8
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import Qt.labs.settings 1.0
import QtQuick.VirtualKeyboard 2.1
import QtSensors 5.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8

TabView {
    id: tabView
    anchors.fill: parent

    style: TabViewStyle {
        frameOverlap: 1
        tab: Rectangle {
            color: styleData.selected ? "grey" :"lightgrey"
            border.color:  "steelblue"
            implicitWidth: Math.max(text.width + 4, 80)
            implicitHeight: 20
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
    Tab {
        title: "Main"
        anchors.fill: parent
        Rectangle {
            id: windowbackround
            anchors.fill: parent
            color: "grey"
            property  int test1: 0
            property  int connected: 0
            property  var gpscom

            Item {
                id: powerTuneSettings
                Settings {
                    property alias brightnessselect: brightness.value
                    property alias connectAtStartUp: connectAtStart.checked
                    property alias gpsswitch: gpsswitch.checked
                    property alias serialPortName: serialName.currentText
                    property alias gpsPortName: serialNameGPS.currentText
                    property alias gpsPortNameindex: serialNameGPS.currentIndex
                    property alias gpsBaud: serialGPSBaud.currentText
                    property alias gpsBaudindex: serialGPSBaud.currentIndex
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
                    property alias unitSelector: unitSelect.currentIndex
                    property alias odometervalue: odometer.text
                    property alias tripmetervalue: tripmeter.text
                    property alias protocol : protocol.currentIndex

                }
                SoundEffect {
                    id: warnsound
                    source: "qrc:/Sounds/alarm.wav"
                }

                Connections{
                    target: Dashboard
                    onOdoChanged:{odometer.text = (Dashboard.Odo).toFixed(0) }
                    onTripChanged:{tripmeter.text = (Dashboard.Trip).toFixed(1) }
                    onWatertempChanged: { if (Dashboard.Watertemp > Dashboard.waterwarn) {playwarning.start()};}
                    onRpmChanged: { if (Dashboard.rpm > Dashboard.rpmwarn) {playwarning.start()};}
                    onKnockChanged: { if (Dashboard.Knock > Dashboard.knockwarn) {playwarning.start()};}
                    onBoostPresChanged: { if (Dashboard.BoostPres > Dashboard.boostwarn) {playwarning.start()};}
                    onSupportedRegChanged: {functsupportedRegs.supportedRegs() }
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
                            visible: { (ecuSelect.currentIndex >= "5") ? false: true; }
                        }
                        ComboBox {
                            id: serialName
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: Connect.portsNames
                            visible: { (ecuSelect.currentIndex >= "5") ? false: true; }
                            property bool initialized: false
                            onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                            Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true; autoconnect.auto(); }
                            delegate: ItemDelegate {
                                width: serialName.width
                                text: serialName.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: serialName.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: serialName.font.family
                                font.pixelSize: serialName.font.pixelSize
                                highlighted: serialName.highlightedIndex === index
                                hoverEnabled: serialName.hoverEnabled
                            }
                        }
                        Text {
                            text: "GPS Port: "
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                            visible: { (gpsswitch.checked == true ) ? true:false; }
                        }
                        ComboBox {
                            id: serialNameGPS
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: Connect.portsNames
                            visible: { (gpsswitch.checked == true ) ? true:false; }
                            delegate: ItemDelegate {
                                width: serialNameGPS.width
                                text: serialNameGPS.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: serialNameGPS.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: serialNameGPS.font.family
                                font.pixelSize: serialNameGPS.font.pixelSize
                                highlighted: serialNameGPS.highlightedIndex === index
                                hoverEnabled: serialNameGPS.hoverEnabled
                            }

                        }
                        Text {
                            text: "GPS Baud: "
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                            visible: { (gpsswitch.checked == true ) ? true:false; }
                        }
                        ComboBox {
                            id: serialGPSBaud
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: [ "2400", "4800", "9600", "14400", "19200", "38400", "57600", "115200"]
                            visible: { (gpsswitch.checked == true ) ? true:false; }
                            Component.onCompleted: {autoconnectGPS.auto()}
                            delegate: ItemDelegate {
                                width: serialGPSBaud.width
                                text: serialGPSBaud.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: serialGPSBaud.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: serialGPSBaud.font.family
                                font.pixelSize: serialGPSBaud.font.pixelSize
                                highlighted: serialGPSBaud.highlightedIndex === index
                                hoverEnabled: serialGPSBaud.hoverEnabled
                            }
                        }

                        Text {
                            text: "Display units:"
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
                                font.weight: unitSelect.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: unitSelect.font.family
                                font.pixelSize: unitSelect.font.pixelSize
                                highlighted: unitSelect.highlightedIndex === index
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
                            model: [ "PowerFC","UDP","Adaptronic Select Modbus","CAN Adaptronic Modular","Consult","HaltechV1","HaltechV2"]

                            property bool initialized: false
                            onCurrentIndexChanged: if (initialized) AppSettings.setECU( currentIndex )
                            Component.onCompleted: { currentIndex = AppSettings.getECU(); initialized = true }
                            delegate: ItemDelegate {
                                width: ecuSelect.width
                                text: ecuSelect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: ecuSelect.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: ecuSelect.font.family
                                font.pixelSize: ecuSelect.font.pixelSize
                                highlighted: ecuSelect.highlightedIndex === index
                                hoverEnabled: ecuSelect.hoverEnabled
                            }
                        }
                        Text {
                            text: "Protocol Type:"
                            font.pixelSize: windowbackround.width / 55
                            color: "white"
                            visible: { (ecuSelect.currentIndex >= "1") ? false: true; }
                        }
                        ComboBox {
                            id: protocol
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            model: [ "New", "Old"]
                            visible: { (ecuSelect.currentIndex >= "1") ? false: true; }

                            property bool initialized: false
                            onCurrentIndexChanged: {Apexi.SetProtocol(currentIndex)}
                            Component.onCompleted: {Apexi.SetProtocol(currentIndex)}
                            delegate: ItemDelegate {
                                width: protocol.width
                                text: protocol.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                                font.weight: protocol.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: protocol.font.family
                                font.pixelSize: protocol.font.pixelSize
                                highlighted: protocol.highlightedIndex === index
                                hoverEnabled: protocol.hoverEnabled
                            }
                        }
                        /*
                Text {
                    id: textloggingSelect
                    visible: { (ecuSelect.currentIndex >= "1") ? false: true; }
                    text: "Log Raw Messages:"

                }
                ComboBox {
                    id: loggerSelect
                    visible: { (ecuSelect.currentIndex >= "1") ? false: true; }
                    width: windowbackround.width / 5
                    height: windowbackround.height /15
                    font.pixelSize: windowbackround.width / 55
                    model: [ "OFF", "ON"]
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setLogging( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getLogging(); initialized = true }
                }
*/
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
                                font.weight: goProSelect.currentIndex === index ? Font.DemiBold : Font.Normal
                                font.family: goProSelect.font.family
                                font.pixelSize: goProSelect.font.pixelSize
                                highlighted: goProSelect.highlightedIndex === index
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
                            inputMethodHints: Qt.ImhDigitsOnly
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
                            inputMethodHints: Qt.ImhDigitsOnly

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
                                //consultset.enabled = true;
                                functdisconnect.disconnectfunc();
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
                            onClicked: { Qt.quit()}
                        }
                        Button {
                            text: "Shutdown"
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            onClicked: {Connect.shutdown()}
                        }

                        Switch {
                            id: connectAtStart
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            text: qsTr("Autoconnect")
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
                        }
                        Switch {
                            id: gpsswitch
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            font.pixelSize: windowbackround.width / 55
                            text: qsTr("GPS")
                            onCheckedChanged: {autoconnectGPS.auto()}
                        }

                        Slider {
                            id:brightness
                            width: windowbackround.width / 5
                            height: windowbackround.height /15
                            stepSize: 5
                            from: 20
                            to: 255
                            //value: brightnessselect
                            visible: Dashboard.screen
                            Component.onCompleted: Connect.setSreenbrightness(brightness.value),tabView.currentIndex = 1; // opens the 2nd tab
                            onPositionChanged: Connect.setSreenbrightness(brightness.value);
                        }

                        Grid {
                            visible: { (ecuSelect.currentIndex >= "1") ? false: true; }
                            rows: 10
                            columns: 4
                            spacing: windowbackround.width / 150
                            //Just a spacer for now still need to do it properly
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
                                validator: IntValidator {bottom: 0; top: 1000;}
                                inputMethodHints: Qt.ImhDigitsOnly
                                placeholderText: qsTr("9")
                            }
                            TextField {
                                id: an2V5
                                width: windowbackround.width / 10
                                height: windowbackround.height /15
                                font.pixelSize: windowbackround.width / 55
                                validator: IntValidator {bottom: 0; top: 1000;}
                                inputMethodHints: Qt.ImhDigitsOnly
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
                                validator: IntValidator {bottom: 0; top: 1000;}
                                inputMethodHints: Qt.ImhDigitsOnly
                                placeholderText: qsTr("Value @ 0V")

                            }
                            TextField {
                                id: an4V5
                                width: windowbackround.width / 10
                                height: windowbackround.height /15
                                font.pixelSize: windowbackround.width / 55
                                validator: IntValidator {bottom: 0; top: 1000;}
                                inputMethodHints: Qt.ImhDigitsOnly
                                placeholderText: qsTr("Value @ 5V")
                            }
                            TextField {
                                id: unitaux2
                                width: windowbackround.width / 10
                                height: windowbackround.height /15
                                font.pixelSize: windowbackround.width / 55
                                placeholderText: qsTr("AFR")
                            }
                            Text  { text: "AN3-4";font.pixelSize: windowbackround.width / 55}
                            /*
                    Text  { text: "AN5-AN6"; windowbackround.width /12;visible: { (interfaceSelect.currentIndex == "1") ? true: false; }}
                    TextField {
                        id: an5V0
                        windowbackround.width /12
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: an6V5
                        windowbackround.width /12
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: unitaux3
                        windowbackround.width /12
                        placeholderText: qsTr("AFR")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    Text  { text: "AN7-AN8"; windowbackround.width /12;visible: { (interfaceSelect.currentIndex == "1") ? true: false; }}
                    TextField {
                        id: an7V0
                        windowbackround.width /12
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: an8V5
                        windowbackround.width /12
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: unitaux4
                        windowbackround.width /12
                        placeholderText: qsTr("AFR")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
*/
                        }

                    }
                }
            }

            //Functions
            Item {
                //Function to automatically connect at Startup , function is called from COmbobox Serialname component.oncompleted
                id: autoconnect
                function auto()
                {
                    // if (connectAtStart.checked == true) Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, interfaceSelect.currentIndex, loggerSelect.currentIndex);
                    if (connectAtStart.checked == true) functconnect.connectfunc(),connectButton.enabled =false,ecuSelect.enabled = false,disconnectButton.enabled = true;//Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, loggerSelect.currentIndex,logger.datalogger()),
                }
            }
            Item {
                //Function to connect and disconnect GPS
                id: autoconnectGPS
                function auto()
                {

                    if (gpsswitch.checked == true)GPS.startGPScom(serialNameGPS.currentText);
                    if (gpsswitch.checked == false)GPS.stopGPScom();
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
                    //Nissanconsult.LiveReqMsg(consRPM.checkState,consRPMREF.checkState,consMAFVolt.checkState,consRHMAFVolt.checkState,consCoolantTemp.checkState,consLHO2Volt.checkState,consRHO2Volt.checkState,consSpeed.checkState,consBattvolt.checkState,consTPS.checkState,consFuelTemp.checkState,consIAT.checkState,consEGT.checkState,consDigitalBitReg.checkState,consInjectTimeLH.checkState,consIGNTiming.checkState,consAACValve.checkState,consAFALPHALH.checkState,consAFALPHARH.checkState,consAFALPHASELFLEARNLH.checkState,consAFALPHASELFLEARNRH.checkState,consDigitalControlReg1.checkState,consDigitalControlReg2.checkState,consMRFCMNT.checkState,consInjecttimeRH.checkState,consWasteGate.checkState,consMAPVolt.checkState,consEngineMount.checkState,consPositionCounter.checkState);
                    Connect.openConnection(serialName.currentText, ecuSelect.currentIndex ,weight.currentText);
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
                    Connect.closeConnection(),GPS.stopGPScom();
                    connected = 0;
                }
            }
            Item {   //Function for Consult to show only supported Regs
                id: functsupportedRegs
                function supportedRegs()
                {
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

            Item {
                //Function to play warning sound
                id: playwarning
                function start()
                {

                    if (warnsound.playing == false) warnsound.play();
                }
            }
            // Virtual Keyboard


            InputPanel {
                id: keyboard;
                y: windowbackround.height; // position the top of the keyboard to the bottom of the screen/display

                anchors.left: windowbackround.left;
                anchors.right: windowbackround.right;


                states: State {
                    name: "visible";
                    when: keyboard.active;
                    PropertyChanges {
                        target: keyboard;
                        // position keyboard on top of the screen
                        y: 0 ;
                    }
                }
                transitions: Transition {
                    from: ""; // default initial state
                    to: "visible";
                    reversible: true; // toggle visibility with reversible: true;
                    ParallelAnimation {
                        NumberAnimation {
                            properties: "y";
                            duration: 250;
                            easing.type: Easing.InOutQuad;
                        }
                    }
                }
            }
        }
    }
    Tab {
        title: "Dash Select"
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

                }

                Grid {
                    rows: 2
                    columns: 4
                    anchors.top: parent.top
                    anchors.topMargin: dashselector.height /120
                    spacing: dashselector.width / 150
                    Text { text: "Dash1"
                        font.pixelSize: dashselector.width / 55 }
                    Text { text: "Dash2"
                        font.pixelSize: dashselector.width / 55}
                    Text { text: "Dash3"
                        font.pixelSize: dashselector.width / 55}
                    Text { text: "Dash4"
                        font.pixelSize: dashselector.width / 55}
                    ComboBox {
                        id: dash1
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech","Mediaplayer","Screentoggle"]
                        property bool initialized: true
                        onCurrentIndexChanged:{select1.selDash1() }
                        Component.onCompleted: {select1.selDash1() }
                        delegate: ItemDelegate {
                            width: dash1.width
                            text: dash1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash1.currentIndex === index ? Font.DemiBold : Font.Normal
                            font.family: dash1.font.family
                            font.pixelSize: dash1.font.pixelSize
                            highlighted: dash1.highlightedIndex === index
                            hoverEnabled: dash1.hoverEnabled
                        }
                    }

                    ComboBox {
                        id: dash2
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech","Mediaplayer"]
                        property bool initialized: true
                        onCurrentIndexChanged:{select2.selDash2() }
                        Component.onCompleted: {select2.selDash2() }
                        delegate: ItemDelegate {
                            width: dash2.width
                            text: dash2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash2.currentIndex === index ? Font.DemiBold : Font.Normal
                            font.family: dash2.font.family
                            font.pixelSize: dash2.font.pixelSize
                            highlighted: dash2.highlightedIndex === index
                            hoverEnabled: dash2.hoverEnabled
                        }
                    }

                    ComboBox {
                        id: dash3
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech","Mediaplayer"]
                        property bool initialized: true
                        onCurrentIndexChanged:{select3.selDash3() }
                        Component.onCompleted: {select3.selDash3() }
                        delegate: ItemDelegate {
                            width: dash3.width
                            text: dash3.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash3.currentIndex === index ? Font.DemiBold : Font.Normal
                            font.family: dash3.font.family
                            font.pixelSize: dash3.font.pixelSize
                            highlighted: dash3.highlightedIndex === index
                            hoverEnabled: dash3.hoverEnabled
                        }
                    }
                    ComboBox {
                        id: dash4
                        width: dashselector.width / 5
                        height: dashselector.height /15
                        font.pixelSize: dashselector.width / 55
                        model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech","Mediaplayer"]
                        property bool initialized: true
                        onCurrentIndexChanged:{select4.selDash4() }
                        Component.onCompleted: {select4.selDash4() }
                        delegate: ItemDelegate {
                            width: dash4.width
                            text: dash4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                            font.weight: dash4.currentIndex === index ? Font.DemiBold : Font.Normal
                            font.family: dash4.font.family
                            font.pixelSize: dash4.font.pixelSize
                            highlighted: dash4.highlightedIndex === index
                            hoverEnabled: dash4.hoverEnabled
                        }
                    }
                    //Function to select Dash1
                    Item {
                        id: select1
                        function selDash1()
                        {
                            if (dash1.currentIndex == "0") {firstPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                            if (dash1.currentIndex == "1") {firstPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
                            if (dash1.currentIndex == "2") {firstPageLoader.source = "qrc:/Gauges/Charts.qml"};
                            if (dash1.currentIndex == "3") {firstPageLoader.source = "qrc:/Gauges/GPS.qml"};
                            if (dash1.currentIndex == "4") {firstPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                            if (dash1.currentIndex == "5") {firstPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
                            if (dash1.currentIndex == "6") {firstPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
                            if (dash1.currentIndex == "7") {firstPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                            if (dash1.currentIndex == "8") {firstPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                            if (dash1.currentIndex == "9") {firstPageLoader.source = "qrc:/Gauges/Fueltechdashboard.qml"};
                            if (dash1.currentIndex == "10"){firstPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                            if (dash1.currentIndex == "11"){firstPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};



                        }

                    }
                    Item {
                        id: select2
                        function selDash2()
                        {
                            if (dash2.currentIndex == "0") {secondPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                            if (dash2.currentIndex == "1") {secondPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
                            if (dash2.currentIndex == "2") {secondPageLoader.source = "qrc:/Gauges/Charts.qml"};
                            if (dash2.currentIndex == "3") {secondPageLoader.source = "qrc:/Gauges/GPS.qml"};
                            if (dash2.currentIndex == "4") {secondPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                            if (dash2.currentIndex == "5") {secondPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
                            if (dash2.currentIndex == "6") {secondPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
                            if (dash2.currentIndex == "7") {secondPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                            if (dash2.currentIndex == "8") {secondPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                            if (dash2.currentIndex == "9") {secondPageLoader.source = "qrc:/Gauges/Fueltechdashboard.qml"};
                            if (dash2.currentIndex == "10"){secondPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                            if (dash2.currentIndex == "11"){secondPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};


                        }

                    }
                    Item {
                        id: select3
                        function selDash3()
                        {
                            if (dash3.currentIndex == "0") {thirdPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                            if (dash3.currentIndex == "1") {thirdPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
                            if (dash3.currentIndex == "2") {thirdPageLoader.source = "qrc:/Gauges/Charts.qml"};
                            if (dash3.currentIndex == "3") {thirdPageLoader.source = "qrc:/Gauges/GPS.qml"};
                            if (dash3.currentIndex == "4") {thirdPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                            if (dash3.currentIndex == "5") {thirdPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
                            if (dash3.currentIndex == "6") {thirdPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
                            if (dash3.currentIndex == "7") {thirdPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                            if (dash3.currentIndex == "8") {thirdPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                            if (dash3.currentIndex == "9") {thirdPageLoader.source = "qrc:/Gauges/Fueltechdashboard.qml"};
                            if (dash3.currentIndex == "10"){thirdPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                            if (dash3.currentIndex == "10"){thirdPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};


                        }

                    }
                    Item {
                        id: select4
                        function selDash4()
                        {
                            if (dash4.currentIndex == "0") {fourthPageLoader.source = "qrc:/Gauges/Cluster.qml"};
                            if (dash4.currentIndex == "1") {fourthPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
                            if (dash4.currentIndex == "2") {fourthPageLoader.source = "qrc:/Gauges/Charts.qml"};
                            if (dash4.currentIndex == "3") {fourthPageLoader.source = "qrc:/Gauges/GPS.qml"};
                            if (dash4.currentIndex == "4") {fourthPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
                            if (dash4.currentIndex == "5") {fourthPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
                            if (dash4.currentIndex == "6") {fourthPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
                            if (dash4.currentIndex == "7") {fourthPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};
                            if (dash4.currentIndex == "8") {fourthPageLoader.source = "qrc:/Gauges/Dyno.qml"};
                            if (dash4.currentIndex == "9") {fourthPageLoader.source = "qrc:/Gauges/Fueltechdashboard.qml"};
                            if (dash4.currentIndex == "10") {fourthPageLoader.source = "qrc:/Gauges/Mediaplayer.qml"};
                            if (dash4.currentIndex == "11") {fourthPageLoader.source = "qrc:/Gauges/Screentoggle.qml"};

                        }
                        Component.onCompleted: tabView.currentIndex = 2 // opens the 3rd tab
                    }
                }
            }
        }
    }
    Tab {
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
    Tab {
        title: "Warnings" // Tab index 3
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
                }


                Grid {
                    id: speedcorrgrid
                    rows:3
                    columns: 4
                    spacing: warningsettings.height /150
                    Text { text: "WaterTemp"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Boost"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Revs"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    Text { text: "Knock"
                        font.pixelSize: warningsettings.width / 55;color:"white"}
                    TextField {
                        id: watertempwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        text:  "110"
                        inputMethodHints: Qt.ImhDigitsOnly // this ensures valid inputs are number only
                        onEditingFinished: Dashboard.setwaterwarn(watertempwarn.text)
                        Component.onCompleted: Dashboard.setwaterwarn(watertempwarn.text)

                    }
                    TextField {
                        id: boostwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhDigitsOnly
                        text:  "0.9"
                        onEditingFinished: Dashboard.setboostwarn(boostwarn.text)
                        Component.onCompleted: Dashboard.setboostwarn(boostwarn.text)
                    }
                    TextField {
                        id: rpmwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhDigitsOnly
                        text:  "10000"
                        onEditingFinished: Dashboard.setrpmwarn(rpmwarn.text)
                        Component.onCompleted: Dashboard.setrpmwarn(rpmwarn.text)
                    }
                    TextField {
                        id: knockwarn
                        width: warningsettings.width / 10
                        height: warningsettings.height /15
                        font.pixelSize: warningsettings.width / 55
                        inputMethodHints: Qt.ImhDigitsOnly
                        text:  "80"
                        onEditingFinished: Dashboard.setknockwarn(knockwarn.text)
                        Component.onCompleted: Dashboard.setknockwarn(knockwarn.text),tabView.currentIndex = 4; // opens the 5th tab
                    }

                }
            }

            // Virtual Keyboard

            Rectangle{
                anchors.fill: parent
                color: "transparent"
                InputPanel {
                    id: keyboard2;
                    anchors.fill: parent


                    states: State {
                        name: "visible";
                        when: keyboard.active;
                        PropertyChanges {
                            target: keyboard2;
                            y: 0 ;
                        }
                    }
                    transitions: Transition {
                        from: ""; // default initial state
                        to: "visible";
                        reversible: true; // toggle visibility with reversible: true;
                        ParallelAnimation {
                            NumberAnimation {
                                properties: "y";
                                duration: 250;
                                easing.type: Easing.InOutQuad;
                            }
                        }
                    }
                }
            }

        }
    }
    Tab {
        title: "Speed" // Tab index 4
        Rectangle{
            id: calcs
            anchors.fill : parent
            color: "grey"

            Item {
                id: speedcorretionsettings
                Settings {
                    property alias speedpercentsetting: speedpercent.text
                    property alias speedplusminussetting: speedplusminus.text

                }

            }
            Grid {
                rows:2
                columns: 2
                id: grid
                spacing: calcs.height /150
                Text { text: "Speed Correction %"
                    font.pixelSize: calcs.width / 55;color:"white"}
                Text { text: "Speed + -"
                    font.pixelSize: calcs.width / 55;color:"white"}
                TextField {
                    id: speedpercent
                    width: calcs.width / 5
                    height: calcs.height /15
                    font.pixelSize: calcs.width / 55
                    text:  "100"
                    inputMethodHints: Qt.ImhDigitsOnly // this ensures valid inputs are number only
                    Component.onCompleted: Dashboard.setspeedpercent(speedpercent.text /100)
                    onEditingFinished: Dashboard.setspeedpercent(speedpercent.text /100)
                }
                TextField {
                    id: speedplusminus
                    width: calcs.width / 5
                    height: calcs.height /15
                    text:  "0"
                    font.pixelSize: calcs.width / 55
                    inputMethodHints: Qt.ImhDigitsOnly
                    Component.onCompleted: tabView.currentIndex = 6; //
                }


            }

            /*TextArea {
                anchors.top : grid.bottom
                width: calcs.width / 5
                text:
                    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, " +
                    "sed do eiusmod tempor incididunt ut labore et dolore magna " +
                    "aliqua. Ut enim ad minim veniam, quis nostrud exercitation " +
                    "ullamco laboris nisi ut aliquip ex ea commodo cosnsequat. ";
            }*/
            Rectangle{
                anchors.fill: parent
                color: "transparent"
                InputPanel {
                    id: keyboard2;
                    anchors.fill: parent
                    states: State {
                        name: "visible";
                        when: keyboard.active;
                        PropertyChanges {
                            target: keyboard2;
                            y: 0 ;
                        }
                    }
                    transitions: Transition {
                        from: ""; // default initial state
                        to: "visible";
                        reversible: true; // toggle visibility with reversible: true;
                        ParallelAnimation {
                            NumberAnimation {
                                properties: "y";
                                duration: 250;
                                easing.type: Easing.InOutQuad;
                            }
                        }
                    }
                }
            }
        }
    }
    Tab {
        title: "Consult"// Tab index 5
        //Nissan Consult requests
        Rectangle{
            id: consultrequestselect
            anchors.fill : parent
            color: "grey"
            Grid {
                rows: 10
                columns: 4

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
                Button {
                    id: supportedRegs
                    text: "Check"
                    width: consultrequestselect.width / 10
                    height: consultrequestselect.height /15
                    font.pixelSize: consultrequestselect.width / 55
                    onClicked: {
                        if (connected == 1){functdisconnect.disconnectfunc();}
                        Connect.checkReg(serialName.currentText);
                        connectButton.enabled =true;
                        ecuSelect.enabled = true;
                        disconnectButton.enabled = false;
                        supportedRegs.enabled = false;
                    }
                }
                Button {
                    id: closeconsultsettings
                    text: "Apply"
                    width: consultrequestselect.width / 10
                    height: consultrequestselect.height /15
                    font.pixelSize: consultrequestselect.width / 55
                    onClicked: {
                        supportedRegs.enabled = true;
                        Connect.LiveReqMsg(consRPM.checkState,consRPMREF.checkState,consMAFVolt.checkState,consRHMAFVolt.checkState,consCoolantTemp.checkState,consLHO2Volt.checkState,consRHO2Volt.checkState,consSpeed.checkState,consBattvolt.checkState,consTPS.checkState,consFuelTemp.checkState,consIAT.checkState,consEGT.checkState,consDigitalBitReg.checkState,consInjectTimeLH.checkState,consIGNTiming.checkState,consAACValve.checkState,consAFALPHALH.checkState,consAFALPHARH.checkState,consAFALPHASELFLEARNLH.checkState,consAFALPHASELFLEARNRH.checkState,consDigitalControlReg1.checkState,consDigitalControlReg2.checkState,consMRFCMNT.checkState,consInjecttimeRH.checkState,consWasteGate.checkState,consMAPVolt.checkState,consEngineMount.checkState,consPositionCounter.checkState,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
                    }

                }
            }
        }
    }
    Tab {
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
                    inputMethodHints: Qt.ImhDigitsOnly // this ensures valid inputs are number only
                    onEditingFinished: Dashboard.setmaxRPM(maxRPM.text)
                    Component.onCompleted: Dashboard.setmaxRPM(maxRPM.text)
                }
                TextField {
                    id: stage1
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "3000"
                    inputMethodHints: Qt.ImhDigitsOnly
                    onEditingFinished:Dashboard.setrpmStage1(stage1.text)
                    Component.onCompleted:Dashboard.setrpmStage1(stage1.text)
                }
                TextField {
                    id: stage2
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "5500"
                    inputMethodHints: Qt.ImhDigitsOnly
                    onEditingFinished:Dashboard.setrpmStage2(stage2.text)
                    Component.onCompleted:Dashboard.setrpmStage2(stage2.text)
                }
                TextField {
                    id: stage3
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "5500"
                    inputMethodHints: Qt.ImhDigitsOnly
                    onEditingFinished:Dashboard.setrpmStage3(stage3.text)
                    Component.onCompleted:Dashboard.setrpmStage3(stage3.text)

                }
                TextField {
                    id: stage4
                    width: rpmSettings.width / 5.5
                    height: rpmSettings.height /15
                    font.pixelSize: rpmSettings.width / 55
                    text:  "7500"
                    inputMethodHints: Qt.ImhDigitsOnly
                    onEditingFinished: Dashboard.setrpmStage4(stage4.text)
                    Component.onCompleted: Dashboard.setrpmStage4(stage4.text),tabView.currentIndex = 0;
                }

            }
            Rectangle{
                anchors.fill: parent
                color: "transparent"
                InputPanel {
                    id: keyboard2;
                    anchors.fill: parent
                    states: State {
                        name: "visible";
                        when: keyboard.active;
                        PropertyChanges {
                            target: keyboard2;
                            y: 0 ;
                        }
                    }
                    transitions: Transition {
                        from: ""; // default initial state
                        to: "visible";
                        reversible: true; // toggle visibility with reversible: true;
                        ParallelAnimation {
                            NumberAnimation {
                                properties: "y";
                                duration: 250;
                                easing.type: Easing.InOutQuad;
                            }
                        }
                    }
                }
            }
        }
    }
    Tab {
        title: "Apexi Dash"// Tab index 5
        Rectangle{
            anchors.fill :parent
            id : apexidashsettings

            property string gauge1
            property string gauge2
            property string gauge3
            property string gauge4
            property string gauge5
            property string gauge6
            Settings {
                property alias vertbarin1: vertbar1.currentIndex
                property alias horizbarin1: horizbar1.currentIndex
                property alias datasourcesin1: datasources1.currentIndex
                property alias decplacesin1: decplaces1.currentIndex
                property alias maxvaltext1: maxval1.text
                property alias unittext1 :unit1.text
                property alias titletext1 :title1.text
                property alias vertbarin2: vertbar2.currentIndex
                property alias horizbarin2: horizbar2.currentIndex
                property alias datasourcesin2: datasources2.currentIndex
                property alias decplacesin2: decplaces2.currentIndex
                property alias maxvaltext2: maxval2.text
                property alias unittext2 :unit2.text
                property alias titletext2 :title2.text
                property alias vertbarin3: vertbar3.currentIndex
                property alias horizbarin3: horizbar3.currentIndex
                property alias datasourcesin3: datasources3.currentIndex
                property alias decplacesin3: decplaces3.currentIndex
                property alias maxvaltext3: maxval3.text
                property alias unittext3 :unit3.text
                property alias titletext3 :title3.text
                property alias vertbarin4: vertbar4.currentIndex
                property alias horizbarin4: horizbar4.currentIndex
                property alias datasourcesin4: datasources4.currentIndex
                property alias decplacesin4: decplaces4.currentIndex
                property alias maxvaltext4: maxval4.text
                property alias unittext4 :unit4.text
                property alias titletext4 :title4.text
                property alias vertbarin5: vertbar5.currentIndex
                property alias horizbarin5: horizbar5.currentIndex
                property alias datasourcesin5: datasources5.currentIndex
                property alias decplacesin5: decplaces5.currentIndex
                property alias maxvaltext5: maxval5.text
                property alias unittext5 :unit5.text
                property alias titletext5 :title5.text
                property alias vertbarin6: vertbar6.currentIndex
                property alias horizbarin6: horizbar6.currentIndex
                property alias datasourcesin6: datasources6.currentIndex
                property alias decplacesin6: decplaces6.currentIndex
                property alias maxvaltext6: maxval6.text
                property alias unittext6 :unit6.text
                property alias titletext6 :title6.text


            }

            // min max horizontal vertical title unit decimal place source
            Grid {
                id: mygrid
                rows:7
                columns: 7
                spacing: 5
                anchors.top : parent.top

                Text { text: "max Value"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                Text { text: "Horiz. Bar"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                Text { text: "Vert. Bar"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                Text { text: "Title"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                Text { text: "Unit"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                Text { text: "Dec. places"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                Text { text: "Source"
                    font.pixelSize: apexidashsettings.width / 55;color:"black"}
                TextField {
                    id: maxval1
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    text: qsTr("0")
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                ComboBox {
                    id: horizbar1
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: horizbar1.width
                        text: horizbar1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: horizbar1.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: horizbar1.font.family
                        font.pixelSize: horizbar1.font.pixelSize
                        highlighted: horizbar1.highlightedIndex === index
                        hoverEnabled: horizbar1.hoverEnabled
                    }
                }
                ComboBox {
                    id: vertbar1
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar1.width
                        text: vertbar1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar1.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar1.font.family
                        font.pixelSize: vertbar1.font.pixelSize
                        highlighted: vertbar1.highlightedIndex === index
                        hoverEnabled: vertbar1.hoverEnabled
                    }
                }
                TextField {
                    id: title1
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                TextField {
                    id: unit1
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                ComboBox {
                    id: decplaces1
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "0","1","2","3"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar1.width
                        text: vertbar1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar1.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar1.font.family
                        font.pixelSize: vertbar1.font.pixelSize
                        highlighted: vertbar1.highlightedIndex === index
                        hoverEnabled: vertbar1.hoverEnabled
                    }
                }
                ComboBox {
                    id: datasources1
                    width: apexidashsettings.width / 4
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "Inj Duty","IGL","IGT","RPM","Speed","Boost","Knock","WtrTemp","AirTemp","BattVolt","PIM","PIM Volt","TPS Volt","InjFrPr","Inj +/-","Fuel Temp","Oil Pump","Pre Control %","Waste Gate %","O2 Sensor 1","O2 Sensor 2","InjFrSc","MAFS1","MAFS2","Dwell","AN1 Raw","AN2 Raw","AN3 Raw","An4 Raw","AUX1(AN1-AN2 Calc)","AUX2(AN3-AN4 Calc)"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: datasources1.width
                        text: datasources1.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: datasources1.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: datasources1.font.family
                        font.pixelSize: datasources1.font.pixelSize
                        highlighted: datasources1.highlightedIndex === index
                        hoverEnabled: datasources1.hoverEnabled
                    }
                }
                TextField {
                    id: maxval2
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    text: qsTr("0")
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                ComboBox {
                    id: horizbar2
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: horizbar2.width
                        text: horizbar2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: horizbar2.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: horizbar2.font.family
                        font.pixelSize: horizbar2.font.pixelSize
                        highlighted: horizbar2.highlightedIndex === index
                        hoverEnabled: horizbar2.hoverEnabled
                    }
                }
                ComboBox {
                    id: vertbar2
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar2.width
                        text: vertbar2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar2.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar2.font.family
                        font.pixelSize: vertbar2.font.pixelSize
                        highlighted: vertbar2.highlightedIndex === index
                        hoverEnabled: vertbar2.hoverEnabled
                    }
                }
                TextField {
                    id: title2
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                TextField {
                    id: unit2
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                ComboBox {
                    id: decplaces2
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "0","1","2","3"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar2.width
                        text: vertbar2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar2.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar2.font.family
                        font.pixelSize: vertbar2.font.pixelSize
                        highlighted: vertbar2.highlightedIndex === index
                        hoverEnabled: vertbar2.hoverEnabled
                    }
                }
                ComboBox {
                    id: datasources2
                    width: apexidashsettings.width / 4
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "Inj Duty","IGL","IGT","RPM","Speed","Boost","Knock","WtrTemp","AirTemp","BattVolt","PIM","PIM Volt","TPS Volt","InjFrPr","Inj +/-","Fuel Temp","Oil Pump","Pre Control %","Waste Gate %","O2 Sensor 1","O2 Sensor 2","InjFrSc","MAFS1","MAFS2","Dwell","AN1 Raw","AN2 Raw","AN3 Raw","An4 Raw","AUX1(AN1-AN2 Calc)","AUX2(AN3-AN4 Calc)"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: datasources2.width
                        text: datasources2.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: datasources2.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: datasources2.font.family
                        font.pixelSize: datasources2.font.pixelSize
                        highlighted: datasources2.highlightedIndex === index
                        hoverEnabled: datasources2.hoverEnabled
                    }
                }
                TextField {
                    id: maxval3
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    text: qsTr("0")
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                ComboBox {
                    id: horizbar3
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: horizbar3.width
                        text: horizbar3.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: horizbar3.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: horizbar3.font.family
                        font.pixelSize: horizbar3.font.pixelSize
                        highlighted: horizbar3.highlightedIndex === index
                        hoverEnabled: horizbar3.hoverEnabled
                    }
                }
                ComboBox {
                    id: vertbar3
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar3.width
                        text: vertbar3.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar3.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar3.font.family
                        font.pixelSize: vertbar3.font.pixelSize
                        highlighted: vertbar3.highlightedIndex === index
                        hoverEnabled: vertbar3.hoverEnabled
                    }
                }
                TextField {
                    id: title3
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                TextField {
                    id: unit3
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                ComboBox {
                    id: decplaces3
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "0","1","2","3"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar3.width
                        text: vertbar3.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar3.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar3.font.family
                        font.pixelSize: vertbar3.font.pixelSize
                        highlighted: vertbar3.highlightedIndex === index
                        hoverEnabled: vertbar3.hoverEnabled
                    }
                }
                ComboBox {
                    id: datasources3
                    width: apexidashsettings.width / 4
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "Inj Duty","IGL","IGT","RPM","Speed","Boost","Knock","WtrTemp","AirTemp","BattVolt","PIM","PIM Volt","TPS Volt","InjFrPr","Inj +/-","Fuel Temp","Oil Pump","Pre Control %","Waste Gate %","O2 Sensor 1","O2 Sensor 2","InjFrSc","MAFS1","MAFS2","Dwell","AN1 Raw","AN2 Raw","AN3 Raw","An4 Raw","AUX1(AN1-AN2 Calc)","AUX2(AN3-AN4 Calc)"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: datasources3.width
                        text: datasources3.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: datasources3.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: datasources3.font.family
                        font.pixelSize: datasources3.font.pixelSize
                        highlighted: datasources3.highlightedIndex === index
                        hoverEnabled: datasources3.hoverEnabled
                    }
                }
                TextField {
                    id: maxval4
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    text: qsTr("0")
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                ComboBox {
                    id: horizbar4
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: horizbar4.width
                        text: horizbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: horizbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: horizbar4.font.family
                        font.pixelSize: horizbar4.font.pixelSize
                        highlighted: horizbar4.highlightedIndex === index
                        hoverEnabled: horizbar4.hoverEnabled
                    }
                }
                ComboBox {
                    id: vertbar4
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar4.width
                        text: vertbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar4.font.family
                        font.pixelSize: vertbar4.font.pixelSize
                        highlighted: vertbar4.highlightedIndex === index
                        hoverEnabled: vertbar4.hoverEnabled
                    }
                }
                TextField {
                    id: title4
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                TextField {
                    id: unit4
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                ComboBox {
                    id: decplaces4
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "0","1","2","3"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar4.width
                        text: vertbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar4.font.family
                        font.pixelSize: vertbar4.font.pixelSize
                        highlighted: vertbar4.highlightedIndex === index
                        hoverEnabled: vertbar4.hoverEnabled
                    }
                }
                ComboBox {
                    id: datasources4
                    width: apexidashsettings.width / 4
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "Inj Duty","IGL","IGT","RPM","Speed","Boost","Knock","WtrTemp","AirTemp","BattVolt","PIM","PIM Volt","TPS Volt","InjFrPr","Inj +/-","Fuel Temp","Oil Pump","Pre Control %","Waste Gate %","O2 Sensor 1","O2 Sensor 2","InjFrSc","MAFS1","MAFS2","Dwell","AN1 Raw","AN2 Raw","AN3 Raw","An4 Raw","AUX1(AN1-AN2 Calc)","AUX2(AN3-AN4 Calc)"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: datasources4.width
                        text: datasources4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: datasources4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: datasources4.font.family
                        font.pixelSize: datasources4.font.pixelSize
                        highlighted: datasources4.highlightedIndex === index
                        hoverEnabled: datasources4.hoverEnabled
                    }
                }
                TextField {
                    id: maxval5
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    text: qsTr("0")
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                ComboBox {
                    id: horizbar5
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: horizbar4.width
                        text: horizbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: horizbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: horizbar4.font.family
                        font.pixelSize: horizbar4.font.pixelSize
                        highlighted: horizbar4.highlightedIndex === index
                        hoverEnabled: horizbar4.hoverEnabled
                    }
                }
                ComboBox {
                    id: vertbar5
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar4.width
                        text: vertbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar4.font.family
                        font.pixelSize: vertbar4.font.pixelSize
                        highlighted: vertbar4.highlightedIndex === index
                        hoverEnabled: vertbar4.hoverEnabled
                    }
                }
                TextField {
                    id: title5
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                TextField {
                    id: unit5
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                ComboBox {
                    id: decplaces5
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "0","1","2","3"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar4.width
                        text: vertbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar4.font.family
                        font.pixelSize: vertbar4.font.pixelSize
                        highlighted: vertbar4.highlightedIndex === index
                        hoverEnabled: vertbar4.hoverEnabled
                    }
                }
                ComboBox {
                    id: datasources5
                    width: apexidashsettings.width / 4
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "Inj Duty","IGL","IGT","RPM","Speed","Boost","Knock","WtrTemp","AirTemp","BattVolt","PIM","PIM Volt","TPS Volt","InjFrPr","Inj +/-","Fuel Temp","Oil Pump","Pre Control %","Waste Gate %","O2 Sensor 1","O2 Sensor 2","InjFrSc","MAFS1","MAFS2","Dwell","AN1 Raw","AN2 Raw","AN3 Raw","An4 Raw","AUX1(AN1-AN2 Calc)","AUX2(AN3-AN4 Calc)"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: datasources5.width
                        text: datasources5.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: datasources5.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: datasources5.font.family
                        font.pixelSize: datasources5.font.pixelSize
                        highlighted: datasources5.highlightedIndex === index
                        hoverEnabled: datasources5.hoverEnabled
                    }
                }
                TextField {
                    id: maxval6
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    text: qsTr("0")
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                ComboBox {
                    id: horizbar6
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: horizbar4.width
                        text: horizbar4.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: horizbar4.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: horizbar4.font.family
                        font.pixelSize: horizbar4.font.pixelSize
                        highlighted: horizbar4.highlightedIndex === index
                        hoverEnabled: horizbar4.hoverEnabled
                    }
                }
                ComboBox {
                    id: vertbar6
                    width: apexidashsettings.width / 9
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "false","true"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: vertbar6.width
                        text: vertbar6.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: vertbar6.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: vertbar6.font.family
                        font.pixelSize: vertbar6.font.pixelSize
                        highlighted: vertbar6.highlightedIndex === index
                        hoverEnabled: vertbar6.hoverEnabled
                    }
                }
                TextField {
                    id: title6
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                TextField {
                    id: unit6
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                }
                ComboBox {
                    id: decplaces6
                    width: apexidashsettings.width / 12
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "0","1","2","3"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: decplaces6.width
                        text: decplaces6.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: decplaces6.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: decplaces6.font.family
                        font.pixelSize: decplaces6.font.pixelSize
                        highlighted: decplaces6.highlightedIndex === index
                        hoverEnabled: decplaces6.hoverEnabled
                    }
                }
                ComboBox {
                    id: datasources6
                    width: apexidashsettings.width / 4
                    height: apexidashsettings.height /15
                    font.pixelSize: apexidashsettings.width / 55
                    model: [ "Inj Duty","IGL","IGT","RPM","Speed","Boost","Knock","WtrTemp","AirTemp","BattVolt","PIM","PIM Volt","TPS Volt","InjFrPr","Inj +/-","Fuel Temp","Oil Pump","Pre Control %","Waste Gate %","O2 Sensor 1","O2 Sensor 2","InjFrSc","MAFS1","MAFS2","Dwell","AN1 Raw","AN2 Raw","AN3 Raw","An4 Raw","AUX1(AN1-AN2 Calc)","AUX2(AN3-AN4 Calc)"]
                    property bool initialized: true
                    delegate: ItemDelegate {
                        width: datasources6.width
                        text: datasources6.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                        font.weight: datasources6.currentIndex === index ? Font.DemiBold : Font.Normal
                        font.family: datasources6.font.family
                        font.pixelSize: datasources6.font.pixelSize
                        highlighted: datasources6.highlightedIndex === index
                        hoverEnabled: datasources6.hoverEnabled

                    }

                }
                ListModel {
                    id: datasources
                    ListElement {name: "Inj Duty"}
                    ListElement {name: "Leadingign"}
                    ListElement {name: "Trailingign"}
                    ListElement {name: "rpm"}
                    ListElement {name: "Speed"}
                    ListElement {name: "BoostPres"}
                    ListElement {name: "Knock"}
                    ListElement {name: "Watertemp"}
                    ListElement {name: "Intaketemp"}
                    ListElement {name: "BatteryV"}
                    ListElement {name: "Intakepress"}
                    ListElement {name: "PressureV"}
                    ListElement {name: "ThrottleV"}
                    ListElement {name: "InjFrPr"}
                    ListElement {name: "Inj +/-"}
                    ListElement {name: "Fuelc"}
                    ListElement {name: "Moilp"}
                    ListElement {name: "Boosttp"}
                    ListElement {name: "Boostwg"}
                    ListElement {name: "O2volt"}
                    ListElement {name: "O2volt_2"}
                    ListElement {name: "InjFrSc"}
                    ListElement {name: "MAF1V"}
                    ListElement {name: "MAF2V"}
                    ListElement {name: "Dwell"}
                    ListElement {name: "AN1V"}
                    ListElement {name: "AN2V"}
                    ListElement {name: "AN3V"}
                    ListElement {name: "AN4V"}
                    ListElement {name: "auxcalc1"}
                    ListElement {name: "auxcalc2"}

                }
                Button {
                    id: writefile
                    text: "Apply"
                    x: 350
                    y: 400
                    onClicked:{

                        gauge1 = ("166,120,300,240,"+maxval1.text+","+decplaces1.currentText +","+unit1.text+","+title1.text+","+vertbar1.currentText +","+horizbar1.currentText +","+"false,"+"Dashboard"+","+(datasources.get(datasources1.currentIndex).name)+","+(datasources.get(datasources1.currentIndex).name))
                        gauge2 = ("166,120,466,240,"+maxval2.text+","+decplaces2.currentText +","+unit2.text+","+title2.text+","+vertbar2.currentText +","+horizbar2.currentText +","+"false,"+"Dashboard"+","+(datasources.get(datasources2.currentIndex).name)+","+(datasources.get(datasources2.currentIndex).name))
                        gauge3 = ("166,120,632,240,"+maxval3.text+","+decplaces3.currentText +","+unit3.text+","+title3.text+","+vertbar3.currentText +","+horizbar3.currentText +","+"false,"+"Dashboard"+","+(datasources.get(datasources3.currentIndex).name)+","+(datasources.get(datasources3.currentIndex).name))
                        gauge4 = ("166,120,300,360,"+maxval4.text+","+decplaces4.currentText +","+unit4.text+","+title4.text+","+vertbar4.currentText +","+horizbar4.currentText +","+"false,"+"Dashboard"+","+(datasources.get(datasources4.currentIndex).name)+","+(datasources.get(datasources4.currentIndex).name))
                        gauge5 = ("166,120,466,360,"+maxval5.text+","+decplaces5.currentText +","+unit5.text+","+title5.text+","+vertbar5.currentText +","+horizbar5.currentText +","+"false,"+"Dashboard"+","+(datasources.get(datasources5.currentIndex).name)+","+(datasources.get(datasources5.currentIndex).name))
                        gauge6 = ("166,120,632,360,"+maxval6.text+","+decplaces6.currentText +","+unit6.text+","+title6.text+","+vertbar6.currentText +","+horizbar6.currentText +","+"false,"+"Dashboard"+","+(datasources.get(datasources6.currentIndex).name)+","+(datasources.get(datasources6.currentIndex).name))

                        Apexi.writeDashfile(gauge1,gauge2,gauge3,gauge4,gauge5,gauge6)
                    }
                }
            }
            //

            // Virtual Keyboard

            InputPanel {
                id: keyboard;
                y: apexidashsettings.height; // position the top of the keyboard to the bottom of the screen/display

                anchors.left: apexidashsettings.left;
                anchors.right: apexidashsettings.right;


                states: State {
                    name: "visible";
                    when: keyboard.active;
                    PropertyChanges {
                        target: keyboard;
                        // position keyboard on top of the screen
                        y: apexidashsettings.height / 1.95;
                    }
                }
                transitions: Transition {
                    from: ""; // default initial state
                    to: "visible";
                    reversible: true; // toggle visibility with reversible: true;
                    ParallelAnimation {
                        NumberAnimation {
                            properties: "y";
                            duration: 250;
                            easing.type: Easing.InOutQuad;
                        }
                    }
                }
            }
            //


        }

    }
    Tab {
        title: "Developer"// Tab index 7
        //Developer Stuff
        Rectangle{
            id: developer
            anchors.top : mygrid.bottom
            color: "black"
            Connections{
                target: Dashboard
                //onSerialStatChanged :{consoletext.append(Dashboard.SerialStat)}
                onSerialStatChanged :{consoletext = Dashboard.SerialStat}
            }
            ScrollView {
                id: scrollconsoletext
                width: 400
                height: parent.height
                TextArea {
                    id: consoletext
                    width: scrollconsoletext.width
                    wrapMode: TextArea.Wrap
                    color: "white"
                }
            }
            Grid {
                anchors.top :parent.top
                anchors.topMargin: parent.height / 20
                anchors.right: parent.right
                rows: 10
                columns: 2
                spacing: parent.width /150
                Button {
                    id: candump
                    text: "CanDump"
                    onClicked: Connect.candump()
                }
                Button {
                    id: minicom
                    text: "Minicom"
                    onClicked: Connect.minicom()
                }
                /*
            Button {
                id: update
                text: "Update"
                onClicked: Connect.update()
                }
                */
            }
        }
    }
}

