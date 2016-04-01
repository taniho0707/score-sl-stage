// main.qml

import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow{
    id: applicationWindow1
    width: 800
    minimumWidth: 640
    height: 600
    minimumHeight: 480
    color: "white"
    title: qsTr("Score Making Tool for IM@S Starlight Stage")
    visible: true

    Rectangle {
        id: rec_file
        x: 0
        width: 140
        color: "#FFFFFF"
        
        Button {
            id: button_new
            x:30; y:40
            width: 120
            text: "New/Open"
            onClicked: ;
        }
        Button {
            id: button_save
            x:30; y:80
            width: 120
            text: "Save"
            onClicked: ;
        }
   }

    Rectangle {
        id: rec_scoreconfig
        x: 0
        width: 140
        color: "#000000"

        Label {
            x: 30; y: 180
            id: label_hand
            font.pixelSize: 18
            text: qsTr("Hand: ")
        }
        Label {
            x: 90; y: 180
            id: label_hand_current
            font.pixelSize: 18
            text: qsTr("")
        }
        Button {
            id: button_lefttouch
            x:30; y:200
            width: 60
            text: "Left"
            onClicked: label_hand_current.text="Left";
        }
        Button {
            id: button_righttouch
            x:100; y:200
            width: 60
            text: "Right"
            onClicked: label_hand_current.text="Right";
        }

        ExclusiveGroup { id: notesGroup }
        RadioButton {
            x: 80; y: 330
            text: "Single"
            checked: true
            exclusiveGroup: notesGroup
        }
        RadioButton {
            x: 80; y: 360
            text: "Long"
            exclusiveGroup: notesGroup
        }
        RadioButton {
            x: 80; y: 390
            text: "LeftFlick"
            exclusiveGroup: notesGroup
        }
        RadioButton {
            x: 80; y: 420
            text: "RightFlick"
            exclusiveGroup: notesGroup
        }
        Image {
            x: 30; y: 330
            source: "img/note1.png"
        }
        Image {
            x: 30; y: 360
            source: "img/note2.png"
        }
        Image {
            x: 30; y: 390
            source: "img/note3.png"
        }
        Image {
            x: 30; y: 420
            source: "img/note4.png"
        }

        Button {
            id: button_prevpage
            x:30; y:500
            width: 60
            text: "-"
            onClicked: label_page_current.text = parseInt(label_page_current.text) - 1;
        }
        Label {
            x: 100; y: 500
            id: label_page_current
            font.pixelSize: 18
            text: qsTr("0")
        }
        Label {
            x: 120; y: 500
            id: label_page_max
            font.pixelSize: 18
            text: qsTr("/10")
        }
        Button {
            id: button_nextpage
            x:150; y:500
            width: 60
            text: "+"
            onClicked: label_page_current.text = 1 + parseInt(label_page_current.text);
        }
    }
}
