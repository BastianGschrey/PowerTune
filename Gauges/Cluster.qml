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
    Component.onCompleted: {
        units.unitadjust()
        if (datastore) {
            gaugelist.clear()
            var datamodel = JSON.parse(datastore)
            for (var i = 0; i < datamodel.length; ++i) gaugelist.append(datamodel[i])
        }
        createDash()
    }
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


    Settings {
        property alias datastorecluster: mainwindow.datastore
    }
    Rectangle{
    z:300
    anchors.fill: mainwindow
    color: "transparent"
    WarningLoader{}
    }
    ListModel {
        id: gaugelist
    }


    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.maindashsetup
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

    Connections{
        target: Dashboard
        onMaindashsetupChanged: {
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

            if (dashvalue.textAt(0) !== "") {
            CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13),val4,val5,val6,val7,val8,val9,val10,val11,val12,val13);
            }
        }

    }

    //adjusts the Gauges to metric or imperial

    property  var unit : Dashboard.speedunits;

    //fade in effect for the Gauges (Welcome animation)



    OpacityAnimator {
        target: speedometer;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: revcounterticks;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }

    OpacityAnimator {
        id: speedoopacity
        target: speedoNeedlemph;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }



    //Backround image for the Gauges
    Image {
        id: backround
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
        source: "/graphics/MainDashnew.png"

    }


    //Rectangle which is centered in the image as reference for the gauge overlay during scaling
    Rectangle
    {
        id: scalerect
        width: backround.paintedWidth
        height: backround.paintedHeight
        anchors.centerIn: backround
        color: "transparent"

        //Test

        Rectangle{
            id: odotrip
            height: scalerect.height /15
            width: scalerect.width /2.33
            anchors.left: scalerect.left
            anchors.leftMargin: scalerect.width / 3.5
            anchors.bottom: scalerect.bottom
            anchors.bottomMargin: scalerect.height / 4
            color: "transparent"


            Text {
                id: tripname
                text:"Trip "
                font.pixelSize: scalerect.width / 50
                anchors.right: trip.left
                anchors.bottom: odotrip.bottom
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: trip
                text:(Dashboard.Trip).toFixed(1)
                font.pixelSize: scalerect.width / 45
                anchors.right: tripunits.left
                anchors.bottom: odotrip.bottom
                font.bold: true
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: tripunits
                text:" km"
                font.pixelSize: scalerect.width / 50
                anchors.right: parent.right
                anchors.bottom: odotrip.bottom
                //font.bold: true
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: odoname
                text:"Total "
                font.pixelSize: scalerect.width / 50
                anchors.left: parent.left
                anchors.bottom: odotrip.bottom
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: odo
                text: (Dashboard.Odo).toFixed(0)
                font.pixelSize: scalerect.width / 45
                anchors.left: odoname.right
                anchors.bottom: odotrip.bottom
                font.bold: true
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: odounit
                text:" km"
                font.pixelSize: scalerect.width / 60
                anchors.left: odo.right
                anchors.bottom: odotrip.bottom
                font.family: "Eurostile"
                color: "grey"

            }
        }


        //Rectangle in which the Speedometer Resides
        Rectangle {
            color: "transparent"
            id: speedo
            height: scalerect.height /1.6
            width: height
            anchors.left: scalerect.left
            anchors.leftMargin: scalerect.width / 18.18 //44
            anchors.top: scalerect.top
            anchors.topMargin: scalerect.height / 9.23 //52


            // Paint Tickmarks and Labels on the Speedo
            CircularGauge {
                id: speedometer
                height: parent.height
                width: height

                value: Dashboard.speed
                anchors.verticalCenter: parent.verticalCenter
                maximumValue: 320

                style: DashboardGaugeStyle {
                    labelStepSize: 20
                    labelInset: toPixels(0.25)
                    needleLength: 0
                    needleTipWidth: 0
                    needleBaseWidth: 0
                    tickmarkLabel:  Text {
                        font.pixelSize: styleData.value >= speedometer.value+15 || styleData.value <= speedometer.value-15  ? speedo.height /22 : (speedometer.value-styleData.value)+speedo.height /11

                        text: styleData.value
                        font.bold : styleData.value >= speedometer.value+10 || styleData.value <= speedometer.value-10  ? false : true
                        color: styleData.value >= speedometer.value+10 || styleData.value <= speedometer.value-10  ? "grey" : "white"
                        antialiasing: true
                    }
                }
            }
            // Speedo Needle animation
            GaugeNeedle_minus180to90  {
                //visible: false
                id: speedoNeedlekph
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.speed / 4.155844155844156

            }
            GaugeNeedle_minus180to90  {
                //visible: false
                id: speedoNeedlemph
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.speed / 2.597402597402597


            }
            Image {
                id: speedoinner
                width: parent.width /1.68
                height: width
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                source: "qrc:/graphics/Tacho_Mitte.png"

            }
            Text {
                id: speedinnertext
                text: Dashboard.speed
                font.pixelSize: scalerect.width / 20
                anchors.centerIn: parent
                font.family: "Eurostile"
                color: "white"

            }
        }
        //Rectangle in which the rev counter resides
        Rectangle {
            color: "transparent"
            id: revcounter
            height: scalerect.height /1.6
            width: height
            anchors.top: scalerect.top
            anchors.topMargin: scalerect.height / 9.23
            anchors.right: scalerect.right
            anchors.rightMargin: scalerect.height / 13 //44

            // Paint Tickmarks and Labels on the Rev counter
            CircularGauge {
                id: revcounterticks
                height: parent.height
                width: height
                value: Dashboard.rpm
                anchors.verticalCenter: parent.verticalCenter
                maximumValue: 10

                style: TachometerStyle {
                    //labelStepSize: 1
                    //labelInset: toPixels(0.21)
                    minimumValueAngle: -90
                    maximumValueAngle: 180
                    needleLength: 0
                    needleTipWidth: 0
                    needleBaseWidth: 0
                    tickmarkLabel:  Text {
                        font.pixelSize: styleData.value >= Dashboard.rpm/1000+0.5 || styleData.value <= Dashboard.rpm/1000-0.5  ? revcounterticks.height /22 : (revcounterticks.value-Dashboard.rpm/1000)+speedo.height /11
                        text: styleData.value
                        font.bold : styleData.value >= Dashboard.rpm/1000+0.5 || styleData.value <= Dashboard.rpm/1000-0.5  ? false : true
                        color: styleData.value <= Dashboard.rpm/1000 ? "white" : "grey"
                        antialiasing: true
                    }
                }

            }



            GaugeNeedle_minus90to180  {
                id: revneedele
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.rpm *0.0077

            }
            Image {
                id: revinner
                width: parent.width /1.68
                height: width
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                source: "qrc:/graphics/Tacho_Mitte.png"
            }
            Text {
                id: revinnertesxt
                text: Dashboard.rpm
                font.pixelSize: scalerect.width / 20
                anchors.centerIn: parent
                font.family: "Eurostile"
                color: "white"

            }
        }

    }


    Rectangle {
        id: touchsurface
        width: parent.width
        height: parent.height
        color: "transparent"
/*
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onClicked: pieMenu.popup(mouseX, mouseY)

        }
*/
    //Setting the scale of the speedo and temp gauges according to metric or imperial
    Item {
        id: units
        function unitadjust()
        {
            if (unit === "imperial") {speedoopacity.target = speedoNeedlemph,speedometer.maximumValue = 200,speedoNeedlemph.visible = true, speedoNeedlekph.visible = false,revneedele.visible = true;tripunits.text = " mi",odounit.text = " mi" };
            if (unit === "metric") {speedoopacity.target = speedoNeedlekph,speedometer.maximumValue = 320,speedoNeedlemph.visible = false, speedoNeedlekph.visible = true,tripunits.text = " km" ,odounit.text = " km"};
        }
    }


}
////////////////////////
    // From Here we do all the Magic stuff for the dynamic creation of the Gauges

    MouseArea {
        id: touchArea
        anchors.fill: parent
        onDoubleClicked:
        {
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
            font.pixelSize: 15
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
            x:0
            y:0
            model: Dashboard.dashfiles
            width: 200
            height: 40
            visible: false
            font.pixelSize: 15
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
                            console.log(userDash.children[i].information +" " + userDash.children[i].title +  " Item no." + i)
                            //Apend all values of each gauge to the List Model
                            gaugelist.append({"type": userDash.children[i].title,"width":userDash.children[i].width,"height":userDash.children[i].height,"x":userDash.children[i].x,"y":userDash.children[i].y,"maxvalue":userDash.children[i].maxvalue,"decplace":userDash.children[i].decimalpoints,"unit":userDash.children[i].mainunit,"id":userDash.children[i].title,"vertgaugevis":userDash.children[i].vertgaugevisible,"horigaugevis":userDash.children[i].horigaugevisible,"secvaluevis":userDash.children[i].secvaluevisible,"valuepropertymain":userDash.children[i].mainvaluename,"valuepropertysec":userDash.children[i].secvaluename,"warnvaluehigh":userDash.children[i].warnvaluehigh,"warnvaluelow":userDash.children[i].warnvaluelow,"framecolor":userDash.children[i].framecolor,"backroundcolor":userDash.children[i].resetbackroundcolor,"titlecolor":userDash.children[i].resettitlecolor,"titletextcolor":userDash.children[i].titletextcolor,"textcolor":userDash.children[i].textcolor,"barcolor":userDash.children[i].barcolor,"titlefontsize":userDash.children[i].titlefontsize,"mainfontsize":userDash.children[i].mainfontsize,"info":userDash.children[i].information})
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
                    Connect.readavailabledashfiles();
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
                    Connect.saveDashtoFile("MainDashexport",saveDashtofilestring);
                }
            }
            Button{
                id: load
                width: 95
                text: "LOAD"
                font.pixelSize: 15
                visible: false
                onClicked: {
                    loadfileselect.visible = false;
                    Connect.setfilename1(loadfileselect.textAt(loadfileselect.currentIndex));
                    btncancelload.visible = false;
                    squaregaugemenu.visible = false;
                    load.visible = false;
                    selectcolor.visible =false;
                    Dashboard.setdraggable(0);
                    Connect.readMaindashsetup();
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
                    load.visible = false;
                    selectcolor.visible =false;
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
         for (var i=0; i<userDash.children.length; ++i)
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
                font.pixelSize: 15
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
                font.pixelSize: 15
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
                font.pixelSize: 15
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
                font.pixelSize: 15
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
////////////////////////
}
