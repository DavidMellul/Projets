#ifndef DRAWHANDLER_H
#define DRAWHANDLER_H

#include "utilities.h"
#include "Point.h"
#include "Droite.h"
#include "Cercle.h"

class DrawHandler
{
    public:
        DrawHandler();
        ~DrawHandler();
        static void startDraw();
        static void endDraw();

        static void draw(Droite d);
        static void draw(Point p);
        static void draw(Cercle c);

        static void setColor(Uint32 color);

    protected:

    private:
        static void putPixel(int x, int y, Uint32 couleur);
        static Uint32 m_color;
};

#endif // DRAWHANDLER_H
