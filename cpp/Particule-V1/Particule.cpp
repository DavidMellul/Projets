#include "Particule.h"

Particule::Particule()
{
    //ctor
}

Particule::Particule(int x, int y, int vx, int vy, int vie)
{
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->vie = vie;
}

Particule::~Particule()
{
    //dtor
}

bool Particule::isAlive()
{
    return (this->vie > 0);
}

int Particule::getVie()
{
    return this->vie;
}

void Particule::update()
{
    if(this->isAlive())
    {
        this->x += this->vx;
        this->y += this->vy;
        this->vie -= 1;
    }
}

SDL_Rect *Particule::getRect()
{
    SDL_Rect *r = new SDL_Rect();

    r->x = this->x;
    r->y = this->y;
    r->w = 3;
    r->h = 3;

    return r;
}

void Particule::reset(int x, int y, int vx, int vy, int vie)
{
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->vie = vie;
}
