#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <typeinfo>
#include <cmath>

using namespace std;

class Complex
{
    public:
        Complex();
        Complex(float Re, float Im);

        float getIm();
        float getRe();

        Complex clone();

        Complex operator+(Complex c);
        Complex operator-(Complex c);
        Complex operator*(Complex c);
        Complex operator/(Complex c);
        Complex operator=(Complex c);

        bool operator==(Complex c);
        bool operator>=(Complex c);
        bool operator<=(Complex c);
        bool operator<(Complex c);
        bool operator>(Complex c);

        float module();

        void display();
        ~Complex();

    protected:

    private:
        float m_Re;
        float m_Im;
};

#endif // COMPLEX_H
