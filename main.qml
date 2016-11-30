// main.qml

import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.1
import ScoreDrawing 1.0


ApplicationWindow{
    id: applicationWindow1
    width: 800
    minimumWidth: 640
    height: 600
    minimumHeight: 480
    color: "white"
    title: qsTr("Score Making Tool for IM@S Starlight Stage")
    visible: true
    property int currentnote: 0
    property int currenthand: 0
    property int currentdenom: 4

    property int maxpage: 10
    property string filename: ''

    FileDialog {
        id: fileDialog
        visible: false
        modality: Qt.WindowModal //: Qt.NonModal
        title: "Choose or Create a file"
        selectExisting: false
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "Score files (*.score)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: true
        onAccepted: {
            filename = fileDialog.fileUrl
            console.log("File loading " + filename);
            score_drawing.setFilename(filename);
            fileDialog.visible = false;
        }
        onRejected: {
            console.log("Rejected");
            fileDialog.visible = false;
        }
    }
    
    Rectangle {
        id: rec_file
        x: 0
        width: 140
        color: "white"
        
        Button {
            id: button_new
            x:30; y:40
            width: 120
            text: "New/Open"
            onClicked: fileDialog.visible = true;
        }
        Button {
            id: button_save
            x:30; y:80
            width: 120
            text: "Save"
            onClicked: {
                score_drawing.save();
            }
        }
    }
    
    Rectangle {
        id: rec_denominator
        x: 0
        width: 140
        color: "white"

        Button {
            id: button_denom_m
            x: 30; y: 140;
            width: 40
            text: "-"
            onClicked: {
                if(currentdenom == 4){
                    currentdenom = 3;
                    label_denom.text = "3連符"
                } else if(currentdenom == 8){
                    currentdenom = 4;
                    label_denom.text = "4分音符"
                } else if(currentdenom == 16){
                    currentdenom = 8;
                    label_denom.text = "8分音符"
                } else if(currentdenom == 32){
                    currentdenom = 16;
                    label_denom.text = "16分音符"
                } else if(currentdenom == 64){
                    currentdenom = 32;
                    label_denom.text = "32分音符"
                }
                score_drawing.setDenom(currentdenom);
            }
        }
        Button {
            id: button_denom_p
            x: 80; y: 140;
            width: 40
            text: "+"
            onClicked: {
                if(currentdenom == 4){
                    currentdenom = 8;
                    label_denom.text = "8分音符"
                } else if(currentdenom == 8){
                    currentdenom = 16;
                    label_denom.text = "16分音符"
                } else if(currentdenom == 16){
                    currentdenom = 32;
                    label_denom.text = "32分音符"
                } else if(currentdenom == 32){
                    currentdenom = 64;
                    label_denom.text = "64分音符"
                } else if(currentdenom == 3){
                    currentdenom = 4;
                    label_denom.text = "4分音符"
                }
                score_drawing.setDenom(currentdenom);
            }
        }
        Label {
            id: label_denom
            x: 130; y: 140;
            font.pixelSize: 18
            text: qsTr("4分音符");
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
            text: qsTr("Left")
        }
        Button {
            id: button_lefttouch
            x:30; y:200
            width: 60
            text: "Left"
            onClicked: {
                currenthand = 0;
                label_hand_current.text="Left";
            }
        }
        Button {
            id: button_righttouch
            x:100; y:200
            width: 60
            text: "Right"
            onClicked: {
                currenthand = 0;
                label_hand_current.text="Right";
            }
        }

        ExclusiveGroup { id: notesGroup }
        RadioButton {
            x: 80; y: 230
            text: "Single"
            checked: true
            exclusiveGroup: notesGroup
            onClicked: currentnote = 0;
        }
        RadioButton {
            x: 80; y: 260
            text: "Long Start"
            exclusiveGroup: notesGroup
            onClicked: currentnote = 1;
        }
        RadioButton {
            x: 80; y: 290
            text: "Long End"
            exclusiveGroup: notesGroup
            onClicked: currentnote = 2;
        }
        RadioButton {
            x: 80; y: 320
            text: "LeftFlick Continue"
            exclusiveGroup: notesGroup
            onClicked: currentnote = 5;
        }
        RadioButton {
            x: 80; y: 350
            text: "LeftFlick End"
            exclusiveGroup: notesGroup
            onClicked: currentnote = 6;
        }
        RadioButton {
            x: 80; y: 380
            text: "RightFlick Continue"
            exclusiveGroup: notesGroup
            onClicked: currentnote = 3;
        }
        RadioButton {
            x: 80; y: 410
            text: "RightFlick End"
            exclusiveGroup: notesGroup
            onClicked: currentnote = 4;
        }
        Image {
            x: 30; y: 230
            source: "img/note1.png"
        }
        Image {
            x: 30; y: 260
            source: "img/note2.png"
        }
        Image {
            x: 30; y: 320
            source: "img/note3.png"
        }
        Image {
            x: 30; y: 380
            source: "img/note4.png"
        }

        Button {
            id: button_prevpage
            x:30; y:500
            width: 40
            text: "-"
            onClicked: {
                if(parseInt(label_page_current.text) > 1){
                    label_page_current.text = parseInt(label_page_current.text) - 1;
                    score_drawing.changePage(parseInt(label_page_current.text));
                    score_drawing.update();
                }
            }
        }
        Label {
            x: 80; y: 500
            id: label_page_current
            font.pixelSize: 18
            text: qsTr("1")
        }
        Label {
            x: 110; y: 500
            id: label_page_max
            font.pixelSize: 18
            text: qsTr("/10")
        }
        Button {
            id: button_nextpage
            x:150; y:500
            width: 40
            text: "+"
            onClicked: {
                label_page_current.text = 1 + parseInt(label_page_current.text);
                score_drawing.changePage(parseInt(label_page_current.text));
                score_drawing.update();
            }
        }
    }

    Rectangle {
        id: rec_score
        x: 250
        y: 50
        width: 300
        height: 500
        color: "white"
        border.color: "black"
        border.width: 2

        MouseArea {
            id: mouse_score
            x: 0
            y: 0
            width: 300
            height: 500
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPositionChanged: {
                score_drawing.setMouse(mouseX, mouseY);
                score_drawing.update();
            }
            onPressed: {
                score_drawing.setMouse(mouseX, mouseY);
                switch(pressedButtons){
                case Qt.LeftButton:
                    score_drawing.setNote(currentnote, currenthand);
                    break;
                case Qt.RightButton:
                    score_drawing.removeNote();
                    break;
                default:
                    rec_score.border.color = "red";
                    break;
                }
                score_drawing.update();
            }
        }
        ScoreDrawing {
            id: score_drawing
            x: 0
            y: 0
            width: 300
            height: 500
            
        }
    }
}
