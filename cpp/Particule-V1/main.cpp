#include "Emetteur.h"

#undef main //output console

using namespace std;

bool handleInput(Emetteur &em);
void handleFps(Uint32 start);
void handleMouse(int x, int y, Emetteur &em);
void draw(Emetteur &em);

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *Fenetre = SDL_SetVideoMode(640, 480, 32, 0);
    SDL_WM_SetCaption("Emetteur de particules - David Mellul", NULL);

    Emetteur e(DEFAULT_POS_X, DEFAULT_POS_Y , NB_PARTICULES, false);
    e.init();

    Uint32 start;

    while(handleInput(e))
    {
        start = SDL_GetTicks();
        e.update();
        draw(e);
        handleFps(start);
    }

    return 0;
}

bool handleInput(Emetteur &em)
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
                em.setPaused(!em.getPausedState());
        }

        else if(e.type == SDL_MOUSEMOTION)
        {
            handleMouse(e.motion.x, e.motion.y, em);
        }
    }

    return true;
}

void draw(Emetteur &em)
{
    SDL_Surface *screen = SDL_GetVideoSurface();

    SDL_FillRect(screen, NULL, BLACK);

    for(Particule p : em.getParticules())
    {
        SDL_FillRect(screen, p.getRect(), WHITE);
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

void handleMouse(int x, int y, Emetteur &em)
{
   if(x > 0 && x < SCREEN_WIDTH  -1
   && y > 0 && y < SCREEN_HEIGHT -1  )
        em.setPosition(x,y);
   else
        em.setPosition(DEFAULT_POS_X, DEFAULT_POS_Y);
}
