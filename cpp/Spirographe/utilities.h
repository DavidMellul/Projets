#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <ctime>
#include <vector>
#include <thread>


#define M_PI 3.14159265359

//

#define ECRAN SDL_GetVideoSurface()
#define FORMAT ECRAN->format

//

#define DEFAULT_PIXEL_COLOR 0xFFFFFF

//

#define COLOR(A,B,C) SDL_MapRGB(FORMAT, A,B,C)
#define WHITE COLOR(255,255,255)
#define BLACK COLOR(0,0,0)

//

#define RAND(MIN, MAX)  ((rand() % (MAX - MIN +1)) + MIN)
#define MIN(A,B) ((A < B) ? A:B)
#define MAX(A,B) ((A > B) ? A:B)

#define NB_MIN_BRAS 2
#define NB_MAX_BRAS 3

#define MIN_SPEED -100
#define MAX_SPEED 100

#define MIN_TAILLE 1
#define MAX_TAILLE 300

#endif // UTILITIES_H_INCLUDED
