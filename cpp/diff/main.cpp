#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

void chargerFichierDansVecteur(string filepath, vector<string> &vecteur) throw (logic_error);
void afficherDifferences(vector<string> &v1, vector<string> &v2);
int plusGrandVecteur(vector<string> &v1, vector<string> &v2);
void help();

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
            if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
            {
              help();
            }
            else
            {
                 help();
            }
    }
    else if(argc == 3)
    {
        vector<string> fichierSource;
        vector<string> fichierDestination;

        cout << "-----Lancement de l'analyse...-----" << endl;

        try
        {
            chargerFichierDansVecteur(argv[1], fichierSource);
            chargerFichierDansVecteur(argv[2], fichierDestination);

            afficherDifferences(fichierSource, fichierDestination);
        }catch(std::exception &e)
        {
            cerr << e.what() << endl;
        }

        cout << "-----Fin de l'analyse...-----" << endl;
    }
    else
    {
        help();
    }
    return 0;
}

void chargerFichierDansVecteur(string filepath, vector<string>& vecteur) throw (logic_error)
{
    ifstream flux;
    flux.open(filepath.c_str(), ifstream::in);

    if(!flux.is_open())
        throw logic_error("Impossible d'accèder au fichier spécifié : "+filepath);
    else
    {
        while(!flux.eof())
        {
            string ligne = "";
            getline(flux,ligne);
            vecteur.push_back(ligne);
        }
        flux.close();
    }
}

void afficherDifferences(vector<string>& v1, vector<string>& v2)
{
    for(int i = 0; i < plusGrandVecteur(v1, v2); i++)
    {
        if(i < v1.size() && i < v2.size())
        {
            if(strcmp(v1[i].c_str(), v2[i].c_str()) != 0)
            {
                cout << i+1 << "c" << i+1 << endl;
                cout << "< " << v1[i] << endl;
                cout << "---" << endl;
                cout << ">" << v2[i] << endl;
            }
        }
        else if(i > v1.size() && i < v2.size())
        {
            cout << v1.size() << "a" << i << "," << v2.size() << endl;
            for(int j = i-1; j < v2.size(); j++)
                cout << "> " << v2[j] << endl;
            i = v2.size();
        }
        else if(i < v1.size() && i > v2.size())
        {
            cout << i << "," << v1.size() << "d" << v2.size() << endl;
            for(int j = i-1; j < v1.size(); j++)
                cout << "< " << v1[j] << endl;

            i = v1.size();
        }
    }
}

int plusGrandVecteur(vector<string>& v1, vector<string>& v2)
{
    return (v1.size() > v2.size()) ? v1.size():v2.size();
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tdiff - Un analyseur de différence entre deux fichiers." << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tdiff [FICHIER_1] [FICHIER_2]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tdiff est un programme réalisé en C++ permettant d'afficher les différences entre deux fichiers." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
