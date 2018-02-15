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
            center: QtPositioning.coordinate(-25.804499,28.301012)
            zoomLevel: 16

            // Draw the outline of Zwartkops Raceway in South Africa onto the map
            MapPolyline {
                id: myhometest
                line.width: 12
                line.color: 'blue'
                path: [

                    {latitude: -25.804287, longitude: 28.300355}, // Start/Finish Line
                    {latitude: -25.804801, longitude: 28.301865}, // Start corner 1

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
