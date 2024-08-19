import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import QtCore

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Word Statistics")

    signal sgnStart(string filePath)
    signal sgnReset()

    property string filePath: ""
    required property var wordsModel

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
        property alias fliePath: root.filePath
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
        histogramModel: wordsModel
    }

    FileDialog {
        id: fileOpenDialog
        fileMode: FileDialog.OpenFile
        options: FileDialog.ReadOnly
        nameFilters: ["Text files (*.txt)", "Markdown files (*.md)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            root.filePath = fileOpenDialog.currentFile;
        }
    }

    footer: ToolBar {
        id: footer
        visible: true

        Flow {
            anchors.fill: parent

            Text {
                id: txtFilepath
                text: root.filePath
            }
            ToolButton {
                text: qsTr("Open")
                icon.name: "document-open"
                onClicked: fileOpenDialog.open()
            }
            ToolButton {
                text: qsTr("Start")
                icon.name: "media-playback-start"
                onClicked: root.sgnStart(root.filePath)
            }
            ToolButton {
                text: qsTr("Pause")
                icon.name: "media-playback-pause"
            }
            ToolButton {
                text: qsTr("Stop")
                icon.name: "media-playback-stop"
                onClicked: resetState()
            }
        }
    }

    function resetState(){
        console.log("State reset to default");
        root.filePath = "";
        root.sgnReset();
    }
}
