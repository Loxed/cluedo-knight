#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "header.h"
#include "carte.h"

/************************CLASSE JOUEUR**************************/

class Joueur
{
private:
    string m_personnage;

    int pos_initiale_x,pos_initiale_y;

    int m_position_x;
    int m_position_y;
    std::string m_nom;

    bool m_alive;
    bool m_joueur_ordinateur;
    int m_score;
    int m_nbr_partie;
    int m_nbr_defaite;
    int m_nbr_victoire;
    int m_niveau;
    int m_deplacement_de;
    std::vector<Carte> m_cartes;
    BITMAP * m_img_joueur;

public:
    Joueur()
    {
        m_img_joueur=create_bitmap(32,32);
        m_personnage="vide";
        m_position_x=8;
        m_position_y=1;
        m_nom="";
        m_alive=true;
        m_score=0;
        m_nbr_partie=0;
        m_nbr_defaite=0;
        m_nbr_victoire=0;
        m_niveau=0;
        m_deplacement_de=0;
    }

    Joueur(string _perso, int _position, std::string _nom, bool _alive, int _score, int _niveau)
        :m_personnage(_perso), m_position_x(8), m_position_y(1), m_nom(_nom), m_alive(true), m_score(_score), m_nbr_partie(0), m_nbr_defaite(0), m_nbr_victoire(0), m_niveau(0),m_deplacement_de(0)
        {
            m_img_joueur=create_bitmap(32,32);
        }
    ~Joueur(){}

    std::string getNom(){return m_nom;}
    int getScore(){return m_score;}
    int getNbrVictoire(){return m_nbr_victoire;}
    int getNbrDefaite(){return m_nbr_defaite;}
    int getNbrPartie(){return m_nbr_partie;}
    int getNiveau(){return m_niveau;}
    Carte getCarte(int i){return m_cartes[i];}
    unsigned int getTaille(){return m_cartes.size();}
    int getPositionX(){return m_position_x;}
    int getPositionY(){return m_position_y;}
    int getDeplacementDe(){return m_deplacement_de;}
    bool getAlive(){return m_alive;}
    BITMAP * get_img_joueur(){return m_img_joueur;}
    string get_personnage(){return m_personnage;}
    int get_pos_initiale_x(){return pos_initiale_x;}
    int get_pos_initiale_y(){return pos_initiale_y;}
    bool get_joueur_ordinateur(){return m_joueur_ordinateur;}


    void setNom(std::string _nom){m_nom=_nom;}
    void setNbrVictoire(int _nbr_victoire){m_nbr_victoire=_nbr_victoire;}
    void setNbrDefaite(int _nbr_defaite){m_nbr_defaite=_nbr_defaite;}
    void setNbrPartie(int _nbr_partie){m_nbr_partie=_nbr_partie;}
    void setNiveau(int _niveau){m_niveau=_niveau;}
    void setScore(int _score){m_score=_score;}
    void setCarte(Carte _carte){m_cartes.push_back(_carte);}
    void setPositionX(int _position_x){m_position_x=_position_x;}
    void setPositionY(int _position_y){m_position_y=_position_y;}
    void setDeplacementDe(int _deplacement_de){m_deplacement_de=_deplacement_de;}
    void setAlive(bool _alive){m_alive = _alive;}
    void set_img_joueur(BITMAP * new_img){m_img_joueur=new_img;}
    void set_personnage(string _nom){m_personnage=_nom;}
    void set_joueur_ordinateur(bool _joueur_ordinateur){m_joueur_ordinateur = _joueur_ordinateur;}

    void set_pos_initiale_x(int x){pos_initiale_x=x;}
    void set_pos_initiale_y(int y){pos_initiale_y=y;}

};

#endif // JOUEUR_H_INCLUDED

