import QtQuick
import QtQuick.Shapes

Rectangle {
    id: root
    property int maxCount: 100
    property int margin: 0

    anchors.leftMargin: margin
    anchors.rightMargin: margin
    anchors.topMargin: margin
    anchors.bottomMargin: margin

    color: "#131e3a"

    Column {
        id: column
        anchors.fill: parent
        padding: 4
        spacing: 6

        Repeater {
            model: words_model

            Item {
                width: parent.width - column.padding - column.padding
                height: (root.height - column.padding) / (words_model.count) - column.spacing

                Item {
                    width: parent.width * (model.count / root.maxCount)
                    height: parent.height



                    Rectangle{
                        width: parent.height
                        height: parent.width
                        anchors.centerIn: parent
                        rotation: 90
                        radius: 2


                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "#0ca9c8"
                        }
                        GradientStop {
                            position: 1.0
                            color: "#1b2d3e"
                        }
                    }
                    }

                    Text {
                        x: 8
                        anchors.verticalCenter: parent.verticalCenter
                        text: index + 1
                        color: "white"
                    }

                    Text {
                        x: 28
                        anchors.verticalCenter: parent.verticalCenter
                        text: model.word
                        color: "white"
                    }

                    Text {
                        anchors.left: parent.right
                        anchors.leftMargin: 6
                        anchors.verticalCenter: parent.verticalCenter
                        text: model.count
                        color: "white"

                    }
                }
            }
        }
    }
}
