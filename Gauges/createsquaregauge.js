//Creates instances of squaregauge, usable at runtime

var component;
var gauge;

function createSquareGauge(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec) {
    component = Qt.createComponent("squaregauge.qml");
    if (component.status == Component.Ready){
        console.log("component ready");
        finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec);
    }
    else {
        component.statusChanged.connect(finishCreation);
        console.log("component not ready!");
    }
}

function finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec) {
    if (component.status == Component.Ready) {
        console.log("creating object");
        gauge = component.createObject(fueltechDash, {"id": setID, "title": setID, "width": setWidth, "height": setHeight,
                                           "maintextvalue": Qt.binding(function(){return SetValueObject[SetValuePropertyMain].toFixed(setDecPlace)}),
                                           "secvalue": Qt.binding(function(){return SetValueObject[SetValuePropertySec].toFixed(setDecPlace)}),
                                           "mainvalue": Qt.binding(function(){return SetValueObject[SetValuePropertyMain]}),
                                           "maxvalue": setMaxValue,
                                           "mainunit": setUnit,
                                           "vertgaugevisible": setVertGaugeVis,
                                           "horigaugevisible": setHoriGaugeVis,
                                           "secvaluevisible": setSecValueVis,
                                           "x": setX, "y": setY});
        console.log("creating object done");
        if (gauge == null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
