#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

#include <QList>

class ComplexNum
{
public:
    ComplexNum(double real,double imag);
    double getReal();
    double getImag();
    double getMagnitude();
    void setReal(double real);
    void setImag(double imag);
    void setNumber(double real,double imag);
    void setNumber(ComplexNum source);

private:
    double real;
    double imag;

};

ComplexNum operator+(ComplexNum front,ComplexNum back);
ComplexNum operator-(ComplexNum front,ComplexNum back);
ComplexNum operator*(ComplexNum front,ComplexNum back);
ComplexNum operator*(ComplexNum front,double back);
ComplexNum operator*(double front,ComplexNum back);
ComplexNum operator+=(ComplexNum &front,ComplexNum back);

QList<ComplexNum> DFT(QList<ComplexNum> source);
QList<ComplexNum> FFT(QList<ComplexNum> source);

#endif // COMPLEXNUM_H
