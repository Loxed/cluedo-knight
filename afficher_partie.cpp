#include "header.h"

///Sous programme pour l'affichage pendant une partie
void afficher_partie(Ressources & m_ressources, Jeu & _jeu, BITMAP *  &retour)
{
    BITMAP * buffer_tour=create_bitmap(W,H);

    rectfill(buffer_tour,0,0,10,10,makecol(255,255,255));

    BITMAP * buffer_rectangle=create_bitmap(620,200);

    ///afficher terrain
    blit(m_ressources.get_imgs().get_img("terrain"),buffer_tour,0,0,0,0,W,H);

    ///afficher plateau et joueurs sur le plateau
    affichage_plateau(_jeu, buffer_tour, m_ressources);

    ///afficher les informations du joueur qui joue

    ///personnage

    //rendre buffer_rectangle transparent
    rectfill(buffer_rectangle,0,0,620,200,m_ressources.get_clrs().get_clr("magic pink"));

    //mettre buffer perso sur buffer rectangle
    masked_stretch_blit(m_ressources.get_anims().get_frame_perso(_jeu.get_joueurs()[_jeu.get_tour()].get_personnage(),_jeu.get_compte_anim()),buffer_rectangle,0,0,m_ressources.get_anims().get_frame_perso(_jeu.get_joueurs()[_jeu.get_tour()].get_personnage(),_jeu.get_compte_anim())->w,m_ressources.get_anims().get_frame_perso(_jeu.get_joueurs()[_jeu.get_tour()].get_personnage(),_jeu.get_compte_anim())->h,10,10,m_ressources.get_anims().get_frame_perso(_jeu.get_joueurs()[_jeu.get_tour()].get_personnage(),_jeu.get_compte_anim())->w*4,m_ressources.get_anims().get_frame_perso(_jeu.get_joueurs()[_jeu.get_tour()].get_personnage(),_jeu.get_compte_anim())->h*4);

    //afficher buffer rectangle sur buffer plateau
    masked_blit(buffer_rectangle,buffer_tour,0,0,20,20,620,220);
    ///cartes du joueur de droite a gauche



    for (unsigned int i=0; i<_jeu.get_joueurs()[_jeu.get_tour()].getTaille(); i++)
    {
        //mettre la bonne carte dans le buffer carte
       // m_ressources.get_imgs().afficher_carte(_jeu.get_joueurs()[_jeu.get_tour()].getCarte(i).getNom());

        //afficher le buffer carte au bon endroit
        masked_stretch_blit(m_ressources.get_imgs().afficher_carte(_jeu.get_joueurs()[_jeu.get_tour()].getCarte(i).getNom()),buffer_tour,0,0,m_ressources.get_imgs().afficher_carte(_jeu.get_joueurs()[_jeu.get_tour()].getCarte(i).getNom())->w,m_ressources.get_imgs().afficher_carte(_jeu.get_joueurs()[_jeu.get_tour()].getCarte(i).getNom())->h,840+180*i,20,m_ressources.get_imgs().afficher_carte(_jeu.get_joueurs()[_jeu.get_tour()].getCarte(i).getNom())->w*2,m_ressources.get_imgs().afficher_carte(_jeu.get_joueurs()[_jeu.get_tour()].getCarte(i).getNom())->h*2);
    }

    blit(buffer_tour,retour,0,0,0,0,W,H);

    destroy_bitmap(buffer_rectangle);

    destroy_bitmap(buffer_tour);
}

