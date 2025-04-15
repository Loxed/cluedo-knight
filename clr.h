#ifndef CLR_H
#define CLR_H

#include "header.h"

using std::cout;
using std::endl;
using std::string;

class Clr
{

private: // encapsulation
    std::map<string, int> m_colors;
protected: // heritage

public:
    Clr()
    {
        std::cout << "- ctor Clr" << std::endl;

        //ajouter couleur
        //m_colors.insert("white",makecol(255,255,255));

        m_colors["white"]=makecol(255,255,255);
        m_colors["black"]=makecol(0,0,0);
        m_colors["magic pink"]=makecol(255,0,255);



    }

    ~Clr()
    {
        std::cout << "~ dtor Clr" << std::endl;

    }

    int get_clr(string _nom)
    {

        //convertir string en char *
        std::vector<char> chaine(_nom.begin(), _nom.end());
        chaine.push_back('\0');

        for(auto & x:m_colors)
        {
            //cout  << x.first << " " << x.second << endl;
            if(x.first == _nom) return x.second; // si c'est le bon son return
        }

        allegro_message("color ''%s'' was not found.",&*chaine.begin());

        return -1;

    }



};


#endif // CLR_H
