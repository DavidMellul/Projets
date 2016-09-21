#ifndef COMPUTER_H
#define COMPUTER_H

#include "Point.h"
#include "utilities.h"

class Computer
{
    public:
        Computer();
        ~Computer();
        static void Rotate(Point& A, Point B, double angle);


    protected:

    private:
};

#endif // COMPUTER_H
