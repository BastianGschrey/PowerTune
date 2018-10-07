//Creates instances of verticalbargauge, usable at runtime
var component;
var gauge;

function createVerticalGauge(setWidth,setHeight,setX,setY,setMinValue,setMaxValue,setDecPlace,setUnit,setID,SetValueObject,SetValueProperty,SetWarnvaluehigh,Setwarnvaluelow) {
    component = Qt.createComponent("verticalbargauge.qml");
    if (component.status == Component.Ready)
        finishCreation(setWidth,setHeight,setX,setY,setMinValue,setMaxValue,setDecPlace,setUnit,setID,SetValueObject,SetValueProperty,SetWarnvaluehigh,Setwarnvaluelow);
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setWidth,setHeight,setX,setY,setMinValue,setMaxValue,setDecPlace,setUnit,setID,SetValueObject,SetValueProperty,SetWarnvaluehigh,Setwarnvaluelow) {
    if (component.status == Component.Ready) {
        gauge = component.createObject(adaptronicDash, {"id": setID, "width": setWidth, "height": setHeight,
                                           "gaugemaxvalue": setMaxValue,
                                           "gaugeminvalue": setMinValue,
                                           "gaugetext": Qt.binding(function(){return SetValueObject[SetValueProperty].toFixed(setDecPlace) +  " " + setUnit}),
                                           "gaugevalue": Qt.binding(function(){return SetValueObject[SetValueProperty]}),
                                           "x": setX, "y": setY});
        //console.log(Qt.binding(function(){return SetValueObject[SetValueProperty].toFixed(setDecPlace) +  " " + setUnit}));
        if (gauge == null) {
            // Error Handling
            //console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        //console.log("Error loading component:", component.errorString());
    }
}
