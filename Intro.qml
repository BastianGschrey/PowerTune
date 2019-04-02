import QtQuick 2.8

Rectangle {
    id: intro
    anchors.fill : parent
    color: "white"
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
        source: "file::///home/pi/Logo/Logo.png"
    }
}
