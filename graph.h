#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <map>
#include <vector>

#include "graphdata.h"

using namespace std;

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);
    Graph(GraphData** matrix, QObject *parent = nullptr);

    int getSize() const;

    vector<int> getShortPath(const int&, const int&);
    vector<int>* getAllShortPathways(const int&);

    GraphData getDistance(const int&, const int&);
    GraphData* getAllDistances(const int&);

signals:

public slots:

private:
    struct algResults {
        algResults(vector<int>* pathways = nullptr, GraphData* distances = nullptr);

        vector<int>* pathways;
        GraphData* distances;
    };

    GraphData** matrix;
    int size;
    map<int, algResults> shortPathways;

    algResults dijkstra(const int) const;
    int findMin(GraphData* const &, bool* const &, const int &) const;
};

#endif // GRAPH_H
