#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

// --------------- ARITHMETIQUE ----------------
#define RAND(MIN, MAX)  ((rand() % (MAX - MIN +1)) + MIN)

// --------------- SDL - COULEURS  ----------------
#define COLOR(r,g,b) SDL_MapRGB(SDL_GetVideoSurface()->format, r,g,b)
#define WHITE COLOR(255,255,255)
#define BLACK COLOR(0,0,0)

// --------------- FRAME RATE ----------------
#define FPS 30
#define SECONDE 1000

// --------------- FENETRE ----------------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// --------------- PARTICULES ----------------
#define NB_PARTICULES 100

#define VX_MIN -5
#define VX_MAX 5

#define VY_MIN -3
#define VY_MAX 5

#define P_WIDTH 3
#define P_HEIGHT 3

#define LIFE_MIN 1
#define LIFE_MAX 50

#define DEFAULT_POS_X SCREEN_WIDTH / 2
#define DEFAULT_POS_Y SCREEN_HEIGHT / 2


#endif // UTILITIES_H_INCLUDED
