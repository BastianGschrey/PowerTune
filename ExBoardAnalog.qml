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
            property alias ex75save : ex75.text
            property alias checkan0ntcsave  : checkan0ntc.checkState
            property alias checkan1ntcsave  : checkan1ntc.checkState
            property alias checkan2ntcsave  : checkan2ntc.checkState
            property alias checkan0100save  : checkan0100.checkState
            property alias checkan01Ksave   : checkan01k.checkState
            property alias checkan1100save  : checkan1100.checkState
            property alias checkan11Ksave   : checkan11k.checkState
            property alias checkan2100save  : checkan2100.checkState
            property alias checkan21Ksave   : checkan21k.checkState
            property alias rpmcheckboxsave  : rpmcheckbox.checkState
            property alias cylindercomboboxsave : cylindercombobox.currentIndex
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
            property alias an7dampingfactorsave : an7dampingfactor.text



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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            enabled: checkan0ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex05
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            enabled: checkan1ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex15
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            enabled: checkan2ntc.checked == true ? false : true
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex25
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex35
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex45
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex55
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex65
            width: main.width / 14
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
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: ex75
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "5"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text {
            text: "Ex AN 7"
            font.pixelSize: main.width / 55;
            color:"white"
        }
        Text {

            text: "damping "
            font.pixelSize: main.width / 55;
            color:"white"
        }
        TextField {
            id:an7dampingfactor
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            text: "0"
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        Text {
            text: "RPM CAN"
            font.pixelSize: main.width / 55;
            color:"white"
        }
        CheckBox {
            id: rpmcheckbox
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        //Placeholder
        Text {
            text: " "
            font.pixelSize: main.width / 55;
            color:"white"
        }

        Text {
            text: "Cylinders"
            font.pixelSize: main.width / 65;
            color:"white"
        }
        ComboBox {
            id: cylindercombobox
            visible: { (rpmcheckbox.checked == true) ? true : false; }
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 75;
            //model: ["2","3","4","5","6","8","12"]
            model: ["0.5","0.6","0.7","0.8","0.9","1","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2","2.1","2.2","2.3","2.4","2.5","2.6","2.7","2.8","2.9","3","3.1","3.2","3.3","3.4","3.5","3.6","3.7","3.8","3.9","4","4.1","4.2","4.3","4.4","4.5","4.6","4.7","4.8","4.9","5","5.1","5.2","5.3","5.4","5.5","5.6","5.7","5.8","5.9","6","6.1","6.2","6.3","6.4","6.5","6.6","6.7","6.8","6.9","7","7.1","7.2","7.3","7.4","7.5","7.6","7.7","7.8","7.9","8","8.1","8.2","8.3","8.4","8.5","8.6","8.7","8.8","8.9","9","9.1","9.2","9.3","9.4","9.5","9.6","9.7","9.8","9.9","10","10.1","10.2","10.3","10.4","10.5","10.6","10.7","10.8","10.9","11","11.1","11.2","11.3","11.4","11.5","11.6","11.7","11.8","11.9","12","12.1","12.2","12.3","12.4","12.5","12.6","12.7","12.8","12.9"]
            onCurrentIndexChanged: inputs.setInputs();
            delegate: ItemDelegate {
                width: cylindercombobox.width
                text: cylindercombobox.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                font.weight: cylindercombobox.currentIndex == index ? Font.DemiBold : Font.Normal
                font.family: cylindercombobox.font.family
                font.pixelSize: cylindercombobox.font.pixelSize
                highlighted: cylindercombobox.highlightedIndex == index
                hoverEnabled: cylindercombobox.hoverEnabled
            }
            }
        Item {
            id: inputs
            function setInputs()
            {
            //console.log("QML Damping"+an7dampingfactor.text)
            //,const int &AN0R3VAL,const int &AN0R4VAL,const int &AN1R3VAL,const int &AN1R4VAL,const int &AN2R3VAL,const int &AN2R4VAL
            Dashboard.setsmootexAnalogInput7(an7dampingfactor.text);
            Dashboard.setEXAnalogVal(ex00.text,ex05.text,ex10.text,ex15.text,ex20.text,ex25.text,ex30.text,ex35.text,ex40.text,ex45.text,ex50.text,ex55.text,ex60.text,ex65.text,ex70.text,ex75.text,checkan0ntc.checkState,checkan1ntc.checkState,checkan2ntc.checkState,checkan0100.checkState,checkan01k.checkState,checkan1100.checkState,checkan11k.checkState,checkan2100.checkState,checkan21k.checkState)
            Dashboard.setSteinhartcalc(t10.text,t20.text,t30.text,r10.text,r20.text,r30.text,t11.text,t21.text,t31.text,r11.text,r21.text,r31.text,t12.text,t22.text,t32.text,r12.text,r22.text,r32.text)
            if(rpmcheckbox.checked == true)
            {
                Extender.variables(cylindercombobox.textAt(cylindercombobox.currentIndex))
            }

            }
        }
    }
    Text {
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.right: parent.right
        text: "Volt. divider jumpers"
        font.pixelSize: main.width / 55;color:"white"}
    Grid {
        id:inputgrid2
        anchors.left:inputgrid.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 40
        rows:4
        columns: 9
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
        Text { text: "100Ω J."
            font.pixelSize: main.width / 55;color:"white"}
        Text { text: "1KΩ J."
            font.pixelSize: main.width / 55;color:"white"}
        CheckBox {
            id: checkan0ntc
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        TextField {
            id: t10
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "-20"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r10
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "15462"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t20
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "20"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r20
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "2500"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t30
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "80"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r30
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "323"
            enabled: checkan0ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        CheckBox {
            id: checkan0100
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        CheckBox {
            id: checkan01k
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        CheckBox {
            id: checkan1ntc
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        TextField {
            id: t11
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "-20"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r11
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
           // text: "14600"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t21
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "20"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r21
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "2200"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t31
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "80"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r31
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "290"
            enabled: checkan1ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        CheckBox {
            id: checkan1100
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        CheckBox {
            id: checkan11k
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        CheckBox {
            id: checkan2ntc
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        TextField {
            id: t12
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "-20"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r12
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "14600"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t22
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "20"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r22
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "2200"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: t32
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "80"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        TextField {
            id: r32
            width: main.width / 14
            height: main.height /15
            font.pixelSize: main.width / 55
            //text: "290"
            enabled: checkan2ntc.checked == true ? true : false
            inputMethodHints: Qt.ImhFormattedNumbersOnly  // this ensures valid inputs are number only
            onEditingFinished: inputs.setInputs()

        }
        CheckBox {
            id: checkan2100
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
        CheckBox {
            id: checkan21k
            width: main.width / 14
            height: main.height /15
            onCheckStateChanged: inputs.setInputs();
            }
    }
    Component.onCompleted: {

    inputs.setInputs();
    }
/*
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
        text: qsTr("Usage : Enter the Value that should be displayed at 0 V in the field Val.@ 0V and the Value that should be displayed at 5 V in the field Val @5V. The calculated values will be available in the corresponding datasource EXAnalogCalcx. Analog 0-3 can also be used for temperature sensors (Connect one side of the Variable resistance Sensor to 5 V and the other side to the AN0/1/2, also enable the 1K pullup resistor ).Set the tick for Temp. in , then  Measure the resistance of the sensor at 3 different temperatures and enter each temperature in degree celsis and enter the Temperature values in T1-T3 and the corresponding resistance in R1-R3. The output will be shown in EXanalogcalc x as temperature. The input will have to be done in degrees celsisus for calibration . The output will show in degrees celsius or fahrenheit, dependending on the Temp units selection in the main settings. ")
    }
    */
    }

