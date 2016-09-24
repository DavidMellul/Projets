#include "utilities.h"

#include "Point.h"
#include "DrawHandler.h"
#include "Computer.h"
#include "Bras.h"

#undef main

using namespace std;

void reset(vector<Bras>& l, vector<Point>& p, double& period, double& deltaPeriod);
bool isInWindow(Point A);
double dist(Point A, Point B);
void help();

int main()
{
    // Lancement du générateur de nombres aléatoires
    srand(time(NULL));

    // Initialisation de la SDL
    SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN);
    SDL_WM_SetCaption("Spirographe - David Mellul", NULL);
    SDL_ShowCursor(false);

    vector<Bras>  l;
    vector<Point> p;
    double period;
    double deltaPeriod;

    double pX = 0;
    double pY = 0;

    bool quit = false;
    bool paused = false;

    reset(l,p,period, deltaPeriod);
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
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;
                    else if(e.key.keysym.sym == SDLK_p)
                        paused = !paused;
                    else if(e.key.keysym.sym == SDLK_r)
                    {
                        SDL_FillRect(ECRAN, NULL, BLACK);
                        reset(l,p, period, deltaPeriod);
                    }

                    break;
                default: break;
            }
        }
        if(!paused)
        {
          DrawHandler::startDraw();
            period = period + deltaPeriod;

            pX = 0;
            pY = 0;
            for(int i = 0; i < l.size(); i++)
             {
                pX += l.at(i).getTaille() * cos(l.at(i).getVitesse() * period + l.at(i).getOrigine());
                pY += l.at(i).getTaille() * sin(l.at(i).getVitesse() * period + l.at(i).getOrigine());
             }
             pX+= ECRAN->w/2;
             pY+= ECRAN->h/2;

            if(isInWindow(Point(pX, pY)))
                DrawHandler::draw(Point(pX,pY));

            DrawHandler::setColor(dist(Point(pX, pY), Point(ECRAN->w/2,ECRAN->h/2))+0xFF00FF);

           DrawHandler::endDraw();
           SDL_Flip(ECRAN);

           // Actualisation de l'écran

        }
    }
    return 0;
}

void reset(vector<Bras>& l, vector<Point>& p, double& period, double& deltaPeriod)
{
    l.clear(); p.clear(); period = 0; deltaPeriod = 0;

    const SDL_VideoInfo vi = *SDL_GetVideoInfo();
    int nbBras = RAND(NB_MIN_BRAS, NB_MAX_BRAS);

    for(int i = 0; i < nbBras; i++)
    {
        l.push_back(Bras(
                         RAND(MIN_TAILLE, MAX_TAILLE),
                         RAND(MIN_SPEED, MAX_SPEED),
                         0));
        if(i == 0)
            l.back().setOrigine(vi.current_w/2);
        else if(i > 0)
            l.back().setOrigine(l.at(l.size()-2).getOrigine() + l.at(l.size()-2).getTaille());
    }

    deltaPeriod = ((double)rand()/(float)(RAND_MAX)) * 0.001;
}

bool isInWindow(Point A)
{
    const SDL_VideoInfo vi = *SDL_GetVideoInfo();
    if(A.getX() > 0 && A.getX() < vi.current_w
       && A.getY() > 0 && A.getY() < vi.current_h)
        return true;
    return false;
}

double dist(Point A, Point B)
{
    double x1 = MAX(A.getX(), B.getX());
    double y1 = MAX(A.getY(), B.getY());
    double x2 = MIN(A.getX(), B.getX());
    double y2 = MIN(A.getY(), B.getY());

    return sqrt( ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) );
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tspg - Un spirographe" << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tspg" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tspg est un programme réalisé en C++ permettant de reproduire aléatoirement le comportement d'un spirographe." << std::endl;
    std::cout << "UTILISATION" << std::endl;
    std::cout << "\tp : pause | resume" << std::endl;
    std::cout << "\tr : reset" << std::endl;
    std::cout << "\tescape : quitter" << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}


