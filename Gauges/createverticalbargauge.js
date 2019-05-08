//Creates instances of verticalbargauge, usable at runtime
var component;
var gauge;

function createVerticalGauge(setWidth,setHeight,setX,setY,setMinValue,setMaxValue,setDecPlace,setUnit,SetValueProperty,SetWarnvaluehigh,Setwarnvaluelow) {
    component = Qt.createComponent("Verticalbargauge.qml");
    if (component.status === Component.Ready)
        finishCreation(setWidth,setHeight,setX,setY,setMinValue,setMaxValue,setDecPlace,setUnit,SetValueProperty,SetWarnvaluehigh,Setwarnvaluelow);
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setWidth,setHeight,setX,setY,setMinValue,setMaxValue,setDecPlace,setUnit,SetValueProperty,SetWarnvaluehigh,Setwarnvaluelow) {
    if (component.status === Component.Ready) {
        gauge = component.createObject(userDash, {
                                           "width": setWidth,
                                           "height": setHeight,
                                           "decimalpoints":setDecPlace,
                                           "maxvalue": setMaxValue,
                                           "minvalue": setMinValue,
                                           "gaugename": setUnit,
                                           "mainvaluename" : SetValueProperty,
                                           "gaugevalue": Qt.binding(function(){return Dashboard[SetValueProperty]}),
                                           "x": setX, "y": setY});
        if (gauge === null) {
            // Error Handling
        }
    } else if (component.status === Component.Error) {
        // Error Handling
        //console.log("Error loading component:", component.errorString());
    }
}
