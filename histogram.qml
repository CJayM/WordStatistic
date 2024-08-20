import QtQuick
import QtQuick.Shapes

Rectangle {
    id: root
    property var histogramModel    
    property int margin: 0    
    property int maxCount: 0

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
            model: histogramModel

            delegate:Item {
                id: chartColumn

                width: parent.width - column.padding - column.padding
                height: (root.height - column.padding) / (15) - column.spacing

                Item {
                    width: (parent.width-margin*2) * (Count/maxCount)
                    height: parent.height

                    Item{
                        id: chartRect
                        width: parent.width -18
                        height: parent.height
                        x: 18

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
                            id: lblName
                            x: 12
                            anchors.verticalCenter: parent.verticalCenter
                            text: Name
                            color: "white"
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: lblName.width > chartRect.width ? lblName.right : chartRect.right
                            anchors.rightMargin: -14
                            text:  Count
                            color: "white"
                        }
                    }

                    Text {
                        x: 0
                        anchors.verticalCenter: parent.verticalCenter
                        text: index + 1
                        color: "white"
                    }


                }
            }
        }
    }
}
