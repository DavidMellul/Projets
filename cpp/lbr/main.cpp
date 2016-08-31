#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

void removeLineBreaks(string &src);
void removeLineBreaks(vector<string> &src);
void display(vector<string> src);

void getFileIntoVector(string filepath, vector<string> &src) throw (logic_error);
void setVectorIntoFile(string filepath, vector<string> &src) throw (logic_error);
void help();

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0)
        {
            try
            {
                vector<string> src;
                getFileIntoVector(argv[2], src);
                removeLineBreaks(src);
                display(src);
            }catch(logic_error e)
            {
                cerr << e.what() << endl;
            }
        }
        else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
            help();
        else
            help();
    }
    else
        help();
    return 0;
}

void removeLineBreaks(string &src)
{
    string strOutput;
    for(char c : src)
    {
        if(c != '\r' && c != '\n')
            strOutput += c;
    }

    src = strOutput;
}

void removeLineBreaks(vector<string>& src)
{
    vector<string> output;
    string out;

    for(string str : src)
    {
        out = str;
        removeLineBreaks(out);
        output.push_back(out);
    }
    src = output;
}

void getFileIntoVector(string filepath, vector<string> &src) throw (logic_error)
{
    ifstream flux;
    flux.open(filepath.c_str(), ifstream::in);

    if(!flux.is_open())
        throw logic_error("Impossible d'accèder au fichier spécifié.");
    else
    {
        string str;
        while(getline(flux, str))
        {
            src.push_back(str);
        }
        flux.close();
    }
}

void setVectorIntoFile(string filepath, vector<string> &src) throw (logic_error)
{
    ofstream flux;
    flux.open(filepath.c_str(), ifstream::out);

    if(!flux.is_open())
        throw logic_error("Impossible d'accèder au fichier spécifié.");
    else
    {
        for(string str : src)
            flux << str;
        flux.close();
    }
}

void display(vector<string> src)
{
    cout << endl;

    for(string str : src)
        cout << str;

    cout << endl;
}

void help()
{
    std::cout << "NAME" << std::endl;
    std::cout << "\tlbr - Un outil pour enlever les retours chariot et autre briseurs de ligne." << std::endl;
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\tlbr -f [FICHIER] | -h" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tlbr est un programme réalisé en C++ permettant de retirer les retours chariot et briseurs de ligne." << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-f | --file [FICHIER] :" << std::endl;
    std::cout << "\t\tPermet de spécifier le fichier d'entrée contenant le code à modifier." << std::endl;
   std::cout << "\t-h | --help" << std::endl;
    std::cout << "\t\tAffiche l'aide." << std::endl;
    std::cout << "AUTHOR" << std::endl;
    std::cout << "\tDavid Mellul" << std::endl;
}
