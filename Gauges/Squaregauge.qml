import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle {

    id: gauge
    width: 250
    height: 200
    property string information: "Square gauge"
    border.color: "#9f9f9f"
    border.width: 2
    Component.onCompleted: set()

    property string mainvaluename
    property string secvaluename
    property alias title: gaugetextfield.text
    property alias mainunit: mainvalueunittextfield.text
    property alias vertgaugevisible: vertgauge.visible
    property alias horigaugevisible: horizgauge.visible
    property alias secvaluevisible: secondaryvaluetextfield.visible
    property alias secvalue: secondaryvaluetextfield.text
    property alias maintextvalue: mainvaluetextfield.text
    property alias mainvalue: mainvaluetextfield.text
    property alias maxvalue: vertgauge.maximumValue
    property alias titlecolor: titlebar.color
    property alias titlefontsize :gaugetextfield.font.pixelSize
    property alias mainfontsize :mainvaluetextfield.font.pixelSize
    property string resettitlecolor
    property string resetbackroundcolor
    property string framecolor
    property string titletextcolor
    property string textcolor
    property string barcolor
    property double mainvalue
    property int maxvalue
    property double warnvaluehigh: 20000
    property double warnvaluelow : -20000

    Drag.active: true

    Connections{
    target: Dashboard
    onDraggableChanged:togglemousearea()
    }

    MouseArea {
        id: touchArea
        anchors.fill: parent
        drag.target: parent
        enabled: false
        //drag.active:
        onDoubleClicked: {
        popupmenu.popup(touchArea.mouseX, touchArea.mouseY);
        }
        /*
        Timer {
            id: pressAndHoldTimer
            interval: 1000
            onTriggered: popupmenu.popup(touchArea.mouseX, touchArea.mouseY);


        }
        onPressed: pressAndHoldTimer.start()
        onReleased: pressAndHoldTimer.stop();*/
    }



    Rectangle {
        id: titlebar
        width: parent.width - 4
        //height: (parent.height) * 0.2
        height: 30
        anchors.top : parent.top
        anchors.left: parent.left
        color: titlecolor
        clip: false
        visible: true
        anchors.topMargin: 2
        anchors.leftMargin: 2

    }

    SequentialAnimation {
        id: anim
        loops: Animation.Infinite
        running: false
        PropertyAnimation {
            target: titlebar
            property: "color"
            from: "darkred"
            to: "red"
            duration: 500
        }
        PropertyAnimation {
            target: titlebar
            property: "color"
            from: "red"
            to: "darkred"
            duration: 500
        }
    }
    SequentialAnimation {
        id: anim2
        loops: Animation.Infinite
        running: false
        PropertyAnimation {
            target: gauge
            property: "color"
            from: "darkred"
            to: "red"
            duration: 500
        }
        PropertyAnimation {
            target: gauge
            property: "color"
            from: "red"
            to: "darkred"
            duration: 500
        }
    }
    Text {
        id: gaugetextfield
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        font.bold: true
        font.family: "Eurostile"
        color: titletextcolor

    }

    Text {
        id: mainvaluetextfield
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 50
        font.family: "Eurostile"
        color: "white"
        onTextChanged: warningindication.warn()
    }

    Text {
        id: mainvalueunittextfield
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 28
        font.family: "Eurostile"
        font.bold: true
        color: textcolor
    }


    Text {
        id: secondaryvaluetextfield
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        height: parent.height * 0.2
        font.pixelSize: 28
        font.family: "Eurostile"
        color: textcolor
    }

    Gauge {
        id: vertgauge
        height: parent.height - 50
        width: parent.width * 0.1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 10
        orientation: Qt.Vertical
        minorTickmarkCount: 0
        tickmarkAlignment: Qt.AlignRight
        value: parent.mainvalue
        maximumValue: parent.maxvalue

        style: GaugeStyle {
            tickmarkLabel: Text {
                font.pixelSize: 14
                color: "transparent"
            }
            tickmark: Item {
                implicitWidth: 18
                implicitHeight: 1

                Rectangle {
                    color: "transparent"
                    anchors.fill: parent
                    anchors.leftMargin: 3
                    anchors.rightMargin: 3
                }
            }
            valueBar: Rectangle {
                id: vertbar
                implicitWidth: 25
                color: barcolor
            }
        }

    }
    Item {
        id: warningindication
        function warn()
        {
            if (mainvaluetextfield.text > warnvaluehigh || mainvaluetextfield.text < warnvaluelow )anim.running = true,anim2.running = true;
            else anim.running = false,anim2.running = false,titlebar.color = resettitlecolor ,gauge.color = resetbackroundcolor;
        }
    }

    function set()
    {
        gauge.color = resetbackroundcolor;
        gauge.border.color = framecolor;
        gauge.titlecolor = resettitlecolor;
        gaugetextfield.color =  titletextcolor;
        secondaryvaluetextfield.color =  textcolor;
        mainvaluetextfield.color =  textcolor;
        mainvalueunittextfield.color =  textcolor;
        //vertgauge.valueBar.color = "green"
    }
    function togglemousearea()
    {
        if (Dashboard.draggable === 1)
        {
         touchArea.enabled = true;
        //    console.log ("Enable square touch");
        }
        else
            touchArea.enabled = false;
        //    console.log ("Disable square touch");
    }
    Gauge {
        id: horizgauge
        height: parent.height * 0.2
        width: parent.width * 0.9
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        orientation: Qt.Horizontal
        minorTickmarkCount: 0
        tickmarkAlignment: Qt.AlignRight
        value: parent.mainvalue
        maximumValue: parent.maxvalue

        style: GaugeStyle {

            tickmarkLabel: Text {
                font.pixelSize: 14
                color: "transparent"
            }
            tickmark: Item {
                implicitWidth: 18
                implicitHeight: 1

                Rectangle {
                    color: "transparent"
                    anchors.fill: parent
                    anchors.leftMargin: 3
                    anchors.rightMargin: 3
                }
            }
            valueBar: Rectangle {
                implicitWidth: 25
                color: barcolor
            }
        }


    }
    Item {
        id: menustructure

        Menu {
            id: popupmenu
            MenuItem {
                text: "Change size"
                font.pixelSize: 15
                onClicked: sizemenu.popup(touchArea.mouseX, touchArea.mouseY)

            }
            MenuItem {
                text: "Change sec value"
                font.pixelSize: 15
                onClicked: {
                    cbxSecondary.visible = true;
                    btnSecSrc.visible = true;
                }
            }
            MenuItem {
                text: "Change title"
                font.pixelSize: 15
                onClicked: {
                    titlenameValue.visible = true;
                    btntitleValue.visible = true;
                }
            }
            MenuItem {
                text: "Set bar gauge max"
                font.pixelSize: 15
                onClicked: {
                    bargaugeMax.visible = true;
                    btnmaxValue.visible = true;
                }
            }
            MenuItem {
                text: "toggle sec value"
                font.pixelSize: 15
                onClicked: {
                    if(secondaryvaluetextfield.visible === true){
                        secondaryvaluetextfield.visible = false;
                    }
                    else{
                        secondaryvaluetextfield.visible = true;
                    }
                }
            }
            MenuItem {
                text: "toggle vertical bar gauge"
                font.pixelSize: 15
                onClicked: {
                    if(vertgauge.visible === true){
                        vertgauge.visible = false;
                    }
                    else{
                        vertgauge.visible = true;
                        horizgauge.visible = false;

                    }
                }
            }

            MenuItem {
                text: "toggle horizontal bar gauge"
                font.pixelSize: 15
                onClicked: {
                    if(horizgauge.visible === true){
                        horizgauge.visible = false;
                    }
                    else{
                        horizgauge.visible = true;
                        vertgauge.visible = false;
                    }
                }
            }

            MenuItem {
                text: "Set min warning"
                font.pixelSize: 15
                onClicked: {
                    txtMinValue.visible = true;
                    btnMinValue.visible = true;
                }
            }

            MenuItem {
                text: "Set max warning"
                font.pixelSize: 15
                onClicked: {
                    txtMaxValue.visible = true;
                    btnMaxValue.visible = true;
                }
            }
            MenuItem {
                text: "Change unit symbol"
                font.pixelSize: 15
                onClicked: symbolMenu.popup(touchArea.mouseX, touchArea.mouseY)
            }
            MenuItem {
                text: "remove gauge"
                font.pixelSize: 15
                onClicked: gauge.destroy()
            }
        }

        Menu {
            id: sizemenu
            MenuItem {
                text: "small"
                onClicked: {

                    gauge.width = 160;
                    gauge.height = 120;
                }
            }
            MenuItem {
                text: "medium"
                onClicked: {

                    gauge.width = 300;
                    gauge.height = 200;
                }
            }
            MenuItem {
                text: "large"
                onClicked: {

                    gauge.width = 400;
                    gauge.height = 266;
                }
            }
        }

        ///////////////////
        Menu {
            id: symbolMenu
            MenuItem {
                text: "°"
                onClicked: {
                    mainvalueunittextfield.text = "°"
                }
            }
            MenuItem {
                text: "°C"
                onClicked: {
                    mainvalueunittextfield.text = "°C"
                }
            }
            MenuItem {
                text: "°F"
                onClicked: {
                    mainvalueunittextfield.text = "°F"
                }
            }
            MenuItem {
                text: "kPa"
                onClicked: {
                    mainvalueunittextfield.text = "kPa"
                }
            }
            MenuItem {
                text: "PSI"
                onClicked: {
                    mainvalueunittextfield.text = "PSI"
                }
            }
            MenuItem {
                text: "ms"
                onClicked: {
                    mainvalueunittextfield.text = "ms"
                }
            }
            MenuItem {
                text: "V"
                onClicked: {
                    mainvalueunittextfield.text = "V"
                }
            }
            MenuItem {
                text: "mV"
                onClicked: {
                    mainvalueunittextfield.text = "mV"
                }
            }
            MenuItem {
                text: "λ"
                onClicked: {
                    mainvalueunittextfield.text = "λ"
                }
            }
            MenuItem {
                text: "kph"
                onClicked: {
                    mainvalueunittextfield.text = "kph"
                }
            }
            MenuItem {
                text: "mph"
                onClicked: {
                    mainvalueunittextfield.text = "mph"
                }
            }
        }
    }

    Item {
        id: secSourceSelector
        anchors.fill: parent

        ComboBox {
            id: cbxSecondary
            visible: false
            textRole: "name"
            //model: dataSourceModel
        }

        Button {
            id: btnSecSrc
            x: 150
            visible: false
            text: "apply"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: {
                cbxSecondary.visible = false;
                btnSecSrc.visible = false;
                secvalue = cbxSecondary.currentIndex;
                secondaryvaluetextfield.visible = true;
            }
        }

    }

    Item {
        id: minValueSelect
        anchors.fill: parent

        TextField {
            id: txtMinValue
            width: 94
            height: 40
            //inputMask: "00000"
            visible: false
            text: warnvaluelow;
            inputMethodHints: Qt.ImhDigitsOnly
        }


        Button {
            id: btnMinValue
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                txtMinValue.visible = false;
                btnMinValue.visible = false;
                warnvaluelow = txtMinValue.text;
            }
        }

    }

    Item {
        id: maxValueSelect
        anchors.fill: parent

        TextField {
            id: txtMaxValue
            width: 94
            height: 40
            //inputMask: "00000"
            visible: false
            text: warnvaluehigh
            inputMethodHints: Qt.ImhDigitsOnly
        }

        Button {
            id: btnMaxValue
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                txtMaxValue.visible = false;
                btnMaxValue.visible = false;
                warnvaluehigh = txtMaxValue.text;
            }
        }

    }
    Item {
        id: titleRename
        anchors.fill: parent

        TextField {
            id: titlenameValue
            width: 94
            height: 40
            visible: false
            text: title
            //inputMethodHints: Qt.ImhDigitsOnly
        }


        Button {
            id: btntitleValue
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                title = titlenameValue.text;
                titlenameValue.visible = false;
                btntitleValue.visible = false;
            }
        }
    }
    Item {
         id: bargaugeMaxVal
         anchors.fill: parent

         TextField {
             id: bargaugeMax
             width: 94
             height: 40
             visible: false
             text: maxvalue
             inputMethodHints: Qt.ImhDigitsOnly
         }

         Button {
             id: btnmaxValue
             x: 119
             text: qsTr("OK")
             anchors.top: parent.top
             anchors.topMargin: 0
             anchors.right: parent.right
             anchors.rightMargin: 0
             visible: false
             onClicked: {
                 maxvalue = bargaugeMax.text;
                 bargaugeMax.visible = false;
                 btnmaxValue.visible = false;
             }
         }
     }
}
