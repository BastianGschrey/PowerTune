import QtQuick 2.8

Rectangle {
    id: mainwindow
    width: parent.width
    height: parent.height
    color: "black"

    Rectangle {
        id: forcecircle
        height: mainwindow.height
        width: mainwindow.height
        color: "Black"

        Rectangle {
            width: forcecircle.height
            height: width
            color: "transparent"
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
            anchors.centerIn: parent

        }
        Rectangle {
            // 1 G
            width: forcecircle.height/2
            height: width
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            radius: width*0.5
            anchors.centerIn: parent

        }

        Rectangle {
            //0.5 G
            width: forcecircle.height/4
            height: width
            color: "transparent"
            border.color: "white"
            border.width: forcecircle.height/100
            radius: width*0.5
            anchors.centerIn: parent

        }

        Rectangle {
            id : ball
            color: "red"
            height: parent.height / 20
            width: height
            radius: width*0.5
            x:((forcecircle.height / 2) - (ball.height /2)) + ((forcecircle.height / 4) * Dashboard.revs)
            y: ((forcecircle.height / 2) - (ball.height /2)) + ((forcecircle.height / 4) * Dashboard.Knock)

        }
    }
}
