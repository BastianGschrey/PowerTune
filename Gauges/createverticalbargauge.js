var component;
var gauge;

function createVerticalGauge(setWidth,setX,setY,setID,setText,SetValueObject,SerValueProperty) {
    component = Qt.createComponent("verticalbargauge.qml");
    console.log(SetValueObject)
    if (component.status == Component.Ready)
        finishCreation(setWidth,setX,setY,setID,setText,SetValueObject,SerValueProperty);
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setWidth,setX,setY,setID,setText,SetValueObject,SerValueProperty) {
    console.log(SetValueObject);
    if (component.status == Component.Ready) {
        gauge = component.createObject(adaptronicDash, {"id": setID,
                                           "gaugetext": Qt.binding(function(){return SetValueObject[SerValueProperty]}),
                                           "x": setX, "y": setY});
        gauge.width = setWidth;
        console.log(SetValueObject);
        if (gauge == null) {
            // Error Handling
            //console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        //console.log("Error loading component:", component.errorString());
    }
}
