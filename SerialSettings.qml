import QtQuick 2.6
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import Qt.labs.settings 1.0

Rectangle {
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
            property alias serialPortName: serialName.currentText
            property alias gpsPortName: serialNameGPS.currentText
            property alias gpsPortNameindex: serialNameGPS.currentIndex
            property alias gpsBaud: serialGPSBaud.currentText
            property alias gpsBaudindex: serialGPSBaud.currentIndex
            property alias ecuType: ecuSelect.currentText
            property alias powerFcInterface: interfaceSelect.currentText
            property alias auxunit1: unitaux1.text
            property alias aux1: an1V0.text
            property alias aux2: an2V5.text
            property alias auxunit2: unitaux2.text
            property alias aux3: an3V0.text
            property alias aux4: an4V5.text
            property alias auxunit3: unitaux3.text
            property alias aux5: an5V0.text
            property alias aux6: an6V5.text
            property alias auxunit4: unitaux4.text
            property alias aux7: an7V0.text
            property alias aux8: an8V5.text
            property alias goProVariant: goProSelect.currentIndex
            property alias password: goPropass.text

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
                Text { text: "ECU Serial Port: " }
                ComboBox {
                    id: serialName
                    width: 200

                    model: Serial.portsNames
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true; autoconnect.auto();logger.datalogger() }
                }
                Text { text: "GPS Port: " }
                    ComboBox {
                        id: serialNameGPS
                        width: 200
                        model: Serial.portsNames

                    }
                Text { text: "GPS Baud: " }
                    ComboBox {
                        id: serialGPSBaud
                        width: 200
                        model: [ "2400", "4800", "9600", "14400", "19200", "38400", "57600", "115200"]

                    }

                Text { text: "ECU Selection:" }
                ComboBox {

                    id: ecuSelect
                    width: 200

                    model: [ "PowerFC", "Adaptronic"]
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setECU( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getECU(); initialized = true }
                }
                Text {
                    id: textinterfaceSelect
                    visible: { (ecuSelect.currentIndex == "1") ? false: true; }
                    text: "PowerFC Interface:"

                }
                ComboBox {
                    id: interfaceSelect
                    visible: { (ecuSelect.currentIndex == "1") ? false: true; }
                    width: 200
                    model: [ "4 Aux Inputs", "8 Aux Inputs"]
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setInterface( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getInterface(); initialized = true }
                }
                Text {
                    id: textloggingSelect
                    visible: { (ecuSelect.currentIndex == "1") ? false: true; }
                    text: "Log Raw Messages:"

                }
                ComboBox {
                    id: loggerSelect
                    visible: { (ecuSelect.currentIndex == "1") ? false: true; }
                    width: 200
                    model: [ "OFF", "ON"]
                    property bool initialized: false
                    onCurrentIndexChanged: if (initialized) AppSettings.setLogging( currentIndex )
                    Component.onCompleted: { currentIndex = AppSettings.getLogging(); initialized = true }
                }
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
                    Component.onCompleted: {transferSettings.sendSettings() }
                }
                Text
                {
                    text: "Logfile name:"
                }
                TextField {
                    id: logfilenameSelect
                    text: qsTr("DataLog")
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
                        // console.log (serialName.currentText);
                        Serial.openConnection(serialName.currentText, ecuSelect.currentIndex, interfaceSelect.currentIndex, loggerSelect.currentIndex,logger.datalogger()),Serial.Auxcalc(unitaux1.text,an1V0.text,an2V5.text,unitaux2.text,an3V0.text,an4V5.text,unitaux3.text,an5V0.text,an6V5.text,unitaux4.text,an7V0.text,an8V5.text);

                    }
                }
                Button {
                    id: disconnectButton
                    text: "Disconnect"
                    onClicked: {
                        Serial.closeConnection(),GPS.stopGPScom();
                    }
                }
                Button {
                    text: "Clear"
                    onClicked: {
                        Serial.clear()
                    }
                }
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
                Text
                {
                    color: "red"
                    text: Dashboard.SerialStat
                }
                Grid {
                    visible: { (ecuSelect.currentIndex == "1") ? false: true; }
                    rows: 5
                    columns: 4
                    spacing: 5
                    Text  { text: ""; width: 50}
                    Text  { text: "Value 0V"; width: 50}
                    Text  { text: "Value 5V"; width: 50}
                    Text  { text: "Unit Name"; width: 50}
                    Text  { text: "AN1-AN2"; width: 50}
                    TextField {
                        id: an1V0
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("9")
                    }
                    TextField {
                        id: an2V5
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("16")
                    }
                    TextField {
                        id: unitaux1
                        width: 50
                        placeholderText: qsTr("AFR")
                    }
                    Text  { text: "AN3-AN4"; width: 50}
                    TextField {
                        id: an3V0
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")

                    }
                    TextField {
                        id: an4V5
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                    }
                    TextField {
                        id: unitaux2
                        width: 50
                        placeholderText: qsTr("AFR")
                    }
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

                }

            }
        }
    }
    // make another grid
 /*
    Item {
        visible: { (ecuSelect.currentIndex == "1") ? false: true; }
        Row {
            x: 50
            y: 200
            spacing: 5

        }
    }
*/
    //Functions
    Item {
        //Function to automatically connect at Startup , function is called from COmbobox Serialname component.oncompleted
        id: autoconnect
        function auto()
        {
            // if (connectAtStart.checked == true) Serial.openConnection(serialName.currentText, ecuSelect.currentIndex, interfaceSelect.currentIndex, loggerSelect.currentIndex);
            if (connectAtStart.checked == true) Serial.openConnection(serialName.currentText, ecuSelect.currentIndex, interfaceSelect.currentIndex, loggerSelect.currentIndex),Serial.Auxcalc(unitaux1.text,an1V0.text,an2V5.text,unitaux2.text,an3V0.text,an4V5.text,unitaux3.text,an5V0.text,an6V5.text,unitaux4.text,an7V0.text,an8V5.text);

        }
    }
    Item {
        //Function to connect and disconnect GPS
        id: autoconnectGPS
        function auto()
        {
            if (gpsswitch.checked == true)GPS.startGPScom(serialNameGPS.currentText,serialGPSBaud.currentText);
            if (gpsswitch.checked == false)GPS.stopGPScom();
        }
    }
    Item {
        //Logger on off function
        id: logger
        property var loggeron: 0
        function datalogger()
        {

            if (loggerswitch.checked == true) logger.loggeron = 1, Serial.startLogging(logfilenameSelect.text, loggeron.valueOf());
            if (loggerswitch.checked == false) logger.loggeron = 0,Serial.stopLogging(logfilenameSelect.text, loggeron.valueOf());
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
        //Function to transmit GoPro rec status on off
        id: goproRec
        property var recording: 0
        function rec()
        {

            if (record.checked == true) goproRec.recording = 1, GoPro.goprorec(recording.valueOf());
            if (record.checked == false) goproRec.recording = 0,GoPro.goprorec(recording.valueOf());


        }
    }


}
