#ifndef COMPUTER_H
#define COMPUTER_H

#include "Point.h"
#include "Cercle.h"
#include "Droite.h"
#include "utilities.h"
#include "DrawHandler.h"


class Computer
{
    public:
        Computer();
        ~Computer();
        static void Rotate(Point& A, Point B, double angle);
        static double toRadians(double angle);


    protected:

    private:
};

#endif // COMPUTER_H
