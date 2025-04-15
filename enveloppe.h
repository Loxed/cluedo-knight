#ifndef ENVELOPPE_H_INCLUDED
#define ENVELOPPE_H_INCLUDED

#include "carte.h"

/************************CLASSE ENVELOPPE**************************/

class Enveloppe
{
private:

    Carte m_zone;
    Carte m_ennemi;
    Carte m_arme;


public:
    Enveloppe();
    ~Enveloppe();

    Carte getSalle();
    Carte getEnnemi();
    Carte getArme();
    void setSalle(Carte _salle);
    void setEnnemi(Carte _ennemi);
    void setArme(Carte _arme);
};

#endif // ENVELOPPE_H_INCLUDED

