#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED


#include "header.h"

using std::cout;
using std::endl;
using std::string;

class Anim
{

private: // encapsulation
    std::vector<BITMAP *> m_tiso;
    std::vector<BITMAP *> m_hornet;
    std::vector<BITMAP *> m_cloth;
    std::vector<BITMAP *> m_knight;
    std::vector<BITMAP *> m_zote;
    std::vector<BITMAP *> m_quirrel;

    std::map<string,int> m_nb_frames;

protected: // heritage

public:
    Anim()
    {
        std::cout << "- ctor Anim" << std::endl;

        charger_anim("RESSOURCES/ANIM/QUIRREL/quirrel",8,m_quirrel);
        m_nb_frames["quirrel"]=8;

        charger_anim("RESSOURCES/ANIM/CLOTH/cloth",5,m_cloth);
        m_nb_frames["cloth"]=5;

        charger_anim("RESSOURCES/ANIM/KNIGHT/knight",16,m_knight);
        m_nb_frames["knight"]=16;

        charger_anim("RESSOURCES/ANIM/ZOTE/zote",16,m_zote);
        m_nb_frames["zote"]=16;

        charger_anim("RESSOURCES/ANIM/TISO/tiso",12,m_tiso);
        m_nb_frames["tiso"]=12;

        charger_anim("RESSOURCES/ANIM/HORNET/hornet",8,m_hornet);
        m_nb_frames["hornet"]=8;

    }

    ~Anim()
    {
        std::cout << "~ dtor Anim" << std::endl;

    }

    ///getter
    int get_nb_frames(string _nom)
    {
        for(auto & x:m_nb_frames)
        {
            if(x.first==_nom) return x.second;
        }

        cout<< "wrong animation name!" << endl;

        return 0;
    }

std::vector<BITMAP *> get_anim(string _nom)
    {
        if(_nom=="quirrel") return m_quirrel;
        if(_nom=="tiso") return m_tiso;
        if(_nom=="hornet") return m_hornet;
        if(_nom=="knight") return m_knight;
        if(_nom=="cloth") return m_cloth;
        if(_nom=="zote") return m_zote;
        else cout<< "wrong animation name!" << endl;

    }

    void charger_anim(string _chemin,int _nb_frames_anims,std::vector<BITMAP*> & m_anims)
    {

    //string stream
        std::ostringstream path;
        string chemin;


        for (int i=0; i<_nb_frames_anims; i++)
        {
            //sprintf (le vider avant)
            path.str("");
            path.clear();

            path << _chemin << i+1 << ".bmp"; // mettre la bonne adresse dedans

            //mettre le sprintf dans string "chemin"
            chemin.clear(); // clear le chemin
            chemin=path.str();//nom



        m_anims.push_back(load_bitmap(chemin.c_str(),NULL));

            ///blindage
            if(!m_anims[i])
                allegro_message("vector could not be loaded by path '%s' in animation.",chemin.c_str());
            else
                cout << "\timage '" << chemin.c_str() << "' was successfully loaded in animation vector." << endl;
        }

    }

    BITMAP * get_frame_perso(string _nom,int i)
    {
        return get_anim(_nom)[(int)i%get_nb_frames(_nom)];
    }

};



#endif // ANIM_H_INCLUDED
