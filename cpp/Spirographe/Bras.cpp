#include "Bras.h"

Bras::Bras()
{
    this->m_Origine = 0;
    this->m_Taille = 0;
    this->m_Vitesse = 0;
}

Bras::Bras(double Taille, double Vitesse, double Origine)
{
    this->m_Taille = Taille;
    this->m_Vitesse = Vitesse;
    this->m_Origine = Origine;
}

void Bras::setTaille(double Taille)
{
    this->m_Taille = Taille;
}

void Bras::setVitesse(double Vitesse)
{
    this->m_Vitesse = Vitesse;
}

void Bras::setOrigine(double Origine)
{
    this->m_Origine = Origine;
}

double Bras::getTaille()
{
    return this->m_Taille;
}

double Bras::getVitesse()
{
    return this->m_Vitesse;
}

double Bras::getOrigine()
{
    return this->m_Origine;
}

Bras::~Bras()
{
    //dtor
}
