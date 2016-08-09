import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.4


TableView {

    anchors.fill: parent
    alternatingRowColors: true

   // selection :  tableview.selection.select(1, 3)    // select row indexes 1, 2 and 3
    //currentRow : 5
   // selectionMode : SelectionMode.ExtendedSelection

   TableViewColumn {
     title: "Base"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N01"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N02"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N03"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N04"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N05"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N06"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N07"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N08"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N09"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N10"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N11"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N12"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N13"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N14"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N15"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N16"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N17"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N18"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N19"
     width: Math.round(parent.width / 21)
   }
   TableViewColumn {
     title: "N20"
     width: Math.round(parent.width / 21)
   }
   style: TableViewStyle
   {
         backgroundColor: "black"
         alternateBackgroundColor: "grey"
         textColor : "white"
         headerDelegate: Rectangle {
                         height: parent.width
                         width: parent.height
                         color: "black"
                         Text {
                             id: textItem
                             anchors.fill: parent
                             //verticalAlignment: Text.AlignVCenter
                            // horizontalAlignment: styleData.textAlignment
                           //  anchors.leftMargin: 12
                             text: styleData.value
                             font.pixelSize: parent.width / 2.2
                             font.bold: true
                             //elide: Text.ElideRight
                             color: "white"
                             renderType: Text.NativeRendering
                         }
                         Rectangle {
                             anchors.right: parent.right
                             anchors.top: parent.top
                             anchors.bottom: parent.bottom
                             anchors.bottomMargin: 1
                             anchors.topMargin: 1
                             width: 1
                             color: "#ccc"

   }

   }
}
}

