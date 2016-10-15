#include "Complex.h"

Complex::Complex()
{
    this->m_Re = 0;
    this->m_Im = 0;
}
Complex::Complex(float Re, float Im)

{
    this->m_Re = Re;
    this->m_Im = Im;
}

Complex Complex::clone()
{
    return *(new Complex(this->getRe(), this->getIm()));
}

float Complex::getRe()
{
    return this->m_Re;
}

float Complex::getIm()
{
    return this->m_Im;
}

Complex Complex::operator+(Complex c)
{
    return Complex(this->m_Re+c.getRe(), this->m_Im+c.getIm());
}

Complex Complex::operator-(Complex c)
{
    return Complex(this->m_Re-c.getRe(), this->m_Im-c.getIm());
}

Complex Complex::operator/(Complex c)
{
    return Complex( ((this->m_Re*c.getRe())-(this->getIm()*c.getIm()))/((c.getRe()*c.getRe())-(c.getIm()*c.getIm())), ((this->m_Re*c.getIm()) + (this->m_Im*c.getRe()))/((c.getRe()*c.getRe())+c.getIm()*c.getIm()));
}

Complex Complex::operator*(Complex c)
{
    return Complex( (this->m_Re*c.getRe())-(this->getIm()*c.getIm()), this->m_Re*c.getIm() + this->m_Im*c.getRe());
}

Complex Complex::operator=(Complex c)
{
    this->m_Re = c.getRe();
    this->m_Im = c.getIm();
    return *this;
}

bool Complex::operator>(Complex c)
{
    return (this->m_Re > c.getRe()) || (this->m_Re == c.getRe() && this->m_Im > c.getIm());
}

bool Complex::operator<(Complex c)
{
    return (this->m_Re < c.getRe()) || (this->m_Re == c.getRe() && this->m_Im < c.getIm());
}

bool Complex::operator==(Complex c)
{
    return (this->m_Re == c.getRe() && this->m_Im == c.getIm());
}

bool Complex::operator>=(Complex c)
{
    return (*this > c || *this == c);
}

bool Complex::operator<=(Complex c)
{
    return (*this < c || *this==c);
}

float Complex::module()
{
    return sqrt((this->m_Re*this->m_Re)+(this->m_Im*this->m_Im));
}

void Complex::display()
{
    cout << this->m_Re;
    string op = (this->m_Im >= 0) ? " + ":" - ";
    cout << op << this->m_Im << "i" << endl;
}


Complex::~Complex()
{
    //dtor
}
