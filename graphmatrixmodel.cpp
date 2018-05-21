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

    return mMatrix->getSize();
}

QVariant GraphMatrixModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == 262)
        int k;

    if (myEnum.contains(role))
        if (mMatrix->getItem(index.row(), myEnum.indexOf(role)).isDef())
            return mMatrix->getItem(index.row(), myEnum.indexOf(role)).getData();

    return ("-");
}

bool GraphMatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mMatrix)
        return false;

    double item;

    if (myEnum.contains(role))
        item = value.toDouble();

    if (mMatrix->setItemAt(index.row(), myEnum.indexOf(role), item)) {
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

    for (int role : myEnum) {
        sym = i++;
        names[role] = sym.c_str();
    }

    return names;
}

QVariant GraphMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
             return QVariant("");

    return section + 1;
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

    for (int i = 1; i < mMatrix->getSize(); i++)
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
