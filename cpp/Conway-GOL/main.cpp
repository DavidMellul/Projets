#include <iostream>
#include <SDL/SDL.h>
#include <ctime>
#include "utilities.h"

#undef main //output console
using namespace std;

bool handleInput(int m[NB_CELL_X][NB_CELL_Y]);
void handleFps(Uint32 start);
void draw(int m[NB_CELL_X][NB_CELL_Y]);

void update(int m[NB_CELL_X][NB_CELL_Y]);
bool isAlive(int x, int y, int m[NB_CELL_X][NB_CELL_Y]);
bool doesntChange(int x, int y, int m[NB_CELL_X][NB_CELL_Y]);
int nbVoisines(int x, int y, int m[NB_CELL_X][NB_CELL_Y]);

void clear(int m[NB_CELL_X][NB_CELL_Y]);
void display(int m[NB_CELL_X][NB_CELL_Y]);
void copy(int m[NB_CELL_X][NB_CELL_Y], int m2[NB_CELL_X][NB_CELL_Y]);
void random(int m[NB_CELL_X][NB_CELL_Y]);

void help();

bool paused = true;
bool drag = false;
bool dragging = false;
bool erasing = false;

int baseX = 0;
int baseY = 0;


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,0);
    SDL_WM_SetCaption("Jeu de la vie - David Mellul", NULL);

    int matrice[NB_CELL_X][NB_CELL_Y];
    clear(matrice);

    Uint32 start;
    srand(time(NULL));

    help();
    while(handleInput(matrice))
    {
        start = SDL_GetTicks();
        if(!paused)
            update(matrice);
        draw(matrice);
        handleFps(start);
    }


    return 0;
}

bool handleInput(int m[NB_CELL_X][NB_CELL_Y])
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
                paused = !paused;
            else if(e.key.keysym.sym == SDLK_d)
                drag = !drag;
            else if(e.key.keysym.sym == SDLK_e)
               {
                  if(paused)
                    clear(m);
               }
            else if(e.key.keysym.sym == SDLK_r)
               {
                  if(paused)
                    random(m);
               }

        }

        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.button.button == SDL_BUTTON_LEFT)
            {
                if(paused)
                {
                    if(!drag)
                     {
                         m[e.motion.x / CELLULE_W][e.motion.y / CELLULE_H] = 1;
                     }
                    else
                    {
                        if(!dragging)
                        {
                            baseX = e.motion.x;
                            baseY = e.motion.y;
                            dragging = true;
                        }
                    }
                }
            }
            else if(e.button.button == SDL_BUTTON_RIGHT)
            {
                if(paused)
                {
                    if(!drag)
                        m[e.motion.x / CELLULE_W][e.motion.y / CELLULE_H] = 0;
                    else if(drag)
                    {
                        if(!dragging)
                        {
                            baseX = e.motion.x;
                            baseY = e.motion.y;
                            dragging = true;
                            erasing = true;
                        }
                    }
                }
            }
        }
        else if(e.type == SDL_MOUSEBUTTONUP)
        {
            if(paused && dragging)
               {
                dragging = false;
                erasing = false;
               }

        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            if(dragging)
            {
                if(e.motion.x > baseX && e.motion.y > baseY)
                {
                    for(int j = baseY; j < e.motion.y; j++)
                    {
                        for(int i = baseX; i < e.motion.x; i++)
                        {
                            m[i / CELLULE_W][j / CELLULE_H] = (erasing ? 0:1);
                        }
                    }
                }
                else if(e.motion.x < baseX && e.motion.y < baseY)
                {
                    for(int j = baseY; j > e.motion.y; j--)
                    {
                        for(int i = baseX; i > e.motion.x; i--)
                        {
                            m[i / CELLULE_W][j / CELLULE_H] = (erasing ? 0:1);
                        }
                    }
                }
                draw(m);
           }
        }

    }

    return true;
}

void update(int m[NB_CELL_X][NB_CELL_Y])
{
    int mat[NB_CELL_X][NB_CELL_Y];
    copy(m, mat);

   for(int j = 0; j < NB_CELL_Y; j++)
    {
        for(int i = 0; i < NB_CELL_X; i++)
         {
            if(isAlive(i,j,m))
                mat[i][j] = 1;
            else if(!doesntChange(i,j,m))
                mat[i][j] = 0;
         }
    }
    copy(mat,m);
}

