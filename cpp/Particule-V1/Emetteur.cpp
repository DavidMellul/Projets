#include "Emetteur.h"

Emetteur::Emetteur()
{
    //ctor
}

Emetteur::Emetteur(int x, int y, int n, bool paused)
{
    this->x = x;
    this->y = y;
    this->n = n;
    this->paused = paused;

    srand(time(NULL));
}

void Emetteur::init()
{
    for(int i = 0; i < this->n; i++)
        this->v.push_back(Particule(this->x, this->y, RAND(VX_MIN,VX_MAX), RAND(VY_MIN, VY_MAX), RAND(LIFE_MIN, LIFE_MAX)));
}

void Emetteur::setPosition(int x, int y)
{
    this-> x = x;
    this-> y = y;
}

void Emetteur::setPaused(bool state)
{
    this->paused = state;
}

void Emetteur::update()
{
    if(!paused)
    {
        for(Particule &p : this->v)
        {
            if(!p.isAlive())
                p.reset(this->x, this->y, RAND(VX_MIN,VX_MAX), RAND(VY_MIN, VY_MAX), RAND(LIFE_MIN, LIFE_MAX));
            p.update();
        }
    }
}

bool Emetteur::getPausedState()
{
    return this->paused;
}

vector<Particule> Emetteur::getParticules()
{
    return this->v;
}

Emetteur::~Emetteur()
{
    //dtor
}

