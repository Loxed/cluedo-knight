#ifndef IMG_H_INCLUDED
#define IMG_H_INCLUDED

#include "header.h"

///CONSTANTES (TAILLE DE LECRAN ETC..)

//taille ecran
#define W 1920
#define H 1080

//nb images pour les cases
#define NB_CASES 17

//taille du plateau
#define TAILLE 25

//taille cases en pixel
#define TAILLE_PX 32

using std::cout;
using std::endl;
using std::string;

class Img
{

private: // encapsulation

    ///images de fond
    std::map<string, BITMAP *> m_fonds;

    //particles
    std::vector<BITMAP *> m_particles;

    //partie

    //cases aléatoire
    std::vector<BITMAP *>cases;


    //cartes
    std::map<string,BITMAP *>cartes;



protected: // heritage

public:

    Img()
    {
        cout << "-ctor Img" << endl;
        /// ------------------- FONDS ------------------- ///

        charger_bitmap("fond_menu_principal","RESSOURCES/IMG/bg_main_menu.bmp");

        ///plateau
        charger_bitmap("plateau","RESSOURCES/IMG/plateau.bmp");
        charger_bitmap("terrain","RESSOURCES/IMG/terrain.bmp");

        //stag
        charger_bitmap("stag","RESSOURCES/IMG/case_stag.bmp");

        //contour
        charger_bitmap("contour","RESSOURCES/IMG/contour.bmp");

        //fin de partie
        charger_bitmap("fin","RESSOURCES/IMG/fond_fin.bmp");

        /// ------------------- PARTICLES ------------------- ///
        //allouer espace
        for (int i=0; i<3; i++)
        {
            m_particles.push_back(create_bitmap(W,H));
        }

        //chargers images
        m_particles[0]=load_bitmap("RESSOURCES/IMG/particles1.bmp",NULL);
        m_particles[1]=load_bitmap("RESSOURCES/IMG/particles2.bmp",NULL);
        m_particles[2]=load_bitmap("RESSOURCES/IMG/particles3.bmp",NULL);

        /// -------------------- CARTES -------------------- ///
        charger_carte("Griffe","RESSOURCES/IMG/armes/claw.bmp");
        charger_carte("Massue","RESSOURCES/IMG/armes/club.bmp");
        charger_carte("Faux","RESSOURCES/IMG/armes/scythe.bmp");
        charger_carte("Aiguillon","RESSOURCES/IMG/armes/nail.bmp");
        charger_carte("Aiguille","RESSOURCES/IMG/armes/needle.bmp");
        charger_carte("Lance","RESSOURCES/IMG/armes/longnail.bmp");

        charger_carte("Cloth","RESSOURCES/IMG/ennemis/cloth.bmp");
        charger_carte("Hornet","RESSOURCES/IMG/ennemis/hornet.bmp");
        charger_carte("Knight","RESSOURCES/IMG/ennemis/knight.bmp");
        charger_carte("Zote","RESSOURCES/IMG/ennemis/zote.bmp");
        charger_carte("Tiso","RESSOURCES/IMG/ennemis/tiso.bmp");
        charger_carte("Quirrel","RESSOURCES/IMG/ennemis/quirrel.bmp");

        charger_carte("Bassin Ancestral","RESSOURCES/IMG/lieux/ancient basin.bmp");
        charger_carte("Jardins de la Reine","RESSOURCES/IMG/lieux/queen gardens.bmp");
        charger_carte("Nid-profond","RESSOURCES/IMG/lieux/deepnest.bmp");
        charger_carte("Frontieres du Royaume","RESSOURCES/IMG/lieux/kingdom edge.bmp");
        charger_carte("Falaises Hurlantes","RESSOURCES/IMG/lieux/howling cliffs.bmp");
        charger_carte("Dirtmouth","RESSOURCES/IMG/lieux/dirtmouth.bmp");
        charger_carte("Mont Cristal","RESSOURCES/IMG/lieux/crystal peaks.bmp");
        charger_carte("La Ruche","RESSOURCES/IMG/lieux/hive.bmp");
        charger_carte("Vertchemin","RESSOURCES/IMG/lieux/greenpath.bmp");
        /// ------------------- CASE ALEATOIRE ------------------- ///

        ///convertir variable en char *
        std::ostringstream sprintf;
        string chemin;
        std::vector<char> chaine;

        //cases aléatoires

        for (int i=0; i<NB_CASES; i++)
        {
            //sprintf (le vider avant)
            sprintf.str("");
            sprintf.clear();


            sprintf << "RESSOURCES/IMG/case" << i+1 << ".bmp"; // mettre la bonne adresse dedans

            //mettre le sprintf dans string "chemin"
            chemin.clear(); // clear le chemin
            chemin=sprintf.str();

            //mettre dans une chaine de char

            chaine.clear(); //clear la chaine

            for(auto & x:chemin) // mettre les termes dans la char *
            {
                chaine.push_back(x);
            }

            chaine.push_back('\0'); // mettre la fin de la chaine de char

            //cout << chaine << endl;

            ///ajouter au vecteur
            cases.push_back(create_bitmap(32,32)); // allouer l'espace

            cases[i]=load_bitmap(&*chaine.begin(),NULL); // mettre la bonne image dedans


            //blindage
            if (!cases[i])
            {

                ///si le fichier est corrompu
                if (file_exists(&*chaine.begin(), 0, NULL))
                {

                    allegro_message("''%s'' was located but could not be loaded.",&*chaine.begin());
                    exit(EXIT_FAILURE);

                }

                else /// si il n'existe pas
                {

                    allegro_message("could not locate ''%s''.",&*chaine.begin());
                    exit(EXIT_FAILURE);
                }
            }

        }
    }

