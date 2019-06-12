import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import Qt.labs.settings 1.0

Rectangle {
    anchors.fill: parent
    color: "grey"
    id: main

    Item {
        id: dashSettings
        Settings {

            property alias an00save : an00.text
            property alias an05save : an05.text
            property alias an10save : an10.text
            property alias an15save : an15.text
            property alias an20save : an20.text
            property alias an25save : an25.text
            property alias an30save : an30.text
            property alias an35save : an35.text
            property alias an40save : an40.text
            property alias an45save : an45.text
            property alias an50save : an50.text
            property alias an55save : an55.text
            property alias an60save : an60.text
            property alias an65save : an65.text
            property alias an70save : an70.text
            property alias an75save : an75.text
            property alias an80save : an80.text
            property alias an85save : an85.text
            property alias an90save : an90.text
            property alias an95save : an95.text
            property alias an100save : an100.text
            property alias an105save : an105.text

        }
    }
    Grid {

        rows:12
        columns: 3
        spacing: 5
        Text { text: "  "
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "Value @ 0V"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "Value @ 5V"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "Analog 0"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an00
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an05
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 1"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an10
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an15
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 2"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an20
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an25
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 3"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an30
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an35
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 4"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an40
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an45
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 5"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an50
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an55
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 6"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an60
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an65
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 7"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an70
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an75
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 8"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an80
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an85
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 9"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an90
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an95
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "Analog 10"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: an100
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: an105
            width: main.width / 5.5
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()
            Component.onCompleted: inputs.setInputs()
        }
        Item {
            id: inputs
            function setInputs()
            {
            Dashboard.setAnalogVal(an00.text,an05.text,an10.text,an15.text,an20.text,an25.text,an30.text,an35.text,an40.text,an45.text,an50.text,an55.text,an60.text,an65.text,an70.text,an75.text,an80.text,an85.text,an90.text,an95.text,an100.text,an105.text)
            //console.log("Setting inputs")
            }
        }
    }
}
