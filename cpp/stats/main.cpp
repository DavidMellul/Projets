#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

void chargerFichierDansVecteur(string filepath, vector<string> &vecteur) throw (logic_error);
int nbCaracteres(vector<string> &v);
int nbCaracteresWSpaces(vector<string> &v);
int nbMots(vector<string> &v);
int nbParagraphes(vector<string> &v);
void afficherStatistiques(vector<string> &v);

void help();

int main(int argc, char* argv[])
{
    vector<string> fichierSource;

    if(argc == 2)
    {
            if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
            {
              help();
            }
            else
            {
                try
                {
                    chargerFichierDansVecteur(argv[1], fichierSource);
                    afficherStatistiques(fichierSource);
                }catch(exception &e)
                {
                    cerr << e.what();
                }
            }
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

int nbCaracteres(vector<string> &v)
{
    int nb = 0;

    for(string s : v)
    {
        for(char c : s)
        {
             nb++;
        }
    }
    return nb;
}

int nbCaracteresWSpaces(vector<string> &v)
{
    int nb = 0;

    for(string s : v)
    {
        for(char c : s)
        {
            if(c != ' ' && c != '\t' && c != '\0')
             nb++;
        }
    }
    return nb;
}

int nbMots(vector<string> &v)
{
  int nb = 0;
  bool word = false;

  for(string s : v)
  {
      for(int i = 0; i < s.length() ; i++)
       {
           if( isspace(s[i]) || s[i] == '\'' || s[i] == '.' || s[i] == ',' || s[i] == '!' || s[i] == '?' || s[i] == ':' || s[i] == ';')
                word = false;
            else
            {
                if(word == false)
                    nb++;

                word = true;
            }
       }
  }


    return nb;
}

int nbParagraphes(vector<string> &v)
{
   int nb = 0;
   int nbP = 0;

    for(string s : v)
    {
        for(char c : s)
        {
             if(c == '\n' && nbP == 1)
             {
                 nb++;
                 nbP--;
             }
             else if(c == '\n' && nbP == 0)
             {
                 nbP++;
             }
        }
    }
    return nb;
}

void afficherStatistiques(vector<string> &v)
{
    cout << "Analyse en cours..." << endl;
    cout << "+--------------------------------------+----+" << endl;
    cout << "| Nombre de caractères               : . " << nbCaracteres(v) << "|" << endl;
    cout << "| Nombre de caracteres (hors espace) : . " << nbCaracteresWSpaces(v) << "|" << endl;
    cout << "| Nombre de mots                     : . " << nbMots(v) << "|" << endl;
    cout << "| Nombre de paragraphes              : . " << nbParagraphes(v) << "|" << endl;
    cout << "+--------------------------------------+----+" << endl;
    cout << "Fin de l'analyse." << endl;
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tstats - Un afficheur de statistiques sur un fichier texte." << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tstats [FICHIER]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tstats est un programme réalisé en C++ permettant d'afficher des statistiques sur un fichier." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
