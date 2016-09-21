#ifndef CERCLE_H
#define CERCLE_H

#include "Point.h"
class Cercle
{
    public:
        Cercle();
        Cercle(double cX, double cY, double r);
        ~Cercle();

        double getCx();
        double getCy();
        double getRadius();

        Point& getCenter();

        void setCenter(Point c);
        void setRadius(double r);


    protected:

    private:
        Point c;
        double r;

};

#endif // CERCLE_H
