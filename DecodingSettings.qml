import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0


Item {
    id: auxSettings

    Settings {
        property alias auxunit1: unitaux1.text
        property alias aux1: an1V0.text
        property alias aux2: an2V5.text
        property alias auxunit2: unitaux2.text
        property alias aux3: an3V0.text
        property alias aux4: an4V5.text

    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "grey"
        Item {
            Row {
                x: 100
                y: 50
                spacing: 5
                Grid {
                    rows: 10
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
                    Text  { text: "AN5-AN6"; width: 50}
                    TextField {
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")
                    }
                    TextField {
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                    }
                    TextField {
                        id: unitaux3
                        width: 50
                        placeholderText: qsTr("AFR")
                    }
                    Text  { text: "AN7-AN8"; width: 50}
                    TextField {
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 0V")
                    }
                    TextField {
                        width: 50
                        validator: IntValidator {bottom: 0; top: 1000;}
                        placeholderText: qsTr("Value @ 5V")
                    }
                    TextField {
                        id: unitaux4
                        width: 50
                        placeholderText: qsTr("AFR")
                    }
                    Text { text: "Unit Display"; width: 50}
                    ComboBox {
                        id: unitSetting
                        width: 50
                        model: [
                            "Metric", "Imperial" ]
                        property bool initialized: false
                        //  onCurrentIndexChanged: if (initialized) AppSettings.setUnits( currentIndex )
                        //   Component.onCompleted: { currentIndex = AppSettings.getUnits(); initialized = true }
                    }
                    Button {
                        text: "OK"
                        onClicked: {
                            SerialSettings.test1(10)
                        }
                    }
                }


            }
        }
    }
}

