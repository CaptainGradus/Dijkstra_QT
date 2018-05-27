import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick 2.7

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

                onClicked: {
                    graph.resetSolutions()
                    signalExit()
                }
            }

            ColumnLayout {
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom

                ListView {
                    id: listView
                    x: 0
                    y: 0
                    width: 110
                    height: 160
                    Layout.fillWidth: true
                    Layout.fillHeight: false
                    Layout.minimumHeight: 250

                    delegate: Item {
                        x: 5
                        width: 80
                        height: 40
                        Row {
                            id: row

                            Text {
                                text: modelData
                                font.pointSize: 10
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            spacing: 10
                        }
                    }
                }

                Button {
                    text: "нарисовать"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 46
                    Layout.preferredWidth: 105

                    onClicked: {
                        if (textFieldTo.text.trim() === "") {
                            graph.draw(textFieldFrom.text.charCodeAt(0) - 'A'.charCodeAt(0))

                            listView.model = graph.getWeights(textFieldFrom.text.charCodeAt(0) - 'A'.charCodeAt(0))
                        }
                        else {
                            graph.draw(textFieldFrom.text.charCodeAt(0) - 'A'.charCodeAt(0),
                                       textFieldTo.text.charCodeAt(0) - 'A'.charCodeAt(0))

                            listView.model = graph.getWeights(textFieldFrom.text.charCodeAt(0) - 'A'.charCodeAt(0),
                                                              textFieldTo.text.charCodeAt(0) - 'A'.charCodeAt(0))

                        }
                        image.source = ""
                        image.source = "file://" + graph.filePath()
                    }
                }

                TextField {
                    id: textFieldFrom
                    text: "A"
                    placeholderText: "from"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 37
                    Layout.preferredWidth: 105
                }
                TextField {
                    id: textFieldTo
                    placeholderText: "to"
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
                autoTransform: true
                cache: false
                sourceSize.width: parent.width
                anchors.fill: parent
                sourceSize.height: parent.height
            }
        }
    }
}
