import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import Graph 1.0

Window {
    visible: true
    width: 640
    height: 480

    minimumWidth: 580
    minimumHeight: 400
    title: qsTr("Алгоритм Дейкстры")

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.preferredHeight: 480
            Layout.preferredWidth: 425

            Label {
                id: label
                text: qsTr("Матрица смежности")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pointSize: 12
                font.family: "Arial"
            }

            GraphMatrix {
                id: graphMatrix
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 425
                Layout.preferredWidth: 425
            }
        }

        ColumnLayout {
            height: parent.height
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            Layout.preferredHeight: graphMatrix.height
            Layout.fillHeight: true

            ColumnLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignTop
                Layout.preferredHeight: 112
                Layout.preferredWidth: 209

                RowLayout {
                    Layout.fillWidth: true
                    Layout.maximumHeight: 50
                    Layout.minimumHeight: 0
                    Layout.minimumWidth: 0

                    Button {
                        id: addVertex
                        text: qsTr("добавить вершин")
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 54
                        Layout.preferredWidth: 209

                        onClicked: {
                            var r = graphData.appendItem()
                            r = 'A'.charCodeAt(0) + r
                            r = String.fromCharCode(r)

                            var col = Qt.createQmlObject('
                            import QtQuick.Controls 1.4;
                            import QtQuick 2.7;
                            TableViewColumn {
                                title: \"' + r + '\"
                                role: \"' + r + '\";
                                width: 40;

                                delegate: TextEdit {
                                    text: model.' + r + ';
                                    onEditingFinished: {
                                        if (!isNaN(text))
                                            model.' + r + ' = Number(text);
                                        else
                                            text = "-";
                                    }
                                }
                            }', graphMatrix, "GraphMatrix.qml");


                            graphMatrix.addColumn(col)
                            graphMatrix.model = Qt.createQmlObject('
                            import Graph 1.0;

                            GraphModel {
                                    matrix: graphData
                            }', graphMatrix, "GraphMatrix.qml");
                        }
                    }

                    TextField {
                        id: addVertexCount
                        text: "1"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 54
                        Layout.preferredWidth: 88
                        placeholderText: qsTr("Text Field")
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.maximumHeight: 50

                    Button {
                        id: removeVertex
                        text: qsTr("убрать вершин")
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 54
                        Layout.preferredWidth: 209

                        onClicked: {
                            graphData.removeItem()
                            graphMatrix.removeColumn(graphMatrix.columnCount - 1)
                        }
                    }

                    TextField {
                        id: removeVertexCount
                        text: "1"
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 54
                        Layout.preferredWidth: 88
                        placeholderText: qsTr("Text Field")
                    }
                }
            }

            Button {
                id: done
                text: qsTr("готово")
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                Layout.fillWidth: true
                Layout.preferredHeight: 54
                Layout.preferredWidth: 209
            }
        }
    }


}
