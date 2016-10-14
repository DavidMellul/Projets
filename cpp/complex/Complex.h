#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <typeinfo>

using namespace std;

class Complex
{
    public:
        Complex();
        Complex(int Re, int Im);

        int getIm();
        int getRe();

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

        void display();
        ~Complex();

    protected:

    private:
        int m_Re;
        int m_Im;
};

#endif // COMPLEX_H
