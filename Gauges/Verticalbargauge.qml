import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle {
    id: gauge
    width: 100
    height: 80
    color: "transparent"
    antialiasing: false
    Drag.active: true

    property string information: "Bar gauge"
    property string gaugename
    property string mainvaluename
    property alias gaugetext: gaugetextfield.text
    property alias gaugevalue: gauge1.value
    property double minvalue: gauge1.minimumValue
    property double maxvalue: gauge1.maximumValue
    property int decimalpoints
    property double warnvaluehigh: 20000
    property double warnvaluelow : -20000

    Connections{
        target: Dashboard
        onDraggableChanged:togglemousearea()
    }

    MouseArea {
        id: touchArea
        anchors.fill: parent
        drag.target: parent
        enabled: false
        onDoubleClicked: {
            popupmenu.popup(touchArea.mouseX, touchArea.mouseY);
        }
    }
    Gauge {
        id: gauge1
        height: 200
        anchors.fill: parent
        anchors.margins: 10
        orientation : Qt.Horizontal
        minorTickmarkCount: 4
        //labelStepSize: 50
        minimumValue: minvalue
        maximumValue: maxvalue
        tickmarkStepSize : maximumValue / 4
        font.pixelSize: 15

        //value: Dashboard.MAP
        Behavior on value {
            NumberAnimation {
                duration: 5
            }
        }
        Text {
            id: gaugetextfield
            font.pixelSize: (parent.height / 3)
            anchors.top : parent.top
            font.bold: true
            font.family: "Eurostile"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            text : gaugevalue.toFixed(decimalpoints) + " " +gaugename
        }
        style: GaugeStyle {
            valueBar: Rectangle {
                implicitWidth:  20
                color: Qt.rgba(gauge1.value / gauge1.maximumValue, 0, 1 - gauge1.value / gauge1.maximumValue, 1)
            }
        }
    }

    Item {
        id: menustructure
        Menu {
            id: popupmenu
            MenuItem {
                text: "Change max value"
                font.pixelSize: 15
                onClicked: {
                    bargaugeMax.visible = true;
                    btnmaxValue.visible = true;
                }
            }
            MenuItem {
                text: "Change min value"
                font.pixelSize: 15
                onClicked:    {
                    txtBarMinValue.visible = true;
                    btnBarMinValue.visible = true;
                }
            }
            MenuItem {
                text: "Change decimal points"
                font.pixelSize: 15
                onClicked:    {
                    cbx_decimalplaces.visible = true;
                    btndecimalplaces.visible = true;
                }
            }
            /*
            MenuItem {
                text: "Change warning max value"
                font.pixelSize: 15
                onClicked:    {
                    txtMaxValue.visible = true;
                    btnMaxValue.visible = true;
                }
            }
            MenuItem {
                text: "Change warning min value"
                font.pixelSize: 15
                onClicked:    {
                    btnminValue.visible = true;
                    bargaugeMin.visible = true;
                }
            }
            */
            MenuItem {
                text: "Change name"
                font.pixelSize: 15
                onClicked:    {
                    txtgaugenamechange.visible = true;
                    btngaugenamechange.visible = true;
                }
            }
            MenuItem {
                text: "remove gauge"
                font.pixelSize: 15
                onClicked: gauge.destroy()
            }

        }
    }
    // Settings submenues
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
        id: minValueSelect
        anchors.fill: parent

        TextField {
            id: txtBarMinValue
            width: 94
            height: 40
            visible: false
            text: minvalue;
        }
        Button {
            id: btnBarMinValue
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                minvalue = txtBarMinValue.text;
            }
        }
    }
    Item{
        id: decimalpointsval
        anchors.fill: parent
        ComboBox {
            id: cbx_decimalplaces
            visible: false
            model: ["0","1","2","3"]
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
            }
        }
    }
    Item {
        id: bargaugeMinVal
        anchors.fill: parent

        TextField {
            id: bargaugeMin
            width: 94
            height: 40
            visible: false
            text: minvalue
        }

        Button {
            id: btnminValue
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                minvalue = bargaugeMin.text;
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
            }
        }
    }
    Item {
        id: gaugenamechange
        anchors.fill: parent

        TextField {
            id: txtgaugenamechange
            width: 94
            height: 40
            visible: false
            text: gaugename
        }

        Button {
            id: btngaugenamechange
            x: 119
            text: qsTr("OK")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            visible: false
            onClicked: {
                hidemenues();
                gaugename = txtgaugenamechange.text;
            }
        }
    }

    //Functions
    function togglemousearea()
    {
        if (Dashboard.draggable === 1)
        {
            touchArea.enabled = true;
        }
        else
            touchArea.enabled = false;
    }
    function hidemenues()
    {
        cbx_decimalplaces.visible = false;
        btndecimalplaces.visible = false;
        bargaugeMax.visible = false;
        btnmaxValue.visible = false;
        btnminValue.visible = false;
        bargaugeMin.visible = false;
        txtMaxValue.visible = false;
        btnMaxValue.visible = false;
        txtBarMinValue.visible = false;
        btnBarMinValue.visible = false;
        txtgaugenamechange.visible = false;
        btngaugenamechange.visible = false;
    }
}
