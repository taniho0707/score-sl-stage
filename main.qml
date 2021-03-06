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
            button_filename.text = score_drawing.getFilename();
            label_page_max.text = ''+score_drawing.getMaxpage();
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

        Label {
            id: button_filename
            x:30; y:30
            width: 140
            text: ""
        }
        
        Button {
            id: button_new
            x:30; y:60
            width: 120
            text: "New/Open"
            onClicked: fileDialog.visible = true;
        }
        Button {
            id: button_save
            x:30; y:90
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
                currenthand = 1;
                label_hand_current.text="Right";
            }
        }

        ExclusiveGroup { id: notesGroup }
        RadioButton {
            x: 80; y: 235
            text: "Single"
            checked: true
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 0; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 265
            text: "Long Start"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 1; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 295
            text: "Long End"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 2; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 325
            text: "LeftFlick Continue"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 5; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 355
            text: "LeftFlick End"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 6; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 385
            text: "RightFlick Continue"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 3; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 415
            text: "RightFlick End"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 4; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 445
            text: "Slide Continue"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 7; score_drawing.setType(currentnote); }
        }
        RadioButton {
            x: 80; y: 475
            text: "Slide End"
            exclusiveGroup: notesGroup
            onClicked: { currentnote = 8; score_drawing.setType(currentnote); }
        }
        Image {
            x: 40; y: 230
            source: "img/note1.png"
        }
        Image {
            x: 40; y: 260
            source: "img/note2.png"
        }
        Image {
            x: 40; y: 290
            source: "img/note3.png"
        }
        Image {
            x: 40; y: 320
            source: "img/note4.png"
        }
        Image {
            x: 40; y: 350
            source: "img/note5.png"
        }
        Image {
            x: 40; y: 380
            source: "img/note6.png"
        }
        Image {
            x: 40; y: 410
            source: "img/note7.png"
        }
        Image {
            x: 40; y: 440
            source: "img/note8.png"
        }
        Image {
            x: 40; y: 470
            source: "img/note9.png"
        }

        Button {
            id: button_prevpage
            x:30; y:560
            width: 40
            text: "-"
            onClicked: {
                if(parseInt(label_page_current.text) > 1){
                    label_page_current.text = parseInt(label_page_current.text) - 1;
                    label_page_max.text = ''+score_drawing.getMaxpage();
                    score_drawing.changePage(parseInt(label_page_current.text));
                    score_drawing.update();
                }
            }
        }
        Label {
            x: 80; y: 560
            id: label_page_current
            font.pixelSize: 18
            text: qsTr("1")
        }
        Label {
            x: 110; y: 560
            id: label_page_slash
            font.pixelSize: 18
            text: qsTr("/")
        }
        Label {
            x: 120; y: 560
            id: label_page_max
            font.pixelSize: 18
            text: qsTr("30")
        }
        Button {
            id: button_nextpage
            x:170; y:560
            width: 40
            text: "+"
            onClicked: {
                if(parseInt(label_page_current.text) < score_drawing.getMaxpage()){
                    label_page_current.text = 1 + parseInt(label_page_current.text);
                    label_page_max.text = ''+score_drawing.getMaxpage();
                    score_drawing.changePage(parseInt(label_page_current.text));
                    score_drawing.update();
                }
            }
        }

        Button {
            id: button_prevmax
            x:30; y:590
            width: 40
            text: "-"
            onClicked: {
                if(score_drawing.getMaxpage() > 1){
                    score_drawing.setMaxpage(score_drawing.getMaxpage() - 1);
                    label_page_max.text = ''+score_drawing.getMaxpage();
                }
            }
        }
        Button {
            id: button_nextmax
            x:170; y:590
            width: 40
            text: "+"
            onClicked: {
                score_drawing.setMaxpage(score_drawing.getMaxpage() + 1);
                label_page_max.text = ''+score_drawing.getMaxpage();
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
