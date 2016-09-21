#include "Computer.h"

Computer::Computer()
{
    //ctor
}

void Computer::Rotate(Point& A, Point B, double angle)
{
    double x1 = A.getX();
    double y1 = A.getY();

    double x2 = B.getX();
    double y2 = B.getY();

    double x3 = cos(angle) * (x1-x2) - sin(angle) * (y1-y2) + x2;
    double y3 = sin(angle) * (x1-x2) + cos(angle) * (y1-y2) + y2;

    A.setX(x3);
    A.setY(y3);
}

Computer::~Computer()
{
    //dtor
}
