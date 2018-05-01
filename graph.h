#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include "data.h"

class Graph
{
private:
    struct algResults;

    Data** matrix;
    int size;
    map<int, algResults> shortPathways;

    algResults dijkstra(const int) const;
    int findMin(Data* const &, bool* const &, const int &) const;
public:
    Graph(Data** matrix);

    int getSize() const;

    vector<int> getShortPath(const int&, const int&);
    vector<int>* getAllShortPathways(const int&);

    Data getDistance(const int&, const int&);
    Data* getAllDistances(const int&);
};

#endif // GRAPH_H
