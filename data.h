#ifndef DATA_H
#define DATA_H


class Data {
private:
    double data;
    bool isDefined;
public:
    Data();
    Data(double data);
    bool isDef();
    double getData();
    void setData(double);
    void undef();
    Data& operator = (const Data&);
    friend bool operator == (const Data&, const Data&);
    friend bool operator != (const Data&, const Data&);
    friend bool operator < (const Data&, const Data&);
    friend bool operator > (const Data&, const Data&);
    friend bool operator <= (const Data&, const Data&);
    friend bool operator >= (const Data&, const Data&);

    friend Data& operator += (Data&, const Data&);
    friend Data& operator -= (Data&, const Data&);
    friend Data& operator *= (Data&, const Data&);
    friend Data& operator /= (Data&, const Data&);

    friend Data operator + (Data);
    friend Data operator - (Data);

    friend Data operator + (Data, const Data&);
    friend Data operator - (Data, const Data&);
    friend Data operator * (Data, const Data&);
    friend Data operator / (Data, const Data&);
};

#endif // DATA_H
