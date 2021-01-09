var component;
var gauge;
function createPicture(setX,setY,setpictureheight,setValuePropertyMain,settriggervalue,setstatepicturesourceoff,setstatepicturesourceon) {
    component = Qt.createComponent("StateGIF.qml");
    if (component.status === Component.Ready){
        //console.log("creating State Pic")
        //console.log("Create trigger:",settriggervalue);
        finishCreation(setX,setY,setpictureheight,setValuePropertyMain,settriggervalue,setstatepicturesourceoff,setstatepicturesourceon);
    }
     else

        component.statusChanged.connect(finishCreation);
}

function finishCreation(setX,setY,setpictureheight,setValuePropertyMain,settriggervalue,setstatepicturesourceoff,setstatepicturesourceon) {
    if (component.status === Component.Ready) {
        gauge = component.createObject(userDash, {

                                           "x": setX,
                                           "y": setY,
                                           "pictureheight":setpictureheight,
                                           "mainvaluename":setValuePropertyMain,
                                           "triggervalue":settriggervalue,
                                           "statepicturesourceoff":setstatepicturesourceoff,
                                           "statepicturesourceon":setstatepicturesourceon

                                       });

        if (gauge === null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status === Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
