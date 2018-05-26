#include "graphdata.h"

using namespace std;

GraphData::GraphData(QObject *parent) : QObject(parent), isDefined(false)
{
}

GraphData::GraphData(double data, QObject *parent) : QObject(parent), data(data), isDefined(true)
{
}

GraphData::GraphData(const GraphData & other) : QObject(other.parent()), data(other.data), isDefined(other.isDefined)
{
}

bool GraphData::isDef() const {
    return isDefined;
}

double GraphData::getData() {
    if (isDefined)
        return data;

    throw logic_error("data is undefined");
}

void GraphData::setData(double data) {
    data = data;
    isDefined = true;
}

void GraphData::undef() {
    isDefined = false;
}

GraphData& GraphData::operator = (const GraphData& var) {
    data = var.data;
    isDefined = var.isDefined;
    return *this;
}

bool operator == (const GraphData& lVar, const GraphData& rVar) {
    if (lVar.isDefined && rVar.isDefined)
        return lVar.data == rVar.data;

    if (lVar.isDefined || rVar.isDefined)
        return false;

    throw logic_error("cannot compare both undefined variables");
}

bool operator != (const GraphData& lVar, const GraphData& rVar) {
    return !(lVar == rVar);
}

bool operator < (const GraphData& lVar, const GraphData& rVar) {
    if (lVar.isDefined && rVar.isDefined)
        return lVar.data < rVar.data;
    else if (!lVar.isDefined && rVar.isDefined)
        return false;
    else if (lVar.isDefined && !rVar.isDefined)
        return true;

    throw logic_error("cannot compare both undefined variables");
}

bool operator > (const GraphData& lVar, const GraphData& rVar) {
    return rVar < lVar;
}

bool operator <= (const GraphData& lVar, const GraphData& rVar) {
    return !(rVar < lVar);
}

bool operator >= (const GraphData& lVar, const GraphData& rVar) {
    return !(lVar < rVar);
}

GraphData& operator += (GraphData& lVar, const GraphData& rVar) {
    if (!rVar.isDefined)
        lVar.isDefined = false;

    lVar.data += rVar.data;
    return lVar;
}

GraphData& operator -= (GraphData& lVar, const GraphData& rVar) {
    if (!rVar.isDefined)
        lVar.isDefined = false;

    lVar.data -= rVar.data;
    return lVar;
}

GraphData& operator *= (GraphData& lVar, const GraphData& rVar) {
    if (!rVar.isDefined)
        lVar.isDefined = false;

    lVar.data *= rVar.data;
    return lVar;
}

GraphData& operator /= (GraphData& lVar, const GraphData& rVar) {
    if (!rVar.isDefined)
        lVar.isDefined = false;

    lVar.data /= rVar.data;
    return lVar;
}

GraphData operator + (GraphData var) {
    return var;
}

GraphData operator - (GraphData var) {
    var.data = -var.data;
    return var;
}

GraphData operator + (GraphData lVar, const GraphData& rVar) {
    return lVar += rVar;
}

GraphData operator - (GraphData lVar, const GraphData& rVar) {
    return lVar -= rVar;
}

GraphData operator * (GraphData lVar, const GraphData& rVar) {
    return lVar *= rVar;
}

GraphData operator / (GraphData lVar, const GraphData& rVar) {
    return lVar /= rVar;
}
