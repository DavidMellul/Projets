#include "Manager.h"

using namespace std;

Manager::Manager()
{
    this->paused = false;
}

void Manager::add(Emetteur e)
{
    e.setPaused(this->paused);
    this->liste.push_back(e);
    this->liste.back().init();
}

void Manager::sub()
{
    if(this->liste.size() > 0)
        this->liste.erase(this->liste.cend());
}

void Manager::pause()
{
    this->paused = !this->paused;

    for(Emetteur &e : this->liste)
        e.setPaused(!e.getPausedState());
}

void Manager::update()
{
    for(Emetteur &e : this->liste)
        e.update();
}

vector<Emetteur> Manager::getEmetteurs()
{
    return this->liste;
}

bool Manager::getPausedState()
{
    return this->paused;
}

Manager::~Manager()
{
    //dtor
}
