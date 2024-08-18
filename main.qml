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

    signal sgnStart()

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
        histogramModel: wordsModel
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
                onClicked: root.sgnStart()
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
