#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QSvgGenerator>
#include <QPainter>
#include <QResource>
#include <QDir>
#include <QDebug>

#include "graphdata.h"
#include "graphdatavector.h"

using namespace std;

class Graph : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GraphDataVector *matrix READ matrix WRITE setMatrix)
    Q_PROPERTY(QFile *file READ file WRITE setFile)
public:
    explicit Graph(QObject *parent = nullptr);

    int getSize() const;

    QVector<int> getShortPath(const int&, const int&);
    QVector<QVector<int>> getAllShortPathways(const int&);

    GraphData getDistance(const int&, const int&);
    QVector<GraphData> getAllDistances(const int&);

    GraphDataVector *matrix() const;
    void setMatrix(GraphDataVector *matrix);

    QFile *file() const;
    void setFile(QFile *value);

signals:

public slots:
    void draw(int start, int end = -100);

    QString filePath();

    void resetSolutions();

    QStringList getWeights(int start, int end = -100);

private:
    const double degToRad = 57.2958;
    struct algResults {
        algResults(QVector<QVector<int>> pathways, QVector<GraphData> distances);
        algResults() {}

        QVector<QVector<int>> pathways;
        QVector<GraphData> distances;
    };

    struct Rib
    {
        Rib() {}
        Rib(int start, int end, bool isShort = false): start(start), end(end), isShort(isShort) {}

        bool operator == (Rib other) {
            return start == other.start && end == other.end;
        }

        int start;
        int end;
        bool isShort;
    };

    GraphDataVector* mMatrix;
    QFile* mFile;

    QMap<int, algResults> shortPathways;

    algResults dijkstra(const int) const;
    int findMin(QVector<GraphData> const &distances, QVector<bool> const &isVisited) const;

    void drawArrow(QPainter& painter, double xStart, double yStart, double xEnd, double yEnd, int weight);
};

#endif // GRAPH_H
