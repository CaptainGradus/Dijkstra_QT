#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent), mMatrix (nullptr), mFile (nullptr)
{
}

Graph::algResults Graph::dijkstra(const int start) const {
    int size = mMatrix->getSize();

    QVector<QVector<int>> tempPathways(size); // пути
    QVector<GraphData> tempDistances(size); // длины путей
    QVector<bool> isVisited(size); // посещена ли вершина
    int counter = size;

    for (int i = 0; i < size; i++)
        tempPathways[i].append(i);

    tempDistances[start] = 0;

    while(counter--) {
        int curVertex = findMin(tempDistances, isVisited);
        isVisited[curVertex] = true;

        for (int i = 0; i < size; i++)
            if (!isVisited[i] && mMatrix->getItem(curVertex, i).isDef())
                if (tempDistances[i] > tempDistances[curVertex] + mMatrix->getItem(curVertex, i)) {
                    tempDistances[i] = tempDistances[curVertex] + mMatrix->getItem(curVertex, i);
                    tempPathways[i] = tempPathways[curVertex];
                    tempPathways[i].push_back(i);
                }
    }

    return algResults(tempPathways, tempDistances);
}

int Graph::findMin(QVector<GraphData> const &distances, QVector<bool> const &isVisited) const {
    GraphData min;
    int minIndex = 0;
    for (int i = 0; i < distances.size(); i++)
        if (!isVisited[i] && distances[i].isDef() && (distances[i] < min)) {
            min = distances[i];
            minIndex = i;
        }
    return minIndex;
}

void Graph::drawArrow(QPainter& painter, double xStart, double yStart, double xEnd, double yEnd, int weight)
{
    double xSE = xEnd - xStart;
    double ySE = yEnd - yStart;

    double deviation = 25;

    double yDev = deviation / (sqrt (1 + pow(ySE / xSE, 2)));
    double xDev = sqrt (pow (deviation, 2) - pow (yDev, 2));

    if (yStart < yEnd)
        xDev = -xDev;

    if (xStart > xEnd)
        yDev = -yDev;

    QPainterPath path;
    path.moveTo(xStart, yStart);

    path.cubicTo((xStart + xEnd) / 2 + xDev, (yStart + yEnd) / 2 + yDev, xEnd, yEnd, xEnd, yEnd);

    painter.drawPath(path);

    double textDev = 5;
    if (xStart > xEnd)
        textDev = -textDev;

    painter.drawText((xStart + xEnd) / 2 + xDev, (yStart + yEnd) / 2 + yDev + textDev, QString::number(weight));

    int len = 20;
    double angle1 = 30 / degToRad;
    double l = sqrt(pow((xStart - xEnd), 2) + pow((yStart - yEnd), 2));

    // точка A
    double angle2 = acos((xEnd - xStart) / l);
    if (yStart > yEnd)
        angle2 = -angle2;
    double angle3 = angle1 - angle2;
    double xA = xEnd - cos(angle3) * len;
    double yA = yEnd + sin(angle3) * len;

    // точка B
    angle2 = acos((yEnd - yStart) / l);
    if (xStart > xEnd)
        angle2 = -angle2;
    angle3 = angle1 - angle2;
    double xB = xEnd + sin(angle3) * len;
    double yB = yEnd - cos(angle3) * len;

    painter.drawLine(xEnd, yEnd, xA, yA);
    painter.drawLine(xA, yA, xB , yB);
    painter.drawLine(xB , yB, xEnd, yEnd);
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

void Graph::draw(int start, int end)
{
    if (!mMatrix || !mFile || start < 0 || (start >= mMatrix->getSize()) || (end < 0 && end != -100) || (end >= mMatrix->getSize()))
        return;

    mFile->reset();

    QSvgGenerator generator;
    generator.setOutputDevice(mFile);
    generator.setSize(QSize(800, 800));
    generator.setViewBox(QRect(0, 0, 800, 800));
    generator.setTitle(tr("graph short pathways with svg"));
    generator.setDescription(tr("An SVG drawing created by the SVG Generator "));

    QVector<QVector<GraphData>> weightMat = mMatrix->items();
    QVector<QVector<int>> pathways;
    if (end == -100)
        pathways = getAllShortPathways(start);
    else
        pathways.append(getShortPath(start, end));

    QVector<Rib> ribs;

    for (int i = 0; i < weightMat.size(); i++)
        for (int j = 0; j < weightMat.size(); j++)
            if (weightMat.at(i).at(j).isDef() && i != j)
                ribs.append(Rib(i, j));


    for (QVector<int> p : pathways)
        for (int i = 0; i < p.size() - 1; i++)
            ribs[ribs.indexOf(Rib(p.at(i), p.at(i + 1)))].isShort = true;

    QPainter painter;

    painter.begin(&generator);

    int radius = 300;
    int xC = 400;
    int yC = 400;
    double angle = 360 / weightMat.size();

    double lilCircleRad = 15;

    QPen pen;
    pen.setWidth(3);

    for (Rib r : ribs) {
        if (end != -100 && !r.isShort)
            continue;

        if (r.isShort)
            pen.setColor(QColor("green"));
        else
            pen.setColor(QColor("gray"));

        painter.setPen(pen);

        double xS = xC - radius * cos(angle * r.start / degToRad);
        double yS = yC - radius * sin(angle * r.start / degToRad);

        double xE = xC - radius * cos(angle * r.end / degToRad);
        double yE = yC - radius * sin(angle * r.end / degToRad);

        double len = sqrt (pow(xS - xE, 2) + pow(yS - yE, 2));
        double an = acos((xE - xS) / len);
        if (yE < yS)
            an = -an;

        drawArrow(painter, xS, yS, xE - lilCircleRad * cos(an), yE - lilCircleRad * sin(an), weightMat[r.start][r.end].getData());
    }

    painter.setPen(QColor("black"));

    for (int i = 0; i < weightMat.size(); i++) {
        int x = xC - radius * cos(angle * i / 57.2958);
        int y = yC - radius * sin(angle * i / 57.2958);

        if (i == start)
            painter.setBrush(QBrush("red"));
        else
            painter.setBrush(QBrush("yellow"));

        painter.drawEllipse(QPoint(x, y), (qreal) lilCircleRad, (qreal) lilCircleRad);

        QString s('A' + i);
        painter.drawText(QPoint(x - 3, y + 3), s);
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

void Graph::resetSolutions()
{
    shortPathways.clear();
}

QStringList Graph::getWeights(int start, int end)
{
    if (!mMatrix || !mFile || start < 0 || (start >= mMatrix->getSize()) || (end < 0 && end != -100) || (end >= mMatrix->getSize()))
        return QStringList();

    QString fromTo;

    QStringList strList;

    if (end == -100) {
        int i = 0;

        for (GraphData val : getAllDistances(start)) {
            fromTo = start + 'A';
            fromTo += "-";
            fromTo += i++ + 'A';
            fromTo += ": ";

            if (val.isDef())
                strList.append(fromTo + QString::number(val.getData()));
            else
                strList.append(fromTo + "?");
        }
    }
    else {
        fromTo = QString(start + 'A');
        fromTo += "-";
        fromTo += QString(end + 'A');
        fromTo += ": ";

        if (getDistance(start, end).isDef())
            strList.append(fromTo + QString::number(getDistance(start, end).getData()));
        else
            strList.append(fromTo + "?");
    }

    return strList;
}

Graph::algResults::algResults(QVector<QVector<int>> pathways, QVector<GraphData> distances) : pathways(pathways), distances(distances)
{}
