//JS Script thats creates dynamical barGauge.qml instances



    //barGauge = component.createObject(mainrectangle, {'title':'TestGauge', 'value':'map', 'orientation'='Qt.Horizontal'});


var component;
var barGauge;

function createbarGaugeObjects() {
    console.log("in js");
    component = Qt.createComponent("BarGauge.qml");
    console.log(component.status);
    if (component.status == Component.Ready){
        console.log("1");
        finishCreation();
    }
    else{
        console.log("2");
        component.statusChanged.connect(finishCreation);
}
}

function finishCreation() {
    console.log("finish creation");
    if (component.status == Component.Ready) {
        console.log("3");
        barGauge = component.createObject(mainrectangle, {'title':'TestGauge', 'value':'map', 'orientation':'Qt.Horizontal'});
        if (barGauge == null) {
            // Error Handling
            console.log("4");
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("5");
        console.log("Error loading component:", component.errorString());
    }
}
