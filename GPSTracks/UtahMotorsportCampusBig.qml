import QtQuick 2.8
import QtLocation 5.8
import QtPositioning 5.8

Item {
    id: mapItem
    anchors.fill: parent
    Rectangle{
        anchors.fill: parent
        Plugin {
            id: mapPlugin
            name: "osm" // "mapboxgl", "esri", ...
            PluginParameter {
                name: 'osm.mapping.offline.directory'
                value: 'file:///offline_tiles/'
            }
        }

        Map {
            anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(40.580162,-112.379281)
            zoomLevel: 16

            // Draw the outline of Zwartkops Raceway in South Africa onto the map
            MapPolyline {
                id: umcbig
                line.width: 12
                line.color: 'blue'
                path: [
                    {latitude: 40.583169, longitude: -112.373225}, // Start/Finish straight
                    {latitude: 40.583072, longitude: -112.385948}, // Start Sunset Bend
                    {latitude: 40.583009, longitude: -112.386325},
                    {latitude: 40.583072, longitude: -112.385948},
                    {latitude: 40.582755, longitude: -112.386695},
                    {latitude: 40.582576, longitude: -112.386797},
                    {latitude: 40.582441, longitude: -112.386833},
                    {latitude: 40.582240, longitude: -112.386818},
                    {latitude: 40.581988, longitude: -112.386673},
                    {latitude: 40.581893, longitude: -112.386544}, // End Sunset Bend
                    {latitude: 40.580794, longitude: -112.385133}, // Start Dreamboat

                     {latitude: 40.583169, longitude: -112.373225}// Start/Finish straight
                ]
            }
            MapPolyline {
                id: startfinish
                line.width: 4
                line.color: 'red'
                path: [

                    {latitude: -25.809486, longitude: 28.112061},
                    {latitude: -25.809390, longitude: 28.112302}
                ]
            }
            // Draw a small circle for current Vehicle Location
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
    }
}
