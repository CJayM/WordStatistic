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

    property bool isFirstReseted: true  // хак для переназначения модели
    property real proccessProgress: 0;
    property alias state: windowState.state

    signal sgnStart(string filePath)
    signal sgnReset()
    signal sgnPause()

    property string filePath: ""
    property string filename: ""
    required property var wordsModel    

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
        property alias fliePath: root.filePath
        property alias flieName: root.filename
    }

    header: Item {
        width: root.width
        height: 22

        Text {
            id: headerText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 4
            font.pointSize: 18
            text: "Статистика слов в файле: " + root.filename
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
            var selectedPath = fileOpenDialog.currentFile
            if (selectedPath === root.filePath)
                return

            root.sgnReset()
            root.filePath = selectedPath
            var parts = root.filePath.split("/")
            if (parts.length > 0)
                root.filename = parts[parts.length - 1];
        }
    }

    footer: ToolBar {
        id: footer
        visible: true        

        Item{
            anchors.fill: parent

            RowLayout{
                anchors.fill: parent
                spacing: 4

                Item{
                    height: 18
                    Layout.fillWidth: true

                    Rectangle{
                        id: progressBar
                        height: parent.height
                        width: parent.width * root.proccessProgress

                        color: "green"
                    }

                    Text {
                        id: txtFilepath
                        x: 18
                        color: "white"
                        text: root.filePath
                    }
                }

                ToolButton {
                    id: btnOpen
                    ToolTip.text: "Указать файл, статистику которого следует рассчитывать"
                    icon.name: "folder-open"

                    onClicked: fileOpenDialog.open()
                }
                ToolSeparator{}

                CheckBox{
                    checked: true
                    text: "Замедлять загрузку"
                    ToolTip.text: "Искусственно замедлять загрузку для просмотра изменения прогрессбара"
                }

                CheckBox{
                    checked: true
                    text: "Случайно"
                    ToolTip.text: "Отображать случайные слова вместо популярных"
                }



                ToolSeparator{}
                ToolButton {
                    id: btnStart
                    ToolTip.text: qsTr("Start")
                    icon.name: "media-playback-start"
                    Layout.alignment: Qt.AlignRight

                    onClicked: root.sgnStart(root.filePath)
                }
                ToolButton {
                    id: btnPause
                    ToolTip.text: qsTr("Pause")
                    icon.name: "media-playback-pause"
                    Layout.alignment: Qt.AlignRight

                    onClicked: root.sgnPause()
                }
                ToolButton {
                    id: btnStop
                    ToolTip.text: qsTr("Stop")
                    icon.name: "media-playback-stop"
                    Layout.alignment: Qt.AlignRight

                    onClicked: resetState()
                }
            }
        }
    }

    Connections {
        target: wordsModel
        function onDataChanged(){ console.log("Data in the model has been changed");}
        function onModelReset(){
            if (isFirstReseted){
                console.log("First reseted");
                isFirstReseted = false; // не понимаю, почему repeater не отображает изменение модели при первом сбросе
                chart.histogramModel = [];
                chart.histogramModel = wordsModel;
            }
        }
    }

    StateGroup {
        id: windowState
        state: "NORMAL"
        states: [State {
            name: "NORMAL"
            PropertyChanges {target: progressBar; visible: false;}
            PropertyChanges {target: btnStart; visible: true;}
            PropertyChanges {target: btnStop; enabled: false;}
            PropertyChanges {target: btnPause; visible: false;}
        },
        State {
            name: "LOADING"
            PropertyChanges {target: progressBar; visible: true;}
            PropertyChanges {target: btnStart; visible: false;}
            PropertyChanges {target: btnStop; enabled: false;}
            PropertyChanges {target: btnPause; visible: true;}
        },
        State {
            name: "PAUSED"
            PropertyChanges {target: progressBar; visible: true;}
            PropertyChanges {target: btnStop; enabled: true;}
            PropertyChanges {target: btnStart; visible: true;}
            PropertyChanges {target: btnPause; visible: false;}
        }
    ]}

    function resetState(){
        root.sgnReset();
    }
}
