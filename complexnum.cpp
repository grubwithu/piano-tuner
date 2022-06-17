#include "complexnum.h"
#include <QtMath>
#include <QList>

ComplexNum::ComplexNum(double real,double imag)
{
    this->imag = imag;
    this->real = real;
}

double ComplexNum::getImag()
{
    return this->imag;
}

double ComplexNum::getReal()
{
    return this->real;
}

void ComplexNum::setImag(double imag)
{
    this->imag = imag;
}

void ComplexNum::setReal(double real)
{
    this->real = real;
}

void ComplexNum::setNumber(double real, double imag)
{
    this->imag = imag;
    this->real = real;
}

void ComplexNum::setNumber(ComplexNum source)
{
    this->real = source.real;
    this->imag = source.imag;
}

ComplexNum operator+(ComplexNum front,ComplexNum back)
{
    return ComplexNum(front.getReal()+back.getReal(),front.getImag()+back.getImag());
}


ComplexNum operator-(ComplexNum front,ComplexNum back)
{
    return ComplexNum(front.getReal()-back.getReal(),front.getImag()-back.getImag());
}

ComplexNum operator*(ComplexNum front,ComplexNum back)
{
    return ComplexNum(front.getReal()*back.getReal()-front.getImag()*back.getImag(),front.getReal()*back.getImag()+front.getImag()*back.getReal());
}

ComplexNum operator*(ComplexNum front,double back)
{
    return ComplexNum(front.getReal()*back,front.getImag()*back);
}

ComplexNum operator*(double front,ComplexNum back)
{
    return ComplexNum(back.getReal()*front,back.getImag()*front);
}

ComplexNum operator+=(ComplexNum &front,ComplexNum back)
{
    front.setReal(front.getReal()+back.getReal());
    front.setImag(front.getImag()+back.getImag());
    return front;
}

double ComplexNum::getMagnitude()
{
    return sqrt(this->imag*this->imag+this->real*this->real);
}

QList<ComplexNum> DFT(QList<ComplexNum> source)
{
    const double pi = acos(-1);
    int length = source.length();
    QList<ComplexNum> ans;
    for(int i=1;i<length;i++)
    {
        ComplexNum temp(0,0);
        for(int j=0;j<length;j++)
        {
            temp += source[j]*(ComplexNum(cos(2*pi*i*j/static_cast<double>(length)),-sin(2*pi*i*j/static_cast<double>(length))));
        }
        ans.push_back(temp);
    }
    return ans;
}

QList<ComplexNum> FFT(QList<ComplexNum> source)
{
    const double pi = acos(-1);
    int length = source.length();
    if(length==1)
        return source;
    QList<ComplexNum> Pe,Po;
    for(int i=0;i<length;i+=2)
    {
        Pe.push_back(source[i]);
        Po.push_back(source[i+1]);
    }
    QList<ComplexNum> ye = FFT(Pe);
    QList<ComplexNum> yo = FFT(Po);
    QList<ComplexNum> ans;
    for(int i=0;i<length/2;i++)
    {
        ans.insert(i,ye[i] + ComplexNum(cos(2*pi*i/length),sin(2*pi*i/length))*yo[i]);
        ans.insert(i+length/2,ye[i] - ComplexNum(cos(2*pi*i/length),sin(2*pi*i/length))*yo[i]);
    }
    return ans;
}
