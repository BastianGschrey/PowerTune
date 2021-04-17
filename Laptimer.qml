import QtQuick 2.9
import QtLocation 5.9
import QtPositioning 5.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0
import IMD 1.0





Rectangle {
    id: mapItem
    anchors.fill: parent
    color: "black"
//Timer is inacurate for real timing therefore we use some Javascript to measure time and update the frontend with the measured time via Timer
    property double startTime: 0
    property int msecondsElapsed: 0

    function restartCounter()  {

        mapItem.startTime = 0;

    }


    function timeChanged()  {
        if(mapItem.startTime==0)
        {
            mapItem.startTime = new Date().getTime(); //returns the number of milliseconds since the epoch (1970-01-01T00:00:00Z);
        }
        var currentTime = new Date().getTime();
        mapItem.msecondsElapsed = (currentTime-startTime)/100;
    }


    Timer  {
        id: elapsedTimer
        interval: 100;
        running: false;
        repeat: true;
        onTriggered: {

            mapItem.timeChanged()
            time.text = new Date(mapItem.msecondsElapsed*100).toLocaleTimeString(Qt.locale(),"mm" + ":" + "ss" + "." + "zzz")

        }
    }

    Connections{
        target: Dashboard
        onGpsLatitudeChanged : {pos.poschanged()}
        onGpsLongitudeChanged : {pos.poschanged()}
        onCurrentLapChanged :{
            if (Dashboard.currentLap > 1)
            {
                laptimeModel.append({"lap":Dashboard.currentLap-1, "time":Dashboard.laptime})
                laptimelistview.incrementCurrentIndex()
            }
            if (Dashboard.currentLap == 0){
                laptimeModel.clear()
                laptimelistview.currentIndex = 0
            }
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "black"
        Plugin {
            id: mapPlugin
            name: "osm"
            //Offline directory for Map Tiles
            PluginParameter {
                name: 'osm.mapping.offline.directory'
                //value: ':/GPSTracks/'
                value: "/home/pi/maptiles/"
            }
            PluginParameter {
                name: 'osm.mapping.providersrepository.disabled'
                value: true
            }

            PluginParameter {
                name: "osm.mapping.providersrepository.address"
                //value: 'qrc:/GPSTracks/'
                value: "/home/pi/maptiles/"
            }

        }





        Connections{
            target: Dashboard
            onCurrentLapChanged :{
                if (Dashboard.currentLap > 0){elapsedTimer.running = true,mapItem.startTime = 0};
                if (Dashboard.currentLap == 0){elapsedTimer.running = false,mapItem.startTime = 0};
            }
        }

        Map {
            id: map
            height : 480
            width : 400
            plugin: mapPlugin
            zoomLevel: 16
            activeMapType: map.supportedMapTypes[1] //6 is good to get tracks
            copyrightsVisible : false
            gesture.enabled: false
            tilt: 0
            bearing: Dashboard.gpsbaering
            color: "black"






                MapPolyline
                {
                    id: trackLine
                    line.width: 10
                    line.color: 'blue'

                }

                MapPolyline {
                    line.width: 10
                    line.color: 'green'
                    path: [
                        //152.9653575639266,-27.22864613746248,0 152.9640338064991,-27.22827994189477,0 152.9634960611712,-27.22815172828676,0 152.963237125486,-27.22808317144805,
                        { latitude: -27.56063144916473, longitude: 153.06099752057867 },
                        { latitude: -27.56117359454, longitude: 153.06079367270368},
                    ]
                }

                Component.onCompleted:
                {
                    var lines = []
                    for(var i=0;i<geopath.size();i++)
                    {
                        lines[i] = geopath.coordinateAt(i)
                    }
                    trackLine.path = lines
                }


            // Draw a small red circle for current Vehicle Location
            MapQuickItem {
                id: marker
                anchorPoint.x: 10
                anchorPoint.y: 10
                width: 15
                coordinate: QtPositioning.coordinate(Dashboard.gpsLatitude,Dashboard.gpsLongitude)
                sourceItem: Rectangle {
                    id: image
                    width:20
                    height: width
                    radius: width*0.5
                    color: "red"
                }
            }
        }
        ComboBox {
            id: countryselect
            width: 170
            height: 30
            anchors.left: map.right
            font.pixelSize: 20
            //model: [ "Current Position","Australia","Germany","New Zealand","South Africa","United Kingdom","USA"]
            model: ["Current Position","Australia","Germany","New Zealand","Malaysia","South Africa","USA"]
            delegate: ItemDelegate {
                width: countryselect.width
                text: countryselect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                font.weight: countryselect.currentIndex == index ? Font.DemiBold : Font.Normal
                font.family: countryselect.font.family
                font.pixelSize: countryselect.font.pixelSize
                highlighted: countryselect.highlightedIndex == index
                hoverEnabled: countryselect.hoverEnabled
            }
            onCurrentIndexChanged: changecountry.change()
        }
        ComboBox {
            id: trackselect
            width: 230
            height: 30
            anchors.left: countryselect.right
            font.pixelSize: 20
            model: [ "Wakefield Park"]
            delegate: ItemDelegate {
                width: trackselect.width
                text: trackselect.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
                font.weight: trackselect.currentIndex == index ? Font.DemiBold : Font.Normal
                font.family: trackselect.font.family
                font.pixelSize: trackselect.font.pixelSize
                highlighted: trackselect.highlightedIndex == index
                hoverEnabled: trackselect.hoverEnabled
            }
            onCurrentIndexChanged: changetrack.change()

        }

        Button {
            id: stop
            //visible: false
            text: "Reset"
            width: 170
            height: 30
            anchors.right: parent.right
             anchors.bottom: parent.bottom
             anchors.margins: 20
            font.pixelSize: 20
            onClicked: {
                        laptimeModel.clear()
                        elapsedTimer.running = false
                        time.text= "00:00.000"
                        mapItem.startTime = 0
                        GPS.resetLaptimer()
                        }
        }
        Grid {
            id:grid1
            rows: 3
            columns: 2
            spacing: 5
            anchors.left: map.right
            anchors.top: countryselect.bottom


            Text { text: "Current : "
                font.pixelSize: 15
                font.bold: true
                color : "orangered"
                font.family: "Eurostile"}
            Text {
                id: time
                text: "00:00.000"
                font.pixelSize: 30
                font.bold: true
                color : "orangered"
                font.family: "Eurostile"}
            /*
            Text { text: "Last Lap:"
                font.pixelSize: 15
                font.bold: true
                color : "white"
                font.family: "Eurostile"}
            Text { text: Dashboard.laptime
                font.pixelSize: 30
                font.bold: true
                color : "white"
                font.family: "Eurostile"}
            */
            Text { text: "Best Lap: "
                font.pixelSize: 15
                font.bold: true
                color: "#00ff00"
                font.family: "Eurostile"}
            Text { text: Dashboard.bestlaptime
                font.pixelSize: 30
                font.bold: true
                color: "#00ff00"
                font.family: "Eurostile"}


            Text { text: "GPS FIX type: "
                font.pixelSize: 15
                font.bold: true
                font.family: "Eurostile"}
            Text { text: Dashboard.gpsFIXtype
                font.pixelSize: 30
                font.bold: true
                font.family: "Eurostile"}
        }

        Rectangle{
            //hides the overflow from the the ListView
            anchors.bottom: laptimes.top
            anchors.right: parent.right
            width: 400
            height: 40
            color: "black"
            z:100
        }

Rectangle{
    id :laptimes
    anchors.top: grid1.bottom
    anchors.left: map.right
    width: 400
    height: 200
    color: "black"

    ListModel {
        id: laptimeModel
    }

    Component {
        id: contactDelegate

        Item {
            id:leftcolum
            width: 400; height: 40
            Row {
            Column {
                Text {
                        text: "LAP " + lap
                        width: 110
                        color: "white"
                        font.pixelSize:  15
                        font.bold: true}
            }
            Column {
                Text { text: time
                       anchors.right: parent.right
                       width: 195
                       color: "white"
                       font.pixelSize:  30
                       font.bold: true}
            }
        }
        }
    }

    ListView {
        id: laptimelistview
        width: 400
        height: 200
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        model: laptimeModel
        delegate: contactDelegate
        highlight: Rectangle { color: "#505050"; radius: 5}
        focus: false
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 1000 }
        }
    }


}
IMD
{
    id:mapIO
}


        Item
        {
            id: changecountry
            function change(){

               /* if (countryselect.textAt(countryselect.currentIndex) == "Current Position"){trackselect.model = ["Tilt 0", "Tilt 45"],map.center= QtPositioning.coordinate(-25.804219,28.300091)};
                //if (countryselect.textAt(countryselect.currentIndex) == "Current Position"){trackselect.model = ["Tilt 0", "Tilt 45"],map.center= QtPositioning.coordinate(Dashboard.gpsLatitude,Dashboard.gpsLongitude)};
                if (countryselect.textAt(countryselect.currentIndex) == "Australia"){trackselect.model = ["Barbagallo Raceway","Carrnell Raceway","Collie Motorplex","Lakeside Raceway","Luddenham Raceway","Queensland Raceway","Wakefield Park"]};
                if (countryselect.textAt(countryselect.currentIndex) == "Germany"){trackselect.model = ["Hockenheim","Nürburgring"]};
                if (countryselect.textAt(countryselect.currentIndex) == "New Zealand"){trackselect.model = ["Pukekohe Park"]};
                if (countryselect.textAt(countryselect.currentIndex) == "Malaysia"){trackselect.model = ["Sepang"]};

                if (countryselect.textAt(countryselect.currentIndex) == "South Africa"){trackselect.model = ["Dezzi","Midvaal","Phakisa","Redstar","Zwartkops"]};
                //if (countryselect.textAt(countryselect.currentIndex) == "United Kingdom"){trackselect.model = ["Silverstone"]};
                if (countryselect.textAt(countryselect.currentIndex) == "USA"){trackselect.model = ["Buttonwillow"]};*/
                //if (countryselect.textAt(countryselect.currentIndex) == "Australia"){trackselect.model =[ mapIO.getTracks("Australia")];}

                    var lines = []
                    var l2 = mapIO.getTracks(countryselect.textAt(countryselect.currentIndex));
                    for(var i=0;i<mapIO.getTrackCount(countryselect.textAt(countryselect.currentIndex));i++)
                    {
                        lines[i] = mapIO.getTracks(countryselect.textAt(countryselect.currentIndex))[i];
                    }


                    trackselect.model = lines;

                console.log(countryselect.textAt(countryselect.currentIndex))
                //changetrack.change()
            }
        }
        Item
        {
            id: changetrack
            function change()
            {
                console.log(trackselect.textAt(trackselect.currentIndex))
                if (trackselect.textAt(trackselect.currentIndex) == "Tilt 0"){map.tilt = 0};
                if (trackselect.textAt(trackselect.currentIndex) == "Tilt 45"){map.tilt = 45};
                if (trackselect.textAt(trackselect.currentIndex) == "Bruce McLaren Motorsport Park"){map.center= QtPositioning.coordinate(-38.666331,176.1430453,17),map.zoomLevel = 15.6,map.bearing  = 43,map.tilt = 0};
                if (trackselect.textAt(trackselect.currentIndex) == "Redstar"){map.center= QtPositioning.coordinate(-26.074283, 28.751711),map.zoomLevel = 16,map.bearing  = 0,map.tilt = 0,Gps.defineFinishLine(-26.075097, 28.755060,-26.075111,28.755229,1)};
                if (trackselect.textAt(trackselect.currentIndex) == "Utah Motorsport Park"){map.center= QtPositioning.coordinate(40.579618,-112.3805621,398),map.zoomLevel = 15.1 ,map.bearing  = 90,map.tilt = 0};
                if (trackselect.textAt(trackselect.currentIndex) == "Wakefield Park"){map.center= QtPositioning.coordinate(-34.840764,149.686800),map.zoomLevel = 16,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(-34.840111,149.685229,-34.840172,149.685433,1)};
                if (trackselect.textAt(trackselect.currentIndex) == "Nürburgring"){map.center= QtPositioning.coordinate(50.358917, 6.965215),map.zoomLevel = 16,map.bearing  = 0,map.tilt = 0};
                if (trackselect.textAt(trackselect.currentIndex) == "Zwartkops"){map.center= QtPositioning.coordinate(-25.809960, 28.111175),map.zoomLevel = 16.6,map.bearing  = 0,map.tilt = 0,Gps.defineFinishLine(-25.809477,28.112105,-25.809404,28.112276,1)};
                if (trackselect.textAt(trackselect.currentIndex) == "Pukekohe Park"){map.center= QtPositioning.coordinate(-37.215300, 174.919707),map.zoomLevel = 15.6,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(-37.215564,174.915710,-37.215510, 174.915914,1)}
                if (trackselect.textAt(trackselect.currentIndex) == "Carrnell Raceway"){map.center= QtPositioning.coordinate(-28.685079, 151.938694),map.zoomLevel = 17,map.tilt = 0,map.bearing  = 22}
                if (trackselect.textAt(trackselect.currentIndex) == "Phakisa"){map.center= QtPositioning.coordinate(-27.904231, 26.713996),map.zoomLevel = 15.6,map.tilt = 0,map.bearing  = 22}
                if (trackselect.textAt(trackselect.currentIndex) == "Midvaal"){map.center= QtPositioning.coordinate(-26.612376, 28.059484),map.zoomLevel = 16,map.tilt = 0,map.bearing  = 22,Gps.defineFinishLine(-26.613392, 28.058586,-26.613509,28.058717,1)}
                if (trackselect.textAt(trackselect.currentIndex) == "Dezzi"){map.center= QtPositioning.coordinate(-30.770474, 30.426004),map.zoomLevel = 16,map.tilt = 0,map.bearing  = 22}
                if (trackselect.textAt(trackselect.currentIndex) == "Buttonwillow"){map.center= QtPositioning.coordinate(35.491242, -119.545396),map.zoomLevel = 15.4,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(35.488681,-119.544514,35.488858,-119.544521,2)}
                if (trackselect.textAt(trackselect.currentIndex) == "Sepang"){map.center= QtPositioning.coordinate(2.760217, 101.738092),map.zoomLevel = 15.6,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(2.760652,101.738394,2.760894,101.738374,2)}
                if (trackselect.textAt(trackselect.currentIndex) == "Barbagallo Raceway"){map.center= QtPositioning.coordinate(-31.664326, 115.789962),map.zoomLevel = 15.7,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(-31.664168,115.786292,-31.664171,115.786459,1)}
                if (trackselect.textAt(trackselect.currentIndex) == "Collie Motorplex"){map.center= QtPositioning.coordinate(-33.431971, 116.244369),map.zoomLevel = 16,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(-33.430061,116.243180,-33.430184, 116.243386,1)}
                if (trackselect.textAt(trackselect.currentIndex) == "Lakeside Raceway"){map.center= QtPositioning.coordinate(-27.228108, 152.964956),map.zoomLevel = 16,map.tilt = 0,map.bearing  = 90,Gps.defineFinishLine(-27.228568, 152.964881,-27.228397, 152.964931,2)}
                if (trackselect.textAt(trackselect.currentIndex) == "Queensland Raceway"){map.center= QtPositioning.coordinate(-27.690381, 152.653035),map.zoomLevel = 16,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(-27.690635, 152.654481,-27.690637, 152.654713,1)}
                if (trackselect.textAt(trackselect.currentIndex) == "Luddenham Raceway"){map.center= QtPositioning.coordinate(-33.857640, 150.717556),map.zoomLevel = 16.7,map.tilt = 0,map.bearing  = 0,Gps.defineFinishLine(-33.858250, 150.718023,-33.858430, 150.718117,1)}


                if(mapIO.getTrackExists(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex)))
                {
                    //console.log("getcentreqml");
                    //console.log(mapIO.getCenter(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex)) + " Position 0");

                    map.center=QtPositioning.coordinate(parseFloat(mapIO.getCenter(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[0]),parseFloat(mapIO.getCenter(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[1]));
                    map.zoomLevel =16;
                    map.tilt = 0;
                    map.bearing = 0;
                    var linex1 = mapIO.getStartFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[0];
                    var liney1 = mapIO.getStartFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[1];
                    var linex2 = mapIO.getStartFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[2];
                    var liney2 = mapIO.getStartFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[3];
                    //TODO fill in DefineFinishLine
                    Gps.defineFinishLine(linex1,liney1,linex2,liney2,mapIO.getStartFinishDirection(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex)));
                    //console.log(mapIO.getStartFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[0]);
                    //var lines = []
                    trackLine.setPath( mapIO.loadMapData(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex)));
                    console.log("Tracklinepath " +trackLine.path);
                    //console.log(lines);

                    if(mapIO.getExistsSecondFinish())
                    {
                        var linex21 = mapIO.getSecondFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[0];
                        var liney21 = mapIO.getSecondFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[1];
                        var linex22 = mapIO.getSecondFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[2];
                        var liney22 = mapIO.getSecondFinishLine(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex))[3];
                        var direction2 = mapIO.getSecondFinishDirection(countryselect.textAt(countryselect.currentIndex),trackselect.textAt(trackselect.currentIndex));
                        Gps.defineFinishLine2(linex21,liney21,linex22,liney22,direction2);
                    }

                }





            }
        }

        Item
        {
            //Needed to permanently update the Map Center if Current Position view is selected
            id: pos
            function poschanged(){
                if (countryselect.textAt(countryselect.currentIndex) == "Current Position"){map.center= QtPositioning.coordinate(Dashboard.gpsLatitude,Dashboard.gpsLongitude)};
            }
        }
    }
}
