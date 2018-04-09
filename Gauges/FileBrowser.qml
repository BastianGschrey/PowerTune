import QtQuick 2.8
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtMultimedia 5.8

Rectangle {
    width: parent.width
    height: parent.height
    property bool playing: false

    TreeView {
        id:mp3selector
        width: parent.width/2
        height: parent.height
        anchors.left: parent.left
        TableViewColumn {
            id:test1
            title: "Name"
            role: "fileName"
            width: 300
        }
        model: Filemodel
        onActivated: Connect.qmlTreeviewclicked(mp3selector.currentIndex)
    }

    MediaPlayer {
        id: playMusic
        autoPlay: false
        volume: 0.5
        source: Dashboard.musicpath
    }
    Rectangle{
        id:playerwindow
        width: parent.width /2
        height:parent.height
        anchors.right: parent.right
        Rectangle{
            id:buttons
            width: parent.width
            height:parent.width /4
            Image {
                id: previous
                anchors.left:parent.left
                width: parent.width /4
                height: width
                fillMode: Image.PreserveAspectFit
                source: "qrc:/graphics/previous.png"

                MouseArea {
                    anchors.fill: parent

                }
            }
            Image {
                id: playpause
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width /4
                height: width
                fillMode: Image.PreserveAspectFit
                source: "qrc:/graphics/play.png"
                // text: playing ? "Stop music" : "Start music"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(playMusic.status == 6) {
                            playMusic.stop()
                            playpause.source = "qrc:/graphics/play.png"
                        } else {
                            playMusic.play()
                            playpause.source = "qrc:/graphics/pause.png"
                            console.log(playMusic.metaData.title)
                            console.log(playMusic.metaData.albumTitle)
                            console.log(playMusic.metaData.genre)
                            console.log(playMusic.metaData.year)
                        }
                    }
                }
            }
            Image {
                id: next
                anchors.right: parent.right
                width: parent.width /4
                height: width
                fillMode: Image.PreserveAspectFit
                source: "qrc:/graphics/next.png"

                MouseArea {
                    anchors.fill: parent

                }
            }
        }
        Slider{
            id:volume
            width: parent.width / 1.5
            anchors.top :buttons.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            value: 0.5
            onValueChanged: playMusic.volume = volume.value
        }


    }
}

