#include "header.h"
#include "carte.h"

Carte::Carte()
{

}

Carte::Carte(std::string _nom)
    :m_nom(_nom)
{

}

Carte::~Carte()
{

}

std::string Carte::getNom()
{
    return m_nom;
}


void Carte::setNom(std::string _nom)
{
    m_nom = _nom;
}

