import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0



Rectangle {
    id: mainrectangle
    width: parent.width
    height: parent.height
    color: "black"

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton

        onClicked: pieMenu.popup(mouseX, mouseY)
    }
    // Remember the Selected Gauges
    Item {
        id: dynamicDashSettings
        Settings {

            property alias sourcegauge1: gauge1.source
            property alias sourcegauge2: gauge2.source
            property alias sourcegauge3: gauge3.source
            property alias sourcegauge4: gauge4.source
            property alias sourcegauge5: gauge5.source
            property alias sourcegauge6: gauge6.source
            property alias sourcegauge7: gauge7.source
            property alias sourcegauge8: gauge8.source
            property alias sourcegauge9: gauge9.source
            property alias sourcegauge10: gauge10.source
            property alias sourcegauge11: gauge11.source
            property alias sourcegauge12: gauge12.source
            property alias sourcegauge13: gauge13.source
            property alias sourcegauge14: gauge14.source
            property alias sourcegauge15: gauge15.source
            property alias sourcegauge16: gauge16.source
            property alias sourcegauge17: gauge17.source
            property alias sourcegauge18: gauge18.source
            property alias sourcegauge19: gauge19.source
            property alias sourcegauge20: gauge20.source

            property alias remembergauge1: remember.gauge1select
            property alias remembergauge2: remember.gauge2select
            property alias remembergauge3: remember.gauge3select
            property alias remembergauge4: remember.gauge4select
            property alias remembergauge5: remember.gauge5select
            property alias remembergauge6: remember.gauge6select
            property alias remembergauge7: remember.gauge7select
            property alias remembergauge8: remember.gauge8select
            property alias remembergauge9: remember.gauge9select
            property alias remembergauge10: remember.gauge10select
            property alias remembergauge11: remember.gauge11select
            property alias remembergauge12: remember.gauge12select
            property alias remembergauge13: remember.gauge13select
            property alias remembergauge14: remember.gauge14select
            property alias remembergauge15: remember.gauge15select
            property alias remembergauge16: remember.gauge16select
            property alias remembergauge17: remember.gauge17select
            property alias remembergauge18: remember.gauge18select
            property alias remembergauge19: remember.gauge19select
            property alias remembergauge29: remember.gauge20select

            property alias widthloader1: loader1.width
            property alias widthloader2: loader2.width
            property alias widthloader3: loader3.width
            property alias widthloader4: loader4.width
            property alias widthloader5: loader5.width
            property alias widthloader6: loader6.width
            property alias widthloader7: loader7.width
            property alias widthloader8: loader8.width
            property alias widthloader9: loader9.width
            property alias widthloader10: loader10.width
            property alias widthloader11: loader11.width
            property alias widthloader12: loader12.width
            property alias widthloader13: loader13.width
            property alias widthloader14: loader14.width
            property alias widthloader15: loader15.width
            property alias widthloader16: loader16.width
            property alias widthloader17: loader17.width
            property alias widthloader18: loader18.width
            property alias widthloader19: loader19.width
            property alias widthloader20: loader20.width

            property alias xloader1: loader1.x
            property alias yloader1: loader1.y
            property alias xloader2: loader2.x
            property alias yloader2: loader2.y
            property alias xloader3: loader3.x
            property alias yloader3: loader3.y
            property alias xloader4: loader4.x
            property alias yloader4: loader4.y
            property alias xloader5: loader5.x
            property alias yloader5: loader5.y
            property alias xloader6: loader6.x
            property alias yloader6: loader6.y
            property alias xloader7: loader7.x
            property alias yloader7: loader7.y
            property alias xloader8: loader8.x
            property alias yloader8: loader8.y
            property alias xloader9: loader9.x
            property alias yloader9: loader9.y
            property alias xloader10: loader10.x
            property alias yloader10: loader10.y
            property alias xloader11: loader11.x
            property alias yloader11: loader11.y
            property alias xloader12: loader12.x
            property alias yloader12: loader12.y
            property alias xloader13: loader13.x
            property alias yloader13: loader13.y
            property alias xloader14: loader14.x
            property alias yloader14: loader14.y
            property alias xloader15: loader15.x
            property alias yloader15: loader15.y
            property alias xloader16: loader16.x
            property alias yloader16: loader16.y
            property alias xloader17: loader17.x
            property alias yloader17: loader17.y
            property alias xloader18: loader18.x
            property alias yloader18: loader18.y
            property alias xloader19: loader19.x
            property alias yloader19: loader19.y
            property alias xloader20: loader20.x
            property alias yloader20: loader20.y
        }
    }
    Item { id:loader1; width: 200; height: width;
        Drag.active: dragArea.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea
            anchors.fill: parent
            drag.target: dragArea
        }
        Loader {
            id: gauge1
            anchors.fill: loader1
        }
    }
    Item { id:loader2; width: 200; height: width;
        Drag.active: dragArea2.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea2
            anchors.fill: parent
            drag.target: dragArea2
        }
        Loader { id: gauge2
            anchors.fill: parent
        }
    }
    Item { id:loader3; width: 200; height: width;
        Drag.active: dragArea3.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea3
            anchors.fill: parent
            drag.target: dragArea3
        }
        Loader { id: gauge3
            anchors.fill: parent
        }
    }
    Item { id:loader4; width: 200; height: width;
        Drag.active: dragArea4.drag.active
        MouseArea {
            id: dragArea4
            anchors.fill: parent
            drag.target: dragArea4
        }
        Loader { id: gauge4
            anchors.fill: parent
        }
    }
    Item { id:loader5; width: 200; height: width
        Drag.active: dragArea5.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea5
            anchors.fill: parent
            drag.target: dragArea5
        }
        Loader { id: gauge5
            anchors.fill: parent}
    }
    Item { id:loader6; width: 200; height: width
        Drag.active: dragArea6.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea6
            anchors.fill: parent
            drag.target: dragArea6
        }
        Loader { id: gauge6
            anchors.fill: parent}
    }
    Item { id:loader7; width: 200; height: width
        Drag.active: dragArea7.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea7
            anchors.fill: parent
            drag.target: dragArea7
        }
        Loader { id: gauge7
            anchors.fill: parent}
    }
    Item { id:loader8; width: 200; height: width
        Drag.active: dragArea8.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea8
            anchors.fill: parent
            drag.target: dragArea8
        }
        Loader { id: gauge8
            anchors.fill: parent}
    }
    Item { id:loader9; width: 200; height: width
        Drag.active: dragArea9.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea9
            anchors.fill: parent
            drag.target: dragArea9
        }
        Loader { id: gauge9
            anchors.fill: parent}
    }
    Item { id:loader10; width: 200; height: width
        Drag.active: dragArea10.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea10
            anchors.fill: parent
            drag.target: dragArea10
        }
        Loader { id: gauge10
            anchors.fill: parent}
    }
    Item { id:loader11; width: 200; height: width
        Drag.active: dragArea11.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea11
            anchors.fill: parent
            drag.target: dragArea11
        }
        Loader { id: gauge11
            anchors.fill: parent}
    }
    Item { id:loader12; width: 200; height: width
        Drag.active: dragArea12.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea12
            anchors.fill: parent
            drag.target: dragArea12
        }
        Loader { id: gauge12
            anchors.fill: parent}
    }
    Item { id:loader13; width: 200; height: width
        Drag.active: dragArea13.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea13
            anchors.fill: parent
            drag.target: dragArea13
        }
        Loader { id: gauge13
            anchors.fill: parent}
    }
    Item { id:loader14; width: 200; height: width
        Drag.active: dragArea14.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea14
            anchors.fill: parent
            drag.target: dragArea14
        }
        Loader { id: gauge14
            anchors.fill: parent}
    }
    Item { id:loader15; width: 200; height: width
        Drag.active: dragArea15.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea15
            anchors.fill: parent
            drag.target: dragArea15
        }
        Loader { id: gauge15
            anchors.fill: parent}
    }
    Item { id:loader16; width: 200; height: width
        Drag.active: dragArea16.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea16
            anchors.fill: parent
            drag.target: dragArea16
        }
        Loader { id: gauge16
            anchors.fill: parent}
    }
    Item { id:loader17; width: 200; height: width
        Drag.active: dragArea17.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea17
            anchors.fill: parent
            drag.target: dragArea17
        }
        Loader { id: gauge17
            anchors.fill: parent}
    }
    Item { id:loader18; width: 200; height: width
        Drag.active: dragArea18.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea18
            anchors.fill: parent
            drag.target: dragArea18
        }
        Loader { id: gauge18
            anchors.fill: parent}
    }
    Item { id:loader19; width: 200; height: width
        Drag.active: dragArea19.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea19
            anchors.fill: parent
            drag.target: dragArea19
        }
        Loader { id: gauge19
            anchors.fill: parent}
    }
    Item { id:loader20; width: 200; height: width
        Drag.active: dragArea20.drag.active
        MouseArea {
            // Mouse area in which the item can be dragged
            id: dragArea20
            anchors.fill: parent
            drag.target: dragArea20
        }
        Loader { id: gauge20
            anchors.fill: parent}
    }


    //gauge Selector with Dropdowns
    Rectangle{
        id: gaugeSelect
        height: mainrectangle.height
        width: mainrectangle.width
        color: "transparent"
        visible: false


        Item {
            Row {
                //  x: 50
                //       y: 200
                spacing: 5
                Grid {
                    rows: 10
                    columns: 6
                    spacing: 5
                    ComboBox {
                        id: selectGaugeNumber
                        width: 60
                        model: ["1","2","3","4","5","6","7","8","9","10",
                            "11","12","13","14","15","16","17","18","19","20"]
                        onCurrentIndexChanged: setRemember.remembersetIndex()
                    }
                    ComboBox {
                        id: selectGauge
                        width: 250
                        currentIndex: 3
                        model: [ "None","Half Gauge Coolant Metric","Half Gauge Coolant Imperial","KMH Round","REV Round"]
                        onCurrentIndexChanged: setSource.sourceSetting(),remember.setIndex(),createGauge.create()
                    }
                    ComboBox {
                        id: dragselect
                        width: 150
                        currentIndex: 0
                        model: [ "movable off"," movable on"]
                        onCurrentIndexChanged: dragstate.dragstateswitch()
                    }

                    Button{
                        width: 120
                        text: "gauge size -"
                        onClicked:sizeminus.sizeminusfunc()
                    }
                    Button{
                        width: 120
                        text: "gauge size +"
                        onClicked:sizeplus.sizeplusfunc()
                    }
                    Button{
                        width: 100
                        text: "close"
                        onClicked:gaugeSelect.visible = false;
                    }
                }
            }
        }
    }


    PieMenu {
        id: pieMenu

        MenuItem {
            text: "Open Gauge Select"
            onTriggered: gaugeSelect.visible = true;
        }

        MenuItem {
            text: "Close Gauge Select"
            onTriggered: gaugeSelect.visible = false;
        }

    }
    //Functions
    Item {
        //Function to set source based on user selection dropdown
        id: setSource
        function sourceSetting()
        {
            if (selectGauge.currentIndex == 0)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 1)createGauge.gaugesource = ("qrc:/Gauges/HalfGaugeWaterDegC.qml");
            if (selectGauge.currentIndex == 2)createGauge.gaugesource = ("qrc:/Gauges/HalfGaugeWaterDegF.qml");
            if (selectGauge.currentIndex == 3)createGauge.gaugesource = ("qrc:/Gauges/RoundGaugeSpeedMetric.qml");
            if (selectGauge.currentIndex == 4)createGauge.gaugesource = ("qrc:/Gauges/GaugeRoundREV.qml");
            if (selectGauge.currentIndex == 5)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 6)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 7)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 8)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 9)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 10)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 11)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 12)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 13)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 14)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 15)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 16)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 17)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 18)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 19)createGauge.gaugesource = ("");
            console.log (createGauge.gaugesource);

        }
    }
    Item {
        //Function to set source based on user selection dropdown
        id: createGauge
        property var gaugesource: "";
        function create()
        {
            console.log (gaugesource);console.log (selectGaugeNumber.currentIndex );


            if (selectGaugeNumber.currentIndex == 0)gauge1.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 1)gauge2.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 2)gauge3.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 3)gauge4.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 4)gauge5.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 5)gauge6.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 6)gauge7.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 7)gauge8.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 8)gauge9.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 9)gauge10.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 10)gauge11.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 11)gauge12.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 12)gauge13.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 13)gauge14.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 14)gauge15.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 15)gauge16.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 16)gauge17.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 17)gauge18.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 18)gauge19.setSource(gaugesource);
            if (selectGaugeNumber.currentIndex == 19)gauge20.setSource(gaugesource);


        }
    }
    Item {
        //Function to remember selectGaugeNumber and selected gauge
        id: remember
        property var gauge1select
        property var gauge2select
        property var gauge3select
        property var gauge4select
        property var gauge5select
        property var gauge6select
        property var gauge7select
        property var gauge8select
        property var gauge9select
        property var gauge10select
        property var gauge11select
        property var gauge12select
        property var gauge13select
        property var gauge14select
        property var gauge15select
        property var gauge16select
        property var gauge17select
        property var gauge18select
        property var gauge19select
        property var gauge20select

        function setIndex()
        {
            console.log ("Save index");
            if (selectGaugeNumber.currentIndex == 0)gauge1select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 1)gauge2select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 2)gauge3select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 3)gauge4select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 4)gauge5select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 5)gauge6select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 6)gauge7select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 7)gauge8select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 8)gauge9select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 9)gauge10select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 10)gauge11select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 11)gauge12select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 12)gauge13select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 13)gauge14select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 14)gauge15select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 15)gauge16select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 16)gauge17select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 17)gauge18select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 18)gauge19select = selectGauge.currentIndex;
            if (selectGaugeNumber.currentIndex == 19)gauge20select = selectGauge.currentIndex;


        }
    }
    Item {
        //Function to remember selectGaugeNumber and selected gauge
        id: setRemember
        function remembersetIndex()
        {
            console.log ("Setting index");
            if (selectGaugeNumber.currentIndex == 0)selectGauge.currentIndex = remember.gauge1select;
            if (selectGaugeNumber.currentIndex == 1)selectGauge.currentIndex = remember.gauge2select;
            if (selectGaugeNumber.currentIndex == 2)selectGauge.currentIndex = remember.gauge3select;
            if (selectGaugeNumber.currentIndex == 3)selectGauge.currentIndex = remember.gauge4select;
            if (selectGaugeNumber.currentIndex == 4)selectGauge.currentIndex = remember.gauge5select;
            if (selectGaugeNumber.currentIndex == 5)selectGauge.currentIndex = remember.gauge6select;
            if (selectGaugeNumber.currentIndex == 6)selectGauge.currentIndex = remember.gauge7select;
            if (selectGaugeNumber.currentIndex == 7)selectGauge.currentIndex = remember.gauge8select;
            if (selectGaugeNumber.currentIndex == 8)selectGauge.currentIndex = remember.gauge9select;
            if (selectGaugeNumber.currentIndex == 9)selectGauge.currentIndex = remember.gauge10select;
            if (selectGaugeNumber.currentIndex == 10)selectGauge.currentIndex = remember.gauge11select;
            if (selectGaugeNumber.currentIndex == 11)selectGauge.currentIndex = remember.gauge12select;
            if (selectGaugeNumber.currentIndex == 12)selectGauge.currentIndex = remember.gauge13select;
            if (selectGaugeNumber.currentIndex == 13)selectGauge.currentIndex = remember.gauge14select;
            if (selectGaugeNumber.currentIndex == 14)selectGauge.currentIndex = remember.gauge15select;
            if (selectGaugeNumber.currentIndex == 15)selectGauge.currentIndex = remember.gauge16select;
            if (selectGaugeNumber.currentIndex == 16)selectGauge.currentIndex = remember.gauge17select;
            if (selectGaugeNumber.currentIndex == 17)selectGauge.currentIndex = remember.gauge18select;
            if (selectGaugeNumber.currentIndex == 18)selectGauge.currentIndex = remember.gauge19select;
            if (selectGaugeNumber.currentIndex == 19)selectGauge.currentIndex = remember.gauge20select;


        }
    }
    Item {
        //Function to remember selectGaugeNumber and selected gauge
        id: sizeplus
        function sizeplusfunc()
        {
            console.log ("increasing size");
            if (selectGaugeNumber.currentIndex == 0)loader1.width = loader1.width + 10;
            if (selectGaugeNumber.currentIndex == 1)loader2.width = loader2.width + 10;
            if (selectGaugeNumber.currentIndex == 2)loader3.width = loader3.width + 10;
            if (selectGaugeNumber.currentIndex == 3)loader4.width = loader4.width + 10;
            if (selectGaugeNumber.currentIndex == 4)loader5.width = loader5.width + 10;
            if (selectGaugeNumber.currentIndex == 5)loader6.width = loader6.width + 10;
            if (selectGaugeNumber.currentIndex == 6)loader7.width = loader7.width + 10;
            if (selectGaugeNumber.currentIndex == 7)loader8.width = loader8.width + 10;
            if (selectGaugeNumber.currentIndex == 8)loader9.width = loader9.width + 10;
            if (selectGaugeNumber.currentIndex == 9)loader10.width = loader10.width + 10;
            if (selectGaugeNumber.currentIndex == 10)loader11.width = loader11.width + 10;
            if (selectGaugeNumber.currentIndex == 11)loader12.width = loader12.width + 10;
            if (selectGaugeNumber.currentIndex == 12)loader13.width = loader13.width + 10;
            if (selectGaugeNumber.currentIndex == 13)loader14.width = loader14.width + 10;
            if (selectGaugeNumber.currentIndex == 14)loader15.width = loader15.width + 10;
            if (selectGaugeNumber.currentIndex == 15)loader16.width = loader16.width + 10;
            if (selectGaugeNumber.currentIndex == 16)loader17.width = loader17.width + 10;
            if (selectGaugeNumber.currentIndex == 17)loader18.width = loader18.width + 10;
            if (selectGaugeNumber.currentIndex == 18)loader19.width = loader19.width + 10;
            if (selectGaugeNumber.currentIndex == 19)loader20.width = loader20.width + 10;


        }
    }
    Item {
        //Function to remember selectGaugeNumber and selected gauge
        id: sizeminus
        function sizeminusfunc()
        {
            console.log ("decreasing size");
            if (selectGaugeNumber.currentIndex == 0)loader1.width = loader1.width - 10;
            if (selectGaugeNumber.currentIndex == 1)loader2.width = loader2.width - 10;
            if (selectGaugeNumber.currentIndex == 2)loader3.width = loader3.width - 10;
            if (selectGaugeNumber.currentIndex == 3)loader4.width = loader4.width - 10;
            if (selectGaugeNumber.currentIndex == 4)loader5.width = loader5.width - 10;
            if (selectGaugeNumber.currentIndex == 5)loader6.width = loader6.width - 10;
            if (selectGaugeNumber.currentIndex == 6)loader7.width = loader7.width - 10;
            if (selectGaugeNumber.currentIndex == 7)loader8.width = loader8.width - 10;
            if (selectGaugeNumber.currentIndex == 8)loader9.width = loader9.width - 10;
            if (selectGaugeNumber.currentIndex == 9)loader10.width = loader10.width - 10;
            if (selectGaugeNumber.currentIndex == 10)loader11.width = loader11.width - 10;
            if (selectGaugeNumber.currentIndex == 11)loader12.width = loader12.width - 10;
            if (selectGaugeNumber.currentIndex == 12)loader13.width = loader13.width - 10;
            if (selectGaugeNumber.currentIndex == 13)loader14.width = loader14.width - 10;
            if (selectGaugeNumber.currentIndex == 14)loader15.width = loader15.width - 10;
            if (selectGaugeNumber.currentIndex == 15)loader16.width = loader16.width - 10;
            if (selectGaugeNumber.currentIndex == 16)loader17.width = loader17.width - 10;
            if (selectGaugeNumber.currentIndex == 17)loader18.width = loader18.width - 10;
            if (selectGaugeNumber.currentIndex == 18)loader19.width = loader19.width - 10;
            if (selectGaugeNumber.currentIndex == 19)loader20.width = loader20.width - 10;


        }
    }

    Item {
        //Function to remember selectGaugeNumber and selected gauge
        id: dragstate
        function dragstateswitch()
        {
            console.log ("change movable");
            if (dragselect.currentIndex == 1)dragArea.drag.target = loader1,dragArea2.drag.target = loader2,dragArea3.drag.target = loader3,dragArea4.drag.target = loader4,dragArea5.drag.target = loader5,dragArea6.drag.target = loader6,dragArea7.drag.target = loader7,dragArea8.drag.target = loader8,dragArea9.drag.target = loader9,dragArea10.drag.target = loader10,dragArea11.drag.target = loader11,dragArea12.drag.target = loader12,dragArea13.drag.target = loader13,dragArea14.drag.target = loader14,dragArea15.drag.target = loader15,dragArea16.drag.target = loader16,dragArea17.drag.target = loader17,dragArea18.drag.target = loader18,dragArea19.drag.target = loader19,dragArea20.drag.target = loader20;
            if (dragselect.currentIndex == 0)dragArea.drag.target = dragArea,dragArea2.drag.target = dragArea2,dragArea3.drag.target = dragArea3,dragArea4.drag.target = dragArea4,dragArea5.drag.target = dragArea5,dragArea6.drag.target = dragArea6,dragArea7.drag.target = dragArea7,dragArea8.drag.target = dragArea8,dragArea9.drag.target = dragArea9,dragArea10.drag.target = dragArea10,dragArea11.drag.target = dragArea11,dragArea12.drag.target = dragArea12,dragArea13.drag.target = dragArea13,dragArea14.drag.target = dragArea14,dragArea15.drag.target = dragArea15,dragArea16.drag.target = dragArea16,dragArea17.drag.target = dragArea17,dragArea18.drag.target = dragArea18,dragArea19.drag.target = dragArea19,dragArea20.drag.target = dragArea20;
            /*
            if (dragselect.currentIndex == 1)loader5.Drag.active = dragArea5.drag.active;
            if (dragselect.currentIndex == 1)loader6.Drag.active = dragArea6.drag.active;
            if (dragselect.currentIndex == 1)loader7.Drag.active = dragArea7.drag.active;
            if (dragselect.currentIndex == 1)loader8.Drag.active = dragArea8.drag.active;
            if (dragselect.currentIndex == 1)loader9.Drag.active = dragArea9.drag.active;
            if (dragselect.currentIndex == 1)loader10.Drag.active = dragArea10.drag.active;
            if (dragselect.currentIndex == 1)loader11.Drag.active = dragArea11.drag.active;
            if (dragselect.currentIndex == 1)loader12.Drag.active = dragArea12.drag.active;
            if (dragselect.currentIndex == 1)loader13.Drag.active = dragArea13.drag.active;
            if (dragselect.currentIndex == 1)loader14.Drag.active = dragArea14.drag.active;
            if (dragselect.currentIndex == 1)loader15.Drag.active = dragArea15.drag.active;
            if (dragselect.currentIndex == 1)loader16.Drag.active = dragArea16.drag.active;
            if (dragselect.currentIndex == 1)loader17.Drag.active = dragArea17.drag.active;
            if (dragselect.currentIndex == 1)loader18.Drag.active = dragArea18.drag.active;
            if (dragselect.currentIndex == 1)loader19.Drag.active = dragArea19.drag.active;
            if (dragselect.currentIndex == 1)loader20.Drag.active = dragArea20.drag.active;
*/

        }
    }
    //Drag.active: dragArea.drag.active

}
