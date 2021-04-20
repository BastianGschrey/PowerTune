import QtQuick 2.8
import QtQuick.Controls 2.1
Item {
    id:mytextlabel
    height: mytext.height
    width:  mytext.width
    //color: "tra"
    property string information: "Text label gauge"
    property string displaytext
    property string fonttype
    property int fontsize
    property string textcolor
    property string datasourcename
    property bool fontbold
    property int decimalpoints
    property string increasedecreaseident
    property double warnvaluehigh: 20000
    property double warnvaluelow : -20000
    property string resettextcolor
    Drag.active: true

    Component.onCompleted: {togglemousearea();
        checkdatasource();
    }
    DatasourcesList{id: powertunedatasource}

    Connections{
        target: Dashboard
        onDraggableChanged: togglemousearea();
    }

    MouseArea {
        id: touchArea
        anchors.fill: parent
        drag.target: parent
        enabled: false
        onDoubleClicked: {
            console.log("double clicked");
            changesize.visible = true;
            changesize.x = touchArea.mouseX;
            changesize.y = touchArea.mouseY;
            for(var i = 0; i < colorselect.model.count; ++i) if (colorselect.textAt(i) === textcolor)colorselect.currentIndex = i ;
            for(var j = 0; j < cbx_sources.model.count; ++j) if (powertunedatasource.get(j).sourcename === datasourcename)cbx_sources.currentIndex = j;
        }
    }
//Rectangle{
      //      id : textrect
      //      color: "blue"
      //      height: mytext.height
      //      width:  mytext.width
    Text {
        id: mytext
        text: displaytext
        font.family: fonttype
        font.pointSize: fontsize
        font.bold: fontbold
        color: textcolor
        anchors.centerIn: parent
        onTextChanged: warningindication.warn();
        }
 //   }
    SequentialAnimation {
        id: anim
        loops: Animation.Infinite
        running: false
        PropertyAnimation {
            target: mytext
            property: "color"
            from: "darkred"
            to: "orange"
            duration: 700
        }
    }
    Rectangle{
        id : changesize
        color: "darkgrey"
        visible: false
        width : 200
        height :480
        Drag.active: true
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            enabled: true
        }

        Grid { width: parent.width
            height:parent.height
            id: popupgrid
            rows: 12
            columns: 1
            rowSpacing :5
            Grid {
                rows: 1
                columns: 5
                rowSpacing :5
                RoundButton{text: "-"
                    width: changesize.width /3
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "decreasefontsize"}
                    onReleased: {timer.running = false;}
                    onClicked: {fontsize--}
                }
                Text{id: sizeTxt
                    text: fontsize
                    font.pixelSize: 15
                    width: changesize.width /3
                    horizontalAlignment: Text.AlignHCenter
                    onTextChanged: fontsize = sizeTxt.text
                }
                RoundButton{ text: "+"
                    width: changesize.width /3
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "increasefontsize"}
                    onReleased: {timer.running = false;}
                    onClicked: {fontsize++}
                }
            }
///////////////


