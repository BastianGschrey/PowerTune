
var component;
var gauge;


function createText(setX,setY,setdisplaytext,setfonttype,setfontsize,settextcolor,setdatasourcename,setfontbold,setdecimalpoints,setWarnvaluehigh,setwarnvaluelow) {
    component = Qt.createComponent("MyTextLabel.qml");
    if (component.status === Component.Ready){
       // console.log("text component ready");
        finishCreation(setX,setY,setdisplaytext,setfonttype,setfontsize,settextcolor,setdatasourcename,setfontbold,setdecimalpoints,setWarnvaluehigh,setwarnvaluelow);
    }
     else
        component.statusChanged.connect(finishCreation);
}

function finishCreation(setX,setY,setdisplaytext,setfonttype,setfontsize,settextcolor,setdatasourcename,setfontbold,setdecimalpoints,setWarnvaluehigh,setwarnvaluelow) {
    if (component.status === Component.Ready) {
        gauge = component.createObject(userDash, {
                                           "x" :setX,
                                           "y" :setY,
                                           "displaytext" :setdisplaytext,
                                           "fonttype" :setfonttype,
                                           "fontsize" : setfontsize,
                                           "textcolor" :settextcolor,
                                           "resettextcolor" :settextcolor,
                                           "datasourcename": setdatasourcename,
                                           "fontbold" :setfontbold,
                                           "decimalpoints" :setdecimalpoints,
                                           "warnvaluehigh" :setWarnvaluehigh,
                                           "warnvaluelow" :setwarnvaluelow
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
