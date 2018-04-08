import QtQuick 2.8
import QtQuick.Controls 2.1
import Qt.labs.settings 1.0
import QtQuick.VirtualKeyboard 2.1
import QtSensors 5.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8



Rectangle {
    id: windowbackround
    width: parent.width
    height: parent.height
    color: "grey"

    property  int test1: 0
    property  var gpscom
    Item {
        id: powerTuneSettings
        Settings {
            property alias brightnessselect: brightness.value
            property alias connectAtStartUp: connectAtStart.checked
            property alias gpsswitch: gpsswitch.checked
            property alias accelswitch: accelsens.checked
            property alias gyrowitch:  gyrosense.checked
            property alias compassswitch: compass.checked
            property alias tempswitch: tempsense.checked
            property alias pressureswitch:pressuresens.checked
            property alias serialPortName: serialName.currentText
            property alias gpsPortName: serialNameGPS.currentText
            property alias gpsPortNameindex: serialNameGPS.currentIndex
            property alias dashselect1 : dash1.currentIndex
            property alias dashselect2 : dash2.currentIndex
            property alias dashselect3 : dash3.currentIndex
            property alias dashselect4 : dash4.currentIndex
            //property alias gpsBaud: serialGPSBaud.currentText
            // property alias gpsBaudindex: serialGPSBaud.currentIndex
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
            property alias watertempwarning: watertempwarn.text
            property alias boostwarning: boostwarn.text
            property alias rpmwarning: rpmwarn.text
            property alias knockwarning: knockwarn.text

        }
        SoundEffect {
            id: warnsound
            source: "qrc:/Sounds/alarm.wav"
        }

        Connections{
            target: Dashboard
            onOdoChanged:{odometer.text = (Dashboard.Odo).toFixed(0) }
            onTripChanged:{tripmeter.text = (Dashboard.Trip).toFixed(1) }
            onWatertempChanged: { if (Dashboard.Watertemp > watertempwarn.text) {playwarning.start()};}
            onRpmChanged: { if (Dashboard.rpm > rpmwarn.text) {playwarning.start()};}
            onKnockChanged: { if (Dashboard.Knock > knockwarn.text) {playwarning.start()};}
            onBoostPresChanged: { if (Dashboard.BoostPres > boostwarn.text) {playwarning.start()};}
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
                visible: { (ecuSelect.currentIndex >= "4") ? false: true; }
                }
                ComboBox {
                    id: serialName
                    width: windowbackround.width / 5
                    height: windowbackround.height /15
                    font.pixelSize: windowbackround.width / 55
                    model: Connect.portsNames
                    visible: { (ecuSelect.currentIndex >= "4") ? false: true; }
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true; autoconnect.auto(); }
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
                    model: [ "PowerFC", "Adaptronic Select Modbus", "OBDII" , "Nissan Consult","UDP Receiver port 45454","CAN Adaptronic Modular","CAN Haltech V2"]

                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setECU( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getECU(); initialized = true }
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
                    color: "white"
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
                    color: "white"
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
                    color: "white"
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
                    color: "white"
                    readOnly: true
                    text: "0"
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
                        functdisconnect.disconnectfunc();
                    }
                }

                Button {
                    id: oppendashselect
                    text: "Dash select"
                    width: windowbackround.width / 5
                    height: windowbackround.height /15
                    font.pixelSize: windowbackround.width / 55
                    onClicked: {dashselector.visible = true}
                }
                Button {
                    id: senhatsel
                    text: "Senshat"
                    width: windowbackround.width / 5
                    height: windowbackround.height /15
                    font.pixelSize: windowbackround.width / 55
                    onClicked: {senhatselector.visible = true}
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
*/              Button{
                text: "Warn Settings"
                width: windowbackround.width / 5
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                onClicked: warningsettings.visible = true
                }
                Button {
                    text: "Quit"
                    width: windowbackround.width / 5
                    height: windowbackround.height /15
                    font.pixelSize: windowbackround.width / 55
                    onClicked: {
                        Qt.quit()
                    }


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
                    Component.onCompleted: Connect.setSreenbrightness(brightness.value);
                    onPositionChanged: Connect.setSreenbrightness(brightness.value);
                }

              /*
                Text
                {
                    color: "red"
                    text: Dashboard.SerialStat
                }

                Text
                {
                    color: "blue"
                    text: Dashboard.RecvData
                }
                Text
                {
                    color: "purple"
                    text: Dashboard.TimeoutStat
                }
                Text
                {
                    color: "purple"
                    text: Dashboard.RunStat
                }
                */
                Grid {
                    visible: { (ecuSelect.currentIndex >= "1") ? false: true; }
                    rows: 10
                    columns: 4
                    spacing: windowbackround.width / 150
                    //Just a spacer for now still need to do it properly
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    Text  { text: ""; width: 50}
                    //Spacer end


                    Text  { text: ""; width: 50}
                    Text  { text: "0V"; width: 50}
                    Text  { text: "5V"; width: 50}
                    Text  { text: "Name"; width: 50}
                    Text  { text: "AN1-2"; width: 50}
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
                    Text  { text: "AN3-4"; width: 50}
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
                    /*
                    Text  { text: "AN5-AN6"; width: 50;visible: { (interfaceSelect.currentIndex == "1") ? true: false; }}
                    TextField {
                        id: an5V0
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: an6V5
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: unitaux3
                        width: 50
                        placeholderText: qsTr("AFR")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    Text  { text: "AN7-AN8"; width: 50;visible: { (interfaceSelect.currentIndex == "1") ? true: false; }}
                    TextField {
                        id: an7V0
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: an8V5
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                        visible: { (interfaceSelect.currentIndex == "1") ? true: false; }
                    }
                    TextField {
                        id: unitaux4
                        width: 50
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
            if (connectAtStart.checked == true) functconnect.connectfunc(),connectButton.enabled =false,ecuSelect.enabled = false,disconnectButton.enabled = true;//Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, loggerSelect.currentIndex,logger.datalogger()),Connect.Auxcalc(unitaux1.text,an1V0.text,an2V5.text,unitaux2.text,an3V0.text,an4V5.text);
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
             Connect.setOdometer(odometer.text)
             Connect.setWeight(weight.text);
             Connect.openConnection(serialName.currentText, ecuSelect.currentIndex ,weight.currentText);
            //else Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, logger.datalogger()),Connect.Auxcalc(unitaux1.text,an1V0.text,an2V5.text,unitaux2.text,an3V0.text,an4V5.text);
        }
    }

    //function to Disconnect
    Item {

        id: functdisconnect
        function disconnectfunc()
        {
             Connect.closeConnection(),GPS.stopGPScom();
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

    Rectangle{

        id: dashselector
        visible: false
        width: parent.width
        height: parent.height
        color: "grey"

        Grid {
            rows: 3
            columns: 4
            spacing: windowbackround.width / 150
            Text { text: "Dash1"
                font.pixelSize: windowbackround.width / 55 }
            Text { text: "Dash2"
            font.pixelSize: windowbackround.width / 55}
            Text { text: "Dash3"
            font.pixelSize: windowbackround.width / 55}
            Text { text: "Dash4"
            font.pixelSize: windowbackround.width / 55}
            ComboBox {
                id: dash1
                width: windowbackround.width / 5
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech"]
                property bool initialized: true
                onCurrentIndexChanged:{select1.selDash1() }
                Component.onCompleted: {select1.selDash1() }
            }

            ComboBox {
                id: dash2
                width: windowbackround.width / 5
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech"]
                property bool initialized: true
                onCurrentIndexChanged:{select2.selDash2() }
                Component.onCompleted: {select2.selDash2() }
            }

            ComboBox {
                id: dash3
                width: windowbackround.width / 5
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech"]
                property bool initialized: true
                onCurrentIndexChanged:{select3.selDash3() }
                Component.onCompleted: {select3.selDash3() }
            }
            ComboBox {
                id: dash4
                width: windowbackround.width / 5
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                model:  ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force","Dyno","FuelTech"]
                property bool initialized: true
                onCurrentIndexChanged:{select4.selDash4() }
                Component.onCompleted: {select4.selDash4() }
            }
            Button {
                id: closedashselector
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                text: "Apply"
                onClicked: {dashselector.visible = false}
            }
        }


    }

  //Warning Settings by Craig Shoesmith
    Rectangle{

        id: warningsettings
        visible: false
        width: parent.width
        height: parent.height
        color: "grey"

        Grid {
            rows:3
            columns: 4
            spacing: 5
            Text { text: "WaterTemp"
            font.pixelSize: windowbackround.width / 55}
            Text { text: "Boost"
            font.pixelSize: windowbackround.width / 55}
            Text { text: "Revs"
            font.pixelSize: windowbackround.width / 55}
            Text { text: "Knock"
            font.pixelSize: windowbackround.width / 55}
            TextField {
                id: watertempwarn
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                inputMethodHints: Qt.ImhDigitsOnly // this ensures valid inputs are number only
            }
            TextField {
                id: boostwarn
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                inputMethodHints: Qt.ImhDigitsOnly
            }
            TextField {
                id: rpmwarn
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                inputMethodHints: Qt.ImhDigitsOnly
            }
            TextField {
                id: knockwarn
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                inputMethodHints: Qt.ImhDigitsOnly
            }


            Button {
                id: closewarningsettings
                text: "Apply"
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                onClicked: {warningsettings.visible = false}

            }
        }
}

//Sensehat Sensors
    Rectangle{

        id: senhatselector
        visible: false
        width: parent.width
        height: parent.height
        color: "grey"

        Grid {
            rows: 6
            columns: 2
            spacing: windowbackround.width / 150
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
            }
            Button {
                id: closedsenshatselector
                text: "Apply"
                width: windowbackround.width / 10
                height: windowbackround.height /15
                font.pixelSize: windowbackround.width / 55
                onClicked: {senhatselector.visible = false}
            }



        }
    }
}


