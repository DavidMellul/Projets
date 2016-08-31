#include "Emulateur.h"
#include <SDL/SDL.h>

#ifdef main
#undef main
#endif  //pour l'output sur la console
using namespace std;

bool handleInput(Emulateur *chip8);
void draw(Emulateur *chip8);
void help();

int main(int argc, char* argv[])
{
    Emulateur *chip8 = new Emulateur();
    chip8->initialize();

    try
    {
        if(argc > 1)
        {
            if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
                help();
            else if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0)
            {
                chip8->loadGame(argv[2]);
                 SDL_Surface *Fenetre = NULL;
                 SDL_Init(SDL_INIT_VIDEO);
                 Fenetre = SDL_SetVideoMode(640, 320, 32, 0);
                 SDL_WM_SetCaption("Chip8 emulator - David Mellul",NULL);

                while(handleInput(chip8)) //Boucle principale
                {
                    if(chip8->update())
                    {
                        draw(chip8);
                        chip8->setDrawState(false);
                    }
                    chip8->emulateCycle();
               }
            }
            else
                help();
        }
        else
            help();
    }catch(logic_error e)
    {
        cerr << e.what() << endl;
    }




    return 0;
}

bool handleInput(Emulateur *chip8)
{
    SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    return false;
                break;

                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            return false;
                        break;

                        case SDLK_1:
                            chip8->setKeyState(0, 1);
                        break;

                        case SDLK_2:
                            chip8->setKeyState(1, 1);
                        break;

                        case SDLK_3:
                            chip8->setKeyState(2, 1);
                        break;

                        case SDLK_c:
                            chip8->setKeyState(3, 1);
                        break;

                        case SDLK_4:
                            chip8->setKeyState(4, 1);
                        break;

                        case SDLK_5:
                            chip8->setKeyState(5, 1);
                        break;

                        case SDLK_6:
                            chip8->setKeyState(6, 1);
                        break;

                        case SDLK_d:
                            chip8->setKeyState(7, 1);
                        break;

                        case SDLK_7:
                            chip8->setKeyState(8, 1);
                        break;

                        case SDLK_8:
                            chip8->setKeyState(9, 1);
                        break;

                        case SDLK_9:
                            chip8->setKeyState(10, 1);
                        break;

                        case SDLK_e:
                            chip8->setKeyState(11, 1);
                        break;

                        case SDLK_a:
                            chip8->setKeyState(12, 1);
                        break;

                        case SDLK_0:
                            chip8->setKeyState(13, 1);
                        break;

                        case SDLK_b:
                            chip8->setKeyState(14, 1);
                        break;

                        case SDLK_f:
                            chip8->setKeyState(15, 1);
                        break;

                        default: break;
                    }
                break;

                case SDL_KEYUP:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            return false;
                        break;

                        case SDLK_1:
                            chip8->setKeyState(0, 0);
                        break;

                        case SDLK_2:
                            chip8->setKeyState(1, 0);
                        break;

                        case SDLK_3:
                            chip8->setKeyState(2, 0);
                        break;

                        case SDLK_c:
                            chip8->setKeyState(3, 0);
                        break;

                        case SDLK_4:
                            chip8->setKeyState(4, 0);
                        break;

                        case SDLK_5:
                            chip8->setKeyState(5, 0);
                        break;

                        case SDLK_6:
                            chip8->setKeyState(6, 0);
                        break;

                        case SDLK_d:
                            chip8->setKeyState(7, 0);
                        break;

                        case SDLK_7:
                            chip8->setKeyState(8, 0);
                        break;

                        case SDLK_8:
                            chip8->setKeyState(9, 0);
                        break;

                        case SDLK_9:
                            chip8->setKeyState(10, 0);
                        break;

                        case SDLK_e:
                            chip8->setKeyState(11, 0);
                        break;

                        case SDLK_a:
                            chip8->setKeyState(12, 0);
                        break;

                        case SDLK_0:
                            chip8->setKeyState(13, 0);
                        break;

                        case SDLK_b:
                            chip8->setKeyState(14, 0);
                        break;

                        case SDLK_f:
                            chip8->setKeyState(15, 0);
                        break;

                        default: break;
                    }
                break;

            }
        }
        return true;
}

void draw(Emulateur* chip8)
{
    unsigned char* gfx = chip8->getGfx();
    Uint32 color;

    SDL_Surface *screen = SDL_GetVideoSurface();
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = 10;
    r.y = 10;

    for(int y = 0; y < 32; ++y)
    {
      for(int x = 0; x < 64; ++x)
        {
			if(gfx[(y*64) + x] == 0)
				color = SDL_MapRGB(screen->format, 0, 0, 0);
			else
				color = SDL_MapRGB(screen->format, 255, 255, 255);

            r.x = x * 10;
            r.y = y * 10;
			SDL_FillRect(screen, &r, color);
        }
    }

    SDL_Flip(screen);
    SDL_Delay(15); //Processeur 60 Hz du chip8 , 15 ~= 16.6
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tChip8 - Un émulateur de chip8" << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tChip8 -f [FICHIER] | -h" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tChip8 est un programme réalisé en C++ permettant d'émuler l'interprêteur chip8 des années 1970." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-f | --file [FICHIER] :" << std::endl;
    std::cout << "\t\tPermet de spécifier le fichier d'entrée contenant les instructions en héxadécimal." << std::endl;
    std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
