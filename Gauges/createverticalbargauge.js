var component;
var gauge;

function createVerticalGauge(setWidth,setX,setY,setMaxValue,setID,SetValueObject,SetValueProperty) {
    component = Qt.createComponent("verticalbargauge.qml");
    console.log(setMaxValue)
    if (component.status == Component.Ready)
        finishCreation(setWidth,setX,setY,setMaxValue,setID,SetValueObject,SetValueProperty);
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setWidth,setX,setY,setMaxValue,setID,SetValueObject,SetValueProperty) {
    console.log(setMaxValue)
    if (component.status == Component.Ready) {
        gauge = component.createObject(adaptronicDash, {"id": setID,
                                           "gaugetext": Qt.binding(function(){return SetValueObject[SetValueProperty]}),
                                           "gaugevalue": Qt.binding(function(){return SetValueObject[SetValueProperty]}),
                                           "x": setX, "y": setY});
        gauge.width = setWidth;
        if (gauge == null) {
            // Error Handling
            //console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        //console.log("Error loading component:", component.errorString());
    }
}
