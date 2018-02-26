import QtQuick 2.8
import QtQuick.Controls 2.1
import Qt.labs.settings 1.0
import QtQuick.VirtualKeyboard 2.1
import QtSensors 5.0


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
            property alias unitSelector: unitSelect.currentIndex

        }

        Item {
            id: sensors
            Component.onCompleted: {
                var types = QmlSensors.sensorTypes();
                console.log(types.join(", "));
            }
        }

        Row {
            x: 5
            y: 5
            spacing: 5
            Grid {
                rows: 10
                columns: 2
                spacing: 5
                // [0]
                Text {
                text: "ECU Serial Port: "
                visible: { (ecuSelect.currentIndex >= "4") ? false: true; }
                }
                ComboBox {
                    id: serialName
                    width: 200
                    model: Connect.portsNames
                    visible: { (ecuSelect.currentIndex >= "4") ? false: true; }
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true; autoconnect.auto(); }
                }
                Text {
                text: "GPS Port: "
                visible: { (gpsswitch.checked == true ) ? true:false; }
                }
                ComboBox {
                    id: serialNameGPS
                    width: 200
                    model: Connect.portsNames
                    visible: { (gpsswitch.checked == true ) ? true:false; }

                }
                Text {
                text: "GPS Baud: "
                visible: { (gpsswitch.checked == true ) ? true:false; }
                }
                ComboBox {
                    id: serialGPSBaud
                    width: 200
                    model: [ "2400", "4800", "9600", "14400", "19200", "38400", "57600", "115200"]
                    visible: { (gpsswitch.checked == true ) ? true:false; }
                    Component.onCompleted: {autoconnectGPS.auto()}

                }

                Text { text: "Display units:" }
                ComboBox {

                    id: unitSelect
                    width: 200

                    model: [ "Metric","Imperial"]
                    property bool initialized: false
                    Component.onCompleted: { Connect.setUnits(currentIndex) }
                    onCurrentIndexChanged: { Connect.setUnits(currentIndex) }

                }
                Text { text: "ECU Selection:" }
                ComboBox {

                    id: ecuSelect
                    width: 200
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
                    width: 200
                    model: [ "OFF", "ON"]
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setLogging( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getLogging(); initialized = true }
                }
*/
                Text { text: "GoPro Variant :" }
                ComboBox {
                    id: goProSelect
                    width: 200
                    model: [ "Hero", "Hero2","Hero3"]

                }
                Text { text: "GoPro Password :" }
                TextField {
                    id: goPropass
                    placeholderText: qsTr("GoPro Password")
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                    Component.onCompleted: {transferSettings.sendSettings() }
                }
                Text
                {
                    text: "Logfile name:"
                }
                TextField {
                    id: logfilenameSelect
                    text: qsTr("DataLog")
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                    //enterKeyAction: EnterKeyAction.Next
                }
                Text
                {
                    text: "Serial Status:"
                }
                TextField {
                    text: qsTr(Dashboard.SerialStat)

                }
            }

            Grid {
                rows: 10
                columns: 2
                spacing: 5

                Button {
                    id: connectButton
                    text: "Connect"
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
                    text: "Open Dashselect"
                    onClicked: {dashselector.visible = true}
                }
                Button {
                    id: senhatsel
                    text: "Senshat"
                    onClicked: {senhatselector.visible = true}
                }
                /*
                Button {
                    text: "Clear"
                    onClicked: {
                        Connect.clear()
                    }
                }
*/              //for official raspberry Pi image only !!!!
                /*
                Button {
                    text: "Pi Update "
                    onClicked: {
                        Connect.update()

                    }
                }
*/
                Button {
                    text: "Quit"
                    onClicked: {
                        Qt.quit()
                    }
                }



                Switch {
                    id: connectAtStart
                    text: qsTr("Autoconnect")
                }
                Switch {
                    id: loggerswitch
                    text: qsTr("Data Logger")
                    Component.onCompleted: {logger.datalogger()}
                    onCheckedChanged: logger.datalogger()

                }

                Switch {
                    id: record
                    text: qsTr("GoPro rec")
                    onCheckedChanged: {transferSettings.sendSettings(),goproRec.rec()}
                }
                Switch {
                    id: gpsswitch
                    text: qsTr("GPS")
                    onCheckedChanged: {autoconnectGPS.auto()}
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
                    spacing: 5
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
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        inputMethodHints: Qt.ImhDigitsOnly
                        placeholderText: qsTr("9")
                    }
                    TextField {
                        id: an2V5
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        inputMethodHints: Qt.ImhDigitsOnly
                        placeholderText: qsTr("16")
                    }
                    TextField {
                        id: unitaux1
                        width: 50
                        placeholderText: qsTr("AFR")
                    }
                    Text  { text: "AN3-4"; width: 50}
                    TextField {
                        id: an3V0
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        inputMethodHints: Qt.ImhDigitsOnly
                        placeholderText: qsTr("Value @ 0V")

                    }
                    TextField {
                        id: an4V5
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        inputMethodHints: Qt.ImhDigitsOnly
                        placeholderText: qsTr("Value @ 5V")
                    }
                    TextField {
                        id: unitaux2
                        width: 50
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
            if (connectAtStart.checked == true) functconnect.connectfunc(),connectButton.enabled =false,ecuSelect.enabled = false,disconnectButton.enabled = true;;//Connect.openConnection(serialName.currentText, ecuSelect.currentIndex, loggerSelect.currentIndex,logger.datalogger()),Connect.Auxcalc(unitaux1.text,an1V0.text,an2V5.text,unitaux2.text,an3V0.text,an4V5.text);

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
             Connect.openConnection(serialName.currentText, ecuSelect.currentIndex);
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
            if (dash1.currentIndex == "0") {firstPageLoader.source = "qrc:/Gauges/Dashboard.qml"};
            if (dash1.currentIndex == "1") {firstPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
            if (dash1.currentIndex == "2") {firstPageLoader.source = "qrc:/Gauges/Charts.qml"};
            if (dash1.currentIndex == "3") {firstPageLoader.source = "qrc:/Gauges/GPS.qml"};
            if (dash1.currentIndex == "4") {firstPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
            if (dash1.currentIndex == "5") {firstPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
            if (dash1.currentIndex == "6") {firstPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
            if (dash1.currentIndex == "7") {firstPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};

        }

    }
    Item {
        id: select2
        function selDash2()
        {
            if (dash2.currentIndex == "0") {secondPageLoader.source = "qrc:/Gauges/Dashboard.qml"};
            if (dash2.currentIndex == "1") {secondPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
            if (dash2.currentIndex == "2") {secondPageLoader.source = "qrc:/Gauges/Charts.qml"};
            if (dash2.currentIndex == "3") {secondPageLoader.source = "qrc:/Gauges/GPS.qml"};
            if (dash2.currentIndex == "4") {secondPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
            if (dash2.currentIndex == "5") {secondPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
            if (dash2.currentIndex == "6") {secondPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
            if (dash2.currentIndex == "7") {secondPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};

        }

    }
    Item {
        id: select3
        function selDash3()
        {
            if (dash3.currentIndex == "0") {thirdPageLoader.source = "qrc:/Gauges/Dashboard.qml"};
            if (dash3.currentIndex == "1") {thirdPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
            if (dash3.currentIndex == "2") {thirdPageLoader.source = "qrc:/Gauges/Charts.qml"};
            if (dash3.currentIndex == "3") {thirdPageLoader.source = "qrc:/Gauges/GPS.qml"};
            if (dash3.currentIndex == "4") {thirdPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
            if (dash3.currentIndex == "5") {thirdPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
            if (dash3.currentIndex == "6") {thirdPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
            if (dash3.currentIndex == "7") {thirdPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};

        }

    }
    Item {
        id: select4
        function selDash4()
        {
            if (dash4.currentIndex == "0") {fourthPageLoader.source = "qrc:/Gauges/Dashboard.qml"};
            if (dash4.currentIndex == "1") {fourthPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml"};
            if (dash4.currentIndex == "2") {fourthPageLoader.source = "qrc:/Gauges/Charts.qml"};
            if (dash4.currentIndex == "3") {fourthPageLoader.source = "qrc:/Gauges/GPS.qml"};
            if (dash4.currentIndex == "4") {fourthPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
            if (dash4.currentIndex == "5") {fourthPageLoader.source = "qrc:/Gauges/RaceDash.qml"};
            if (dash4.currentIndex == "6") {fourthPageLoader.source = "qrc:/Gauges/RaceDashApexi.qml"};
            if (dash4.currentIndex == "7") {fourthPageLoader.source = "qrc:/Gauges/ForceMeter.qml"};

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
            spacing: 5
            Text { text: "Dash1" }
            Text { text: "Dash2" }
            Text { text: "Dash3" }
            Text { text: "Dash4" }
            ComboBox {
                id: dash1
                width: 180
                model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force"]
                property bool initialized: true
                onCurrentIndexChanged:{select1.selDash1() }
                Component.onCompleted: {select1.selDash1() }
            }

            ComboBox {
                id: dash2
                width: 180
                model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force"]
                property bool initialized: true
                onCurrentIndexChanged:{select2.selDash2() }
                Component.onCompleted: {select2.selDash2() }
            }

            ComboBox {
                id: dash3
                width: 180
                model: ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force"]
                property bool initialized: true
                onCurrentIndexChanged:{select3.selDash3() }
                Component.onCompleted: {select3.selDash3() }
            }
            ComboBox {
                id: dash4
                width: 180
                model:  ["Main Dash", "Adaptronic","Charts", "GPS", "PowerFC Sensors","Race Dash","Race Dash Apexi","G-Force"]
                property bool initialized: true
                onCurrentIndexChanged:{select4.selDash4() }
                Component.onCompleted: {select4.selDash4() }
            }
            Button {
                id: closedashselector
                text: "Apply"
                onClicked: {dashselector.visible = false}
            }
        }


    }

    Rectangle{

        id: senhatselector
        visible: false
        width: parent.width
        height: parent.height
        color: "grey"

        Grid {
            rows: 6
            columns: 2
            spacing: 5
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
                onClicked: {senhatselector.visible = false}
            }


        }
    }
}


