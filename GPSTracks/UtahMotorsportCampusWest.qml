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
            center: QtPositioning.coordinate(-25.809991,28.111000)
            zoomLevel: 16

            // Draw the outline of Zwartkops Raceway in South Africa onto the map
            MapPolyline {
                id: zwartkopstrack
                line.width: 12
                line.color: 'blue'
                path: [

                    {latitude: -25.809442, longitude: 28.112182}, // Start/Finish Line
                    {latitude: -25.808848, longitude: 28.111851}, // Start corner 1
                    {latitude: -25.808876, longitude: 28.111866},
                    {latitude: -25.808625, longitude: 28.111700},
                    {latitude: -25.808506, longitude: 28.111592},
                    {latitude: -25.808446, longitude: 28.111512},
                    {latitude: -25.808374, longitude: 28.111390},
                    {latitude: -25.808324, longitude: 28.111231},
                    {latitude: -25.808301, longitude: 28.111057},
                    {latitude: -25.808296, longitude: 28.110916},
                    {latitude: -25.808433, longitude: 28.110311}, // End Corner 1
                    {latitude: -25.808892, longitude: 28.109140}, // Start Corner 2
                    {latitude: -25.808886, longitude: 28.109046},
                    {latitude: -25.808845, longitude: 28.108916},
                    {latitude: -25.808754, longitude: 28.108848},
                    {latitude: -25.808605, longitude: 28.108857},
                    {latitude: -25.808436, longitude: 28.108972},
                    {latitude: -25.808359, longitude: 28.109133}, // End Corner 2
                    {latitude: -25.807891, longitude: 28.110330}, // Start Corner 3
                    {latitude: -25.807846, longitude: 28.110629},
                    {latitude: -25.807816, longitude: 28.110927},
                    {latitude: -25.807822, longitude: 28.111084},
                    {latitude: -25.807846, longitude: 28.111262},
                    {latitude: -25.807917, longitude: 28.111568},
                    {latitude: -25.807966, longitude: 28.111721},
                    {latitude: -25.808194, longitude: 28.112140},
                    {latitude: -25.808415, longitude: 28.112393},
                    {latitude: -25.808705, longitude: 28.112615},
                    {latitude: -25.808816, longitude: 28.112670},// End Corner 3
                    {latitude: -25.810641, longitude: 28.113553},// Start Corner 4
                    {latitude: -25.810975, longitude: 28.113599},
                    {latitude: -25.811169, longitude: 28.113539},
                    {latitude: -25.811453, longitude: 28.113323},
                    {latitude: -25.811643, longitude: 28.113059},
                    {latitude: -25.811765, longitude: 28.112729},
                    {latitude: -25.811789, longitude: 28.112524},// End Corner 4
                    {latitude: -25.811936, longitude: 28.110830},
                    {latitude: -25.812028, longitude: 28.109097},// Start Corner 5
                    {latitude: -25.812004, longitude: 28.108964},
                    {latitude: -25.811930, longitude: 28.108876},
                    {latitude: -25.811797, longitude: 28.108823},
                    {latitude: -25.811745, longitude: 28.108837},// End Corner 5
                    {latitude: -25.810903, longitude: 28.109043},// Start Corner 6
                    {latitude: -25.810771, longitude: 28.109147},
                    {latitude: -25.810706, longitude: 28.109284},
                    {latitude: -25.810701, longitude: 28.109462},
                    {latitude: -25.810742, longitude: 28.109593},
                    {latitude: -25.810814, longitude: 28.109690},// End Corner 6
                    {latitude: -25.811203, longitude: 28.110081},// Start Corner 7
                    {latitude: -25.811280, longitude: 28.110209},
                    {latitude: -25.811348, longitude: 28.110405},
                    {latitude: -25.811349, longitude: 28.110649},// End Corner 7
                    {latitude: -25.811191, longitude: 28.112574},// Start Corner 8
                    {latitude: -25.811159, longitude: 28.112728},
                    {latitude: -25.811060, longitude: 28.112865},
                    {latitude: -25.810914, longitude: 28.112910},
                    {latitude: -25.810759, longitude: 28.112884},// End Corner 8
                    {latitude: -25.809442, longitude: 28.112182} // Start/Finish Line
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
