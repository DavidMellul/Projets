#ifndef DROITE_H
#define DROITE_H

#include "Point.h"

class Droite
{
    public:
        Droite();
        Droite(Point A, Point B);
        ~Droite();

        Point& getOrigine();
        Point& getExtremite();

        void setOrigine(Point A);
        void setExtremite(Point B);

    protected:

    private:
        Point A;
        Point B;
};

#endif // DROITE_H
