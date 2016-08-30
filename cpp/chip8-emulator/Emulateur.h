#ifndef EMULATEUR_H
#define EMULATEUR_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include <SDL/SDL.h>

using namespace std;

class Emulateur
{
    public:
        Emulateur();
        ~Emulateur();
        void initialize();
        void loadGame(string game) throw(logic_error);
        void emulateCycle();
        bool update();
        unsigned char* getGfx();
        void setKeyState(int k, int state);
        void setDrawState(bool state);


    protected:

    private:
        unsigned short opcode; //code d'instruction processeur
        unsigned char memoire[4096]; //mémoire
        unsigned char V[16]; //registres

        unsigned short I; //index de registre
        unsigned short pc; //Compteur de programmes

        unsigned char gfx[2048]; //mémoire graphique

        unsigned char delay_timer; //compteur de fps
        unsigned char sound_timer; //compteur de son

        unsigned short _stack[16]; //pile
        unsigned short _sp; //pointeur de pile

        unsigned char key[16];  //clavier

        unsigned char chip8_fontset[80]; //police

        int bufferSize;
        char *buffer;
        bool drawFlag;
};

#endif // EMULATEUR_H
