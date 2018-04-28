#include "graph.h"

struct Graph::algResults {
    algResults(std::vector<int>* pathways, Data* distances) : pathways(pathways), distances(distances)
    {}
    std::vector<int>* pathways;
    Data* distances;
};

Graph::Graph(Data** matrix)
{
    this->matrix = matrix;
}

Graph::algResults Graph::dijkstra(const int start) const {
    std::vector<int>* tempPathways = new std::vector<int>[size];
    Data* tempDistances = new Data[size];
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

        for (int i = 0; i < size && !isVisited[i] && matrix[curVertex][i].isDef() && (tempDistances[i] > tempDistances[curVertex] + matrix[curVertex][i]); i++) {
            tempDistances[curVertex] = tempDistances[i] + matrix[curVertex][i];
            tempPathways[i] = tempPathways[curVertex];
            tempPathways[i].push_back(i);
        }
    }

    return
}

int Graph::findMin(Data* const &distances, bool* const &isVisited, const int &size) const {
    int min = 0;
    for (int i = 1; i < size; i++)
        if (!isVisited[i] && distances[i] < distances[min])
            min = i;
    return min;
}
