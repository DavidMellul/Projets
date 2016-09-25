#ifndef PARTICULE_H
#define PARTICULE_H

#include <SDL/SDL.h>
#include "utilities.h"

class Particule
{
    public:
        Particule();
        Particule(int x, int y, int vx, int vy, int vie);
        ~Particule();

        bool isAlive();
        void update();

        int getVie();
        SDL_Rect *getRect();

        void reset(int x, int y, int vx, int vy, int vie);
   protected:

    private:
        int x;
        int y;
        int vx;
        int vy;
        int vie;
};

#endif // PARTICULE_H
