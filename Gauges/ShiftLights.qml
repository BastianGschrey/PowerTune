import QtQuick 2.0



Item {
    width:800
    height:480
    property  int rpmwarn1: 3000
    property  int rpmwarn2: 5000
    property  int rpmwarn3: 6000
    property  int rpmwarn4: 8000
    Connections{
        target: Dashboard
        onRpmChanged: {
            if (Dashboard.rpm > rpmwarn1) {led1.source = "qrc:/graphics/ledgreen.png",led8.source = "qrc:/graphics/ledgreen.png"};
            if (Dashboard.rpm > rpmwarn2) {led2.source = "qrc:/graphics/ledgreen.png",led7.source = "qrc:/graphics/ledgreen.png"};
            if (Dashboard.rpm > rpmwarn3) {led3.source = "qrc:/graphics/ledyellow.png",led6.source = "qrc:/graphics/ledyellow.png"};
            if (Dashboard.rpm > rpmwarn4) {led4.source = "qrc:/graphics/ledred.png",led5.source = "qrc:/graphics/ledred.png"};
            if (Dashboard.rpm < rpmwarn1) {led1.source = "qrc:/graphics/ledoff.png",led8.source = "qrc:/graphics/ledoff.png"};
            if (Dashboard.rpm < rpmwarn2) {led2.source = "qrc:/graphics/ledoff.png",led7.source = "qrc:/graphics/ledoff.png"};
            if (Dashboard.rpm < rpmwarn3) {led3.source = "qrc:/graphics/ledoff.png",led6.source = "qrc:/graphics/ledoff.png"};
            if (Dashboard.rpm < rpmwarn4) {led4.source = "qrc:/graphics/ledoff.png",led5.source = "qrc:/graphics/ledoff.png"};
        }
    }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 20
            Image {
                id : led1
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led2
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led3
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led4
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led5
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led6
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led7
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }
            Image {
                id : led8
                height: 35
                width: 35
                source: "/graphics/ledoff.png"
            }

        }
    }

