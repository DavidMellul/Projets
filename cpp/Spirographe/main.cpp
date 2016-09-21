#include "utilities.h"

#include "Point.h"
#include "Droite.h"
#include "DrawHandler.h"
#include "Computer.h"

using namespace std;

#undef main

void reset(Cercle &c, Cercle &c2, Droite &d, double &a);
bool isInWindow(Point p);
bool equals(Point p1, Point p2);


int main(int argc, char* argv[])
{
    if(argc != 1)
    {
        if(argc == 2)
        {
            if(strcmp(argv[1], "/s") != 0)
                exit(0);
        }
    }
    else
    {
        exit(0);
    }
    srand(time(NULL));

    SDL_SetVideoMode(0,0, 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    SDL_WM_SetCaption("Spirographe - David Mellul", NULL);
    SDL_ShowCursor(false);

    vector<Point>Tableau;

    Cercle c;
    Cercle c2;
    Droite d;

    double tours = 0;
    double angle = 0;

    bool quit = false;
    bool paused = false;


    reset(c,c2,d, angle);
    DrawHandler::setColor(0xFF00FF);

    while(!quit)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    quit = true;
                break;

                case SDL_KEYDOWN:
                    quit = true;
                break;

                case SDL_MOUSEMOTION:
                    if(SDL_GetTicks() > 1000)
                        quit = true;
                break;

                default: break;
            }
        }
        if(!paused)
        {
          tours++;
          SDL_FillRect(ECRAN, NULL, BLACK);
          DrawHandler::startDraw();
                Computer::Rotate(c2.getCenter(), c.getCenter(),(M_PI*0.10)/180);
                d.setOrigine(c2.getCenter());
                d.setExtremite(Point(c2.getCx()+(c2.getRadius()*2), c2.getCy()));
                Computer::Rotate(d.getExtremite(), d.getOrigine(), (M_PI*angle)*0.01*tours/180);
                Tableau.push_back(d.getExtremite());
                for(Point p : Tableau)
                    if(isInWindow(p))
                        DrawHandler::draw(p);
                if(Tableau.size() > 1000 && equals(d.getExtremite(), Tableau.at(1))  )
                {
                   Tableau.clear();
                   reset(c, c2, d, angle);
                   SDL_Delay(2000);
                }
           DrawHandler::endDraw();
           SDL_Flip(ECRAN);
        }

    }
    return 0;
}

void reset(Cercle& c, Cercle& c2, Droite& d, double &a)
{
    const SDL_VideoInfo *vi = SDL_GetVideoInfo();

    int cRadius = RAND(50, 300);
    int c2Radius = RAND(-cRadius/2, cRadius/2);
    int tailleStylo = RAND(-c2Radius*2, c2Radius*2);

    c.setCenter(Point(vi->current_w/2, vi->current_h/2));
    c.setRadius(cRadius);

    c2.setCenter(Point(c.getCx()+cRadius+c2Radius, c.getCy()));
    c2.setRadius(abs(c2Radius));
    Computer::Rotate(c2.getCenter(), c.getCenter(), RAND(-360,360));

    d.setOrigine(c2.getCenter());
    d.setExtremite(Point(c2.getCx()+(tailleStylo), c2.getCy()));

    a = RAND(-360,360);
}

bool isInWindow(Point p)
{
    int x = p.getX();
    int y = p.getY();
    const SDL_VideoInfo *vi = SDL_GetVideoInfo();

    if(x > 0 && x < vi->current_w
    && y > 0 && y < vi->current_h)
        return true;
    return false;
}

bool equals(Point p1, Point p2)
{
    int diffX = p1.getX() - p2.getX();
    int diffY = p1.getY() - p2.getY();
   return diffX >= -1 && diffX <= 1 && diffY >= -1 && diffY <= 1;
}

