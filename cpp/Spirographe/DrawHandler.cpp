#include "DrawHandler.h"

Uint32 DrawHandler::m_color;

DrawHandler::DrawHandler()
{
    //ctor
}

void DrawHandler::startDraw()
{
    SDL_LockSurface(ECRAN);
}

void DrawHandler::endDraw()
{
    SDL_UnlockSurface(ECRAN);
}

void DrawHandler::putPixel(int x, int y, Uint32 couleur)
{
     Uint8 *p = (Uint8*)ECRAN->pixels + y * ECRAN->pitch + x * 4;
    *(Uint32*)p = couleur;
}

void DrawHandler::draw(Point p)
{
    putPixel(p.getX(), p.getY(), m_color);
}

void DrawHandler::setColor(Uint32 color)
{
    m_color = color;
}

DrawHandler::~DrawHandler()
{
    //dtor
}
