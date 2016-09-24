#ifndef BRAS_H
#define BRAS_H


class Bras
{
    public:
        Bras();
        Bras(double Taille, double Vitesse, double Origine);

        void setTaille(double Taille);
        void setOrigine(double Origine);
        void setVitesse(double Vitesse);

        double getTaille();
        double getOrigine();
        double getVitesse();
        ~Bras();

    protected:

    private:
        double m_Taille;
        double m_Vitesse;
        double m_Origine;
};

#endif // BRAS_H
