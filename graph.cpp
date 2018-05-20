#include "graph.h"

//struct Graph::algResults {
//    algResults(vector<int>* pathways = nullptr, GraphData* distances = nullptr) : pathways(pathways), distances(distances)
//    {}

//    vector<int>* pathways;
//    GraphData* distances;
//};

Graph::Graph(QObject *parent) : QObject(parent), matrix(nullptr)
{
}


Graph::Graph(GraphData** matrix, QObject *parent) : QObject(parent), matrix(matrix)
{
}

Graph::algResults Graph::dijkstra(const int start) const {
    vector<int>* tempPathways = new vector<int>[size];
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

        for (int i = 0; i < size && !isVisited[i] && matrix[curVertex][i].isDef(); i++)
            if (tempDistances[i] > tempDistances[curVertex] + matrix[curVertex][i]) {
                tempDistances[curVertex] = tempDistances[i] + matrix[curVertex][i];
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
    return this->size;
}

vector<int> Graph::getShortPath(const int& start, const int& end) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(pair<int, algResults>(start, dijkstra(start)));

    return shortPathways[start].pathways[end];
}

vector<int>* Graph::getAllShortPathways(const int& start) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(pair<int, algResults>(start, dijkstra(start)));

    vector<int>* temp = new vector<int>[size];
    for (int i = 0; i < size; i++)
        temp[i] = shortPathways[start].pathways[i];

    return temp;
}

GraphData Graph::getDistance(const int& start, const int& end) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(pair<int, algResults>(start, dijkstra(start)));

    return shortPathways[start].distances[end];
}

GraphData* Graph::getAllDistances(const int& start) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(pair<int, algResults>(start, dijkstra(start)));

    GraphData* temp = new GraphData[size];
    for (int i = 0; i < size; i++)
        temp[i] = shortPathways[start].distances[i];

    return temp;
}

Graph::algResults::algResults(vector<int> *pathways, GraphData *distances) : pathways(pathways), distances(distances)
{}
