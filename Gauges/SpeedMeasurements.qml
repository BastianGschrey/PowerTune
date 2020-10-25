import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0


Rectangle {
    id: measurements
    anchors.fill: parent
    color: "black"
    Component.onCompleted: units.start()
    //////////////////////////////
       //STAGING Lights
    Connections{
        target: Dashboard
        onSpeedChanged :{speedchange.start()}
    }
    Connections{
        target: Dashboard
        onSpeedunitsChanged :{units.start()}
    }
    property int measurementstarted : 0;
    property int startmeasurement : 0;
    //Function
    Item {
        id: speedchange
        function start()
        {
        if (Dashboard.speed > 0 && startmeasurement === 1 &&measurementstarted === 0)
       {
            measurementstarted = 1;
        Calculations.stopreactiontimer();
        Calculations.startdragtimer();
        }
        }
    }
    Item {
        id: units
        function start()
        {
        if (Dashboard.speedunits === "metric")
        {
            hundred.text = "0-100 km/h TIME: "
            twohundred.text = "100-200 km/h TIME: "
            threehundred.text = "200-300 km/h TIME: "
        }
        else
        {
            hundred.text = "0-60 mph TIME: "
            twohundred.text = "60-120 mph TIME: "
            threehundred.text = "120-180 mph TIME: "

        }
        }
    }

Row{
    id: staginglight
    anchors.right: parent.right
    anchors.rightMargin: parent.width /15
    anchors.top: parent.top
    anchors.topMargin: parent.height / 10
    spacing: 20
    Image {
        id : stagelight1
        height: 35
        width: 35
        source: "/graphics/ledoff.png"
    }
    Image {
        id : stagelight2
        height: 35
        width: 35
        source: "/graphics/ledoff.png"
    }
    }
            Column {
                anchors.right: parent.right
                anchors.rightMargin: parent.width /15
                anchors.top: staginglight.bottom
                anchors.topMargin: parent.width /50
                spacing: 20
                Image {
                    id : orangeled1
                    height: 35
                    width: 35
                    source: "/graphics/ledoff.png"
                }
                Image {
                    id : orangeled2
                    height: 35
                    width: 35
                    source: "/graphics/ledoff.png"
                }
                Image {
                    id : orangeled3
                    height: 35
                    width: 35
                    source: "/graphics/ledoff.png"
                }
                Image {
                    id : greenled
                    height: 35
                    width: 35
                    source: "/graphics/ledoff.png"
                }
                Image {
                    id : redled
                    height: 35
                    width: 35
                    source: "/graphics/ledoff.png"
                }

            }
    //////////////////////////////


    Grid {
        anchors.top :parent.top
        anchors.topMargin: parent.height / 20
        spacing: parent.width /150
        rows: 20
        columns: 4
        //spacing: measurements.width /150
        // [0]
        Button {
            id: trafficButton
            text: "Start Staging Tree"
            width: measurements.width / 5
            height: measurements.height /10
            font.pixelSize: measurements.width / 55
            onClicked: {
                Dashboard.reactiontime = 0;
                Dashboard.sixtyfoottime = 0;
                Dashboard.sixtyfootspeed = 0;
                Dashboard.threehundredthirtyfoottime = 0;
                Dashboard.threehundredthirtyfootspeed = 0;
                Dashboard.eightmiletime = 0;
                Dashboard.eightmilespeed = 0;
                Dashboard.quartermiletime = 0;
                Dashboard.quartermilespeed = 0;
                Dashboard.eightmiletime = 0;
                Dashboard.eightmilespeed = 0;
                Dashboard.thousandfoottime = 0;
                Dashboard.thousandfootspeed = 0;
                Dashboard.zerotohundredt = 0;
                Dashboard.hundredtotwohundredtime = 0;
                Dashboard.twohundredtothreehundredtime = 0;
                Dashboard.reactiontime = 0;
            startmeasurement = 0;
            measurementstarted = 0;
            greenled.source = "qrc:/graphics/ledoff.png"
            redled.source = "qrc:/graphics/ledoff.png"
            stagelight1.source = "qrc:/graphics/ledyellow.png"
            stagelight2 .source = "qrc:/graphics/ledyellow.png"
            redled.source = "qrc:/graphics/ledoff.png"
            stagelight.running = true;

            }
        }
 /*
        Button {
            id: nostagebutton
            text: "Start Measurement"
            width: measurements.width / 5
            height: measurements.height /10
            font.pixelSize: measurements.width / 55
            onClicked: {
                Dashboard.reactiontime = 0;
                Dashboard.sixtyfoottime = 0;
                Dashboard.sixtyfootspeed = 0;
                Dashboard.threehundredthirtyfoottime = 0;
                Dashboard.threehundredthirtyfootspeed = 0;
                Dashboard.eightmiletime = 0;
                Dashboard.eightmilespeed = 0;
                Dashboard.quartermiletime = 0;
                Dashboard.quartermilespeed = 0;
                Dashboard.eightmiletime = 0;
                Dashboard.eightmilespeed = 0;
                Dashboard.thousandfoottime = 0;
                Dashboard.thousandfootspeed = 0;
                Dashboard.zerotohundredt = 0;
                Dashboard.hundredtotwohundredtime = 0;
                Dashboard.twohundredtothreehundredtime = 0;
                Dashboard.reactiontime = 0;
                greenled.source = "qrc:/graphics/ledgreen.png"
                redled.source = "qrc:/graphics/ledoff.png"
                stagelight1.source = "qrc:/graphics/ledyellow.png"
                stagelight2 .source = "qrc:/graphics/ledyellow.png"
                redled.source = "qrc:/graphics/ledoff.png"
            startmeasurement = 1;
            measurementstarted = 0;
            }
        }
*/        Text {
            width: measurements.width / 5
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }


        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
////
        Text {
            text: "R/T : "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: (Dashboard.reactiontime).toFixed(3)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "60' TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: (Dashboard.sixtyfoottime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "60' TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: (Dashboard.sixtyfootspeed)
            font.pixelSize: measurements.width / 40
            color: "white"
        }

        Text {
            text: "330' TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: (Dashboard.threehundredthirtyfoottime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "330' TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: (Dashboard.threehundredthirtyfootspeed)
            font.pixelSize: measurements.width / 40
            color: "white"
        }




        Text {
            text: "1/8 MILE TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: (Dashboard.eightmiletime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }

        Text {
            text: "1/8 MILE TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.eightmilespeed)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "1000' TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }

        Text {
            text:  (Dashboard.thousandfoottime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "1000' TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.thousandfootspeed)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "1/4 TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.quartermiletime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: "1/4 TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.quartermilespeed)
            font.pixelSize: measurements.width / 40
            color: "white"
        }

        Text {
            id : hundred
            text: "0-100 km/h TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.zerotohundredt)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            id : twohundred
            text:"100-200 km/h TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.hundredtotwohundredtime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            id : threehundred
            text:"200-300 km/h TIME: "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text:  (Dashboard.twohundredtothreehundredtime)
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: measurements.width / 40
            color: "white"
        }




    }
    Item {
        Timer {
            id: stagelight
            interval: 5000;
            running: false
            onTriggered: {
            stagelight1.source = "qrc:/graphics/ledoff.png"
            stagelight2 .source = "qrc:/graphics/ledoff.png"
            orangeled1.source = "qrc:/graphics/ledyellow.png"
            orange1.running = true
            }
        }
    }
    Item {
        Timer {
            id: orange1
            interval: 500;
            running: false
            onTriggered: {
            orange2.running = true
            orangeled1.source = "qrc:/graphics/ledoff.png"
            orangeled2.source = "qrc:/graphics/ledyellow.png"
            }
        }
    }
    Item {
        Timer {
            id: orange2
            interval: 500;
            running: false
            onTriggered: {
                orange3.running = true
                orangeled2.source = "qrc:/graphics/ledoff.png"
                orangeled3.source = "qrc:/graphics/ledyellow.png"
            }
        }
    }
    Item {
        Timer {
            id: orange3
            interval: 500;
            running: false
            onTriggered: {
                green.running = true
                orangeled3.source = "qrc:/graphics/ledoff.png"
                greenled.source = "qrc:/graphics/ledgreen.png"
                Calculations.startreactiontimer();
            }
        }
    }
    Item {
        Timer {
            id: green
            interval: 400;
            running: false
            onTriggered: {
                // CHeck the time difference
                if (Dashboard.speed >0)
                {
                redled.source = "qrc:/graphics/ledred.png"
                }
                startmeasurement = 1;
            }
        }
    }
}
