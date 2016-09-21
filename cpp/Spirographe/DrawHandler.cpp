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

void DrawHandler::draw(Droite d)
{
    double x1 = d.getOrigine().getX();
    double x2 = d.getExtremite().getX();

    double y1 = d.getOrigine().getY();
    double y2 = d.getExtremite().getY();

    double x = d.getOrigine().getX();
    double y = d.getOrigine().getY();

    double Dx,Dy;
    double xincr,yincr;
    double erreur;
    double i;

    Dx = abs(x2-x1);
    Dy = abs(y2-y1);

    if(x1<x2)
        xincr = 1;
    else
        xincr = -1;

    if(y1<y2)
        yincr = 1;
    else
        yincr = -1;

  if(Dx>Dy)
  {
      erreur = Dx/2;
      for(double i = 0 ; i < Dx ; i++)
      {
          x += xincr;
          erreur += Dy;
          if(erreur>Dx)
          {
              erreur -= Dx;
              y += yincr;
          }
            putPixel(x, y, m_color);
      }
  }
  else
  {
      erreur = Dy/2;
      for(double i = 0 ; i < Dy ; i++)
      {
          y += yincr;
          erreur += Dx;
          if(erreur>Dy)
          {
              erreur -= Dy;
              x += xincr;
          }
        putPixel(x, y, m_color);
        }
  }

    putPixel(x1, y1, m_color);
    putPixel(x2, y2, m_color);

}

void DrawHandler::draw(Cercle c)
{
    double x = c.getRadius();
    double y = 0;
    double err = 0;
    double x0 = c.getCx();
    double y0 = c.getCy();

    while (x >= y)
    {
        putPixel(x0 + x, y0 + y, m_color);
        putPixel(x0 + y, y0 + x,m_color);
        putPixel(x0 - y, y0 + x, m_color);
        putPixel(x0 - x, y0 + y, m_color);
        putPixel(x0 - x, y0 - y, m_color);
        putPixel(x0 - y, y0 - x, m_color);
        putPixel(x0 + y, y0 - x, m_color);
        putPixel(x0 + x, y0 - y, m_color);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}

void DrawHandler::setColor(Uint32 color)
{
    m_color = color;
}

DrawHandler::~DrawHandler()
{
    //dtor
}
