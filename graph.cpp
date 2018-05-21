#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent)
{
}


Graph::Graph(GraphDataVector matrix, QObject *parent) : QObject(parent), matrix(matrix)
{
}

Graph::algResults Graph::dijkstra(const int start) const {
    int size = matrix.getSize();

    QVector<int>* tempPathways = new QVector<int>[size];
    GraphData* tempDistances = new GraphData[size];
    bool* isVisited = new bool[size];
    int counter = size;

    tempDistances[start] = 0;

    for (int i = 0; i < size; i++) {
        if (i != start)
            tempDistances[i].undef();
        isVisited[i] = false;
    }

    while(counter--) {
        int curVertex = findMin(tempDistances, isVisited, size);
        isVisited[curVertex] = true;

        for (int i = 0; i < size && !isVisited[i] && matrix.getItem(curVertex, i).isDef(); i++)
            if (tempDistances[i] > tempDistances[curVertex] + matrix.getItem(curVertex, i)) {
                tempDistances[curVertex] = tempDistances[i] + matrix.getItem(curVertex, i);
                tempPathways[i] = tempPathways[curVertex];
                tempPathways[i].push_back(i);
            }
    }

    return algResults(tempPathways, tempDistances);
}

int Graph::findMin(GraphData* const &distances, bool* const &isVisited, const int &size) const {
    int min = 0;
    for (int i = 1; i < size; i++)
        if (!isVisited[i] && distances[i] < distances[min])
            min = i;
    return min;
}

int Graph::getSize() const{
    return matrix.getSize();
}

QVector<int> Graph::getShortPath(const int& start, const int& end) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    return shortPathways[start].pathways[end];
}

QVector<int>* Graph::getAllShortPathways(const int& start) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    QVector<int>* temp = new QVector<int>[matrix.getSize()];
    for (int i = 0; i < matrix.getSize(); i++)
        temp[i] = shortPathways[start].pathways[i];

    return temp;
}

GraphData Graph::getDistance(const int& start, const int& end) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    return shortPathways[start].distances[end];
}

GraphData* Graph::getAllDistances(const int& start) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    GraphData* temp = new GraphData[matrix.getSize()];
    for (int i = 0; i < matrix.getSize(); i++)
        temp[i] = shortPathways[start].distances[i];

    return temp;
}

Graph::algResults::algResults(QVector<int> *pathways, GraphData *distances) : pathways(pathways), distances(distances)
{}
