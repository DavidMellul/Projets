#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(double x, double y);
        ~Point();


        double getX();
        double getY();
        void setX(double x);
        void setY(double y);

    protected:

    private:
        double x;
        double y;
};

#endif // POINT_H
