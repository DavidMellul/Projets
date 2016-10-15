#include "utilities.h"
#undef main

using namespace std;

int main ( int argc, char** argv )
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,FLAGS);
    SDL_WM_SetCaption("Mandelbrot - David Mellul", nullptr);


    float x1 = -1.5;
    float x2 = 1.5;
    float y1 = -1.5;
    float y2 = 1.5;

    float image_x = SCREEN_WIDTH;
    float image_y = SCREEN_HEIGHT;

    float zoom_x = image_x/(x2 - x1);
    float zoom_y = image_y/(y2 - y1);

    int ITERATIONS_MAX = 50;

    bool running = true;
    bool needsUpdate = true;
    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            break;

                        default: break;
                    }
                    break;
                        case SDL_MOUSEBUTTONDOWN:
                            switch(e.button.button)
                            {
                                case SDL_BUTTON_WHEELUP:
                                    ITERATIONS_MAX++;
                                    needsUpdate = true;
                                    break;
                                case SDL_BUTTON_WHEELDOWN:
                                    ITERATIONS_MAX--;
                                    needsUpdate = true;
                                    break;
                                default: break;
                            }
                            break;
                default: break;
            }
        }
        if(needsUpdate)
        {
           DrawHandler::startDraw();

            for(float i = 0; i < image_x; i++)
            {
                for(float j = 0; j < image_y; j++)
                {
                    Complex c(-0.8,0.156);
                    Complex z(i/zoom_x+x1,j/zoom_y+y1);
                    int iteration = 0;

                    while(iteration < ITERATIONS_MAX && z.module() < 2)
                    {
                        z = z*z;
                        z = z+c;
                        iteration++;
                    }
                   if(iteration < ITERATIONS_MAX)
                   {
                        DrawHandler::setColor(0x000000 | iteration*255/ITERATIONS_MAX);
                   }
                   else if(iteration == ITERATIONS_MAX)
                   {
                        DrawHandler::setColor(0x000000);
                   }
                        DrawHandler::putPixel(i,j);
                }
            }
            SDL_Flip(ECRAN);
            DrawHandler::endDraw();
            needsUpdate = false;
        }

        }

    return 0;
}
