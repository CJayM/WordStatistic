import QtQuick
import QtQuick.Layouts

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Word Statistics")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: chart
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "red"
        }
        Rectangle {
            id: bottom_panel
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            color: "green"
        }
    }
}
