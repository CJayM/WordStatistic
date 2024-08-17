import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Word Statistics")

    ListModel {
        id: words_model

        ListElement {
            word: "First word"
            count: 88
        }
        ListElement {
            word: "Second word"
            count: 76
        }
        ListElement {
            word: "Third word"
            count: 63
        }
        ListElement {
            word: "Fourth word"
            count: 62
        }
        ListElement {
            word: "Fifth word"
            count: 58
        }
        ListElement {
            word: "Sixth word"
            count: 55
        }
        ListElement {
            word: "Seventh word"
            count: 43
        }
        ListElement {
            word: "Eighth word"
            count: 40
        }
        ListElement {
            word: "Ninth word"
            count: 38
        }
        ListElement {
            word: "Tenth word"
            count: 36
        }
        ListElement {
            word: "Eleventh word"
            count: 34
        }
        ListElement {
            word: "Twelfth word"
            count: 22
        }
        ListElement {
            word: "Thirteenth word"
            count: 19
        }
        ListElement {
            word: "Fourteenth word"
            count: 13
        }
        ListElement {
            word: "Fifteenth word"
            count: 9
        }
    }

    header: Item {
        width: root.width
        height: 22

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 4
            font.pointSize: 18
            text: "Статистика слов в файле"
            color: "white"
        }
    }

    background: Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#293863"
            }
            GradientStop {
                position: 1.0
                color: "#212e51"
            }
        }
    }

    Histogram {
        id: chart
        margin: 12
        anchors.fill: parent
    }

    FileDialog {
        id: fileOpenDialog
        fileMode: FileDialog.OpenFile
        options: FileDialog.ReadOnly
        nameFilters: ["Text files (*.txt)", "Markdown files (*.md)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            text_path.text = fileOpenDialog.currentFile
        }
    }

    footer: ToolBar {
        id: footer
        visible: true

        Flow {
            anchors.fill: parent

            Text {
                id: text_path
                text: qsTr("Opened document")
            }
            ToolButton {
                text: qsTr("Open")
                icon.name: "document-open"
                onClicked: fileOpenDialog.open()
            }
            ToolButton {
                text: qsTr("Start")
                icon.name: "media-playback-start"
            }
            ToolButton {
                text: qsTr("Pause")
                icon.name: "media-playback-pause"
            }
            ToolButton {
                text: qsTr("Stop")
                icon.name: "media-playback-stop"
            }
        }
    }
}
