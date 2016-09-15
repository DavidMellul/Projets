#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

// --------------- MATHS ---------------

#define RAND(MIN, MAX)  ((rand() % (MAX - MIN +1)) + MIN)

// --------------- SDL - COULEURS  ----------------
#define COLOR(r,g,b) SDL_MapRGB(SDL_GetVideoSurface()->format, r,g,b)
#define WHITE COLOR(255,255,255)
#define BLACK COLOR(0,0,0)
#define BLUE COLOR(0,0,255)

// --------------- FRAME RATE ----------------
#define FPS 10
#define SECONDE 1000

// --------------- FENETRE ----------------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// --------------- PARTICULES ----------------
#define CELLULE_W 15
#define CELLULE_H 15

#define NB_CELL_X SCREEN_WIDTH  / CELLULE_W
#define NB_CELL_Y SCREEN_HEIGHT / CELLULE_H



#endif // UTILITIES_H_INCLUDED
