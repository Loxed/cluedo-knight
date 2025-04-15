#ifndef FNT_H_INCLUDED
#define FNT_H_INCLUDED

#include "header.h"

class Fnt
{

private: // encapsulation
    std::map<string, FONT *> m_fonts;

protected: // heritage

public:
    Fnt()
    {
        std::cout << "- ctor Fnt" << std::endl;
        charger_font("T20","RESSOURCES/FNT/T20.pcx",m_fonts);
        charger_font("T30","RESSOURCES/FNT/T30.pcx",m_fonts);
        charger_font("T40","RESSOURCES/FNT/T40.pcx",m_fonts);

        //fleches
        charger_font("F40","RESSOURCES/FNT/F40.pcx",m_fonts);

        //icons
        charger_font("I40","RESSOURCES/FNT/icons40.pcx",m_fonts);




    }

    ~Fnt()
    {
        std::cout << "~ dtor Fnt" << std::endl;
    }

    ///getter
    FONT * get_fnt(string _nom)
    {

        //convertir string en char *
        std::vector<char> chaine(_nom.begin(), _nom.end());
        chaine.push_back('\0');

        for(auto x:m_fonts)
        {
            if(x.first == _nom) return x.second; // si c'est le bon son return
        }

        allegro_message("font ''%s'' was not found.",&*chaine.begin());

        return font;
    }

    //methodes
    void charger_font(string _nom, string _chemin, std::map<string, FONT *> & m_fonts)
    {
        //nom
        std::vector<char> nom(_nom.begin(), _nom.end());
        nom.push_back('\0');

        //chemin
        std::vector<char> chemin(_chemin.begin(), _chemin.end());
        chemin.push_back('\0');


        m_fonts[&*nom.begin()]=load_font(&*chemin.begin(),NULL,NULL);

        ///blindage
        if(!m_fonts.find(&*nom.begin())->second)
            allegro_message("font '%s' could not load or find path '%s'.",&*nom.begin(),&*chemin.begin());
        else
            cout << "\tfont '" << _nom << "' was successfully created." << endl;
    }

};


#endif // FNT_H_INCLUDED
