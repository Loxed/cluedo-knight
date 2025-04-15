#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "header.h"
#include "ressources.h"


using std::cout;
using std::endl;
using std::string;
class Plateau
{

private: // encapsulation

    BITMAP * m_plateau;

    //std::vector<std::vector<BITMAP *>> m_cases;

    BITMAP * m_cases[25][25];

    Ressources m_ressources;


protected: // heritage

public:
    Plateau()
    {
        cout << "- ctor plateau" << endl;
        //allouer l'espace au plateau
        m_plateau=create_bitmap(800,800);

        ///mettre les cases dans le plateau
        for (int i=0;i<25;i++)
        {
            for (int j=0;j<25;j++)
            {
                //m_cases[i].push_back(create_bitmap(32,32));
                m_cases[i][j]=create_bitmap(32,32);
            //allouer l'espace
                //m_cases[i].push_back(m_ressources.get_imgs().get_case());

                //cases aléatoires
                m_cases[i][j]=m_ressources.get_imgs().get_case();

                ///mettre les cases sur le plateau
                blit(m_cases[i][j],m_plateau,0,0,32*i,32*j,32,32);
            }
        }

    }

    ~Plateau()
    {
        cout << "~ dtor plateau" << endl;
    }

    //getter
    BITMAP * get_plateau(){return m_plateau;}

    //setter

};


#endif // PLATEAU_H_INCLUDED
