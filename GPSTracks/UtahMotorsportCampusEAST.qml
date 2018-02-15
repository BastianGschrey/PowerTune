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
            center: QtPositioning.coordinate(40.580301,-112.383705)
            zoomLevel: 16

            // Draw the outline of Zwartkops Raceway in South Africa onto the map
            MapPolyline {
                id: umcEast
                line.width: 12
                line.color: 'blue'
                path: [

                    {latitude: 40.583176, longitude: -112.373406}, // End 23 Release
                    {latitude: 40.583136, longitude: -112.378157}, // Start "East one"
                    {latitude: 40.583094, longitude: -112.378391},
                    {latitude: 40.583030, longitude: -112.378523},
                    {latitude: 40.582948, longitude: -112.378620},
                    {latitude: 40.582824, longitude: -112.378701},
                    {latitude: 40.582654, longitude: -112.378777},
                    {latitude: 40.582561, longitude: -112.378785},
                    {latitude: 40.582453, longitude: -112.378757},
                    {latitude: 40.582354, longitude: -112.378696},
                    {latitude: 40.582264, longitude: -112.378579},
                    {latitude: 40.582188, longitude: -112.378402},
                    {latitude: 40.582164, longitude: -112.378241}, // End "East one"
                    {latitude: 40.582139, longitude: -112.377677}, // Start "Fast"
                    {latitude: 40.582085, longitude: -112.377400},
                    {latitude: 40.581988, longitude: -112.377100},
                    {latitude: 40.581531, longitude: -112.375853},
                    {latitude: 40.581520, longitude: -112.375813}, // End "Fast"
                    {latitude: 40.581395, longitude: -112.375569} // Start "Faster"
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