    //dtor
    ~Img()
    {
        std::cout << "~ dtor img" << std::endl;
    }

    ///getters

    BITMAP * get_img(string _nom)
    {

        //convertir string en char *
        std::vector<char> chaine(_nom.begin(), _nom.end());
        chaine.push_back('\0');

        for(auto & x:m_fonds)
        {
            if(x.first == _nom) return x.second; // si c'est le bon son return
        }

        allegro_message("image ''%s'' was not found.",&*chaine.begin());

        return NULL;

    }

    BITMAP * & get_particule(int _i)
    {
        return m_particles[_i];
    }

    //recevoir une case du plateau
    BITMAP * & get_case()
    {
        int rng=rand()%NB_CASES;

        return cases[rng];
    }

    void charger_bitmap(string _nom, string _chemin)
    {
        //nom
        std::vector<char> nom(_nom.begin(), _nom.end());
        nom.push_back('\0');

        //chemin
        std::vector<char> chemin(_chemin.begin(), _chemin.end());
        chemin.push_back('\0');


        m_fonds[&*nom.begin()]=load_bitmap(&*chemin.begin(),NULL);

        ///blindage
        if(!m_fonds.find(&*nom.begin())->second)
            allegro_message("image '%s' could not load or find path '%s'.",&*nom.begin(),&*chemin.begin());
        else
            cout << "\timage '" << _nom << "' was successfully created." << endl;
    }
    ///charger cartes

    void charger_carte(string _nom, string _chemin)
    {
        //nom
        std::vector<char> nom(_nom.begin(), _nom.end());
        nom.push_back('\0');

        //chemin
        std::vector<char> chemin(_chemin.begin(), _chemin.end());
        chemin.push_back('\0');


        cartes[&*nom.begin()]=load_bitmap(&*chemin.begin(),NULL);

        ///blindage
        if(!cartes.find(&*nom.begin())->second)
            allegro_message("image '%s' could not load or find path '%s'.",&*nom.begin(),&*chemin.begin());
        else
            cout << "\timage '" << _nom << "' was successfully created." << endl;
    }

    BITMAP * afficher_carte(string _nom)
    {
        //convertir string en char *
        std::vector<char> chaine(_nom.begin(), _nom.end());
        chaine.push_back('\0');

        for(auto & x:cartes)
        {
            if(x.first == _nom) return x.second; // si c'est le bon son return
        }

        allegro_message("image ''%s'' was not found.",&*chaine.begin());

        return NULL;
    }



};


#endif // IMG_H_INCLUDED
