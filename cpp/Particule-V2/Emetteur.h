#ifndef EMETTEUR_H
#define EMETTEUR_H


#include <iostream>
#include <vector>
#include <ctime>

#include <SDL/SDL.h>
#include "Particule.h"
#include "utilities.h"

using namespace std;
class Emetteur
{
    public:
        Emetteur();
        Emetteur(int x, int y, int n, bool paused);
        ~Emetteur();

        void setPaused(bool state);
        bool getPausedState();
        void setPosition(int x, int y);

        void init();
        void update();

        vector<Particule> getParticules();

    protected:

    private:
        vector<Particule> v;
        int x;
        int y;
        int n;
        bool paused;
};

#endif // EMETTEUR_H
