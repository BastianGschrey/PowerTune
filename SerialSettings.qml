import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    Row {
        x: 5
        y: 5
        spacing: 5
        Grid {
            rows: 10
            columns: 2
            spacing: 5
            // [0]
            Text { text: "Serial port name: " }
            ComboBox {
                id: serialName
                width: 200
                editable: false
                model: Serial.portsNames
            }
            // [1]
            Text { text: "Baud rate:"; width: 200}
            ComboBox {
                id: baudRate
                width: 200
                editable: false
                model: [
                    1200, 2400, 2400,
                    4800, 9600, 19200,
                    38400, 57600, 115200 ]
                property bool initialized: false
                onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true }
            }
            // [2]
            Text { text: "Parity:" }
            ComboBox {
                id: parity
                width: 200
                editable: false
                model: [
                    "No Parity", "Even Parity", "Odd Parity",
                    "Space Parity", "Mark Parity" ]
                property bool initialized: false
                onCurrentIndexChanged: if (initialized) AppSettings.setParity( currentIndex )
                Component.onCompleted: { currentIndex = AppSettings.getParity(); initialized = true }
            }
            // [3]
            Text { text: "Data bits:" }
            ComboBox {
                id: databits
                width: 200
                editable: false
                model: [ "Data 5", "Data 6", "Data 7", "Data 8" ]
                property bool initialized: false
                onCurrentIndexChanged: if (initialized) AppSettings.setDataBits( currentIndex )
                Component.onCompleted: { currentIndex = AppSettings.getDataBits(); initialized = true }
            }
            // [4]
            Text { text: "Stop bits:" }
            ComboBox {
                id: stopBits
                width: 200
                editable: false
                model: [ "One stop", "Two Stop", "One and half stop" ]
                property bool initialized: false
                onCurrentIndexChanged: if (initialized) AppSettings.setStopBits( currentIndex )
                Component.onCompleted: { currentIndex = AppSettings.getStopBits(); initialized = true }
            }
            // [5]
            Text { text: "Flow control:" }
            ComboBox {
                id: flowcontrol
                width: 200
                editable: false
                model: [ "No flow control", "Hardware control", "Software control" ]
                property bool initialized: false
                onCurrentIndexChanged: if (initialized) AppSettings.setFlowControl( currentIndex )
                Component.onCompleted: { currentIndex = AppSettings.getFlowControl(); initialized = true }
            }
        }
        Button {
            text: "Connect"
            onClicked: {
                Serial.openConnection(serialName.currentText, baudRate.currentText, parity.currentIndex,
                                      databits.currentIndex, stopBits.currentIndex, flowcontrol.currentIndex)
            }
        }
        Button {
            text: "Disconnect"
            onClicked: {
                Serial.closeConnection()
            }
        }
        Button {
            text: "Clear"
            onClicked: {
                Serial.clear()
            }
        }
    }
}
