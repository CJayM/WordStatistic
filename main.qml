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

    Rectangle {
        id: chart
        anchors.fill: parent

        color: "red"
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
