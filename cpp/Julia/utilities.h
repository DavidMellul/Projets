#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <SDL/SDL.h>
#include <iostream>

#include "DrawHandler.h"
#include "Complex.h"

// --------------- MATHS ---------------

#define RAND(MIN, MAX)  ((rand() % (MAX - MIN +1)) + MIN)

// --------------- SDL - UTILES  ----------------

#define ECRAN SDL_GetVideoSurface()
#define FLAGS SDL_HWSURFACE | SDL_DOUBLEBUF

// --------------- SDL - COULEURS  ----------------
#define COLOR(r,g,b) SDL_MapRGB(ECRAN->format, r,g,b)
#define WHITE COLOR(255,255,255)
#define BLACK COLOR(0,0,0)
#define BLUE COLOR(0,0,255)

// --------------- FENETRE ----------------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480





#endif // UTILITIES_H_INCLUDED
