#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <fstream>

using namespace std;

void crypterChaine(string& str); //L'algorithme de cryptage permet également de décrypter une chaîne cryptée
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
               cout << "Fichier finalisé." << endl;
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
        throw logic_error("Impossible de lire le fichier spécifié.");
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
        throw logic_error("Impossible d'écrire dans le fichier spécifié.");
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
    std::cout << "\tROT47 - Un crypteur/decrypteur de chaîne et fichier." << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tROT47 -c \"[CHAINE]\" | -f [FICHIER] | -h" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tROT47 est un programme réalisé en C++ permettant de crypter et decrypter une chaîne ou un fichier en utilisant le célèbre algorithme de César en rotation par 47." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-f | --file [FICHIER] :" << std::endl;
    std::cout << "\t\tPermet de spécifier le fichier d'entrée contenant le message à encrypter/decrypter." << std::endl;
    std::cout << "\t-c | --chaine \"[CHAINE]\"" << std::endl;
    std::cout << "\t\tPermet de spécifier directement la chaine à crypter/décrypter." << std::endl;
    std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
