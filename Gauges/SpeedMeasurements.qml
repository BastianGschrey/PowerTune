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
    Loader {
        id: rpmbarloader
        anchors.fill: measurements
        source: "qrc:/Gauges/RPMBarStyle1.qml"
    }

    //STAGING Lights
    Connections{
        target: Dashboard
        onSpeedChanged :{speedchange.start()}
    }
    Connections{
        target: Dashboard
        onSpeedunitsChanged :{units.start()}
    }

    Connections{
        target: Dashboard
        onReactiontimeChanged :{reactiontimecheck.start()}
    }


    property int measurementstarted : 0;
    property int startmeasurement : 0;
    property var sliptextcolor: "white";
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
        id: reactiontimecheck
        function start()
        {
           // console.log("Reactiontime changed")
        if (Dashboard.reactiontime < 0 )
       {
            //reactiotimertimetext.color = "red"
            //reactiotimertext.color = "red"
            redled.source = "qrc:/graphics/ledred.png"
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
    anchors.bottom: staginglights2.top
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
                id: staginglights2
                anchors.right: parent.right
                anchors.rightMargin: parent.width /15
                anchors.bottom: measurements.bottom
                anchors.bottomMargin: parent.width /150
                spacing: parent.width /200
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
        id:timegrid
        anchors.bottom: measurements.bottom
        anchors.topMargin: parent.height / 20
        spacing: parent.width /200
        rows: 9
        columns: 2

        Text {
            id:reactiotimertext
            text: "R/T : "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            id:reactiotimertimetext
            text: (Dashboard.reactiontime).toFixed(3)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: "60' TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: (Dashboard.sixtyfoottime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: "330' TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text:  (Dashboard.threehundredthirtyfoottime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }


        Text {
            text: "1/8 MILE TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: (Dashboard.eightmiletime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: "1000' TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }

        Text {
            text:  (Dashboard.thousandfoottime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: "1/4 TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text:  (Dashboard.quartermiletime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            id : hundred
            text: "0-100 km/h TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text:  (Dashboard.zerotohundredt)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            id : twohundred
            text:"100-200 km/h TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text:  (Dashboard.hundredtotwohundredtime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            id : threehundred
            text:"200-300 km/h TIME: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text:  (Dashboard.twohundredtothreehundredtime)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }

}

    Grid {
        anchors.bottom: measurements.bottom
        anchors.bottomMargin: parent.height / 7
        anchors.left: timegrid.right
        anchors.leftMargin: parent.width /20
        spacing: parent.width /200
        rows: 9
        columns: 2
        Text {
            text: "60' TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: (Dashboard.sixtyfootspeed)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: "330' TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: (Dashboard.threehundredthirtyfootspeed)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text: "1/8 MILE TOP SPEED: "
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
        Text {
            text:  (Dashboard.eightmilespeed)
            font.pixelSize: measurements.width / 40
            color: sliptextcolor
        }
    Text {
        text: "1000' TOP SPEED: "
        font.pixelSize: measurements.width / 40
        color: sliptextcolor
    }
    Text {
        text:  (Dashboard.thousandfootspeed)
        font.pixelSize: measurements.width / 40
        color: sliptextcolor
    }
    Text {
        text: "1/4 TOP SPEED: "
        font.pixelSize: measurements.width / 40
        color: sliptextcolor
    }
    Text {
        text:  (Dashboard.quartermilespeed)
        font.pixelSize: measurements.width / 40
        color: sliptextcolor
    }



}
    Item {
        Timer {
            id: stagelight
            interval: 5000;
            running: false
            onTriggered: {
            startmeasurement = 1;
            stagelight1.source = "qrc:/graphics/ledoff.png"
            stagelight2 .source = "qrc:/graphics/ledoff.png"
            orangeled1.source = "qrc:/graphics/ledyellow.png"
            measurements.color = "#ffb366"
            sliptextcolor = "transparent"
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
            measurements.color = "#ffd966"
            sliptextcolor = "transparent"
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

                measurements.color = "yellow"
                sliptextcolor = "transparent"
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
                backroundcolortimer.running = true
                orangeled3.source = "qrc:/graphics/ledoff.png"
                greenled.source = "qrc:/graphics/ledgreen.png"
                measurements.color = "limegreen"
                sliptextcolor = "transparent"
                calculationtimer.running = true
                Calculations.qmlrealtime();
            }
        }
    }
    Item {
        Timer {
            id: backroundcolortimer
            interval: 200;
            running: false
            onTriggered: {
                 measurements.color = "black"
                sliptextcolor = "white"
            }
        }
    }
    Item {
        Timer {
            id: calculationtimer
            interval: 3000;
            running: false
            onTriggered: {
                Calculations.calculatereactiontime();
            }
        }
    }
    Button {
        id: trafficButton
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
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
        measurements.color = "orange"
        sliptextcolor = "transparent"
        startmeasurement = 1;
        Calculations.startreactiontimer();
        if (Dashboard.speed > 0)
        {
        stagelight.running = false;
        startmeasurement = 0;
        measurements.color = "red"
        sliptextcolor = "transparent"
        }
        }
    }

}
