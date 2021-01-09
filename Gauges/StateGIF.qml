import QtQuick 2.5
import QtQuick.Controls 2.1

Item {
    id: statepicture
    height: pictureheight
    width : pictureheight
    property string information: "State GIF"
    property string statepicturesourceoff
    property string statepicturesourceon
    property int pictureheight
    property string increasedecreaseident
    property string mainvaluename
    property double triggervalue : 0
    Drag.active: true
    DatasourcesList{id: powertunedatasource}
    Component.onCompleted: {togglemousearea();
                            bind();
                            }


    Connections{
        target: Dashboard
        onDraggableChanged: togglemousearea();
        onBackroundpicturesChanged: updatppiclist();
    }

     AnimatedImage {
        anchors.fill: parent
        id: statepictureoff
        playing : true
        fillMode: Image.PreserveAspectFit
        source:  statepicturesourceoff
        visible: true
    }
     AnimatedImage {
        anchors.fill: parent
        id: statepictureon
        playing : true
        fillMode: Image.PreserveAspectFit
        source:  statepicturesourceon
        visible: false
    }
    Text {
        id: mainvaluetextfield
        visible: false
        onTextChanged: {
            warningindication.warn();
        }
    }
    MouseArea {
        id: touchArea
        anchors.fill: parent
        drag.target: parent
        enabled: false
        onDoubleClicked: {
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
        height :320
        Drag.active: true
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            enabled: true
        }
        Grid { width: parent.width
            height:parent.height
            rows: 7
            columns: 1
            rowSpacing :5
            Grid {
                rows: 1
                columns: 3
                rowSpacing :5
                RoundButton{text: "-"
                    width: changesize.width /3.2
                    font.pixelSize: 15
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
                    onTextChanged: {pictureheight = sizeTxt.text}
                }
                RoundButton{ text: "+"
                    font.pixelSize: 15
                    width: changesize.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "increasePicture"}
                    onReleased: {timer.running = false;}
                    onClicked: {pictureheight++}
                }
            }
            Grid {
                rows: 4
                columns: 2
                rowSpacing :5
            Text{
                text: "Pic. Off"
                font.pixelSize: 12

            }

            ComboBox {
                id: pictureSelectoroff
                width: 140
                height: 40
                font.pixelSize: 12
                model: Dashboard.backroundpictures
                currentIndex: 0
                onCurrentIndexChanged: {
                    statepicturesourceoff = "file:///home/pi/Logo/" + pictureSelectoroff.textAt(pictureSelectoroff.currentIndex);
                    //statepicturesourceoff = "file:" + pictureSelectoroff.textAt(pictureSelectoroff.currentIndex); // windows
                    statepictureoff.source = statepicturesourceoff;
                                       }
                delegate: ItemDelegate {
                    width: pictureSelectoroff.width
                    text: pictureSelectoroff.textRole ? (Array.isArray(pictureSelectoroff.model) ? modelData[pictureSelectoroff.textRole] : model[pictureSelectoroff.textRole]) : modelData
                    font.weight: pictureSelectoroff.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: pictureSelectoroff.font.family
                    font.pixelSize: pictureSelectoroff.font.pixelSize
                    highlighted: pictureSelectoroff.highlightedIndex === index
                    hoverEnabled: pictureSelectoroff.hoverEnabled
                }
            }
            Text{
                text: "Pic. On"
                font.pixelSize: 12
            }
            ComboBox {
                id: pictureSelectoron
                width: 140
                height: 40
                font.pixelSize: 12
                model: Dashboard.backroundpictures
                currentIndex: 0
                onCurrentIndexChanged: {
                    statepicturesourceon = "file:///home/pi/Logo/" + pictureSelectoron.textAt(pictureSelectoron.currentIndex);
                    //statepicturesourceon = "file:" + pictureSelectoron.textAt(pictureSelectoron.currentIndex); // windows
                    statepictureon.source = statepicturesourceon;
                }



                delegate: ItemDelegate {
                    width: pictureSelectoron.width
                    text: pictureSelectoron.textRole ? (Array.isArray(pictureSelector.model) ? modelData[pictureSelector.textRole] : model[pictureSelector.textRole]) : modelData
                    font.weight: pictureSelectoron.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: pictureSelectoron.font.family
                    font.pixelSize: pictureSelectoron.font.pixelSize
                    highlighted: pictureSelectoron.highlightedIndex === index
                    hoverEnabled: pictureSelectoron.hoverEnabled
                }
            }
            Text{
                text: "Source"
                font.pixelSize: 12
            }
            ComboBox {
                id: cbxMain
                textRole: "titlename"
                model: powertunedatasource
                width: 140
                height: 40
                font.pixelSize: 12
                Component.onCompleted: {for(var i = 0; i < cbxMain.model.count; ++i) if (powertunedatasource.get(i).sourcename === mainvaluename)cbxMain.currentIndex = i,bind()}
                onCurrentIndexChanged: bind();
            }
            Text{
                text: "Trigger"
                font.pixelSize: 12
            }
            TextField {
                id: triggeronvalue
                width: 140
                height: 40
                text: triggervalue
                //onTextChanged: triggervalue = triggeronvalue.text
                font.pixelSize: 12
            }
            }
            RoundButton{
                width: parent.width
                text: "Delete picture"
                font.pixelSize: 15
                onClicked: statepicture.destroy();
            }
            RoundButton{
                width: parent.width
                text: "Close"
                font.pixelSize: 15
                onClicked: {
                    triggervalue = triggeronvalue.text;
                    mainvaluename = powertunedatasource.get(cbxMain.currentIndex).sourcename;
                    changesize.visible = false;
            }
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
    Item {
        id: warningindication
        function warn()
        {
          //  //console.log("warning" +mainvaluetextfield.text);
          //  //console.log("Trigger" +mainvaluetextfield.text);
            if (mainvaluetextfield.text >= triggervalue ){statepictureoff.visible = false,statepictureon.visible = true}
            if (mainvaluetextfield.text < triggervalue ){statepictureoff.visible = true,statepictureon.visible = false}
//            else {statepictureoff.visible = true,statepictureon.visible = false};

        }
    }
    function togglemousearea()
    {
    //    //console.log("toggle" + Dashboard.draggable);
        if (Dashboard.draggable === 1)
        {
            touchArea.enabled = true;
        }
        else
            touchArea.enabled = false;
    }
    function increaseDecrease()
    {
        ////console.log("ident "+ increasedecreaseident);
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
    function bind()
    {
        mainvaluetextfield.text = Qt.binding(function(){return Dashboard[mainvaluename]});
    }

    // These functions update the Picture sources in the ComboBoxes
    function updatppiclist()
    {
                    for(var i = 0; i < pictureSelectoron.count; ++i) //
                    if (statepicturesourceon === "file:///home/pi/Logo/" + pictureSelectoron.textAt(i))
                    pictureSelectoron.currentIndex = i
                    updatppiclistoff()
    }
    function updatppiclistoff()
    {
                    for(var i = 0; i < pictureSelectoroff.count; ++i) //
                    if (statepicturesourceoff === "file:///home/pi/Logo/" + pictureSelectoroff.textAt(i))
                    pictureSelectoroff.currentIndex = i
    }
}
