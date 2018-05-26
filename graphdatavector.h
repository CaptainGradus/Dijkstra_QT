#ifndef GRAPHDATAVECTOR_H
#define GRAPHDATAVECTOR_H

#include <QObject>
#include <QVector>

#include "graphdata.h"

using namespace std;

class GraphDataVector : public QObject
{
    Q_OBJECT
public:
    explicit GraphDataVector(QObject *parent = nullptr);

    GraphDataVector(const GraphDataVector& other);

    QVector<QVector<GraphData>> items() const;

    bool setItemAt (int rowIndex, int columnIndex, GraphData item);

    int getSize() const;

    GraphData getItem(int rowIndex, int columnIndex) const;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int item);
    void postItemRemoved();

public slots:
    int appendItem();
    void removeItem();

private:
    int size;
    QVector<QVector<GraphData>> vector;
};

#endif // GRAPHDATAVECTOR_H
