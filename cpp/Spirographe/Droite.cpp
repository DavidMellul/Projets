#include "Droite.h"

Droite::Droite()
{
    this->A = Point(0,0);
    this->B = Point(0,1);
}
Droite::Droite(Point A, Point B)
{
    this->A = A;
    this->B = B;
}

Point& Droite::getOrigine()
{
    return this->A;
}

Point& Droite::getExtremite()
{
    return this->B;
}

void Droite::setOrigine(Point A)
{
    this->A = A;
}

void Droite::setExtremite(Point B)
{
    this->B = B;
}

Droite::~Droite()
{
    //dtor
}
