#include <iostream>
#include "Complex.h"
using namespace std;

int main()
{
    Complex A(1,2);
    A.display();

    Complex B(1,2);
    B.display();

    Complex C = (A+B).clone();
    C.display();

    Complex D = C*C;
    D.display();

    Complex E = C/C;
    E.display();

    cout << endl;

    if(A == B)
        cout << "A = B" << endl;
    if(C > A && C > B)
        cout << "C > A et C > B" << endl;
    if(C > D)
        cout << "C > D" << endl;
    if(E == Complex(1,0))
        cout << "C / C = 1 = E" << endl;

    return 0;
}
