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
            count: 39
        }
        ListElement {
            word: "Second word"
            count: 43
        }
        ListElement {
            word: "Third word"
            count: 28
        }
    }

    Rectangle {
        id: chart
        anchors.fill: parent

        color: "red"

        Column {
            anchors.fill: parent
            padding: 4
            spacing: 4

            Repeater {
                model: words_model

                Rectangle {
                    width: parent.width
                    height: parent.height / words_model.count
                    color: "gray"

                    Rectangle {
                        width: parent.width* (model.count/ 43)
                        height: parent.height

                        color: "lightblue"

                        Text {
                            x: 12
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.word
                        }
                    }
                }
            }
        }
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
