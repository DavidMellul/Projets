#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <stack>
#include <cstring>
#include <cstdio>
#include <algorithm>

void interpreterFichier(std::string file) throw (std::logic_error);
void interpreterCode(std::string str) throw (std::logic_error);
void verifierIntegrite(std::string str) throw (std::logic_error);
void help();

int main(int argc, char* argv[])
{
    try
    {
        if(argc == 1)
            {
                help();
            }
        else
            {
                if(strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"--code") == 0)
                {
                    if(argc == 3)
                    {
                        interpreterCode(argv[2]);
                    }
                    else
                    {
                        help();
                    }
                }
                else if(strcmp(argv[1],"-f") == 0 || strcmp(argv[1],"--file") == 0)
                {
                    if(argc == 3)
                    {
                        interpreterFichier(argv[2]);
                    }
                    else
                    {
                        help();
                    }
                }
                else if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
                {
                    help();
                }
                else
                {
                    help();
                }
            }
    }catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}


void interpreterFichier(std::string file) throw (std::logic_error)
{
    std::ifstream flux;
    flux.open(file.c_str(), std::ifstream::in);

    if(!flux.is_open())
        throw std::logic_error("Impossible d'ouvrir le fichier spécifié.");
    else
    {
        std::string input = "";
        while(!flux.eof())
        {
            char c;
            flux.get(c);
            input += c;
        }
        flux.close();
        interpreterCode(input);
    }
}

void interpreterCode(std::string str) throw (std::logic_error)
{
        str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
        verifierIntegrite(str);

        std::cout << "-----Lancement de l'interprêteur-----" << std::endl << std::endl;
        std::string input = str;
        std::vector<char> output(30000, 0);
        char* pointeurSortie = &output[0];
        char* pointeurEntree = &input[0];

        while(*pointeurEntree)
        {
            switch(*pointeurEntree)
            {
                case '>': pointeurSortie++; break;
                case '<': pointeurSortie--; break;
                case '+': (*pointeurSortie)++; break;
                case '-': (*pointeurSortie)--; break;
                case '.':  putchar(*pointeurSortie); break;
                case ',': *pointeurSortie = getchar(); break;
                case '[':
                        {
                            if(*pointeurSortie == 0)
                            {
                                int nbCouples = 1;
                                do
                                {
                                    pointeurEntree++;
                                    if(*pointeurEntree == '[') nbCouples++;
                                    else if(*pointeurEntree == ']') nbCouples--;
                                }while(nbCouples != 0);
                            }
                        }
                        break;
                case ']':
                         {
                            int nbCouples = 0;
                            do
                            {
                                if(*pointeurEntree == '[') nbCouples++;
                                else if(*pointeurEntree == ']') nbCouples--;
                                pointeurEntree--;
                            }while(nbCouples != 0);
                         }
                        break;
                default: break;
            }
            pointeurEntree++;
        }
             std::cout << std::endl << "-----Fin du programme-----" << std::endl << std::endl;
}


void verifierIntegrite(std::string str) throw (std::logic_error)
{
    int nbCouples = 0;

    for(char c : str)
    {
        switch(c)
        {
            case '[': nbCouples++; break;
            case ']': nbCouples--; break;
            default: break;
        }
    }

  if(nbCouples > 0)
        throw std::logic_error("Un symbole ']' est manquant.");
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tBFI - Un interprêteur de Brainfuck" << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tBFI -c \"[CODE]\" | -f [FICHIER] | -h" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tBFI est un programme réalisé en C++ permettant d'interprêter et d'exécuter des programmes écrits en brainfuck." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-f | --file [FICHIER] :" << std::endl;
    std::cout << "\t\tPermet de spécifier le fichier d'entrée contenant le code écrit en brainfuck." << std::endl;
    std::cout << "\t-c | --code \"[CODE]\"" << std::endl;
    std::cout << "\t\tPermet de spécifier directement le code en brainfuck à exécuter." << std::endl;
    std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
