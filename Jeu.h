#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "header.h"
#include "joueur.h"
#include "carte.h"
#include "plateau.h"
#include "enveloppe.h"

using std::cout;
using std::endl;
using std::string;

class Jeu
{

private: // encapsulation


    ///joueurs
    std::vector<Joueur> m_joueurs;
    int m_nb_joueurs; // nombre de joueurs
    int m_nb_joueurs_ordinateurs;

    std::vector<string> m_perso_joueur;

    float compte_anim;

    //tour
    int m_tour;

    //fin de partie
    int m_fin_partie;

    ///cartes
    //cartes ennemis
    std::vector<Carte> m_ennemis;

    //cartes zones
    std::vector<Carte> m_zones;

    //cartes armes
    std::vector<Carte> m_armes;

    ///Enveloppe
    Enveloppe m_enveloppe;

    ///Plateau
    Plateau m_plateau;

    ///pioche de cartes restantes apres init partie

    std::vector<Carte> m_pioche;

protected: // heritage

public:
    Jeu()
    {
        std::cout << "- ctor Jeu" << std::endl;

        ///noms des persos

        m_perso_joueur.push_back("quirrel");
        m_perso_joueur.push_back("knight");
        m_perso_joueur.push_back("zote");
        m_perso_joueur.push_back("tiso");
        m_perso_joueur.push_back("hornet");
        m_perso_joueur.push_back("cloth");

        m_fin_partie=0;

        m_tour=0;

        ///construction des 6 joueurs + nombre de joueur par default a 3
        m_nb_joueurs=3;

        std::ostringstream nom_joueur;
        for(int i=0; i<6; i++)
        {
            //joueur 1-6
            nom_joueur.str("");
            nom_joueur.clear();
            nom_joueur << "joueur" << i+1;

            //creer vecteur
            m_joueurs.push_back(Joueur("vide",0,nom_joueur.str(),true,0,0));
        }

        ///construction des cartes

        //ennemi
        m_ennemis.push_back(Carte("Hornet"));
        m_ennemis.push_back(Carte("Knight"));
        m_ennemis.push_back(Carte("Tiso"));
        m_ennemis.push_back(Carte("Cloth"));
        m_ennemis.push_back(Carte("Zote"));
        m_ennemis.push_back(Carte("Quirrel"));

        //zone
        m_zones.push_back(Carte("Falaises Hurlantes"));
        m_zones.push_back(Carte("Dirtmouth"));
        m_zones.push_back(Carte("Mont Cristal"));
        m_zones.push_back(Carte("Vertchemin"));
        m_zones.push_back(Carte("Jardins de la Reine"));
        m_zones.push_back(Carte("Nid-profond"));
        m_zones.push_back(Carte("Bassin Ancestral"));
        m_zones.push_back(Carte("La Ruche"));
        m_zones.push_back(Carte("Frontieres du Royaume"));

        //arme
        m_armes.push_back(Carte("Aiguillon"));
        m_armes.push_back(Carte("Lance"));
        m_armes.push_back(Carte("Griffe"));
        m_armes.push_back(Carte("Aiguille"));
        m_armes.push_back(Carte("Faux"));
        m_armes.push_back(Carte("Massue"));

        compte_anim=0;
    }

    ~Jeu()
    {
        std::cout << "~ dtor Jeu" << std::endl;

    }

    ///getters
    //nb joueurs
    int get_nb_joueur(){return m_nb_joueurs;}
    int get_nb_joueur_ordinateur(){return m_nb_joueurs_ordinateurs;}

    //tour
    int get_tour(){return m_tour;}



    //joueurs
    std::vector<Joueur> & get_joueurs(){return m_joueurs;}

    //ennemis
    std::vector<Carte> & get_ennemis(){return m_ennemis;}

    //zones
    std::vector<Carte> & get_zones(){return m_zones;}

    //armes
    std::vector<Carte> & get_armes(){return m_armes;}

    //pioche
    std::vector<Carte> & get_pioche(){return m_pioche;}

