//Creates instances of Maingauge, usable at runtime

var component;
var gauge;

function createMainGauges(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec,Setwarnvaluehigh,Setwarnvaluelow,Setframeclolor,Setbackroundcolor,Settitlecolor,Settitletextcolor,Settextcolor,Setbarcolor,SetTitlefontsize,SetMainfontsize) {
    component = Qt.createComponent("SquareGaugeMain.qml");
    if (component.status === Component.Ready){
        console.log("component ready");
        finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec,Setwarnvaluehigh,Setwarnvaluelow,Setframeclolor,Setbackroundcolor,Settitlecolor,Settitletextcolor,Settextcolor,Setbarcolor,SetTitlefontsize,SetMainfontsize);
    }
    else {
        component.statusChanged.connect(finishCreation);
        console.log("component not ready!");
    }
}

function finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec,Setwarnvaluehigh,Setwarnvaluelow,Setframeclolor,Setbackroundcolor,Settitlecolor,Settitletextcolor,Settextcolor,Setbarcolor,SetTitlefontsize,SetMainfontsize) {
    if (component.status === Component.Ready) {
        gauge = component.createObject(userDash, {"id": setID, "title":setID, "width": setWidth, "height": setHeight,
                                           "mainvalue": Qt.binding(function(){return SetValueObject[SetValuePropertyMain].toFixed(setDecPlace)}),
                                           "secvalue": Qt.binding(function(){return SetValueObject[SetValuePropertySec].toFixed(setDecPlace)}),
                                           "maxvalue": setMaxValue,
                                           "warnvaluehigh": Setwarnvaluehigh,
                                           "warnvaluelow":Setwarnvaluelow,
                                           "mainunit": setUnit,
                                           "titlecolor":Settitlecolor,
                                           "resettitlecolor":Settitlecolor,
                                           "framecolor":Setframeclolor,
                                           "resetbackroundcolor":Setbackroundcolor,
                                           "textcolor":Settextcolor,
                                           "titletextcolor":Settitletextcolor,
                                           "barcolor":Setbarcolor,
                                           "titlefontsize":SetTitlefontsize,
                                           "mainfontsize":SetMainfontsize,
                                           "vertgaugevisible": setVertGaugeVis,
                                           "horigaugevisible": setHoriGaugeVis,
                                           "secvaluevisible": setSecValueVis,
                                           "x": setX, "y": setY});
        if (gauge == null) {
            // Error Handling
            console.log("Error creating object");
        }

    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
