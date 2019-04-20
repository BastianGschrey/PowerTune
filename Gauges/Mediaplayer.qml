import QtQuick 2.8
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.1
import QtQuick.Extras 1.4
import QtMultimedia 5.8

Rectangle {
    width: 800
    height: 480
    property bool playing: false
    Connections{
        target: Dashboard
        onMusicpathChanged : folderModel.folder = Dashboard.musicpath
    }
    TreeView {
        id:mp3selector
        width: parent.width/2
        height: parent.height /2
        anchors.top:parent.top
        visible: false
        TableViewColumn {
            id:test1
            title: "Name"
            role: "fileName"
            width: 300
        }
        model: Dirmodel
        onActivated: Connect.qmlTreeviewclicked(mp3selector.currentIndex),folderModel.folder = Dashboard.musicpath;
    }
    ListView {
        id: list
        width: parent.width/2
        height: parent.height
        anchors.bottom: parent.bottom
        model: folderModel
        onCurrentIndexChanged: {
            // This will handle changing playlist with all possible selection methods
            playMusic.source = folderModel.get(currentIndex, "fileURL")
        }
        FolderListModel {
            id: folderModel
            showDirs: false
            nameFilters: ["*.mp3"]
        }
        delegate: Component {
            Item {
                width: parent.width
                height: 40
                Column {
                    Text { text: fileName }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        list.currentIndex = index
                    }
                }
            }
        }
        highlight: Rectangle {
            color: 'lightsteelblue'
        }
        focus: true
    }

    MediaPlayer {
        id: playMusic
        autoPlay: true
        volume: 0.5
    }
    Rectangle{
        id:playerwindow
        width: parent.width /2
        height:parent.height
        anchors.right: parent.right
        color: "transparent"
        Rectangle{
            id: controls
            width: parent.width /2
            height: width /4
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            Image {
                id: coverart
                width: parent.width /1.5
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                //just a placeholder for now
                source: "qrc:/graphics/Tacho_Mitte.png"
            }
            Rectangle{
                id:buttons
                width: parent.width
                height:parent.width /5
                anchors.top: coverart.bottom
                Image {
                    id: previous
                    anchors.left:parent.left
                    width: parent.width /5
                    height: width
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/graphics/previous.png"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.decrementCurrentIndex()
                    }
                }
                Image {
                    id: playpause
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width /5
                    height: width
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/graphics/play.png"

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
                    width: parent.width /5
                    height: width
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/graphics/next.png"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.incrementCurrentIndex()

                    }
                }
            }
        }
        Slider{
            id:volume
            width: parent.width / 1.5
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            value: 0.5
            onValueChanged: playMusic.volume = volume.value
        }
        ProgressBar{
            id:progress
            width: parent.width / 1.5
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            value: playMusic.position
            to: playMusic.duration
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 6
                color: "#e6e6e6"
                radius: 3
            }

            contentItem: Item {
                implicitWidth: 200
                implicitHeight: 20

                Rectangle {
                    width: progress.visualPosition * parent.width
                    height: parent.height
                    radius: 2
                    color: "lightsteelblue"
                }
            }
        }
        RoundButton {
            id: folderselect
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: volume.top
            text: "select folder"
            onClicked: if (mp3selector.visible == false){mp3selector.visible = true,list.height = parent.height /2,folderselect.text = "close folder"}else{mp3selector.visible = false,list.height = parent.height,folderselect.text = "select folder"}
        }
    }
    Rectangle{
    anchors.fill: parent
    color: "transparent"
    WarningLoader{}
    }
}
