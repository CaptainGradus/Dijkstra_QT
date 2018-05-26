#include "graphdatavector.h"

GraphDataVector::GraphDataVector(QObject *parent) : QObject(parent), size(6)
{
    vector.fill(QVector<GraphData>(size, GraphData()), size);
}

GraphDataVector::GraphDataVector(const GraphDataVector& other) : QObject(other.parent()), size(other.size), vector(other.items())
{

}

QVector<QVector<GraphData> > GraphDataVector::items() const
{
    return vector;
}

bool GraphDataVector::setItemAt(int rowIndex, int columnIndex, GraphData item)
{
    if (!(rowIndex < size && columnIndex < size))
        return false;

    vector[rowIndex][columnIndex] = item;
    return true;
}

int GraphDataVector::getSize() const
{
    return size;
}

GraphData GraphDataVector::getItem(int rowIndex, int columnIndex) const
{
    if (rowIndex < size && columnIndex < size)
        return vector[rowIndex][columnIndex];

    throw out_of_range("out of range");
}

int GraphDataVector::appendItem() {
    emit preItemAppended();

    vector.append(QVector<GraphData>(size++, GraphData()));

    for (QVector<GraphData>& vec : vector)
        vec.append(GraphData());

    emit postItemAppended();

    return size - 1;
}

void GraphDataVector::removeItem() {
    if (size > 0) {
        emit preItemRemoved(--size);

        vector.pop_back();

        for (QVector<GraphData>& vec : vector)
            vec.pop_back();

        emit postItemRemoved();
    }
}
