
var component;
var gauge;

function createPicture(setX,setY,setpictureheight,setPictureSource) {
    component = Qt.createComponent("Picture.qml");
    if (component.status === Component.Ready){
        //console.log("Pictre ready");
        finishCreation(setX,setY,setpictureheight,setPictureSource);
    }
     else
        //console.log("creating Pic")
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setX,setY,setpictureheight,setPictureSource) {
    if (component.status === Component.Ready) {
        gauge = component.createObject(userDash, {
                                           "x": setX,
                                           "y": setY,
                                           "pictureheight":setpictureheight,
                                           "picturesource" :setPictureSource
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
