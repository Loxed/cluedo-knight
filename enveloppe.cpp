#include "header.h"
#include "enveloppe.h"

Enveloppe::Enveloppe()
{

}

Enveloppe::~Enveloppe()
{

}

Carte Enveloppe::getSalle()
{
    return m_zone;
}

Carte Enveloppe::getEnnemi()
{
    return m_ennemi;
}

Carte Enveloppe::getArme()
{
    return m_arme;
}

void Enveloppe::setSalle(Carte _salle)
{
    m_zone = _salle;
}

void Enveloppe::setEnnemi(Carte _ennemi)
{
    m_ennemi = _ennemi;
}

void Enveloppe::setArme(Carte _arme)
{
    m_arme = _arme;
}

