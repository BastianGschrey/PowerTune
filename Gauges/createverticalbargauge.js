var component;
var gauge;

function createVerticalGauge(setWidth,setX,setY,setID,setText,setValue) {
    component = Qt.createComponent("verticalbargauge.qml");
    console.log(setValue)
    if (component.status == Component.Ready)
        finishCreation(setWidth,setX,setY,setID,setText,setValue);
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setWidth,setX,setY,setID,setText,setValue) {
    console.log(setValue);
    if (component.status == Component.Ready) {
        gauge = component.createObject(adaptronicDash, {"id": setID, "gaugetext": Qt.binding(function(){return setValue.MAP}), "x": setX, "y": setY});
        gauge.width = setWidth;
        console.log(setValue);
        if (gauge == null) {
            // Error Handling
            //console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        //console.log("Error loading component:", component.errorString());
    }
}
