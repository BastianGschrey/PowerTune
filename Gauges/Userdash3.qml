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
import "qrc:/Gauges/createsquaregaugeUserDash.js" as CreateSquareGaugeScript

Item {
    id: mainwindow
    anchors.fill: parent
    property string datastore: ""
    property string saveDashtofilestring : ""
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

    Drag.active: true

    ListModel {
        id: gaugelist
    }

    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup3
        visible:false
    }

    DatasourcesList{id: powertunedatasource}

    Component.onCompleted: {
        if (datastore) {
            gaugelist.clear()
            var datamodel = JSON.parse(datastore)
            for (var i = 0; i < datamodel.length; ++i) gaugelist.append(datamodel[i])
        }
        createDash()
        console.log("")
    }
    /*
    onClosing: {
      var datamodel = []
      for (var i = 0; i < gaugelist.count; ++i) datamodel.push(gaugelist.get(i))
      datastore = JSON.stringify(datamodel)
    }
*/
    Settings {
        property alias datastore3: mainwindow.datastore
        property alias rpmbackround3: rpmstyleselector.currentIndex
    }



    Connections{
        target: Dashboard

        onDashsetup3Changed:
        {
            if (dashvalue.textAt(8) === "true") {val1 = true};
            if (dashvalue.textAt(8) === "false") {val1 = false};
            if (dashvalue.textAt(9) === "true") {val2 = true};
            if (dashvalue.textAt(9) === "false") {val2 = false};
            if (dashvalue.textAt(10) === "true") {val3 = true};
            if (dashvalue.textAt(10) === "false") {val3 = false};
            if (dashvalue.textAt(14) !== "") {val4 = dashvalue.textAt(14);}else {val4 = 20000;}
            if (dashvalue.textAt(15) !== "") {val5 = dashvalue.textAt(15);}else {val5 = -20000;}
            if (dashvalue.textAt(16) !== "") {val6 = dashvalue.textAt(16);}else {val6 = "#9f9f9f";}
            if (dashvalue.textAt(17) !== "") {val7 = dashvalue.textAt(17);}else {val7 = "black";}
            if (dashvalue.textAt(18) !== "") {val8 = dashvalue.textAt(18);}else {val8 = "#9f9f9f";}
            if (dashvalue.textAt(19) !== "") {val9 = dashvalue.textAt(19);}else {val9 = "white";}
            if (dashvalue.textAt(20) !== "") {val10 = dashvalue.textAt(20);}else {val10 = "white";}
            if (dashvalue.textAt(21) !== "") {val11 = dashvalue.textAt(21);}else {val11 = "grey";}
            if (dashvalue.textAt(22) !== "") {val12 = dashvalue.textAt(22);}else {val12 = 28;}
            if (dashvalue.textAt(23) !== "") {val13 = dashvalue.textAt(23);}else {val13 = 50;}
            CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13),val4,val5,val6,val7,val8,val9,val10,val11,val12,val13);
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
    Rectangle{
        anchors.fill: parent
        z:100 //This makes the Rectangle appear in front of the bar gauges
        color: "transparent"
        WarningLoader{}
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
            btnadd.visible = true;
            btncancel.visible = true;
            btnsave.visible = true;
            btnclear.visible = true;
            loadfromfile.visible = true;
            squaregaugemenu.visible = true;
            Dashboard.setdraggable(1);
            //pimenu.popup(touchArea.mouseX,touchArea.mouseY)
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
            KeyboardStyle{
                fullScreenInputCursor: Rectangle{
                    width: 1
                    color: "blue"
                    visible: parent.blinkStatus
                }
                keyboardBackground: Rectangle{
                    anchors.fill: parent
                    color: "green"
                }

            }

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
        height: 200
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
            rows:4
            columns: 1

            Text {
                text: qsTr("RPM Style:")
                font.pixelSize: 25
                font.bold: true
            }
            ComboBox {
                id: rpmstyleselector
                width: 200
                height: 40
                model: ["None", "Style1","Style2", "Style3", "Style4"]
                onCurrentIndexChanged: rpmgauge.selector();
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
        height: 300
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
            x:0
            y:0
            textRole: "titlename"
            width: 200
            height: 40
            model: powertunedatasource
        }
        ComboBox {
            id: loadfileselect
            x:0
            y:0
            model: Dashboard.dashfiles
            width: 200
            height: 40
            visible: false
        }

        Grid{
            rows:6
            columns: 2
            //anchors.top : cbx_sources.bottom
            spacing:10
            x:0
            y:45

            Button {
                id: btnadd
                width: 95
                height: 40
                text: qsTr("ADD")
                font.pixelSize: 15
                onClicked: {
                    CreateSquareGaugeScript.createSquareGauge(266,119,0,240,248,0,powertunedatasource.get(cbx_sources.currentIndex).defaultsymbol,powertunedatasource.get(cbx_sources.currentIndex).titlename,false,true,false,"Dashboard",powertunedatasource.get(cbx_sources.currentIndex).sourcename,powertunedatasource.get(cbx_sources.currentIndex).sourcename,10000,-20000,"lightsteelblue","black","lightsteelblue","white","white","blue",25,40);
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }

            Button {
                id: btnsave
                width: 95
                text: qsTr("SAVE")
                font.pixelSize: 15
                onClicked: {
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                    // Clearing the gaugelist
                    gaugelist.clear()
                    for (var i=0; i<userDash.children.length; ++i)
                    {

                        //Check which type of gauges we have and send info to console
                        if(userDash.children[i].information === "Square gauge"){
                            //console.log(userDash.children[i].information +" " + userDash.children[i].valuepropertymain +  " Item no." + i)
                            //Apend all values of each gauge to the List Model
                            gaugelist.append({"type": userDash.children[i].title,"width":userDash.children[i].width,"height":userDash.children[i].height,"x":userDash.children[i].x,"y":userDash.children[i].y,"maxvalue":userDash.children[i].maxvalue,"decplace":userDash.children[i].decimalpoints,"unit":userDash.children[i].mainunit,"id":userDash.children[i].title,"vertgaugevis":userDash.children[i].vertgaugevisible,"horigaugevis":userDash.children[i].horigaugevisible,"secvaluevis":userDash.children[i].secvaluevisible,"valuepropertymain":userDash.children[i].mainvaluename,"valuepropertysec":userDash.children[i].secvaluename,"warnvaluehigh":userDash.children[i].warnvaluehigh,"warnvaluelow":userDash.children[i].warnvaluelow,"framecolor":userDash.children[i].framecolor,"backroundcolor":userDash.children[i].resetbackroundcolor,"titlecolor":userDash.children[i].resettitlecolor,"titletextcolor":userDash.children[i].titletextcolor,"textcolor":userDash.children[i].textcolor,"barcolor":userDash.children[i].barcolor,"titlefontsize":userDash.children[i].titlefontsize,"mainfontsize":userDash.children[i].mainfontsize})
                            //console.log(gaugelist.get(i).width)

                        }
                        if(userDash.children[i].information === "Bar gauge"){
                            //console.log(userDash.children[i].information +" " + userDash.children[i].title +  " Item no." + i)
                        }
                        if(userDash.children[i].information === "Round gauge"){
                            //console.log(userDash.children[i].information +" " + userDash.children[i].title +  " Item no." + i)
                        }
                    }

                    var datamodel = []
                    for (var j = 0; j < gaugelist.count; ++j) datamodel.push(gaugelist.get(j))
                    datastore = JSON.stringify(datamodel)

                }
            }
            Button {
                id: btnopencolorselect
                width:95
                text: qsTr("COLORS")
                font.pixelSize: 15
                onClicked: {
                    selectcolor.visible =true;
                    squaregaugemenu.visible = false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btnclear
                width: 95
                text: "CLEAR"
                font.pixelSize: 15
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
                text: "IMPORT"
                font.pixelSize: 15

                onClicked: {

                    btncancelload.visible = true;
                    loadfromfile.visible = false;
                    loadfileselect.visible = true;
                    btnadd.visible = false;
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
                }
            }
            Button{
                id: savetofile
                width: 95
                text: "EXPORT"
                font.pixelSize: 15

                onClicked: {
                    squaregaugemenu.visible = false;
                    Dashboard.setdraggable(0);
                    selectcolor.visible =false;
                    saveDashtofile();
                    Connect.saveDashtoFile("Dash3Export",saveDashtofilestring);
                }
            }
            Button{
                id: load
                width: 95
                text: "LOAD"
                font.pixelSize: 15
                visible: false
                onClicked: {
                    Connect.setfilename3(loadfileselect.textAt(loadfileselect.currentIndex));
                    loadfileselect.visible = false;
                    btncancelload.visible = false;
                    squaregaugemenu.visible = false;
                    load.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                    Connect.readdashsetup3();
                }
            }
            Button{
                id: btncancelload
                width: 95
                text: "CANCEL"
                font.pixelSize: 15
                visible: false
                onClicked: {
                    loadfileselect.visible = false;
                    btncancelload.visible = false;
                    squaregaugemenu.visible = false;
                    squaregaugemenu
                    load.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button{
                id: btnbackround
                width: 95
                text: "RPM"
                font.pixelSize: 15
                onClicked: {
                    rpmbackroundselector.visible =true;
                    squaregaugemenu.visible = false;
                    btnbackround.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
            Button {
                id: btncancel
                width: 95
                text: "CLOSE"
                font.pixelSize: 15
                onClicked:  {
                    squaregaugemenu.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                }
            }
        }
    }
    // End
    /*
    PieMenu{
        id: pimenu
        z:120
        Quick1.MenuItem{
            text: "Add square gauge"
            onTriggered: function() { print("Action 3"); }
        }
        Quick1.MenuItem{
            text: "Add bar gauge"
        }
        Quick1.MenuItem{
            text: "Add analoge gauge"
        }
        Quick1.MenuItem{
            text: "Change color square gauge"
        }
        Quick1.MenuItem{
            text: "Export to file"
        }
        Quick1.MenuItem{
            text: "Import from file"
        }
    }
*/
    //We put all Gauges here
    Item{
        id: userDash
        anchors.fill: parent

    }

    ///////////////////Functions
    function saveDashtofile()
    {
         saveDashtofilestring = ""
         for (var i=0; i<gaugelist.rowCount(); ++i)
             saveDashtofilestring += (userDash.children[i].width+","+userDash.children[i].height+","+userDash.children[i].x+","+userDash.children[i].y+","+userDash.children[i].maxvalue+","+userDash.children[i].decimalpoints+","+userDash.children[i].mainunit+","+userDash.children[i].title+","+userDash.children[i].vertgaugevisible+","+userDash.children[i].horigaugevisible+","+userDash.children[i].secvaluevisible+","+"Dashboard"+","+userDash.children[i].mainvaluename+","+userDash.children[i].secvaluename+","+userDash.children[i].warnvaluehigh+","+userDash.children[i].warnvaluelow+","+userDash.children[i].framecolor+","+userDash.children[i].resetbackroundcolor+","+userDash.children[i].resettitlecolor+","+userDash.children[i].titletextcolor+","+userDash.children[i].textcolor+","+userDash.children[i].barcolor+","+userDash.children[i].titlefontsize+","+userDash.children[i].mainfontsize+","+userDash.children[i].information+"\r\n");

    }

    function createDash()
    {
        console.log("create Dashboard")
        for (var i=0; i<gaugelist.rowCount(); ++i)
            CreateSquareGaugeScript.createSquareGauge(gaugelist.get(i).width,gaugelist.get(i).height,gaugelist.get(i).x,gaugelist.get(i).y,gaugelist.get(i).maxvalue,gaugelist.get(i).decplace,gaugelist.get(i).unit,gaugelist.get(i).id,gaugelist.get(i).vertgaugevis,gaugelist.get(i).horigaugevis,gaugelist.get(i).secvaluevis,"Dashboard",gaugelist.get(i).valuepropertymain,gaugelist.get(i).valuepropertysec,gaugelist.get(i).warnvaluehigh,gaugelist.get(i).warnvaluelow,gaugelist.get(i).framecolor,gaugelist.get(i).backroundcolor,gaugelist.get(i).titlecolor,gaugelist.get(i).titletextcolor,gaugelist.get(i).textcolor,gaugelist.get(i).barcolor,gaugelist.get(i).titlefontsize,gaugelist.get(i).mainfontsize);

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
                console.log("From" + userDash.children[i].resettitlecolor)
                userDash.children[i].resettitlecolor = colorselect.textAt(colorselecttitlebar.currentIndex)
                console.log("To" + userDash.children[i].resettitlecolor)
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
        /*
        Item {
            id: colorsettingsSaved
            Settings {
                property alias indexframecolor: colorselect.currentIndex
                property alias indextitlebarcolor: colorselecttitlebar.currentIndex
                property alias indexbackroundcolor: backroundcolor.currentIndex
                property alias indexbargaugecolor: bargaugecolor.currentIndex
                property alias indextitletextcolor: titlecolor.currentIndex
                property alias indexmaintextcolor: valuetext.currentIndex
            }
        }
        */
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
                onCurrentIndexChanged: changeframeclolor()
                delegate:

                    ItemDelegate {
                    id:itemDelegate
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
                onCurrentIndexChanged: changetitlebarclolor()

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




