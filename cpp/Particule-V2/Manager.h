#ifndef MANAGER_H
#define MANAGER_H

#include "Emetteur.h"

using namespace std;

class Manager
{
    public:
        Manager();
        ~Manager();

        void add(Emetteur e);
        void sub();
        void pause();

        void update();
        bool getPausedState();
        vector<Emetteur> getEmetteurs();
    protected:

    private:
        vector<Emetteur> liste;
        bool paused;
};

#endif // MANAGER_H
