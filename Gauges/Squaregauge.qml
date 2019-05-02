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
    Component.onCompleted: {set();

    }

    property string mainvaluename
    property string secvaluename
    property alias title: gaugetextfield.text
    property alias mainunit: mainvalueunittextfield.text
    property alias vertgaugevisible: vertgauge.visible
    property alias horigaugevisible: horizgauge.visible
    property alias secvaluevisible: secondaryvaluetextfield.visible
    property alias secvalue: secondaryvaluetextfield.text
    property alias mainvalue : placeholder.text
    property double maxvalue: vertgauge.maximumValue
    property alias titlecolor: titlebar.color
    property alias titlefontsize :gaugetextfield.font.pixelSize
    property alias mainfontsize :mainvaluetextfield.font.pixelSize
    property string resettitlecolor
    property string resetbackroundcolor
    property string framecolor
    property string titletextcolor
    property string textcolor
    property string barcolor
    property int decimalpoints
    property double warnvaluehigh: 20000
    property double warnvaluelow : -20000

    Drag.active: true
    DatasourcesList{id: powertunedatasource}
/*
    //Intro
    SequentialAnimation {
        id: intro
        running: true
        onRunningChanged:{
        if (intro.running == false )gauge.value  = Qt.binding(function(){return Dashboard[mainvaluename]});
        }
        NumberAnimation {
            id :animation
            target: mainvaluetextfield
            property: "text"
            easing.type: Easing.InOutSine
            from: minvalue
            to: maxvalue
            duration: 500
        }
        NumberAnimation {
            id :animation1
            target: mainvaluetextfield
            property: "text"
            easing.type: Easing.InOutSine
            from: maxvalue
            to: minvalue
            duration: 500
        }
    }
    */
    Connections{
        target: Dashboard
        onDraggableChanged:togglemousearea()
    }
    Text {
        id : placeholder
        onTextChanged: { toggledecimal();}
        Component.onCompleted: {toggledecimal();}
        visible: false
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
    }



    Rectangle {
        id: titlebar
        width: parent.width - 4
        //height: (parent.height) * 0.2
        height: parent.height / 4
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
        anchors.verticalCenter: titlebar.verticalCenter
        anchors.horizontalCenter: titlebar.horizontalCenter
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
        onTextChanged: {
            warningindication.warn();
        }
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
        height: parent.height - titlebar.height
        width: parent.width * 0.1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
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
                implicitWidth: vertgauge.width
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
    //
    function toggledecimal()
    {
        if (decimalpoints < 4)
        {
            mainvaluetextfield.text = parseFloat(placeholder.text).toFixed(decimalpoints);
        }
        else
            mainvaluetextfield.text = placeholder.text;
    }
    function hidemenues()
    {
        txtMaxValue.visible = false;
        btnMaxValue.visible = false;
        txtMinValue.visible = false;
        btnMinValue.visible = false;
        txtwidth.visible = false;
        txtheight.visible = false;
        btnSize.visible =false;
        cbx_titlefontsize.visible =false;
        btntitlefontsize.visible =false;
        cbx_gaugefontsize.visible =false;
        btngaugefontsize.visible =false;
        cbx_decimalplaces.visible  = false;
        btndecimalplaces.visible = false;
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
                implicitWidth: horizgauge.height
                color: barcolor
            }
        }


    }
    Item {
        id: menustructure

        Menu {
            id: popupmenu
            MenuItem {
                text: "Change gauge size"
                font.pixelSize: 15
                onClicked: sizemenu.popup(touchArea.mouseX, touchArea.mouseY)
            }
            MenuItem {
                text: "Title font size"
                font.pixelSize: 15
                onClicked:    {
                    cbx_titlefontsize.visible =true;
                    btntitlefontsize.visible =true;
                }

            }
            MenuItem {
                text: "Gauge font size"
                font.pixelSize: 15
                onClicked:
                {
                    btngaugefontsize.visible =true;
                    cbx_gaugefontsize.visible =true;
                }
            }
            MenuItem {
                text: "Change sec value"
                font.pixelSize: 15
                onClicked: {
                    hidemenues();
                    cbxSecondary.visible = true;
                    btnSecSrc.visible = true;
                }
            }
            MenuItem {
                text: "Change title"
                font.pixelSize: 15
                onClicked: {
                    hidemenues();
                    titlenameValue.visible = true;
                    btntitleValue.visible = true;
                }
            }
            MenuItem {
                text: "Set decimal"
                font.pixelSize: 15
                onClicked: {
                    hidemenues();
                    cbx_decimalplaces.visible = true;
                    btndecimalplaces.visible = true;
                }
            }
            MenuItem {
                text: "Set bar gauge max"
                font.pixelSize: 15
                onClicked: {
                    hidemenues();
                    bargaugeMax.visible = true;
                    btnmaxValue.visible = true;
                }
            }
            MenuItem {
                text: "Toggle sec value"
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
                text: "Toggle vertical bar gauge"
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
                text: "Toggle horizontal bar gauge"
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
                    hidemenues();
                    txtMinValue.visible = true;
                    btnMinValue.visible = true;
                }
            }

            MenuItem {
                text: "Set max warning"
                font.pixelSize: 15
                onClicked: {
                    hidemenues();
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

                    gauge.width = 199;
                    gauge.height = 119;
                }
            }
            MenuItem {
                text: "medium"
                onClicked: {

                    gauge.width = 266;
                    gauge.height = 119;
                }
            }
            MenuItem {
                text: "large"
                onClicked: {

                    gauge.width = 533;
                    gauge.height = 119;
                }
            }
            MenuItem {
                text: "custom"
                onClicked: {
                    txtwidth.visible = true;
                    txtheight.visible = true;
                    btnSize.visible =true;
                }
            }
        }


        Menu {
            id: symbolMenu
            MenuItem {
                text: "None"
                onClicked: {
                    mainvalueunittextfield.text = ""
                }
            }
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
            textRole: "titlename"
            model: powertunedatasource
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
                secvalue = Qt.binding(function(){return Dashboard[powertunedatasource.get(cbxSecondary.currentIndex).sourcename]});
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
            visible: false
            text: warnvaluelow;
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
                hidemenues();
            }
        }
    }
    Item {
        id: gaugeSizeselect
        anchors.fill: parent

        TextField {
            id: txtwidth
            width: 94
            height: 40
            visible: false
            text: gauge.width;
        }
        TextField {
            id: txtheight
            anchors.top : txtwidth.bottom
            width: 94
            height: 40
            visible: false
            text: gauge.height;
        }
        Button {
            id: btnSize
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                gauge.width = txtwidth.text;
                gauge.height = txtheight.text;
            }
        }
    }
    Item {
        id: decimalplacesSelect
        anchors.fill: parent

        ComboBox {
            id: cbx_decimalplaces
            visible: false
            model: ["0","1","2","3","N/A"]
        }
        Button {
            id: btndecimalplaces
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                decimalpoints = cbx_decimalplaces.currentIndex;
                toggledecimal();
            }
        }
    }
    Item {
        id: titlefontsizeSelect
        anchors.fill: parent

        ComboBox {
            id: cbx_titlefontsize
            visible: false
            model: [10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260]
        }
        Button {
            id: btntitlefontsize
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                gaugetextfield.font.pixelSize = cbx_titlefontsize.textAt(cbx_titlefontsize.currentIndex);
            }
        }
    }
    Item {
        id: gaugefontsizeSelect
        anchors.fill: parent

        ComboBox {
            id: cbx_gaugefontsize
            visible: false
            model: [10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260]
        }
        Button {
            id: btngaugefontsize
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                mainvaluetextfield.font.pixelSize = cbx_gaugefontsize.textAt(cbx_gaugefontsize.currentIndex);
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
            //inputMethodHints: Qt.ImhDigitsOnly
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
                hidemenues();
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
                hidemenues();
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
                hidemenues();
                maxvalue = bargaugeMax.text;
                bargaugeMax.visible = false;
                btnmaxValue.visible = false;
            }
        }
    }
}
