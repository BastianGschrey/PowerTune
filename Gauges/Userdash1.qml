import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.0
import QtQml.Models 2.3
import Qt.labs.settings 1.0
import QtQuick.Controls 1.4 as Quick1
import QtQuick.VirtualKeyboard 2.1
import QtQuick.VirtualKeyboard.Styles 2.2
import "../Gauges"
import "qrc:/Gauges/createRoundGauge.js" as CreateRoundgaugeScript
import "qrc:/Gauges/createsquaregaugeUserDash.js" as CreateSquareGaugeScript
import "qrc:/Gauges/createverticalbargauge.js" as CreateBargaugeScript
import "qrc:/Gauges/createText.js" as CreateTextScript
import "qrc:/Gauges/createPicture.js" as CreatePictureScript
import "qrc:/Gauges/createStatePicture.js" as CreateStatePictureScript
import "qrc:/Gauges/createStateGIF.js" as CreateStateGIFScript

Item {
    id: mainwindow
    anchors.fill: parent
    property string datastore: ""
    property string saveDashtofilestring : ""
    property string gaugeType : ""
    property string backroundpicturesource1 : ""
    property bool val1: false
    property bool val2: false
    property bool val3: false
    property double val4 : 20000
    property int val5 : -20000
    property string val6 : "transparent"
    property string val7 : "transparent"
    property string val8 : "transparent"
    property string val9 : "transparent"
    property string val10 : "transparent"
    property string val11 : "transparent"
    property int val12
    property int val13
    property string val14 : "Square Gauge"
    property int parser

    Drag.active: true
    MyTextLabel{x:10
        y:10
        z:300}
    ListModel {
        id: gaugelist
    }
    Rectangle{
        id: mainbackroundcolor
        anchors.fill: parent

    }
    Image {
        id:backroundpicture1
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        z: 0
    }

    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup1
        visible:false
        font.pixelSize: 15
        delegate: ItemDelegate {
            width: dashvalue.width
            text: dashvalue.textRole ? (Array.isArray(dashvalue.model) ? modelData[dashvalue.textRole] : model[dashvalue.textRole]) : modelData
            font.weight: dashvalue.currentIndex === index ? Font.DemiBold : Font.Normal
            font.family: dashvalue.font.family
            font.pixelSize: dashvalue.font.pixelSize
            highlighted: dashvalue.highlightedIndex === index
            hoverEnabled: dashvalue.hoverEnabled
        }
    }

    DatasourcesList{id: powertunedatasource}

    Component.onCompleted: {
        if (datastore) {
            gaugelist.clear()
            var datamodel = JSON.parse(datastore)
            for (var i = 0; i < datamodel.length; ++i) gaugelist.append(datamodel[i])
        }
        createDash()
    }

    Settings {
        property alias datastore1: mainwindow.datastore
        property alias rpmbackround1: rpmstyleselector.currentIndex
        property alias extraLoader1: extraSelector.currentIndex
        property alias savebackroundpicture1: backroundpicture1.source
        property alias savemainbackroundcolor: mainbackroundcolor.color

    }

    ////////Readout Gauge Elements from file and create dynamically ( only needed for importing a dash)
    Connections{
        target: Dashboard

        onBackroundpicturesChanged: updatppiclist();
        onDashsetup1Changed:
        {
            if (dashvalue.textAt(1) !== "") {

              //  console.log("new item " +dashvalue.textAt(0) );


                if (dashvalue.textAt(0) === "Bar gauge")
                {
                    //  console.log("Create Bar Gauge")
                    CreateBargaugeScript.createVerticalGauge(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),dashvalue.textAt(8),dashvalue.textAt(9),dashvalue.textAt(10),dashvalue.textAt(11));
                }
                if (dashvalue.textAt(0) === "Round gauge")
                {
                    //console.log("create Round Gauge")
                    CreateRoundgaugeScript.createRoundGauge(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),dashvalue.textAt(8),dashvalue.textAt(9),dashvalue.textAt(10),dashvalue.textAt(11),dashvalue.textAt(12),dashvalue.textAt(13),dashvalue.textAt(14),dashvalue.textAt(15),dashvalue.textAt(16),dashvalue.textAt(17),dashvalue.textAt(18),dashvalue.textAt(19),dashvalue.textAt(20),dashvalue.textAt(21),dashvalue.textAt(22),dashvalue.textAt(23),dashvalue.textAt(24),dashvalue.textAt(25),dashvalue.textAt(26),dashvalue.textAt(27),dashvalue.textAt(28),dashvalue.textAt(29),dashvalue.textAt(30),dashvalue.textAt(31),dashvalue.textAt(32),dashvalue.textAt(33),dashvalue.textAt(34),dashvalue.textAt(35),dashvalue.textAt(36),dashvalue.textAt(37),dashvalue.textAt(38),dashvalue.textAt(39),dashvalue.textAt(40),dashvalue.textAt(41),dashvalue.textAt(42),dashvalue.textAt(43),dashvalue.textAt(44),dashvalue.textAt(45),dashvalue.textAt(46),dashvalue.textAt(47),dashvalue.textAt(48),(dashvalue.textAt(49).toLowerCase() === 'true' ? true : false),(dashvalue.textAt(50).toLowerCase() === 'true' ? true : false),(dashvalue.textAt(51).toLowerCase() === 'true' ? true : false),dashvalue.textAt(52),dashvalue.textAt(53),dashvalue.textAt(54),dashvalue.textAt(55),(dashvalue.textAt(56).toLowerCase() === 'true' ? true : false),dashvalue.textAt(57),dashvalue.textAt(58),dashvalue.textAt(59),dashvalue.textAt(60),dashvalue.textAt(61),dashvalue.textAt(62),dashvalue.textAt(63),dashvalue.textAt(64),dashvalue.textAt(65),(dashvalue.textAt(66).toLowerCase() === 'true' ? true : false));
                }

                if (dashvalue.textAt(0) === "Square gauge")
                {
                    //console.log("create Square Gauge")
                    CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),dashvalue.textAt(8),(dashvalue.textAt(9).toLowerCase() === 'true' ? true : false),(dashvalue.textAt(10).toLowerCase() === 'true' ? true : false),(dashvalue.textAt(11).toLowerCase() === 'true' ? true : false),dashvalue.textAt(12),dashvalue.textAt(13),dashvalue.textAt(14),dashvalue.textAt(15),dashvalue.textAt(16),dashvalue.textAt(17),dashvalue.textAt(18),dashvalue.textAt(19),dashvalue.textAt(20),dashvalue.textAt(21),dashvalue.textAt(22),dashvalue.textAt(23),dashvalue.textAt(24),dashvalue.textAt(25),dashvalue.textAt(26),dashvalue.textAt(27),dashvalue.textAt(28));
                }

                if (dashvalue.textAt(0) === "gauge image")
                {
                    // console.log("Create image")
                    CreatePictureScript.createPicture(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4));
                }
                if (dashvalue.textAt(0) === "Text label gauge")
                {
                    //console.log("Create Text label")
                    CreateTextScript.createText(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),(dashvalue.textAt(8).toLowerCase() === 'true' ? true : false),dashvalue.textAt(9),dashvalue.textAt(10),dashvalue.textAt(11));
                }
                if (dashvalue.textAt(0) === "State gauge")
                {
                    // //console.log("Create image")
                    CreateStatePictureScript.createPicture(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7));
                }
                if (dashvalue.textAt(0) === "State GIF")
                {
                    // //console.log("Create image")
                    CreateStateGIFScript.createPicture(dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7));
                }

            }

        }

    }

    Loader{
        id: rpmbarloader
        anchors.fill:parent
        source: ""
    }



    Item{
        id: rpmgauge
        function selector()
        {
            switch (rpmstyleselector.currentIndex) {

            case 0:
            {
                rpmbarloader.source = ""
                break;
            }
            case 1:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMBarStyle1.qml"
                break;
            }
            case 2:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMBARStyle2.qml"
                break;
            }
            case 3:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMbarStyle3.qml"
                break;
            }
            case 4:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMbar.qml"
                break;
            }
            }
        }
    }

    function updatppiclist()
    {
                    for(var i = 0; i < backroundSelector.count; ++i)
//                    if (backroundpicture1.source == "file:///home/pi/Logo/" + backroundSelector.textAt(i))
                        if (backroundpicture1.source == "file:"  + backroundSelector.textAt(i))


                    backroundSelector.currentIndex = i
    }


    Rectangle{
        anchors.fill: parent
        z:300 //This makes the Rectangle appear in front of the bar gauges
        color: "transparent"
        WarningLoader{}
    }

    Loader{
        id: extraLoader
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height: parent.height /2.2
        width: parent.width /2.7
    }


    // From Here we do all the Magic stuff for the dynamic creation of the Gauges


    MouseArea {
        id: touchArea
        anchors.fill: parent
        onDoubleClicked:
        {

            btnbackround.visible = true;
            savetofile.visible = true;
            squaregaugemenu.visible =true;
            btnopencolorselect.visible = true;
            cbx_sources.visible = true;
            btnaddSquare.visible = true;
            btncancel.visible = true;
            btnsave.visible = true;
            btnclear.visible = true;
            loadfromfile.visible = true;
            squaregaugemenu.visible = true;
            btnaddRound.visible = true;
            btnaddText.visible = true;
            btnaddPicture.visible = true;
            btnaddStatePicture.visible = true;
            btnaddStateGIF.visible = true;
            btnaddBar.visible = true;
            Dashboard.setdraggable(1);
        }
    }
    // Virtual Keyboard
    Rectangle{
        id: keyboardcontainer
        color: "darkgrey"
        visible: false
        width :500
        height:180
        z:220
        MouseArea {
            id: touchAkeyboardcontainer
            anchors.fill:parent
            drag.target: keyboardcontainer
        }
        InputPanel {
            id: keyboard
            anchors.fill: parent
            visible: false

            states: State {
                name: "visible";
                when: keyboard.active;
                PropertyChanges {
                    target: keyboard;
                    visible: true
                }
                PropertyChanges {
                    target: keyboardcontainer;
                    visible: true;
                    x:0
                    y:0
                }
            }
        }
    }
    /// RPM STYLE SELECTOR and Backround picture loader
    Rectangle{
        id: rpmbackroundselector
        width: 200
        height: 300
        color : "darkgrey"
        x :590
        y: 0
        z:200
        visible: false
        MouseArea {
            id: touchArearpmbackroundselector
            anchors.fill:parent
            drag.target: rpmbackroundselector
        }
        Grid{
            rows:10
            columns: 1
            rowSpacing :5

            Text {
                text: qsTr("RPM Style:")
                font.pixelSize: 20
                font.bold: true
            }
            ComboBox {
                id: rpmstyleselector
                width: 200
                height: 40
                font.pixelSize: 15
                model: ["None", "Style1","Style2", "Style3", "Style4"]
                onCurrentIndexChanged: rpmgauge.selector();
                delegate: ItemDelegate {
                    width: rpmstyleselector.width
                    text: rpmstyleselector.textRole ? (Array.isArray(rpmstyleselector.model) ? modelData[rpmstyleselector.textRole] : model[rpmstyleselector.textRole]) : modelData
                    font.weight: rpmstyleselector.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: rpmstyleselector.font.family
                    font.pixelSize: rpmstyleselector.font.pixelSize
                    highlighted: rpmstyleselector.highlightedIndex === index
                    hoverEnabled: rpmstyleselector.hoverEnabled
                }
            }
            Text {
                text: qsTr("Backround picture:")
                font.pixelSize: 20
                font.bold: true
            }
            ComboBox {
                id: backroundSelector
                width: 200
                height: 40
                font.pixelSize: 12
                model: Dashboard.backroundpictures
                currentIndex: 0
                onCurrentIndexChanged: {

                    backroundpicturesource1 = "file:///home/pi/Logo/" + backroundSelector.textAt(backroundSelector.currentIndex);
                    //backroundpicturesource1 = "file:///c:/Logo/" + backroundSelector.textAt(backroundSelector.currentIndex);
                    //backroundpicturesource1 = "file:" + backroundSelector.textAt(backroundSelector.currentIndex);
                    backroundpicture1.source = backroundpicturesource1;
                }
                delegate: ItemDelegate {
                    width: backroundSelector.width
                    text: backroundSelector.textRole ? (Array.isArray(backroundSelector.model) ? modelData[backroundSelector.textRole] : model[backroundSelector.textRole]) : modelData
                    font.weight: backroundSelector.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: backroundSelector.font.family
                    font.pixelSize: backroundSelector.font.pixelSize
                    highlighted: backroundSelector.highlightedIndex === index
                    hoverEnabled: backroundSelector.hoverEnabled
                }
            }
            Text {
                text: qsTr("Backround color:")
                font.pixelSize: 20
                font.bold: true
            }
            ComboBox {
                id: mainbackroundcolorselect
                width: 200;
                height:40
                model: ColorList{}
                visible: true
                font.pixelSize: 15


                delegate:

                    ItemDelegate {
                    id:itemDelegate
                    width: mainbackroundcolorselect.width
                    font.pixelSize: 15
                    Rectangle {
                        id: backroundcolorcbxcolor
                        width: mainbackroundcolorselect.width
                        height: 50
                        color:  itemColor

                        Text {

                            text: itemColor
                            anchors.centerIn: parent
                            font.pixelSize: 15
                        }
                    }
                }
                Component.onCompleted: {
                    for(var i = 1; i < mainbackroundcolorselect.model.count; ++i)
                   if (Qt.colorEqual(mainbackroundcolor.color,mainbackroundcolorselect.textAt(i)))
                    mainbackroundcolorselect.currentIndex = i
                }
                 onCurrentIndexChanged:  mainbackroundcolor.color = mainbackroundcolorselect.textAt(mainbackroundcolorselect.currentIndex)

            }
            Text {
                text: qsTr("Extra:")
                font.pixelSize: 20
                font.bold: true
            }
            ComboBox {
                id: extraSelector
                width: 200
                height: 40
                font.pixelSize: 15
                model: ["None", "PFC Sensors"]
                onCurrentIndexChanged: setextra();
                delegate: ItemDelegate {
                    width: extraSelector.width
                    text: extraSelector.textRole ? (Array.isArray(extraSelector.model) ? modelData[extraSelector.textRole] : model[extraSelector.textRole]) : modelData
                    font.weight: extraSelector.currentIndex === index ? Font.DemiBold : Font.Normal
                    font.family: extraSelector.font.family
                    font.pixelSize: extraSelector.font.pixelSize
                    highlighted: extraSelector.highlightedIndex === index
                    hoverEnabled: extraSelector.hoverEnabled
                }
            }
            Button {
                id: btncloserpm
                text: qsTr("CLOSE:")
                font.pixelSize: 15
                width: 200
                height: 40
                onClicked:{rpmbackroundselector.visible =false;}
            }
        }
    }
    /// The Gauge Creation Menu
    Rectangle{
        id: squaregaugemenu
        width: 200
        height: 400
        color : "darkgrey"
        x :590
        y: 0
        z:200
        visible: false
        MouseArea {
            id: touchAreasquaregaugemenu
            anchors.fill:parent
            drag.target: squaregaugemenu
        }
        ComboBox {
            id: cbx_sources
            font.pixelSize: 15
            textRole: "titlename"
            width: 200
            height: 40
            model: powertunedatasource
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
        ComboBox {
            id: loadfileselect
            font.pixelSize: 15
            model: Dashboard.dashfiles
            width: 200
            height: 40
            visible: false
            delegate: ItemDelegate {
                width: loadfileselect.width
                text: loadfileselect.textRole ? (Array.isArray(loadfileselect.model) ? modelData[loadfileselect.textRole] : model[loadfileselect.textRole]) : modelData
                font.weight: loadfileselect.currentIndex === index ? Font.DemiBold : Font.Normal
                font.family: loadfileselect.font.family
                font.pixelSize: loadfileselect.font.pixelSize
                highlighted: loadfileselect.highlightedIndex === index
                hoverEnabled: loadfileselect.hoverEnabled
            }
        }

        Grid{
            rows:7
            columns: 2
            //anchors.top : cbx_sources.bottom
            spacing:10
            x:0
            y:45

            Button {
                id: btnaddSquare
                width: 95
                height: 40
                text: qsTr("Add Square")
                font.pixelSize: 12
                onClicked: {
                    console.log(powertunedatasource.get(cbx_sources.currentIndex).decimalpoints);
                    CreateSquareGaugeScript.createSquareGauge(266,119,0,240,248,powertunedatasource.get(cbx_sources.currentIndex).decimalpoints,powertunedatasource.get(cbx_sources.currentIndex).defaultsymbol,powertunedatasource.get(cbx_sources.currentIndex).titlename,false,true,false,"Dashboard",powertunedatasource.get(cbx_sources.currentIndex).sourcename,powertunedatasource.get(cbx_sources.currentIndex).sourcename,10000,-20000,"lightsteelblue","black","lightsteelblue","white","white","blue",25,40,powertunedatasource.get(cbx_sources.currentIndex).decimalpoints2,"Lato","Lato");
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnaddBar
                width: 95
                height: 40
                text: qsTr("Add Bar")
                font.pixelSize: 12
                onClicked: {
                    CreateBargaugeScript.createVerticalGauge(320,80,10,0,0,8000,powertunedatasource.get(cbx_sources.currentIndex).decimalpoints,powertunedatasource.get(cbx_sources.currentIndex).titlename,powertunedatasource.get(cbx_sources.currentIndex).sourcename,1000,0);
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnaddRound
                width: 95
                height: 40
                text: qsTr("Add Round")
                font.pixelSize: 12
                onClicked: {
                    CreateRoundgaugeScript.createRoundGauge(400,20,20,powertunedatasource.get(cbx_sources.currentIndex).sourcename,powertunedatasource.get(cbx_sources.currentIndex).maxvalue,0,powertunedatasource.get(cbx_sources.currentIndex).maxvalue,-1000,-145,90,powertunedatasource.get(cbx_sources.currentIndex).maxvalue,powertunedatasource.get(cbx_sources.currentIndex).divisor,powertunedatasource.get(cbx_sources.currentIndex).stepsize,1,powertunedatasource.get(cbx_sources.currentIndex).stepsize,powertunedatasource.get(cbx_sources.currentIndex).decimalpoints,2,38,3,3,8,3,15,5,0.50,0.40,0.33,0.25,20,5,93,8,0,0,"red","darkred","aliceblue","red","grey","darkgrey","darkgrey","black","grey","black","dodgerblue","deepskyblue","lightskyblue","transparent",true,true,true,"Lato",30,50,10,false,"Lato",powertunedatasource.get(cbx_sources.currentIndex).titlename,"red",0,0,0,0,0,0,"false");
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnaddText
                width: 95
                height: 40
                text: qsTr("Add Text")
                font.pixelSize: 12
                onClicked: {
                    CreateTextScript.createText(100,50,"Textelement","Lato",15,"red","",true,0,20000,-20000)
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnaddPicture
                width: 95
                height: 40
                text: qsTr("Add Image")
                font.pixelSize: 12
                onClicked: {
                    CreatePictureScript.createPicture(10,10,100,"qrc:/graphics/slectImage.png")
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnaddStatePicture
                width: 95
                height: 40
                text: qsTr("State Img")
                font.pixelSize: 12
                onClicked: {
                   // console.log("create State gauge ");
                    CreateStatePictureScript.createPicture(10,10,100,"speed",1,"qrc:/graphics/selectStateImage.png","qrc:/graphics/selectStateImage.png");
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnaddStateGIF
                width: 95
                height: 40
                text: qsTr("State GIF")
                font.pixelSize: 12
                onClicked: {
                   // console.log("create State gauge ");
                    CreateStateGIFScript.createPicture(10,10,100,"speed",1,"qrc:/graphics/StateGIF.gif","qrc:/graphics/StateGIF.gif");
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnsave
                width: 95
                text: qsTr("SAVE")
                font.pixelSize: 12
                onClicked: {
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                    savedash();
                }
            }

            Button {
                id: btnopencolorselect
                width:95
                text: qsTr("Colors")
                font.pixelSize: 12
                onClicked: {
                    selectcolor.visible =true;
                    squaregaugemenu.visible = false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnclear
                width: 95
                text: "Clear"
                font.pixelSize: 12
                onClicked:  {

                    selectcolor.visible =false;
                    squaregaugemenu.visible = false;
                    Dashboard.setdraggable(0);
                    for (var i=0; i<userDash.children.length; ++i)
                    {
                        userDash.children[i].destroy()
                    }
                }
            }

            Button{
                id: loadfromfile
                width: 95
                text: "Import"
                font.pixelSize: 12

                onClicked: {
                    Connect.readavailabledashfiles();
                    btnaddRound.visible = false;
                    btnaddText.visible = false;
                    btnaddPicture.visible = false;
                    btnaddStatePicture.visible = false;
                    btnaddStateGIF.visible = false;
                    btnaddBar.visible = false;
                    btncancelload.visible = true;
                    loadfromfile.visible = false;
                    loadfileselect.visible = true;
                    btnaddSquare.visible = false;
                    btncancel.visible = false;
                    cbx_sources.visible = false;
                    btnsave.visible = false;
                    btnclear.visible = false;
                    selectcolor.visible = false;
                    savetofile.visible = false;
                    btnopencolorselect.visible = false;
                    loadfromfile.visible = false;
                    load.visible = true;
                    selectcolor.visible =false;
                    btnbackround.visible =false;
                    savedash();
                }
            }
            Button{
                id: savetofile
                width: 95
                text: "Export"
                font.pixelSize: 12

                onClicked: {
                    squaregaugemenu.visible = false;
                    Dashboard.setdraggable(0);
                    btnaddRound.visible = false;
                    btnaddText.visible = false;
                    btnaddPicture.visible = false;
                    btnaddStatePicture.visible = false;
                    btnaddStateGIF.visible = false;
                    selectcolor.visible =false;
                    savedash();
                    saveDashtofile();
                    Connect.saveDashtoFile("Dash1Export",saveDashtofilestring);
                }
            }
            Button{
                id: load
                width: 95
                text: "Load"
                font.pixelSize: 12
                visible: false
                onClicked: {
                    loadfileselect.visible = false;
                    Connect.setfilename1(loadfileselect.textAt(loadfileselect.currentIndex));
                    btncancelload.visible = false;
                    squaregaugemenu.visible = false;
                    load.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                    Connect.readdashsetup1();
                }
            }
            Button{
                id: btncancelload
                width: 95
                text: "Cancel"
                font.pixelSize: 12
                visible: false
                onClicked: {
                    loadfileselect.visible = false;
                    btncancelload.visible = false;
                    squaregaugemenu.visible = false;
                    load.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);

                }
            }
            Button{
                id: btnbackround
                width: 95
                text: "Background"
                font.pixelSize: 12
                onClicked: {
                    rpmbackroundselector.visible =true;
                    squaregaugemenu.visible = false;
                    btnbackround.visible =false;
                    Dashboard.setdraggable(0);
                    Connect.readavailablebackrounds();
                }
            }

            Button {
                id: btncancel
                width: 95
                text: "Close"
                font.pixelSize: 12
                onClicked:  {
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
        }
    }
    //We put all Gauges here
    Item{
        id: userDash
        anchors.fill: parent
    }
    ///////////////////Functions
    function setextra()
    {
        switch (extraSelector.currentIndex){
        case 0:{
            extraLoader.source = "";
            break;
        }
        case 1:{
            extraLoader.setSource("qrc:/Gauges/PFCSensors.qml",{ sizeoftext : mainwindow.width /54});
            break;
        }
        }
    }

    function saveDashtofile()
    {
        saveDashtofilestring = ""
        for (var i=0; i<userDash.children.length; ++i)
        {
            if (userDash.children[i].information === "Bar gauge")
            {
                saveDashtofilestring += (userDash.children[i].information+","+userDash.children[i].width+","+userDash.children[i].height+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].minvalue+","+userDash.children[i].maxvalue+","+userDash.children[i].decimalpoints+","+userDash.children[i].gaugename+","+userDash.children[i].mainvaluename+","+userDash.children[i].warnvaluehigh+","+userDash.children[i].warnvaluelow+","+userDash.children[i].decimalpoints2+","+"\r\n");
            }
            if (userDash.children[i].information === "Square gauge")
            {
                saveDashtofilestring += (userDash.children[i].information+","+userDash.children[i].width+","+userDash.children[i].height+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].maxvalue+","+userDash.children[i].decimalpoints+","+userDash.children[i].mainunit+","+userDash.children[i].title+","+userDash.children[i].vertgaugevisible+","+userDash.children[i].horigaugevisible+","+userDash.children[i].secvaluevisible+","+"Dashboard"+","+userDash.children[i].mainvaluename+","+userDash.children[i].secvaluename+","+userDash.children[i].warnvaluehigh+","+userDash.children[i].warnvaluelow+","+userDash.children[i].framecolor+","+userDash.children[i].resetbackroundcolor+","+userDash.children[i].resettitlecolor+","+userDash.children[i].titletextcolor+","+userDash.children[i].textcolor+","+userDash.children[i].barcolor+","+userDash.children[i].titlefontsize+","+userDash.children[i].mainfontsize+","+userDash.children[i].decimalpoints2+","+userDash.children[i].textFonttype+","+userDash.children[i].valueFonttype+",\r\n");
            }
            if (userDash.children[i].information === "gauge image")
            {
                saveDashtofilestring += (userDash.children[i].information+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].pictureheight+","+userDash.children[i].picturesource+"\r\n");
            }
            if (userDash.children[i].information === "Text label gauge")
            {
                saveDashtofilestring += (userDash.children[i].information+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].displaytext+","+userDash.children[i].fonttype+","+userDash.children[i].fontsize+","+userDash.children[i].textcolor+","+userDash.children[i].datasourcename+","+userDash.children[i].fontbold+","+userDash.children[i].decimalpoints+","+userDash.children[i].warnvaluehigh+","+userDash.children[i].warnvaluelow+",\r\n");
            }
            if (userDash.children[i].information === "Round gauge")
            {
                saveDashtofilestring += (userDash.children[i].information+","+
                                         userDash.children[i].width+","+
                                         userDash.children[i].x+","+
                                         userDash.children[i].y+","+
                                         userDash.children[i].mainvaluename+","+
                                         userDash.children[i].maxvalue+","+
                                         userDash.children[i].minvalue+","+
                                         userDash.children[i].warnvaluehigh+","+
                                         userDash.children[i].warnvaluelow+","+
                                         userDash.children[i].startangle+","+
                                         userDash.children[i].endangle+","+
                                         userDash.children[i].redareastart+","+
                                         userDash.children[i].divider+","+
                                         userDash.children[i].tickmarksteps+","+
                                         userDash.children[i].minortickmarksteps+","+
                                         userDash.children[i].setlabelsteps+","+
                                         userDash.children[i].decimalpoints+","+
                                         userDash.children[i].needleinset+","+
                                         userDash.children[i].setlabelinset+","+
                                         userDash.children[i].setminortickmarkinset+","+
                                         userDash.children[i].setmajortickmarkinset+","+
                                         userDash.children[i].minortickmarkheight+","+
                                         userDash.children[i].minortickmarkwidth+","+
                                         userDash.children[i].tickmarkheight+","+
                                         userDash.children[i].tickmarkwidth+","+
                                         userDash.children[i].trailhighboarder+","+
                                         userDash.children[i].trailmidboarder+","+
                                         userDash.children[i].traillowboarder+","+
                                         userDash.children[i].trailbottomboarder+","+
                                         userDash.children[i].labelfontsize+","+
                                         userDash.children[i].needleTipWidth+","+
                                         userDash.children[i].needleLength+","+
                                         userDash.children[i].needleBaseWidth+","+
                                         userDash.children[i].redareainset+","+
                                         userDash.children[i].redareawidth+","+
                                         userDash.children[i].needlecolor+","+
                                         userDash.children[i].needlecolor2+","+
                                         userDash.children[i].backroundcolor+","+
                                         userDash.children[i].warningcolor+","+
                                         userDash.children[i].minortickmarkcoloractive+","+
                                         userDash.children[i].minortickmarkcolorinactive+","+
                                         userDash.children[i].majortickmarkcoloractive+","+
                                         userDash.children[i].majortickmarkcolorinactive+","+
                                         userDash.children[i].labelcoloractive+","+
                                         userDash.children[i].labelcolorinactive+","+
                                         userDash.children[i].outerneedlecolortrailsave+","+
                                         userDash.children[i].middleneedlecortrailsave+","+
                                         userDash.children[i].lowerneedlecolortrailsave+","+
                                         userDash.children[i].innerneedlecolortrailsave+","+
                                         userDash.children[i].needlevisible+","+
                                         userDash.children[i].ringvisible+","+
                                         userDash.children[i].needlecentervisisble+","+
                                         userDash.children[i].labelfont+","+
                                         userDash.children[i].desctextx+","+
                                         userDash.children[i].desctexty+","+
                                         userDash.children[i].desctextfontsize+","+
                                         userDash.children[i].desctextfontbold+","+
                                         userDash.children[i].desctextfonttype+","+
                                         userDash.children[i].desctextdisplaytext+","+
                                         userDash.children[i].desctextdisplaytextcolor+","+
                                         userDash.children[i].peakneedlecolor+","+
                                         userDash.children[i].peakneedlecolor2+","+
                                         userDash.children[i].peakneedlelenght+","+
                                         userDash.children[i].peakneedlebasewidth+","+
                                         userDash.children[i].peakneedletipwidth+","+
                                         userDash.children[i].peakneedleoffset+","+
                                         userDash.children[i].peakneedlevisible+"\r\n");
            }
            if (userDash.children[i].information === "State gauge")
            {
                saveDashtofilestring += (userDash.children[i].information+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].pictureheight+","+userDash.children[i].mainvaluename+","+userDash.children[i].triggervalue+","+userDash.children[i].statepicturesourceoff+","+userDash.children[i].statepicturesourceon+"\r\n");
            }

            if (userDash.children[i].information === "State GIF")
            {
                saveDashtofilestring += (userDash.children[i].information+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].pictureheight+","+userDash.children[i].mainvaluename+","+userDash.children[i].triggervalue+","+userDash.children[i].statepicturesourceoff+","+userDash.children[i].statepicturesourceon+"\r\n");
            }
        }
    }
    function createDash()
    {
        //console.log("create Dashboard")

        for (var i=0; i<gaugelist.rowCount(); ++i)
        {
            switch (gaugelist.get(i).info) {

            case "Bar gauge": {
                //                                                     setWidth,              setHeight,              setX,               setY,             setMinValue,                setMaxValue,            setDecPlace,             setUnit,                   SetValueProperty,              SetWarnvaluehigh,              Setwarnvaluelow
                CreateBargaugeScript.createVerticalGauge(gaugelist.get(i).width,gaugelist.get(i).height,gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).minvalue,gaugelist.get(i).maxvalue,gaugelist.get(i).decplace,gaugelist.get(i).unit,gaugelist.get(i).valuepropertymain,gaugelist.get(i).warnvaluehigh,gaugelist.get(i).warnvaluelow);
                break;
            }
            case "Square gauge": {
                CreateSquareGaugeScript.createSquareGauge(gaugelist.get(i).width,gaugelist.get(i).height,gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).maxvalue,gaugelist.get(i).decplace,gaugelist.get(i).unit,gaugelist.get(i).id,gaugelist.get(i).vertgaugevis,gaugelist.get(i).horigaugevis,gaugelist.get(i).secvaluevis,"Dashboard",gaugelist.get(i).valuepropertymain,gaugelist.get(i).valuepropertysec,gaugelist.get(i).warnvaluehigh,gaugelist.get(i).warnvaluelow,gaugelist.get(i).framecolor,gaugelist.get(i).backroundcolor,gaugelist.get(i).titlecolor,gaugelist.get(i).titletextcolor,gaugelist.get(i).textcolor,gaugelist.get(i).barcolor,gaugelist.get(i).titlefontsize,gaugelist.get(i).mainfontsize,gaugelist.get(i).decplace2,gaugelist.get(i).textfont,gaugelist.get(i).valuefont);
                break;
            }
            case "gauge image": {
                CreatePictureScript.createPicture(gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).pictureheight,gaugelist.get(i).picturesource);
                break;
            }
            case "Text label gauge": {
                CreateTextScript.createText(gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).displaytext,gaugelist.get(i).fonttype,gaugelist.get(i).fontsize,gaugelist.get(i).textcolor,gaugelist.get(i).datasourcename,gaugelist.get(i).fontbold,gaugelist.get(i).decimalpoints,gaugelist.get(i).warnvaluehigh,gaugelist.get(i).warnvaluelow);
                break;
            }
            case "Round gauge": {
                CreateRoundgaugeScript.createRoundGauge(gaugelist.get(i).width,
                                                        gaugelist.get(i).x,
                                                        gaugelist.get(i).y,
                                                        gaugelist.get(i).mainvaluename,
                                                        gaugelist.get(i).maxvalue,
                                                        gaugelist.get(i).minvalue,
                                                        gaugelist.get(i).warnvaluehigh,
                                                        gaugelist.get(i).warnvaluelow,
                                                        gaugelist.get(i).startangle,
                                                        gaugelist.get(i).endangle,
                                                        gaugelist.get(i).redareastart,
                                                        gaugelist.get(i).divider,
                                                        gaugelist.get(i).tickmarksteps,
                                                        gaugelist.get(i).minortickmarksteps,
                                                        gaugelist.get(i).setlabelsteps,
                                                        gaugelist.get(i).decimalpoints,
                                                        gaugelist.get(i).needleinset,
                                                        gaugelist.get(i).setlabelinset,
                                                        gaugelist.get(i).setminortickmarkinset,
                                                        gaugelist.get(i).setmajortickmarkinset,
                                                        gaugelist.get(i).minortickmarkheight,
                                                        gaugelist.get(i).minortickmarkwidth,
                                                        gaugelist.get(i).tickmarkheight,
                                                        gaugelist.get(i).tickmarkwidth,
                                                        gaugelist.get(i).trailhighboarder,
                                                        gaugelist.get(i).trailmidboarder,
                                                        gaugelist.get(i).traillowboarder,
                                                        gaugelist.get(i).trailbottomboarder,
                                                        gaugelist.get(i).labelfontsize,
                                                        gaugelist.get(i).needleTipWidth,
                                                        gaugelist.get(i).needleLength,
                                                        gaugelist.get(i).needleBaseWidth,
                                                        gaugelist.get(i).redareainset,
                                                        gaugelist.get(i).redareawidth,
                                                        gaugelist.get(i).needlecolor,
                                                        gaugelist.get(i).needlecolor2,
                                                        gaugelist.get(i).backroundcolor,
                                                        gaugelist.get(i).warningcolor,
                                                        gaugelist.get(i).minortickmarkcoloractive,
                                                        gaugelist.get(i).minortickmarkcolorinactive,
                                                        gaugelist.get(i).majortickmarkcoloractive,
                                                        gaugelist.get(i).majortickmarkcolorinactive,
                                                        gaugelist.get(i).labelcoloractive,
                                                        gaugelist.get(i).labelcolorinactive,
                                                        gaugelist.get(i).outerneedlecolortrailsave,
                                                        gaugelist.get(i).middleneedlecortrailsave,
                                                        gaugelist.get(i).lowerneedlecolortrailsave,
                                                        gaugelist.get(i).innerneedlecolortrailsave,
                                                        gaugelist.get(i).needlevisible,
                                                        gaugelist.get(i).ringvisible,
                                                        gaugelist.get(i).needlecentervisisble,
                                                        gaugelist.get(i).labelfont,
                                                        gaugelist.get(i).desctextx,
                                                        gaugelist.get(i).desctexty,
                                                        gaugelist.get(i).desctextfontsize,
                                                        gaugelist.get(i).desctextfontbold,
                                                        gaugelist.get(i).desctextfonttype,
                                                        gaugelist.get(i).desctextdisplaytext,
                                                        gaugelist.get(i).desctextdisplaytextcolor,
                                                        gaugelist.get(i).peakneedlecolor,
                                                        gaugelist.get(i).peakneedlecolor2,
                                                        gaugelist.get(i).peakneedlelenght,
                                                        gaugelist.get(i).peakneedlebasewidth,
                                                        gaugelist.get(i).peakneedletipwidth,
                                                        gaugelist.get(i).peakneedleoffset,
                                                        gaugelist.get(i).peakneedlevisible
                                                        );
                break;
            }
            case "State gauge": {
                //console.log("Save state");
                CreateStatePictureScript.createPicture(gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).height,gaugelist.get(i).source,gaugelist.get(i).trigger,gaugelist.get(i).pictureoff,gaugelist.get(i).pictureon);
                break;
            }
            case "State GIF": {
                //console.log("Save state");
                CreateStateGIFScript.createPicture(gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).height,gaugelist.get(i).source,gaugelist.get(i).trigger,gaugelist.get(i).pictureoff,gaugelist.get(i).pictureon);
                break;
            }
            }
        }
    }

    function changeframeclolor()
    {
        for (var i=0; i<userDash.children.length; ++i)
        {
            if(userDash.children[i].information === "Square gauge")
            {
                userDash.children[i].framecolor = colorselect.textAt(colorselect.currentIndex)
                userDash.children[i].set()
            }
        }
    }
    function changetitlebarclolor()
    {
        for (var i=0; i<userDash.children.length; ++i)
        {
            if(userDash.children[i].information === "Square gauge")
            {
                userDash.children[i].resettitlecolor = colorselect.textAt(colorselecttitlebar.currentIndex)
                userDash.children[i].set()
            }
        }
    }

    function changebackroundcolor()
    {
        for (var i=0; i<userDash.children.length; ++i)
        {
            if(userDash.children[i].information === "Square gauge")
            {
                userDash.children[i].resetbackroundcolor = backroundcolor.textAt(backroundcolor.currentIndex)
                userDash.children[i].set()
            }
        }
    }
    function changebargaugecolor()
    {
        for (var i=0; i<userDash.children.length; ++i)
        {
            if(userDash.children[i].information === "Square gauge")
            {
                userDash.children[i].barcolor = bargaugecolor.textAt(bargaugecolor.currentIndex)
                userDash.children[i].set()
            }
        }
    }
    function changetitlecolor()
    {
        for (var i=0; i<userDash.children.length; ++i)
        {
            if(userDash.children[i].information === "Square gauge")
            {
                userDash.children[i].titletextcolor = titlecolor.textAt(titlecolor.currentIndex)
                userDash.children[i].set()
            }
        }
    }
    function changevaluetextcolor()
    {
        for (var i=0; i<userDash.children.length; ++i)
        {
            if(userDash.children[i].information === "Square gauge")
            {
                userDash.children[i].textcolor = valuetext.textAt(valuetext.currentIndex)
                userDash.children[i].set()
            }
        }
    }
    function savedash()
    {

        gaugelist.clear()
        for (var i=0; i<userDash.children.length; ++i)
        {


            //Check which type of gauges we have and send info to console
            if(userDash.children[i].information === "Square gauge"){
                //console.log("Save Square");
                //Apend all values of each gauge to the List Model
                gaugelist.append({"type": userDash.children[i].title,"width":userDash.children[i].width,"height":userDash.children[i].height,"x":userDash.children[i].x,"y":userDash.children[i].y,"maxvalue":userDash.children[i].maxvalue,"decplace":userDash.children[i].decimalpoints,"unit":userDash.children[i].mainunit,"id":userDash.children[i].title,"vertgaugevis":userDash.children[i].vertgaugevisible,"horigaugevis":userDash.children[i].horigaugevisible,"secvaluevis":userDash.children[i].secvaluevisible,"valuepropertymain":userDash.children[i].mainvaluename,"valuepropertysec":userDash.children[i].secvaluename,"warnvaluehigh":userDash.children[i].warnvaluehigh,"warnvaluelow":userDash.children[i].warnvaluelow,"framecolor":userDash.children[i].framecolor,"backroundcolor":userDash.children[i].resetbackroundcolor,"titlecolor":userDash.children[i].resettitlecolor,"titletextcolor":userDash.children[i].titletextcolor,"textcolor":userDash.children[i].textcolor,"barcolor":userDash.children[i].barcolor,"titlefontsize":userDash.children[i].titlefontsize,"mainfontsize":userDash.children[i].mainfontsize,"info":userDash.children[i].information,"decplace2":userDash.children[i].decimalpoints2,"textfont":userDash.children[i].textFonttype,"valuefont":userDash.children[i].valueFonttype})
            }
            if(userDash.children[i].information === "Bar gauge"){


                gaugelist.append({"type": userDash.children[i].title,"width":userDash.children[i].width,"height":userDash.children[i].height,"x":userDash.children[i].x,"y":userDash.children[i].y,"maxvalue":userDash.children[i].maxvalue,"decplace":userDash.children[i].decimalpoints,"unit":userDash.children[i].gaugename,"id":userDash.children[i].title,"valuepropertymain":userDash.children[i].mainvaluename,"warnvaluehigh":userDash.children[i].warnvaluehigh,"warnvaluelow":userDash.children[i].warnvaluelow,"info":userDash.children[i].information,"minvalue":userDash.children[i].minvalue})

                ;

            }
            if(userDash.children[i].information === "gauge image"){
                //console.log("Save Image");
                gaugelist.append({"info":userDash.children[i].information,"x":userDash.children[i].x,"y":userDash.children[i].y,"pictureheight":userDash.children[i].pictureheight,"picturesource":userDash.children[i].picturesource})
            }
            if(userDash.children[i].information === "Text label gauge"){
                //console.log("Text label gauge");

                gaugelist.append({"info":userDash.children[i].information,"width":userDash.children[i].width,"height":userDash.children[i].height,"x":userDash.children[i].x,"y":userDash.children[i].y,"displaytext":userDash.children[i].displaytext,"fonttype":userDash.children[i].fonttype,"fontsize":userDash.children[i].fontsize,"textcolor":userDash.children[i].textcolor,"datasourcename":userDash.children[i].datasourcename,"fontbold":userDash.children[i].fontbold,"decimalpoints":userDash.children[i].decimalpoints,"warnvaluehigh":userDash.children[i].warnvaluehigh,"warnvaluelow":userDash.children[i].warnvaluelow})

            }

            if(userDash.children[i].information === "Round gauge"){
                //console.log("Round gauge");
                //                                                                                              Width,                               setX,                     setY,                         Setmainvalue,                                    Setmaxvalue,                               Setminvalue,                              Setwarnvaluehigh,                                      Setwarnvaluelow,                                 Setredareastart,                                    Setdivider,                              Setneedletipwidth,                                    Setneedlelenght,                                    Setneedlebasewidth,                                     Setstartangle,                                 Setendangle,                               Settickmarksteps,                                     Setminortickmarksteps,                                         Setlabelsteps,                                    Setlabelinset,                                    Setminortickmarkinset,                                            Setmajortickmarkinset,                                           Setredareainset,                                   Settickmarkcolor,                                    Setneedlecolor,                                    Setdecimalpoints,                                  Setouterneedlecolortrail,                                            Setmiddleneedlecortrail,                                            Setlowerneedlecolortrail,                                           Setinnerneedlecolortrail,                                            Setwarningcolor,                                    Setlabelfontsize,                                    Setlabelcolor1,                                 Setlabelcolor2,                                  Setminortickmarkheight,                                          Setminortickmarkwidth,                                          Settickmarkheight,                                     Settickmarkwidth,                                   Setneedlevisible,S                                    etRingvisible,                                   SetBackroundcolor
                gaugelist.append({  "info":userDash.children[i].information,
                                     "width":userDash.children[i].width,
                                     "x":userDash.children[i].x,
                                     "y":userDash.children[i].y,
                                     "mainvaluename":userDash.children[i].mainvaluename,
                                     "maxvalue":userDash.children[i].maxvalue,
                                     "minvalue":userDash.children[i].minvalue,
                                     "warnvaluehigh":userDash.children[i].warnvaluehigh,
                                     "warnvaluelow":userDash.children[i].warnvaluelow,
                                     "startangle":userDash.children[i].startangle,
                                     "endangle":userDash.children[i].endangle,
                                     "redareastart":userDash.children[i].redareastart,
                                     "divider":userDash.children[i].divider,
                                     "tickmarksteps":userDash.children[i].tickmarksteps,
                                     "minortickmarksteps":userDash.children[i].minortickmarksteps,
                                     "setlabelsteps":userDash.children[i].setlabelsteps,
                                     "decimalpoints":userDash.children[i].decimalpoints,
                                     "needleinset":userDash.children[i].needleinset,
                                     "setlabelinset":userDash.children[i].setlabelinset,
                                     "setminortickmarkinset":userDash.children[i].setminortickmarkinset,
                                     "setmajortickmarkinset":userDash.children[i].setmajortickmarkinset,
                                     "minortickmarkheight":userDash.children[i].minortickmarkheight,
                                     "minortickmarkwidth":userDash.children[i].minortickmarkwidth,
                                     "tickmarkheight":userDash.children[i].tickmarkheight,
                                     "tickmarkwidth":userDash.children[i].tickmarkwidth,
                                     "trailhighboarder":userDash.children[i].trailhighboarder,
                                     "trailmidboarder":userDash.children[i].trailmidboarder,
                                     "traillowboarder":userDash.children[i].traillowboarder,
                                     "trailbottomboarder":userDash.children[i].trailbottomboarder,
                                     "labelfontsize":userDash.children[i].labelfontsize,
                                     "needleTipWidth":userDash.children[i].needleTipWidth,
                                     "needleLength":userDash.children[i].needleLength,
                                     "needleBaseWidth":userDash.children[i].needleBaseWidth,
                                     "redareainset":userDash.children[i].redareainset,
                                     "redareawidth":userDash.children[i].redareawidth,
                                     "tickmarkcolor":userDash.children[i].tickmarkcolor,
                                     "needlecolor":userDash.children[i].needlecolor,
                                     "needlecolor2":userDash.children[i].needlecolor2,
                                     "backroundcolor":userDash.children[i].backroundcolor,
                                     "warningcolor":userDash.children[i].warningcolor,
                                     "minortickmarkcoloractive":userDash.children[i].minortickmarkcoloractive,
                                     "minortickmarkcolorinactive":userDash.children[i].minortickmarkcolorinactive,
                                     "majortickmarkcoloractive":userDash.children[i].majortickmarkcoloractive,
                                     "majortickmarkcolorinactive":userDash.children[i].majortickmarkcolorinactive,
                                     "labelcoloractive":userDash.children[i].labelcoloractive,
                                     "labelcolorinactive":userDash.children[i].labelcolorinactive,
                                     "outerneedlecolortrailsave":userDash.children[i].outerneedlecolortrailsave,
                                     "middleneedlecortrailsave":userDash.children[i].middleneedlecortrailsave,
                                     "lowerneedlecolortrailsave":userDash.children[i].lowerneedlecolortrailsave,
                                     "innerneedlecolortrailsave":userDash.children[i].innerneedlecolortrailsave,
                                     "needlevisible":userDash.children[i].needlevisible,
                                     "ringvisible":userDash.children[i].ringvisible,
                                     "needlecentervisisble":userDash.children[i].needlecentervisisble,
                                     "labelfont":userDash.children[i].labelfont,
                                     "desctextx":userDash.children[i].desctextx,
                                     "desctexty":userDash.children[i].desctexty,
                                     "desctextfontsize":userDash.children[i].desctextfontsize,
                                     "desctextfontbold":userDash.children[i].desctextfontbold,
                                     "desctextfonttype":userDash.children[i].desctextfonttype,
                                     "desctextdisplaytext":userDash.children[i].desctextdisplaytext,
                                     "desctextdisplaytextcolor":userDash.children[i].desctextdisplaytextcolor,
                                     "peakneedlecolor":userDash.children[i].peakneedlecolor,
                                     "peakneedlecolor2":userDash.children[i].peakneedlecolor2,
                                     "peakneedlelenght":userDash.children[i].peakneedlelenght,
                                     "peakneedlebasewidth":userDash.children[i].peakneedlebasewidth,
                                     "peakneedletipwidth":userDash.children[i].peakneedletipwidth,
                                     "peakneedleoffset":userDash.children[i].peakneedleoffset,
                                     "peakneedlevisible":userDash.children[i].peakneedlevisible
                                 })
            }

            if(userDash.children[i].information === "State gauge"){
                //console.log("Save Image" ,userDash.children[i].mainvaluename);
                gaugelist.append({   "info":userDash.children[i].information,
                                     "x":userDash.children[i].x,
                                     "y":userDash.children[i].y,
                                     "height":userDash.children[i].pictureheight,
                                     "source":userDash.children[i].mainvaluename,
                                     "trigger":userDash.children[i].triggervalue,
                                     "pictureoff":userDash.children[i].statepicturesourceoff,
                                     "pictureon":userDash.children[i].statepicturesourceon})
            }
            if(userDash.children[i].information === "State GIF"){
                //console.log("Save Image" ,userDash.children[i].mainvaluename);
                gaugelist.append({   "info":userDash.children[i].information,
                                     "x":userDash.children[i].x,
                                     "y":userDash.children[i].y,
                                     "height":userDash.children[i].pictureheight,
                                     "source":userDash.children[i].mainvaluename,
                                     "trigger":userDash.children[i].triggervalue,
                                     "pictureoff":userDash.children[i].statepicturesourceoff,
                                     "pictureon":userDash.children[i].statepicturesourceon})
            }
        }
        var datamodel = []
        for (var j = 0; j < gaugelist.count; ++j) datamodel.push(gaugelist.get(j))
        datastore = JSON.stringify(datamodel)
    }
    //Color Selection panel
    Rectangle{
        id: selectcolor
        x:0
        y:0
        height :200
        width: 500
        color: "darkgrey"
        visible: false

        MouseArea {
            id: touchAreacolorselect
            anchors.fill:parent
            drag.target: selectcolor
        }

        Grid{
            rows:5
            columns: 3
            anchors.centerIn: parent
            spacing:5
            // FrameColor
            Text {
                text: qsTr("Frame color:")
                font.pixelSize: 15
            }
            Text {
                text: qsTr("Titlebar color:")
                font.pixelSize: 15
            }
            Text {
                text: qsTr("Backround color:")
                font.pixelSize: 15
            }
            ComboBox {
                id: colorselect
                width: 150;
                model: ColorList{}
                visible: true
                font.pixelSize: 15
                onCurrentIndexChanged: changeframeclolor()
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

            // Titlebarcolor
            ComboBox {
                id: colorselecttitlebar
                width: 150;
                model: ColorList{}
                visible: true
                font.pixelSize: 15
                onCurrentIndexChanged: changetitlebarclolor()
                //Component.onCompleted: {for(var i = 0; i < colorselecttitlebar.model.count; ++i) if (colorselecttitlebar.textAt(i) === "green")colorselecttitlebar.currentIndex = i }
                delegate:

                    ItemDelegate {
                    font.pixelSize: 15
                    width: colorselecttitlebar.width

                    Rectangle {
                        width: colorselecttitlebar.width
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
                    width: colorselecttitlebar.width
                    height: colorselecttitlebar.height
                    color:  colorselecttitlebar.currentText
                }
            }
            // Backroundcolor
            ComboBox {

                id: backroundcolor
                width: 150;
                model: ColorList{}
                font.pixelSize: 15
                visible: true
                onCurrentIndexChanged: changebackroundcolor()

                delegate:

                    ItemDelegate {
                    width: backroundcolor.width
                    font.pixelSize: 15
                    Rectangle {
                        width: backroundcolor.width
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
                    width: backroundcolor.width
                    height: backroundcolor.height
                    color:  backroundcolor.currentText
                }
            }
            Text {
                text: qsTr("Bargauge color:")
                font.pixelSize: 15
            }
            Text {
                text: qsTr("Title text color:")
                font.pixelSize: 15
            }
            Text {
                text: qsTr("Main text color:")
                font.pixelSize: 15
            }
            // BargaugeColor
            ComboBox {
                id: bargaugecolor
                width: 150;
                model: ColorList{}
                font.pixelSize: 15
                visible: true
                onCurrentIndexChanged: changebargaugecolor()

                delegate:

                    ItemDelegate {
                    width: bargaugecolor.width
                    font.pixelSize: 15
                    Rectangle {

                        width: bargaugecolor.width
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
                    width: bargaugecolor.width
                    height: bargaugecolor.height
                    color:  bargaugecolor.currentText
                }
            }

            //Title text

            ComboBox {

                id: titlecolor
                width: 150;
                model: ColorList{}
                visible: true
                font.pixelSize: 15
                onCurrentIndexChanged: changetitlecolor()

                delegate:

                    ItemDelegate {
                    width: titlecolor.width
                    font.pixelSize: 15
                    Rectangle {

                        width: titlecolor.width
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
                    width: titlecolor.width
                    height: titlecolor.height
                    color:  titlecolor.currentText
                }
            }

            //ValueText

            ComboBox {

                id: valuetext
                width: 150;
                model: ColorList{}
                visible: true
                font.pixelSize: 15
                onCurrentIndexChanged: changevaluetextcolor()

                delegate:

                    ItemDelegate {
                    width: valuetext.width
                    font.pixelSize: 15
                    Rectangle {

                        width: valuetext.width
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
                    width: valuetext.width
                    height: valuetext.height
                    color:  valuetext.currentText
                }
            }
            Button {
                id: btnclosecolorselect
                width:150
                text: qsTr("CLOSE")
                font.pixelSize: 15
                onClicked: {selectcolor.visible = false;}

            }
        }
    }
}
