#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include <QObject>

class GraphData : public QObject
{
    Q_OBJECT
public:
    explicit GraphData(QObject *parent = nullptr);
    GraphData(double data, QObject *parent = nullptr);
    GraphData(const GraphData&);
    bool isDef();
    double getData();
    void setData(double);
    void undef();
    GraphData& operator = (const GraphData&);

    friend bool operator == (const GraphData&, const GraphData&);
    friend bool operator != (const GraphData&, const GraphData&);
    friend bool operator < (const GraphData&, const GraphData&);
    friend bool operator > (const GraphData&, const GraphData&);
    friend bool operator <= (const GraphData&, const GraphData&);
    friend bool operator >= (const GraphData&, const GraphData&);

    friend GraphData& operator += (GraphData&, const GraphData&);
    friend GraphData& operator -= (GraphData&, const GraphData&);
    friend GraphData& operator *= (GraphData&, const GraphData&);
    friend GraphData& operator /= (GraphData&, const GraphData&);

    friend GraphData operator + (GraphData);
    friend GraphData operator - (GraphData);

    friend GraphData operator + (GraphData, const GraphData&);
    friend GraphData operator - (GraphData, const GraphData&);
    friend GraphData operator * (GraphData, const GraphData&);
    friend GraphData operator / (GraphData, const GraphData&);

signals:

public slots:

private:
    double data;
    bool isDefined;
};

#endif // GRAPHDATA_H
