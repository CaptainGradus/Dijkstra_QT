#ifndef GRAPHMATRIXMODEL_H
#define GRAPHMATRIXMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include "graphdatavector.h"

class GraphDataVector;

class GraphMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(GraphDataVector *matrix READ matrix WRITE setMatrix)
public:
    explicit GraphMatrixModel(QObject *parent = nullptr);

    QVector<int> myEnum;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    GraphDataVector* matrix() const;
    void setMatrix(GraphDataVector *matrix);

    void addEnum();

    virtual QHash<int, QByteArray> roleNames() const override;

private:
    GraphDataVector* mMatrix;

public slots:
    QVariant getData(int rowIndex, int columnIndex) const;
};

#endif // GRAPHMATRIXMODEL_H
