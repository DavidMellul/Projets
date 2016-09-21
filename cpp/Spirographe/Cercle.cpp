#include "Cercle.h"

Cercle::Cercle()
{
    //ctor
}

Cercle::Cercle(double cX, double cY, double r)
{
    this->c.setX(cX);
    this->c.setY(cY);
    this->r = r;
}

double Cercle::getCx()
{
    return this->c.getX();
}

double Cercle::getCy()
{
    return this->c.getY();
}

double Cercle::getRadius()
{
    return this->r;
}

Point& Cercle::getCenter()
{
    return this->c;
}

void Cercle::setRadius(double r)
{
    this->r = r;
}

void Cercle::setCenter(Point c)
{
    this->c = c;
}

Cercle::~Cercle()
{
    //dtor
}
