#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <ctime>
#include <vector>
#include <thread>


#define M_PI 3.14

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

#endif // UTILITIES_H_INCLUDED
