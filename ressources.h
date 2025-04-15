#ifndef RESSOURCES_H_INCLUDED
#define RESSOURCES_H_INCLUDED

#include "img.h"
#include "msc.h"
#include "clr.h"
#include "fnt.h"
#include "anim.h"

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

//volume musique soutenance
#define VOL_MSC 255


class Ressources
{

private: // encapsulation
    //composition

    Anim m_anim; //animations, tableau de bitmaps
    Img m_img; // images statiques
    Clr m_clr; // couleurs avec makecol()
    Fnt m_fnt; // polices custom du jeu
    Msc m_msc; // musiques du jeu, en .ogg si possible
//   Snd m_snd; // effets sonores, .wav

    int volume_msc;
    int volume_fx;

    //partiules
    float compteur_cos;

    //plateau
    std::vector<std::vector<char>> case_plateau; // stocker les cases du plateau

    std::vector<char> vect_1d; //

protected: // heritage

public:

    Ressources()
    {
    std::cout << "- ctor Ressources" << std::endl;
    volume_msc=VOL_MSC;
    volume_fx=128;
    compteur_cos=0;

    /// ----- mat plateau ----- ///

    //ouvrir fichier
    FILE* file_plat = fopen("RESSOURCES/MAP/plateau.txt", "r");

    //blindage
    if (!file_plat)
    {
        std::cerr << "Could not open the file - '" << "RESSOURCES/MAP/plateau.txt" << "'" << endl;
        //return EXIT_FAILURE;
    }

    //mettre 25 cases dans un vecteur 1d

    for(int i=0; i<27; i++)
    {
        vect_1d.push_back('.');
    }

    for (int i=0; i<27; i++)
    {
    //allouer place
    case_plateau.push_back(vect_1d);

        for (int j=0; j<27; j++)
        {
            //mettre les termes dans le plateau
            case_plateau[i][j]=getc(file_plat);
        }

        //ne pas stocker le \n
        getc(file_plat);
    }

    //fermer fichier
    fclose(file_plat);

    for (int i=0; i<27; i++)
    {
        for (int j=0; j<27; j++)
        {
            printf("%c",case_plateau[i][j]);
        }
        cout << endl;
    }

    cout << endl << endl;

    }

    ~Ressources()
    {
    std::cout << "~ dtor Ressources" << std::endl;
    }

    ///getters
    Anim & get_anims(){return m_anim;}
    Img & get_imgs(){ return m_img;}
    Clr & get_clrs(){ return m_clr;}
    Fnt & get_fnts(){ return m_fnt;}
    Msc & get_mscs(){ return m_msc;}
    //Snd & get_snds(){ return m_snd;}

    int & get_volume_fx(){return volume_fx;}
    int & get_volume_msc(){return volume_msc;}

    //vecteur map
    std::vector<std::vector<char>> get_map(){return case_plateau;}

    ///setters
    void set_volume_fx(int v){volume_fx=v;}
    void set_volume_msc(int v){volume_msc=v;}



    ///methodes

    ///AFFICHAGE

    //particules
    void afficher_particules(BITMAP * & buffer_param)
    {
    //variable pour faire monter les parts
       compteur_cos+=0.001;
       if(compteur_cos==360)compteur_cos=0;
       //bitmap a renvoyer
    BITMAP * buffer_particules=create_bitmap(W,H);

        ///particules
        //fond rose pour apres remask blit
        rectfill(buffer_particules,0,0,W,H,m_clr.get_clr("magic pink"));
        //1
        masked_blit(m_img.get_particule(0),buffer_particules,0,0,0.2*W*sin(compteur_cos),0.4*H/2*cos(compteur_cos),W,H);

        //2
        masked_blit(m_img.get_particule(1),buffer_particules,0,0,-0.3*W*sin(compteur_cos),0.4*H/2*cos(compteur_cos),W,H);

        //3
        masked_blit(m_img.get_particule(2),buffer_particules,0,0,0.4*W*sin(compteur_cos),-0.2*H/2*cos(compteur_cos),W,H);

        blit(buffer_particules,buffer_param,0,0,0,0,W,H);

        destroy_bitmap(buffer_particules);
    }


};

#endif // RESSOURCES_H_INCLUDED