void draw(int m[NB_CELL_X][NB_CELL_Y])
{
    SDL_Surface *screen = SDL_GetVideoSurface();
    SDL_Rect r;

    SDL_FillRect(screen, NULL, BLACK);

    for(int i = 0; i < NB_CELL_X; i++ )
    {
        for(int j = 0; j < NB_CELL_Y; j++)
        {
            r.x = i*CELLULE_W;
            r.y = j*CELLULE_H;
            r.w = CELLULE_W;
            r.h = CELLULE_H;

            if(m[i][j] == 1)
                SDL_FillRect(screen, &r, WHITE);
        }
    }

    for(int i = 0; i < SCREEN_HEIGHT; i += CELLULE_H) // Grille - Lignes
    {
        r.x = 0;
        r.y = i;
        r.w = SCREEN_WIDTH;
        r.h = 1;
        SDL_FillRect(screen, &r, BLUE);
    }

    for(int i = 0; i < SCREEN_WIDTH; i+= CELLULE_W) // Grille - Colonnes
    {
        r.x = i;
        r.y = 0;
        r.w = 1;
        r.h = SCREEN_HEIGHT;
        SDL_FillRect(screen, &r, BLUE);
    }

    SDL_Flip(screen);
    SDL_Delay(50);
}


int nbVoisines(int x, int y, int m[NB_CELL_X][NB_CELL_Y])
{
    int n = 0;

        if(m[x-1][y] == 1 && x > 0)
        {
            n++;     // gauche
        }
        if(m[x+1][y] == 1 && x < NB_CELL_X -1)
        {
            n++;    // droite
        }
        if(m[x][y+1] == 1 && y < NB_CELL_Y -1)
        {
            n++;     // bas
        }
        if(m[x][y-1] == 1 && y > 0)
        {
            n++;     // haut
        }
        if(m[x-1][y-1] == 1 && y > 0 && x > 0)
        {
            n++;   // diagonale haute gauche
        }
        if(m[x+1][y-1] == 1 && x < NB_CELL_X -1 && y > 0 )
        {
            n++;   // diagonale haute droite
        }
        if(m[x-1][y+1] == 1 && x > 0 && y < NB_CELL_Y -1)
        {
            n++;   // diagonale basse gauche
        }
        if(m[x+1][y+1] == 1 && x < NB_CELL_X -1 && y < NB_CELL_Y -1 )
        {
            n++;   // diagonale basse droite
        }

    return n;
}

bool isAlive(int x, int y, int m[NB_CELL_X][NB_CELL_Y])
{
   return (nbVoisines(x,y,m) == 3);
}

bool doesntChange(int x, int y, int m[NB_CELL_X][NB_CELL_Y])
{
    return (nbVoisines(x,y,m) == 2);
}

void clear(int m[NB_CELL_X][NB_CELL_Y])
{
     for(int j = 0; j < NB_CELL_Y; j++)
    {
        for(int i = 0; i < NB_CELL_X; i++)
         {
            m[i][j] = 0;
         }
    }
}

void display(int m[NB_CELL_X][NB_CELL_Y])
{
    for(int j = 0; j < NB_CELL_Y; j++)
    {
        for(int i = 0; i < NB_CELL_X; i++)
         {
            cout << m[i][j];
            cout << (i == NB_CELL_X -1 ? "":",");
         }
        cout << endl;
    }
}

void copy(int m[NB_CELL_X][NB_CELL_Y], int m2[NB_CELL_X][NB_CELL_Y])
{
    for(int j = 0; j < NB_CELL_Y; j++)
    {
        for(int i = 0; i < NB_CELL_X; i++)
         {
             m2[i][j] = m[i][j];
         }
    }
}

void handleFps(Uint32 start)
{
    Uint32 tempsEcoule = SDL_GetTicks();

    if(tempsEcoule - start < (SECONDE / FPS))
    {
        SDL_Delay(SECONDE / FPS - (SDL_GetTicks() - start));
    }
}

void random(int m[NB_CELL_X][NB_CELL_Y])
{
    clear(m);

    for(int i = 0; i < NB_CELL_X; i++)
        for(int j = 0; j < NB_CELL_Y; j++)
            m[i][j] = RAND(0,1);

            draw(m);
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tconway - Une simulation du jeu de la vie" << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tconway" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tconway est un programme réalisé en C++ permettant de simuler l'automate cellulaire du jeu de la vie." << std::endl;
    std::cout << "UTILISATION" << std::endl;
    std::cout << "\tp : pause | resume" << std::endl;
    std::cout << "\td : drag enabled | drag disabled" << std::endl;
    std::cout << "\te : erase" << std::endl;
    std::cout << "\tr : random" << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
