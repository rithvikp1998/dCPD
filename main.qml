import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4         /* For ComboBox, Button */
import QtQuick.Controls.Styles 1.4  /* For ComboBox */
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 800
    height: 540
    //title: "Print Dialog"

    Text {
        id: printer_text
        text: qsTr("Printer : ")
        x: 40
        y: 40
        font.pointSize: 12
    }

    ComboBox {
        id: printers_list
        x: 120
        y: 40
        width: 200
        height: 24
        model: ["Printer 1", "Printer 2", "Printer 3"]
    }

    Text {
        id: presets_text
        text: qsTr("Presets : ")
        x: 40
        y: 80
        font.pointSize: 12
    }

    ComboBox {
        id: presets_list
        x: 120
        y: 80
        width: 200
        height: 24
        model: ["Preset 1", "Preset 2", "Preset 3"]
    }

    Text {
        id: copies_text
        text: qsTr("Copies : ")
        x: 40
        y: 120
        font.pointSize: 12
    }

    TextField {
        id: copies_field
        property int copies: 1
        text: copies
        x: 120
        y: 120
        width: 80
        height: 24

        onTextChanged: {
            if(copies_field.text != '')
                copies = copies_field.text
            else
                copies = 0
        }
    }

    Button {
        id: copies_increment
        text: "+"
        width: 24
        height: 24
        x: 120 + 80
        y: 120

        onClicked: increment()

        function increment() {
            copies_field.copies += 1
        }
    }

    Button {
        id: copies_decrement
        text: "-"
        width: 24
        height: 24
        x: 120 + 80 + 24
        y: 120

        onClicked: decrement()

        function decrement(){
            if(copies_field.copies > 1)
                copies_field.copies -= 1
        }
    }

    CheckBox {
        x: 120 + 80 + 24 + 24 + 20
        y: 120
        text: qsTr("Collated")
    }

    Text {
        id: page_range_text
        text: "Pages : "
        font.pointSize: 12
        x: 40
        y: 180
    }

    ColumnLayout {
        ExclusiveGroup { id: page_range_group }
        x: 120
        y: 170

        RadioButton {
            id: all_pages_button
            text: "All Pages"
            checked: true
            exclusiveGroup: page_range_group
        }


        RadioButton {
            id: range_pages_button
            text: "Range"
            exclusiveGroup: page_range_group
        }
    }

    TextField {
        id: range_left
        property int value: 1
        text: value
        x: 200
        y: 195
        width: 50
        height: 24
        font.pointSize: 12

        onTextChanged: {
            if(range_left.text != '')
                value = range_left.text
            else
                value = 1
        }
    }

    Text {
        x: 260
        y: 195
        text: qsTr(" - ")
        font.pointSize: 12
    }

    TextField {
        id: range_right
        property int value: 1
        text: value
        x: 280
        y: 195
        width: 50
        height: 24
        font.pointSize: 12

        onTextChanged: {
            if(range_right.text != '')
                value = range_right.text
            else
                value = 1
        }
    }

    Text {
        id: paper_text
        text: qsTr("Paper Size : ")
        x: 40
        y: 240
        font.pointSize: 12
    }

    ComboBox {
        id: papers_list
        x: 140
        y: 240
        width: 200
        height: 24
        model: ["A4", "A3", "Legal", "Letter"]
    }

    Text {
        x: 40
        y: 280
        id: orientation_text
        text: qsTr("Orientation : ")
    }

    RowLayout {
        ExclusiveGroup { id: orientation_group }
        x: 140
        y: 280

        RadioButton {
            id: landscape_button
            text: "Landscape"
            checked: true
            exclusiveGroup: orientation_group
        }


        RadioButton {
            id: potrait_button
            text: "Potrait"
            exclusiveGroup: orientation_group
        }
    }

    Text {
        id: application_text
        text: qsTr("Application : ")
        x: 40
        y: 320
        font.pointSize: 12
    }

    ComboBox {
        id: applications_list
        x: 140
        y: 320
        width: 200
        height: 24
        model: ["Firefox", "LibreOffice", "Photo Viewer"]
    }

    Text {
        id: info
        text: qsTr("This menu depends on the application you are printing from")
        x: 40
        y: 360
        font.pointSize: 10
    }

    Image {
        id: preview
        x: 480
        y: 80
        width: 200
        height: 280
        source: "Images/preview.png"
    }

    /*Text {
        id: temp
        text: qsTr(pdfpreviewdata.test)
        x: 400
        y: 40
        font.pointSize: 12
    }*/
}
