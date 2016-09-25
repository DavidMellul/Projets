#include "Manager.h"

#undef main //output console

using namespace std;

bool handleInput(Manager &m);
void handleFps(Uint32 start);
void handleMouse(int x, int y, Manager &m);
void draw(Manager &m);

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0);
    SDL_WM_SetCaption("Emetteur de particules - David Mellul", NULL);

    Uint32 start;
    Manager m;

    while(handleInput(m))
    {
        start = SDL_GetTicks();
        m.update();
        draw(m);
        handleFps(start);
    }

    return 0;
}

bool handleInput(Manager &m)
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
            return false;

        else if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE)
                return false;
            else if(e.key.keysym.sym == SDLK_p)
                m.pause();
        }

        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.button.button == SDL_BUTTON_LEFT)
            {
                handleMouse(e.motion.x, e.motion.y, m);
            }
            else
            {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    m.sub();
                }
            }
        }
    }

    return true;
}

void draw(Manager &m)
{
    SDL_Surface *screen = SDL_GetVideoSurface();

    SDL_FillRect(screen, NULL, WHITE);

    for(Emetteur &em : m.getEmetteurs())
    {
        for(Particule &p : em.getParticules())
        {
            SDL_FillRect(screen, p.getRect(), BLACK);
        }
    }
    SDL_Flip(screen);
}

void handleFps(Uint32 start)
{
    Uint32 tempsEcoule = SDL_GetTicks();

    if(tempsEcoule - start < (SECONDE / FPS))
    {
        SDL_Delay(SECONDE / FPS - (SDL_GetTicks() - start));
    }
}

void handleMouse(int x, int y, Manager &m)
{
    m.add(Emetteur(x,y,NB_PARTICULES,false));
}
