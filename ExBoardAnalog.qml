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
        id:exsave
        Settings {

            property alias ex00save : ex00.text
            property alias ex05save : ex05.text
            property alias ex10save : ex10.text
            property alias ex15save : ex15.text
            property alias ex20save : ex20.text
            property alias ex25save : ex25.text
            property alias ex30save : ex30.text
            property alias ex35save : ex35.text
            property alias ex40save : ex40.text
            property alias ex45save : ex45.text
            property alias ex50save : ex50.text
            property alias ex55save : ex55.text
            property alias ex60save : ex60.text
            property alias ex65save : ex65.text
            property alias ex70save : ex70.text
            property alias checkan0ntcsave : checkan0ntc.checkState
            property alias checkan1ntcsave : checkan1ntc.checkState
            property alias checkan2ntcsave : checkan2ntc.checkState
            property alias t10save : t10.text
            property alias r10save : r10.text
            property alias t20save : t20.text
            property alias r20save : r20.text
            property alias t30save : t30.text
            property alias r30save : r30.text
            property alias t11save : t11.text
            property alias r11save : r11.text
            property alias t21save : t21.text
            property alias r21save : r21.text
            property alias t31save : t31.text
            property alias r31save : r31.text
            property alias t12save : t12.text
            property alias r12save : r12.text
            property alias t22save : t22.text
            property alias r22save : r22.text
            property alias t32save : t32.text
            property alias r32save : r32.text


        }
    }

    Grid {
        id:inputgrid
        rows:12
        columns: 3
        spacing: 5
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 40
        Text { text: "  "
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "Val. @ 0V"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "Val. @ 5V"
            font.pixelSize: main.width / 55;color:"white"}

        Text { text: "EX AN 0"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex00
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            enabled: checkan0ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex05
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            enabled: checkan0ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }

        Text { text: "EX AN 1"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex10
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            enabled: checkan1ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex15
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            enabled: checkan1ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "EX AN 2"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex20
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            enabled: checkan2ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex25
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            enabled: checkan2ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "EX AN 3"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex30
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex35
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "EX AN 4"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex40
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex45
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "EX AN 5"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex50
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex55
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "EX AN 6"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex60
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex65
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text { text: "EX AN 7"
            font.pixelSize: main.width / 55;color:"white"}
        TextField {
            id: ex70
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex75
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }

        Item {
            id: inputs
            function setInputs()
            {

            //console.log("Checkstates :" + checkan0ntc.checkState + checkan1ntc.checkState + checkan2ntc.checkState)
            Dashboard.setEXAnalogVal(ex00.text,ex05.text,ex10.text,ex15.text,ex20.text,ex25.text,ex30.text,ex35.text,ex40.text,ex45.text,ex50.text,ex55.text,ex60.text,ex65.text,ex70.text,ex75.text,checkan0ntc.checkState,checkan1ntc.checkState,checkan2ntc.checkState)
            Dashboard.setSteinhartcalc(t10.text,t20.text,t30.text,r10.text,r20.text,r30.text,t11.text,t21.text,t31.text,r11.text,r21.text,r31.text,t12.text,t22.text,t32.text,r12.text,r22.text,r32.text)
            }
        }
    }
    Grid {
        id:inputgrid2
        anchors.left:inputgrid.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 40
        rows:4
        columns: 7
        spacing: 5
        Text { text: "Temp. In"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "T1 (°C)"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "R1 (Ω)"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "T2 (°C)"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "R2 (Ω)"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "T3 (°C)"
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "R3 (Ω)"
            font.pixelSize: main.width / 55;color:"white"}
        CheckBox {
            id: checkan0ntc
            width: main.width / 12
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        TextField {
            id: t10
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "-20"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r10
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "15462"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t20
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "20"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r20
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "2500"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t30
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "80"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r30
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "323"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        CheckBox {
            id: checkan1ntc
            width: main.width / 12
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        TextField {
            id: t11
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "-20"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r11
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
           // text: "14600"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t21
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "20"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r21
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "2200"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t31
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "80"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r31
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "290"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        CheckBox {
            id: checkan2ntc
            width: main.width / 12
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        TextField {
            id: t12
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "-20"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r12
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "14600"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t22
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "20"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r22
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "2200"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t32
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "80"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r32
            width: main.width / 12
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "290"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
    }
    Component.onCompleted: {

    inputs.setInputs();
    }

    Text {
        id: explanationtext
        anchors.left: inputgrid.right
        anchors.leftMargin: 20
        anchors.top: inputgrid2.bottom
        anchors.topMargin: 20
        font.pixelSize: parent.width / 55
        font.bold: true
        width: parent.width / 1.5
        horizontalAlignment: Text.AlignHCenter
        color: "black"
        wrapMode: Text.WordWrap
        text: qsTr("Usage : Enter the Value that should be displayed at 0 V in the field Val.@ 0V and the Value that should be displayed at 5 V in the field Val @5V. The calculated values will be available in the corresponding datasource EXAnalogCalcx. Analog 0-3 can also be used for temperature sensors (5V input with 330 Ohm Resistor (R1) for the Voltage divider and 1.43 K in parallel to the Sensor).Set the tick for Temp. in , then  Measure the resistance of the sensor at 3 different temperatures and enter each temperature in degree celsis and enter the Temperature values in T1-T3 and the corresponding resistance in R1-R3. The output will be shown in EXanalogcalc x as temperature. The input will have to be done in degrees celsisus for calibration . The output will show in degrees celsius or fahrenheit, dependending on the Temp units selection in the main settings. ")
    }
    }

