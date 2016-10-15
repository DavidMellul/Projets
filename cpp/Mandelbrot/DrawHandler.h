#ifndef DRAWHANDLER_H
#define DRAWHANDLER_H

#include "utilities.h"

class DrawHandler
{
    public:
        DrawHandler();
        ~DrawHandler();
        static void startDraw();
        static void endDraw();

        static void setColor(Uint32 color);
        static void putPixel(int x, int y);

    protected:

    private:
        static Uint32 m_color;
};

#endif // DRAWHANDLER_H