///////////////
            TextField{
                id: changetext
                text : displaytext
                width: parent.width
                font.pixelSize: 15 
                onTextChanged: {
                    displaytext = changetext.text;
                    }

            }
            ComboBox {
                id: colorselect
                width: 200;
                model: ColorList{}
                visible: true
                font.pixelSize: 15
                currentIndex: 1
                onCurrentIndexChanged: textcolor = colorselect.textAt(colorselect.currentIndex)
                delegate:

                    ItemDelegate {
                    id:itemDelegate2
                    width: colorselect.width
                    font.pixelSize: 15
                    Rectangle {
                        width: colorselect.width
                        height: 50
                        color:  itemColor
                        Text {
                            text: itemColor
                            anchors.centerIn: parent
                            font.pixelSize: 15
                        }
                    }
                }

                background:Rectangle{
                    width: colorselect.width
                    height: colorselect.height
                    color:  colorselect.currentText
                }
            }
            ComboBox{
                id: cbx_titlefontstyle
                width: parent.width
                model: Qt.fontFamilies()
                visible:true
                font.pixelSize: 15
                currentIndex: 1
                onCurrentIndexChanged: {fonttype = cbx_titlefontstyle.textAt(cbx_titlefontstyle.currentIndex)
                }
                delegate:
                    ItemDelegate {
                    text: modelData
                    width: cbx_titlefontstyle.width
                    font.pixelSize: 15
                    font.family: modelData
                }
            }
            ComboBox {
                id: cbx_sources
                font.pixelSize: 15
                textRole: "titlename"
                width: 200
                height: 40
                model: powertunedatasource
                currentIndex: 1
                delegate: ItemDelegate {
                    width: cbx_sources.width
                    text: cbx_sources.textRole ? (Array.isArray(cbx_sources.model) ? modelData[cbx_sources.textRole] : model[cbx_sources.textRole]) : modelData
                    font.weight: cbx_sources.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: cbx_sources.font.family
                    font.pixelSize: cbx_sources.font.pixelSize
                    highlighted: cbx_sources.highlightedIndex === index
                    hoverEnabled: cbx_sources.hoverEnabled
                }
            }
        Text{
            text: "Warn value high :"
            font.pointSize: 7
            }
            ////
            Grid {
                //anchors.horizontalCenter: popupgrid.horizontalCenter
                rows: 1
                columns: 3
                rowSpacing :5
                RoundButton{text: "-"
                    width: popupgrid.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "decreasewarnvaluehigh"}
                    onReleased: {timer.running = false;}
                    onClicked: {warnvaluehigh--}
                }
                TextField{id: warnvaluehightxt
                    text: warnvaluehigh
                    width: popupgrid.width /3.2
                    font.pointSize: 7
                    horizontalAlignment: Text.AlignHCenter
                    inputMethodHints: Qt.ImhDigitsOnly
                    onTextChanged: warnvaluehigh = warnvaluehightxt.text
                }
                RoundButton{ text: "+"
                    width: popupgrid.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "increasewarnvaluehigh"}
                    onReleased: {timer.running = false;}
                    onClicked: {warnvaluehigh++}
                }
            }
            Text{
                text: "Warn value low :"
                font.pointSize: 7
                }
            Grid {
                rows: 1
                columns: 3
                rowSpacing :5
                //anchors.horizontalCenter: popupgrid.horizontalCenter
                RoundButton{text: "-"
                    width: popupgrid.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "decreasewarnvaluelow"}
                    onReleased: {timer.running = false;}
                    onClicked: {warnvaluelow--}
                }
                TextField{id: warnvaluelowxt
                    text: warnvaluelow
                    width: popupgrid.width /3.2
                    font.pointSize: 7
                    horizontalAlignment: Text.AlignHCenter
                    onTextChanged: warnvaluelow = warnvaluelowxt.text
                    inputMethodHints: Qt.ImhDigitsOnly
                }
                RoundButton{ text: "+"
                    width: popupgrid.width /3.2
                    onPressAndHold: {timer.running = true;
                        increasedecreaseident = "increasewarnvaluelow"}
                    onReleased: {timer.running = false;}
                    onClicked: {warnvaluelow++}
                }
            }
            RoundButton{
                text: "Use Datasource"
                width: parent.width
                font.pixelSize: 15
                onClicked: {
                    datasourcename = powertunedatasource.get(cbx_sources.currentIndex).sourcename;
                    decimalpoints = powertunedatasource.get(cbx_sources.currentIndex).decimalpoints;
                    checkdatasource();
                }
            }
            RoundButton {
                text: "Delete"
                font.pixelSize: 15
                width: parent.width
                onClicked: mytextlabel.destroy();
            }
            RoundButton{
                text: "Close"
                width: parent.width
                font.pixelSize: 15
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
    function checkdatasource()
    {
        if (datasourcename != ""){
            if (decimalpoints < 4)
            {
                changetext.text  = Qt.binding(function(){return Dashboard[datasourcename].toFixed(decimalpoints)});
            }
            else
                changetext.text  = Qt.binding(function(){return Dashboard[datasourcename]});
        }
    }
    Item {
        id: warningindication
        function warn()
        {
            console.log("Textwarning triggered")
            console.log(mytext.text)
            if (mytext.text > warnvaluehigh || mytext.text < warnvaluelow )anim.running = true;
            else anim.running = false,mytext.color = resettextcolor;
            //if (displaytext.text > peakval)peakval = displaytext.text;
            //console.log (peakval);

        }
    }
    function togglemousearea()
    {
        //console.log("toggle" + Dashboard.draggable);
        if (Dashboard.draggable === 1)
        {
            touchArea.enabled = true;
        }
        else
            touchArea.enabled = false;
    }
    function increaseDecrease()
    {
        console.log("ident "+ increasedecreaseident);
        switch(increasedecreaseident)
        {

        case "increasefontsize": {
            fontsize++;
            break;
        }
        case "increasewarnvaluelow" :{
            warnvaluelow++;
            break;
        }
        case "increasewarnvaluehigh" :{
            warnvaluehigh++;
            break;
        }
        case "decreasewarnvaluelow" :{
            warnvaluelow--;
            break;
        }
        case "decreasewarnvaluehigh" :{
            warnvaluehigh--;
            break;
        }
        case "decreasefontsize": {
            fontsize--;
            break;
        }
        }
    }
}
