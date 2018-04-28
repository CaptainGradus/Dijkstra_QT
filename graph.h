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
    std::map<int, algResults> shortPathways;

    void dijkstra(const int) const;
    int findMin(Data* const &, bool* const &, const int &) const;
public:
    Graph(Data** matrix);
};

#endif // GRAPH_H