    //enveloppe
    Enveloppe & getEnveloppe(){return m_enveloppe;}

    //plateau
    Plateau & get_Plateau(){return m_plateau;}

    //fin de partie
    int get_fin_partie(){return m_fin_partie;}

    std::vector<string> & get_m_perso_joueur(){return m_perso_joueur;}

    float get_compte_anim(){return compte_anim;}

    ///setters

    void set_compte_anim(float i){compte_anim=i;}

    //fin de partie
    void set_fin_partie(int _fin_partie) {m_fin_partie=_fin_partie;}

    //nombre de joueurs
    void set_nb_joueur(int _nb_joueurs){m_nb_joueurs= _nb_joueurs;}
    void set_nb_joueur_ordinateur(int _nb_joueurs_ordinateurs){m_nb_joueurs_ordinateurs = _nb_joueurs_ordinateurs;}
    void set_joueur(Joueur _joueur, int index){m_joueurs[index]=_joueur;}

    //tour
    void set_tour(int _tour)
    {
        m_tour=_tour%m_nb_joueurs;
    }



    ///============================== METHODES ==============================///

    void creer_enveloppe()
    {

        cout << "creation de l'enveloppe" << endl;

        int arme,ennemi,zone; // generer aleatoirement une carte

        arme=rand()%6;
        ennemi=rand()%6;
        zone=rand()%9;


        //  myvector.erase (myvector.begin()+5);

        ///mettre type dans l'enveloppe
        m_enveloppe.setArme(m_armes[arme]);
        m_enveloppe.setEnnemi(m_ennemis[ennemi]);
        m_enveloppe.setSalle(m_zones[zone]);

        ///virer type de sa pioche
        m_armes.erase(m_armes.begin()+arme);
        m_ennemis.erase(m_ennemis.begin()+ennemi);
        m_zones.erase(m_zones.begin()+zone);

    }

    void charger_enveloppe(string arme, string ennemi, string salle)
    {
        Carte carte;
        carte.setNom(arme);
        m_enveloppe.setArme(carte);
        carte.setNom(salle);
        m_enveloppe.setSalle(carte);
        carte.setNom(ennemi);
        m_enveloppe.setEnnemi(carte);
    }

    //mettre cartes restantes dans la pioche

    void remplir_pioche()
    {//    v1.insert(v1.end(), v2.begin(), v2.end());
        cout << "mise des cartes restantes dans la pioche" << endl;

        m_pioche.insert(m_pioche.end(),m_armes.begin(),m_armes.end());
        m_pioche.insert(m_pioche.end(),m_zones.begin(),m_zones.end());
        m_pioche.insert(m_pioche.end(),m_ennemis.begin(),m_ennemis.end());

        //vider les autres pioches

        m_armes.clear();
        m_ennemis.clear();
        m_zones.clear();
    }

    ///affichage a enlever apres?

    void afficher_joueur()
    {
        for(unsigned int i=0; i<6; i++)
        {
            cout << m_joueurs[i].getNom() << endl;
        }
    }

    void afficher_cartes()
    {

        cout << "armes:" << endl;
        for(auto x: m_armes)
        {
            cout << "\t" << x.getNom() << endl;
        }

        cout << "ennemis:" << endl;
        for(auto x: m_ennemis)
        {
            cout << "\t" << x.getNom() << endl;
        }


        cout << "endroits:" << endl;
        for(auto x: m_zones)
        {
            cout << "\t" << x.getNom() << endl;
        }

        cout << "pioche:" << endl;

        for(auto x : m_pioche)
        {
            cout << "\t" << x.getNom() << endl;
        }

        cout << "enveloppe:" << endl;

        cout << "\t" << m_enveloppe.getArme().getNom() << endl;
        cout << "\t" << m_enveloppe.getEnnemi().getNom() << endl;
        cout << "\t" << m_enveloppe.getSalle().getNom() << endl;


    }

    void supp_carte_pioche(int nbr)
    {
        m_pioche.erase(m_pioche.begin()+nbr);
    }


};



#endif // JEU_H_INCLUDED
