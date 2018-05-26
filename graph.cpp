#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent), mMatrix (nullptr), mFile (nullptr)
{
}

Graph::algResults Graph::dijkstra(const int start) const {
    int size = mMatrix->getSize();

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

        for (int i = 0; i < size && !isVisited[i] && mMatrix->getItem(curVertex, i).isDef(); i++)
            if (tempDistances[i] > tempDistances[curVertex] + mMatrix->getItem(curVertex, i)) {
                tempDistances[curVertex] = tempDistances[i] + mMatrix->getItem(curVertex, i);
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

QFile *Graph::file() const
{
    return mFile;
}

void Graph::setFile(QFile *value)
{
    mFile = value;
}

int Graph::getSize() const{
    return mMatrix->getSize();
}

QVector<int> Graph::getShortPath(const int& start, const int& end) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    return shortPathways[start].pathways[end];
}

QVector<QVector<int>> Graph::getAllShortPathways(const int& start) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    QVector<QVector<int>> temp(mMatrix->getSize());
    for (int i = 0; i < mMatrix->getSize(); i++)
        temp[i] = shortPathways[start].pathways[i];

    return temp;
}

GraphData Graph::getDistance(const int& start, const int& end) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    return shortPathways[start].distances[end];
}

QVector<GraphData> Graph::getAllDistances(const int& start) {
    if (shortPathways.find(start) == shortPathways.end())
        shortPathways.insert(start, dijkstra(start));

    QVector<GraphData> temp(mMatrix->getSize());
    for (int i = 0; i < mMatrix->getSize(); i++)
        temp[i] = shortPathways[start].distances[i];

    return temp;
}

GraphDataVector *Graph::matrix() const
{
    return mMatrix;
}

void Graph::setMatrix(GraphDataVector *matrix)
{
    mMatrix = matrix;
}

void Graph::draw(int start)
{
    if (!mMatrix && !mFile)
        return;

    QSvgGenerator generator;
    generator.setOutputDevice(mFile);
    generator.setSize(QSize(400, 400));
    generator.setViewBox(QRect(0, 0, 400, 400));
    generator.setTitle(tr("graph short pathways with svg"));
    generator.setDescription(tr("An SVG drawing created by the SVG Generator "));

    QVector<QVector<GraphData>> weightMat = mMatrix->items();
    QVector<QVector<int>> pathways = getAllShortPathways(start);
    QVector<Rib> ribs;

    for (int i = 0; i < weightMat.size(); i++)
        for (int j = 0; j < weightMat.size(); j++)
            if (weightMat.at(i).at(j).isDef())
                ribs.append(Rib(i, j));


    for (QVector<int> p : pathways)
        for (int i = 0; i < p.size() - 1; i++)
            ribs[ribs.indexOf(Rib(p.at(i), p.at(i + 1)))].isShort = true;


    QPainter painter;

    painter.begin(&generator);
    painter.setRenderHint(QPainter::Antialiasing);

    int radius = 100;
    int xC = 200;
    int yC = 200;
    double angle = 360 / weightMat.size();

    for (Rib r : ribs)
        if (r.isShort)
            painter.drawLine(xC + radius * cos(angle * r.start), yC + radius * sin(angle * r.start),
                             xC + radius * cos(angle * r.end), yC + radius * sin(angle * r.end));

    int circleWidth = 40;
    int circleHeight = 40;

    for (int i = 0; i < weightMat.size(); i++) {
        QRect rect (xC + radius * cos(angle * i) - circleWidth / 2, yC + radius * sin(angle * i) - circleHeight / 2, circleWidth, circleHeight);

        if (i == start)
            painter.fillRect(rect, QColor("red"));
        else
            painter.fillRect(rect, QColor("yellow"));

        QString s ('A' + i);
        painter.drawText(rect, Qt::AlignCenter, s);

        painter.drawEllipse(rect);
    }

    painter.end();
}

QString Graph::filePath()
{
    if (!mFile) {
        qDebug() << "no file";
        return "";
    }

    QFileInfo fileInfo(*mFile);
    return fileInfo.absoluteFilePath().mid(2);
}

Graph::algResults::algResults(QVector<int> *pathways, GraphData *distances) : pathways(pathways), distances(distances)
{}
