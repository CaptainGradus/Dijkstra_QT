import QtQuick.Window 2.2
import QtQuick 2.9
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
//import QtQuick 2.15

import Graph 1.0

TableView {
    id: tableView
    clip: true
    anchors.fill: parent
    sortIndicatorVisible: false
    backgroundVisible: true
    alternatingRowColors: true

    TableViewColumn {
        title: "X"
        role: "Name"
        width: 40
    }

    TableViewColumn {
        title: "A"
        role: "A"
        width: 40

        delegate: TextEdit {
            text: model.A
            onEditingFinished: {
                if (isNaN(text) || text < 0)
                    text = "-"
                model.A = text
            }
        }
    }
    TableViewColumn {
        title: "B"
        role: "B"
        width: 40

        delegate: TextEdit {
            text: model.B
            onEditingFinished: {
                if (isNaN(text) || text < 0)
                    text = "-"
                model.B = text
            }
        }
    }
    TableViewColumn {
        title: "C"
        role: "C"
        width: 40

        delegate: TextEdit {
            text: model.C
            onEditingFinished: {
                if (isNaN(text) || text < 0)
                    text = "-"
                model.C = text
            }
        }
    }
    TableViewColumn {
        title: "D"
        role: "D"
        width: 40

        delegate: TextEdit {
            text: model.D
            onEditingFinished: {
                if (isNaN(text) || text < 0)
                    text = "-"
                model.D = text
            }
        }
    }
    TableViewColumn {
        title: "E"
        role: "E"
        width: 40

        delegate: TextEdit {
            text: model.E
            onEditingFinished: {
                if (isNaN(text) || text < 0)
                    text = "-"
                model.E = text
            }
        }
    }
    TableViewColumn {
        title: "F"
        role: "F"
        width: 40

        delegate: TextEdit {
            text: model.F

            onEditingFinished: {
                if (isNaN(text) || text < 0)
                    text = "-"
                model.F = text
            }
        }
    }

    model: GraphModel {
        matrix: graphData
    }
}
