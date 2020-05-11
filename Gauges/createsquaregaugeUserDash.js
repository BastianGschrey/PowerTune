//Creates instances of SquaregaugeRaceDash, usable at runtime

var component;
var gauge;

function createSquareGauge(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec,Setwarnvaluehigh,Setwarnvaluelow,Setframeclolor,Setbackroundcolor,Settitlecolor,Settitletextcolor,Settextcolor,Setbarcolor,SetTitlefontsize,SetMainfontsize,setDecPlace2,setTextfont,setValuefont) {
    component = Qt.createComponent("Squaregauge.qml");
    if (component.status === Component.Ready){
       // console.log("component ready");
        finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec,Setwarnvaluehigh,Setwarnvaluelow,Setframeclolor,Setbackroundcolor,Settitlecolor,Settitletextcolor,Settextcolor,Setbarcolor,SetTitlefontsize,SetMainfontsize,setDecPlace2,setTextfont,setValuefont);
     //console.log("setting 1 decimal"+ setDecPlace);
     //console.log("setting 2 decimal"+ setDecPlace2);

    }
    else {
        component.statusChanged.connect(finishCreation);
        console.log("component not ready!");
    }
}

function finishCreation(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec,Setwarnvaluehigh,Setwarnvaluelow,Setframeclolor,Setbackroundcolor,Settitlecolor,Settitletextcolor,Settextcolor,Setbarcolor,SetTitlefontsize,SetMainfontsize,setDecPlace2,setTextfont,setValuefont) {
    if (component.status === Component.Ready) {
        gauge = component.createObject(userDash, {"id": setID, "title":setID, "width": setWidth, "height": setHeight,
                                           //"mainvalue": Qt.binding(function(){return Dashboard[SetValuePropertyMain].toFixed(setDecPlace)}),
                                           //"secvalue": Qt.binding(function(){return Dashboard[SetValuePropertySec].toFixed(setDecPlace)}),
                                           "mainvalue": Qt.binding(function(){return Dashboard[SetValuePropertyMain]}),
                                           "secvalue": Qt.binding(function(){return Dashboard[SetValuePropertySec]}),
                                           "decimalpoints":setDecPlace,
                                           "decimalpoints2":setDecPlace2,
                                           "mainvaluename":SetValuePropertyMain,
                                           "secvaluename":SetValuePropertySec,
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
                                           "x": setX, "y": setY,
                                           "textFonttype": setTextfont,
                                           "valueFonttype": setValuefont});
        if (gauge === null) {
            // Error Handling
            console.log("Error creating object");
        }

    } else if (component.status === Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
