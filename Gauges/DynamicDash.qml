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


        }
    }

    Loader { id: gauge1 }
    Loader { id: gauge2 }
    Loader { id: gauge3 }
    Loader { id: gauge4 }
    Loader { id: gauge5 }
    Loader { id: gauge6 }
    Loader { id: gauge7 }
    Loader { id: gauge8 }
    Loader { id: gauge9 }
    Loader { id: gauge10}
    Loader { id: gauge11}
    Loader { id: gauge12}
    Loader { id: gauge13}
    Loader { id: gauge14}
    Loader { id: gauge15}
    Loader { id: gauge16}
    Loader { id: gauge17}
    Loader { id: gauge18}
    Loader { id: gauge19}
    Loader { id: gauge20}

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
                    columns: 4
                    spacing: 5
                    ComboBox {
                        id: selectGaugeNumber
                        width: 30
                        model: ["1","2","3","4","5","6","7","8","9","10",
                            "11","12","13","14","15","16","17","18","19","20"]
                        onCurrentIndexChanged: setRemember.remembersetIndex()
                    }
                    ComboBox {
                        id: selectGauge
                        width: 300
                        currentIndex: 3
                        model: [ "None","Half Gauge Coolant Metric","Half Gauge Coolant Imperial"]
                        onCurrentIndexChanged: setSource.sourceSetting(),remember.setIndex(),createGauge.create()
                    }
                  /*  TextField {
                        id: gaugesize
                        width: 50
                        placeholderText: qsTr("200")
                        validator: IntValidator {bottom: 0; top: 3000;}

                    }
                    */

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
            if (selectGauge.currentIndex == 3)createGauge.gaugesource = ("");
            if (selectGauge.currentIndex == 4)createGauge.gaugesource = ("");
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

}
