#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED

#include "header.h"

/************************CLASSE CARTE**************************/

class Carte
{
private:
    std::string m_nom;

public:

    Carte();
    Carte(std::string _nom);
    ~Carte();

    void setNom(std::string _nom);

    std::string getNom();

};

#endif // CARTE_H_INCLUDED

