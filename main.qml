import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Алгоритм Дейкстры")

    TableView {
        id: tableView
        x: 167
        y: 119
        width: 442
        height: 223
        backgroundVisible: true
        alternatingRowColors: true

        TableViewColumn {
            role: "data"
            title: "0"
        }

        TableViewColumn {
            role: "data"
            title: "0"
        }

        TableViewColumn {
            role: "data"
            title: "0"
        }

        model: ListModel {
            ListElement {
                data: Data
            }

            ListElement {
                data: Data
            }

            ListElement {
                data: Data
            }
        }
    }

    Button {
        id: button
        x: 418
        y: 402
        width: 201
        height: 59
        text: qsTr("Найти минимальные пути")
    }

    Label {
        id: label
        x: 297
        y: 77
        text: qsTr("Матрица смежности")
        font.pointSize: 12
        font.family: "Arial"
    }


    Rectangle {
        id: rectangle
        x: 167
        y: 411
        width: 64
        height: 42
        color: "#ffffff"
        radius: 0
        border.color: "#000000"
        border.width: 30

        TextField {
            id: textField
            anchors.rightMargin: 2
            anchors.leftMargin: 2
            anchors.bottomMargin: 2
            anchors.topMargin: 2
            topPadding: 6
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            placeholderText: qsTr("старт")
        }
    }

}
