import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Rectangle {
    width: parent.width
    height: parent.height
    color: "grey"

TabView {
    id: tabView
    anchors.fill: parent
    Tab {
        title: "Serial"
        SerialSettings{}
    }
}
}
