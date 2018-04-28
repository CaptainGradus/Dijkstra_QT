#include <stdexcept>
#include "data.h"

Data::Data()
{
    this->isDefined = false;
}

Data::Data(double data) {
    this->data = data;
    this->isDefined = true;
}

bool Data::isDef() {
    return this->isDefined;
}

double Data::getData() {
    if (isDefined)
        return this->data;
    throw std::logic_error("data is undefined");
}

void Data::setData(double data) {
    this->data = data;
    this->isDefined = true;
}

void Data::undef() {
    this->isDefined = false;
}

Data& Data::operator = (const Data& var) {
    this->data = var.data;
    this->isDefined = var.isDefined;
    return *this;
}

bool operator == (const Data& lVar, const Data& rVar) {
    if (lVar.isDefined && rVar.isDefined)
        return lVar.data == rVar.data;
    else if (lVar.isDefined || rVar.isDefined)
        return false;
    throw std::logic_error("cannot compare undefined variables");
}

bool operator != (const Data& lVar, const Data& rVar) {
    return !(lVar == rVar);
}

bool operator < (const Data& lVar, const Data& rVar) {
    if (lVar.isDefined && rVar.isDefined)
        return lVar.data < rVar.data;
    else if (!lVar.isDefined && rVar.isDefined)
        return false;
    else if (lVar.isDefined && !rVar.isDefined)
        return true;
    throw std::logic_error("cannot compare undefined variables");
}

bool operator > (const Data& lVar, const Data& rVar) {
    return rVar < lVar;
}

bool operator <= (const Data& lVar, const Data& rVar) {
    return !(rVar < lVar);
}

bool operator >= (const Data& lVar, const Data& rVar) {
    return !(lVar < rVar);
}

Data& operator += (Data& lVar, const Data& rVar) {
    if (lVar.isDefined && rVar.isDefined) {
        lVar.data += rVar.data;
        return lVar;
    }
    throw std::logic_error("cannot operate with an undefined variable");
}

Data& operator -= (Data& lVar, const Data& rVar) {
    if (lVar.isDefined && rVar.isDefined) {
        lVar.data -= rVar.data;
        return lVar;
    }
    throw std::logic_error("cannot operate with an undefined variable");
}

Data& operator *= (Data& lVar, const Data& rVar) {
    if (lVar.isDefined && rVar.isDefined) {
        lVar.data *= rVar.data;
        return lVar;
    }
    throw std::logic_error("cannot operate with an undefined variable");
}

Data& operator /= (Data& lVar, const Data& rVar) {
    if (lVar.isDefined && rVar.isDefined) {
        lVar.data /= rVar.data;
        return lVar;
    }
    throw std::logic_error("cannot operate with an undefined variable");
}

Data operator + (Data var) {
    if (var.isDefined)
        return var;
    throw std::logic_error("cannot operate with an undefined variable");
}

Data operator - (Data var) {
    if (var.isDefined) {
        var.data = -var.data;
        return var;
    }
    throw std::logic_error("cannot operate with an undefined variable");
}

Data operator + (Data lVar, const Data& rVar) {
    return lVar += rVar;
}

Data operator - (Data lVar, const Data& rVar) {
    return lVar -= rVar;
}

Data operator * (Data lVar, const Data& rVar) {
    return lVar *= rVar;
}

Data operator / (Data lVar, const Data& rVar) {
    return lVar /= rVar;
}




