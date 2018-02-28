import QtQuick 2.8

Item {
    id: mainwindow
    width: parent.width
    height: parent.height


    Rectangle {
        id: forcecircle
        height: mainwindow.height/1.5
        width: height
        color: "black"
        anchors.centerIn: parent

        Text {
        id: lattxt
        text:  "Lateral    G:          " +(Dashboard.accely).toFixed(2)
        color: "white"
        anchors.bottom: longtxt.top
        anchors.horizontalCenter: forcecircle.horizontalCenter
        font.bold: true
        font.family: "Eurostile"
        font.pixelSize: forcecircle.width / 20
        }
        Text {
        id: longtxt
        text: "Longitudinal G:    " + (Dashboard.accelx).toFixed(2)
        color: "white"
        anchors.bottom: forcecircle.top
        anchors.bottomMargin: forcecircle.width /50
        anchors.horizontalCenter: forcecircle.horizontalCenter
        font.bold: true
        font.family: "Eurostile"
        font.pixelSize: forcecircle.width / 20
        }
        Rectangle {
            width: forcecircle.height
            height: width
            color: "black"
            border.color: "white"
            border.width: forcecircle.height/100
            radius: width*0.5

        }

        Rectangle {
            // 1.5 G
            width: forcecircle.height/1.33
            height: width
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            radius: width*0.5
            anchors.centerIn: forcecircle

        }
        Rectangle {
            // 1 G
            width: forcecircle.height/2
            height: width
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            radius: width*0.5
            anchors.centerIn: forcecircle

        }

        Rectangle {
            width: forcecircle.height/4
            height: width
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            radius: width*0.5
            anchors.centerIn: forcecircle

        }
        Rectangle {
            //line in x
            width: forcecircle.height
            height: forcecircle.height/100
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            anchors.centerIn: forcecircle

        }
        Rectangle {
            //line in x
            width: forcecircle.height /100
            height: forcecircle.height
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            anchors.centerIn: forcecircle

        }

        Rectangle {
            id : ball
            color: "red"
            height: parent.height / 20
            width: height
            radius: width*0.5
            x:((forcecircle.height / 2) - (ball.height /2)) + ((forcecircle.height / 4) * Dashboard.accelx)
            y: ((forcecircle.height / 2) - (ball.height /2)) + ((forcecircle.height / 4) * Dashboard.accely)

        }
    }
}
