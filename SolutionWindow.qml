import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import Graph 1.0

Window {
    id: solutionWindow
    width: 640
    height: 480
    signal signalExit

    minimumWidth: 580
    minimumHeight: 400
    title: qsTr("Алгоритм Дейкстры")

    Graph {
        id: graph
        matrix: graphData
        file: svgFile
    }

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.maximumWidth: 150
            Layout.preferredHeight: parent.height

            Button {
                text: "назад"
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: true
                Layout.preferredHeight: 46
                Layout.preferredWidth: 105

                onClicked: signalExit()
            }

            ColumnLayout {
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom 

                Button {
                    text: "нарисовать"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 46
                    Layout.preferredWidth: 105

                    onClicked: {
                        graph.draw(textField.text)
                        image.update()
                    }
                }

                SpinBox {
                    id: textField
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.preferredHeight: 37
                    Layout.preferredWidth: 105
                }
            }
        }

        Frame {
            id: frame
            padding: 0
            rightPadding: 0
            bottomPadding: 0
            leftPadding: 0
            topPadding: 0
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            Layout.preferredWidth: 200

            Image {
                id: image
                sourceSize.width: parent.width
                anchors.fill: parent
                sourceSize.height: parent.height
                source: graph.filePath()
            }
        }
    }


}
