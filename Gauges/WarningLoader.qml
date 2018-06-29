import QtQuick 2.8

Rectangle {
    id: loadersource
    anchors.fill: parent
    color:"transparent"

    property bool rpmwarn
    property bool boostwarn
    property bool coolanttempwarn
    property bool knockwarn
    //property var warnmsg : "hello"

    Loader {
        id: warningSign
        source: ""
    }
    Text {
        id: warnmsg
        text:"test"
        visible: false
        onTextChanged: {loadersource.setloadersource()}
    }
    Connections{
        target: Dashboard
        onRpmChanged:{if (Dashboard.rpm > Dashboard.rpmwarn) {rpmwarn = true,warnmsg.text = "Danger to Manifold",console.log(warnmsg.text)} else rpmwarn= false }
        onPimChanged:{if (Dashboard.pim > Dashboard.boostwarn) {boostwarn = true,warnmsg.text = "Boost exceeded " +Dashboard.pim} else boostwarn= false }
        onWatertempChanged:{if (Dashboard.Watertemp > Dashboard.waterwarn) {coolanttempwarn = true,warnmsg.text = "Coolant Temp. exceeded " +Dashboard.Watertemp} else coolanttempwarn= false }
        onKnockChanged:{if (Dashboard.Knock > Dashboard.knockwarn) {knockwarn = true,warnmsg.text = "Knock exceeded " +Dashboard.Knock} else knockwarn= false }
    }

    Connections{
        target: loadersource
        onRpmwarnChanged:{loadersource.setloadersource()}
        onBoostwarnChanged:{loadersource.setloadersource()}
        onCoolanttempwarnChanged:{loadersource.setloadersource()}
        onKnockwarnChanged:{loadersource.setloadersource()}
    }


    function setloadersource()
    {
        if (rpmwarn == true || boostwarn == true || coolanttempwarn == true ||knockwarn == true ) {warningSign.setSource("qrc:/Gauges/Warning.qml",{ "warningtext": warnmsg.text })};
        if (rpmwarn == false && boostwarn == false && coolanttempwarn == false && knockwarn == false ){warningSign.source = ""} //Removes all warning signs
    }

}
//
