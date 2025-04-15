#ifndef CLR_H_INCLUDED
#define CLR_H_INCLUDED

#include "header.h"

using std::cout;
using std::endl;
using std::string;

class Msc
{

private: // encapsulation
    std::map<string, SAMPLE *> m_msc;

protected: // heritage

public:
    Msc()
    {
        cout << "- ctor musiques" << endl;
        charger_sample("Main Menu","RESSOURCES/MSC/Main Menu.wav");
        charger_sample("Forgotten Crossroads","RESSOURCES/MSC/Forgotten Crossroads.wav");
        charger_sample("City of Tears","RESSOURCES/MSC/City of Tears.wav");
        charger_sample("Crystal Peaks","RESSOURCES/MSC/Crystal Peaks.wav");
        charger_sample("Greenpath","RESSOURCES/MSC/Greenpath.wav");
        charger_sample("Kingdom's Edge","RESSOURCES/MSC/Kingdom's Edge.wav");
        charger_sample("Queen's Gardens","RESSOURCES/MSC/Queen's Gardens.wav");
        charger_sample("Resting Grounds","RESSOURCES/MSC/Resting Grounds.wav");

    }

    ~Msc()
    {
        cout << "~ dtor musiques:" <<endl;
    }




    ///getters

    SAMPLE * get_msc(string _nom)
    {

        //convertir string en char *
        std::vector<char> chaine(_nom.begin(), _nom.end());
        chaine.push_back('\0');

        for(auto & x:m_msc)
        {
            //cout  << x.first << " " << x.second << endl;
            if(x.first == _nom) return x.second; // si c'est le bon son return
        }

        allegro_message("music ''%s'' was not found.",&*chaine.begin());

        return NULL;

    }


    ///pas besoin de setters

    //methodes
    void charger_sample(string _nom, string _chemin)
    {
        //nom
        std::vector<char> nom(_nom.begin(), _nom.end());
        nom.push_back('\0');

        //chemin
        std::vector<char> chemin(_chemin.begin(), _chemin.end());
        chemin.push_back('\0');


        m_msc[&*nom.begin()]=load_sample(&*chemin.begin());

        ///blindage
        if(!m_msc.find(&*nom.begin())->second)
            allegro_message("music '%s' could not load or find path '%s'.",&*nom.begin(),&*chemin.begin());
        else
            cout << "\tsample '" << _nom << "' was successfully created." << endl;
    }

};



#endif // CLR_H_INCLUDED
