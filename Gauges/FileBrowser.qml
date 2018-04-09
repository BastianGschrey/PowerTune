import QtQuick 2.8
import QtQuick.Controls 1.4
import QtMultimedia 5.8

Rectangle {
    width: parent.width
    height: parent.height
    property bool playing: false


    Audio {
        id: playMusic
        source: "qrc:/Sounds/tiltshifted_lost_neon_sun.mp3"
    }

    Image {
        id: previous
        anchors.right: playpause.left
        width: parent.width /10
        height: width
        fillMode: Image.PreserveAspectFit
        source: "qrc:/graphics/previous.png"

  MouseArea {
        anchors.fill: parent

    }
  }
    Image {
        id: playpause
        anchors.right: next.left
        width: parent.width /10
        height: width
        fillMode: Image.PreserveAspectFit
        source: "qrc:/graphics/play.png"
       // text: playing ? "Stop music" : "Start music"

  MouseArea {
        anchors.fill: parent
        onClicked: {
            if(playing == true) {
                playMusic.stop()
                playing = false,playpause.source = "/graphics/pause.png"
            } else {
                playMusic.play()
                playing = true,playpause.source = "/graphics/play.png"
            }
        }
    }
  }
    Image {
        id: next
        anchors.right: parent.right
        width: parent.width /10
        height: width
        fillMode: Image.PreserveAspectFit
        source: "qrc:/graphics/next.png"

  MouseArea {
        anchors.fill: parent

    }
  }

TreeView {
    id:mp3selector
    width: parent.width/2
    height: parent.height
    TableViewColumn {
        title: "Name"
        role: "fileName"
        width: 300
    }
    model: my_model
}
}
