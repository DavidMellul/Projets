#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <fstream>

using namespace std;

void crypterChaine(string& str); //L'algorithme de cryptage permet �galement de d�crypter une cha�ne crypt�e
void crypterFichier(string filepath) throw (logic_error);
void help();

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--chaine") == 0)
        {
          string input = argv[2];
          crypterChaine(input);
          cout << input << endl;
        }
        else if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0)
        {
            try
            {
               crypterFichier(argv[2]);
               cout << "Fichier finalis�." << endl;
            }catch(exception &e)
            {
                cerr << e.what() << endl;
            }
        }
        else
        {
            help();
        }
    }
    else
    {
        help();
    }
    return 0;
}

void crypterChaine(string& str)
{
    for(int i = 0; i < str.length(); i++)
    {
        char c = str[i];

        if( c >= 33 && c <= 126 )
        {
            if( c >= 33 && c < 79 )
            {
                c += 47;
            }
            else
            {
                c -= 47;
            }
        }

        str[i] = c;
    }
}

void crypterFichier(string filepath) throw (logic_error)
{
    vector<string> source;

    ifstream fichierEntrant;
    ofstream fichierSortant;

    fichierEntrant.open(filepath.c_str(), ifstream::in);
    if(!fichierEntrant.is_open())
        throw logic_error("Impossible de lire le fichier sp�cifi�.");
    else
    {
        while(!fichierEntrant.eof())
        {
            string str = "";
            getline(fichierEntrant, str);
            source.push_back(str);
        }
        fichierEntrant.close();
    }

    fichierSortant.open(filepath.c_str(), ofstream::trunc);
    if(!fichierSortant.is_open())
        throw logic_error("Impossible d'�crire dans le fichier sp�cifi�.");
    else
    {
        for(int i = 0; i < source.size(); i++)
        {
            crypterChaine(source[i]);
            fichierSortant << source[i];
        }
    }
    fichierSortant.close();
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tROT47 - Un crypteur/decrypteur de cha�ne et fichier." << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tROT47 -c \"[CHAINE]\" | -f [FICHIER] | -h" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tROT47 est un programme r�alis� en C++ permettant de crypter et decrypter une cha�ne ou un fichier en utilisant le c�l�bre algorithme de C�sar en rotation par 47." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-f | --file [FICHIER] :" << std::endl;
    std::cout << "\t\tPermet de sp�cifier le fichier d'entr�e contenant le message � encrypter/decrypter." << std::endl;
    std::cout << "\t-c | --chaine \"[CHAINE]\"" << std::endl;
    std::cout << "\t\tPermet de sp�cifier directement la chaine � crypter/d�crypter." << std::endl;
    std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
