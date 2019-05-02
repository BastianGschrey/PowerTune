import QtQuick 2.5
import QtQuick.Controls 2.1

Item {
    id: picture
    height: pictureheight
    width : pictureheight
    property string information: "gauge image"
    property string picturesource
    property int pictureheight
    property string increasedecreaseident
    Drag.active: true
    Component.onCompleted: togglemousearea();

    Connections{
        target: Dashboard
        onDraggableChanged: togglemousearea();
    }

    Image {
        anchors.fill: parent
        id: mypicture
        fillMode: Image.PreserveAspectFit
        source:  picturesource
    }
    MouseArea {
        id: touchArea
        anchors.fill: parent
        drag.target: parent
        enabled: false
        onDoubleClicked: {
            //console.log("double clicked");
            changesize.visible = true;
            Connect.readavailablebackrounds();
            changesize.x = touchArea.mouseX;
            changesize.y = touchArea.mouseY;
        }
    }
    Rectangle{
        id : changesize
        color: "darkgrey"
        visible: false
        width : 200
        height :150
        Drag.active: true
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            enabled: true
        }
        Grid { width: parent.width
            height:parent.height
            rows: 4
            columns: 1
            rowSpacing :5
            Grid {
                rows: 1
                columns: 3
                rowSpacing :5
                RoundButton{text: "-"
                    width: changesize.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "decreasePicture"}
                    onReleased: {timer.running = false;}
                    onClicked: {pictureheight--}
                }
                Text{id: sizeTxt
                    text: pictureheight
                    font.pixelSize: 15
                    width: changesize.width /3.2
                    horizontalAlignment: Text.AlignHCenter
                    onTextChanged: pictureheight = sizeTxt.text
                }
                RoundButton{ text: "+"
                    width: changesize.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "increasePicture"}
                    onReleased: {timer.running = false;}
                    onClicked: {pictureheight++}
                }
            }
            ComboBox {
                id: pictureSelector
                width: 200
                height: 40
                font.pixelSize: 15
                model: Dashboard.backroundpictures
                currentIndex: 0
                onCurrentIndexChanged: {
                    picturesource = "file:///home/pi/Logo/" + pictureSelector.textAt(pictureSelector.currentIndex);
                    //picturesource = "file:" + pictureSelector.textAt(pictureSelector.currentIndex); // windows
                    mypicture.source = picturesource;
                                       }
                delegate: ItemDelegate {
                    width: pictureSelector.width
                    text: pictureSelector.textRole ? (Array.isArray(pictureSelector.model) ? modelData[pictureSelector.textRole] : model[pictureSelector.textRole]) : modelData
                    font.weight: pictureSelector.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: pictureSelector.font.family
                    font.pixelSize: pictureSelector.font.pixelSize
                    highlighted: pictureSelector.highlightedIndex === index
                    hoverEnabled: pictureSelector.hoverEnabled
                }
            }
            RoundButton{
                width: parent.width
                text: "Delete picture"
                font.pixelSize: 15
                onClicked: picture.destroy();
            }
            RoundButton{
                width: parent.width
                text: "Close"
                onClicked: changesize.visible = false;
            }
        }
    }

    Item {
        Timer {
            id: timer
            interval: 50; running: false; repeat: true
            onTriggered: {increaseDecrease()}
        }

        Text { id: time }
    }
    function togglemousearea()
    {
    //    console.log("toggle" + Dashboard.draggable);
        if (Dashboard.draggable === 1)
        {
            touchArea.enabled = true;
        }
        else
            touchArea.enabled = false;
    }
    function increaseDecrease()
    {
        //console.log("ident "+ increasedecreaseident);
        switch(increasedecreaseident)
        {

        case "increasePicture": {
            pictureheight++;
            break;
        }
        case "decreasePicture": {
            pictureheight--;
            break;
        }
        }
    }
}
