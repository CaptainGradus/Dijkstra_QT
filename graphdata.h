#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include <QObject>
#include <stdexcept>

class GraphData : public QObject
{
    Q_OBJECT
public:
    explicit GraphData(QObject *parent = nullptr);
    GraphData(double data, QObject *parent = nullptr);
    GraphData(const GraphData&);
    GraphData& operator = (const GraphData&);

    bool isDef() const;
    double getData();
    void setData(double);
    void undef();

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
