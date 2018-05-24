#include <string>

#include "graphmatrixmodel.h"

using namespace std;

GraphMatrixModel::GraphMatrixModel(QObject *parent)
    : QAbstractTableModel(parent), mMatrix(nullptr)
{
    myEnum.append(Qt::UserRole);
}

int GraphMatrixModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mMatrix->getSize();
}

int GraphMatrixModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mMatrix->getSize() + 1;
}

QVariant GraphMatrixModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == myEnum.at(0)) {
        QString s ('A' + index.row());
        return s;
    }

    if (myEnum.contains(role))
        if (mMatrix->getItem(index.row(), myEnum.indexOf(role) - 1).isDef())
            return mMatrix->getItem(index.row(), myEnum.indexOf(role) - 1).getData();

    return ("-");
}

bool GraphMatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mMatrix)
        return false;

    double item;

    if (myEnum.contains(role))
        item = value.toDouble();

    if (mMatrix->setItemAt(index.row(), myEnum.indexOf(role) - 1, item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags GraphMatrixModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QHash<int, QByteArray> GraphMatrixModel::roleNames() const
{
    QHash<int, QByteArray> names;

    char i = 'A';
    string sym;

    for (int j = 1; j < myEnum.size(); j++, i++) {
        sym = i;
        names[myEnum.at(j)] = sym.c_str();
    }
    names[myEnum.at(0)] = "Name";

    return names;
}

QVariant GraphMatrixModel::getData(int rowIndex, int columnIndex) const
{
    if (mMatrix->getItem(rowIndex, columnIndex).isDef())
        return mMatrix->getItem(rowIndex, columnIndex).getData();

    return ("-");
}

GraphDataVector *GraphMatrixModel::matrix() const
{
    return mMatrix;
}

void GraphMatrixModel::setMatrix(GraphDataVector *matrix)
{
    beginResetModel();

    if (mMatrix)
        mMatrix->disconnect(this);

    mMatrix = matrix;

    for (int i = 0; i < mMatrix->getSize(); i++)
        addEnum();

    if (mMatrix) {
        connect (mMatrix, &GraphDataVector::preItemAppended, this, [=]() {
                 beginInsertRows(QModelIndex(), mMatrix->getSize(), mMatrix->getSize());
                beginInsertColumns(QModelIndex(), mMatrix->getSize(), mMatrix->getSize());
                 addEnum();
        });

        connect (mMatrix, &GraphDataVector::postItemAppended, this, [=]() {
            endInsertColumns();
            endInsertRows();});

        connect (mMatrix, &GraphDataVector::preItemRemoved, this, [=](int index) {
                 beginResetModel();
            //beginRemoveRows(QModelIndex(), index, index);

                myEnum.pop_back();
        });

        connect (mMatrix, &GraphDataVector::postItemRemoved, this, [=]() {
                 endResetModel();
            /*endRemoveRows();*/});
    }

    endResetModel();
}

void GraphMatrixModel::addEnum()
{
    myEnum.append(myEnum.last() + 1);
}
