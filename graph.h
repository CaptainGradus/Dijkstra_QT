#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QMap>
#include <QVector>

#include "graphdata.h"
#include "graphdatavector.h"

using namespace std;

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);
    Graph(GraphDataVector matrix, QObject *parent = nullptr);

    int getSize() const;

    QVector<int> getShortPath(const int&, const int&);
    QVector<int>* getAllShortPathways(const int&);

    GraphData getDistance(const int&, const int&);
    GraphData* getAllDistances(const int&);

signals:

public slots:

private:
    struct algResults {
        algResults(QVector<int>* pathways = nullptr, GraphData* distances = nullptr);

        QVector<int>* pathways;
        GraphData* distances;
    };

    GraphDataVector matrix;
    QMap<int, algResults> shortPathways;

    algResults dijkstra(const int) const;
    int findMin(GraphData* const &, bool* const &, const int &) const;
};

#endif // GRAPH_H
