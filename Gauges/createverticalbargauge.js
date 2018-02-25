var component;
var gauge;

function createVerticalGauge(setWidth,setHeight,setX,setY,setMaxValue,setUnit,setID,SetValueObject,SetValueProperty) {
    component = Qt.createComponent("verticalbargauge.qml");
    if (component.status == Component.Ready)
        finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setUnit,setID,SetValueObject,SetValueProperty);
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setUnit,setID,SetValueObject,SetValueProperty) {
    console.log(setHeight)
    if (component.status == Component.Ready) {
        gauge = component.createObject(adaptronicDash, {"id": setID, "width": setWidth, "height": setHeight,
                                           "gaugemaxvalue": setMaxValue,
                                           "gaugetext": Qt.binding(function(){return SetValueObject[SetValueProperty] + " " + setUnit}),
                                           "gaugevalue": Qt.binding(function(){return SetValueObject[SetValueProperty]}),
                                           "x": setX, "y": setY});
        //gauge.width = setWidth;
        //gauge.height = setHeight
        if (gauge == null) {
            // Error Handling
            //console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        //console.log("Error loading component:", component.errorString());
    }
}
