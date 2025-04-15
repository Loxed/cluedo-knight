#include "header.h"
#include <vector>

///Sous programme pour les boutons sur les cartes de la partie
void text_card_ex(Ressources & m_ressources,Jeu & m_jeu, BITMAP * *destination, std::string nom_image, int pos_x, int pos_y, int * choix, int valeur_a_prendre)
{
    //Variable
    int click=0;

    //buffer
    BITMAP * carte=create_bitmap(80,160);

    //afficher la carte
    carte = m_ressources.get_imgs().afficher_carte(nom_image);

    if(mouse_x>=pos_x&&mouse_x<=pos_x+80&&mouse_y>=pos_y&&mouse_y<=pos_y+100) //si je suis sur la carte
    {
        //afficher un contour autour de la carte
        masked_blit(m_ressources.get_imgs().get_img("contour"),*destination,0,0,pos_x-5,pos_y-5,90,110);

        if(mouse_b==1) // si je clique
        {
            rest(150);
            click=valeur_a_prendre;
        }

    }

    //afficher la carte
    masked_blit(carte,*destination,0,0,pos_x,pos_y,80,100);

    if(click!=0) //si j'appuie sur le bouton
    {
        *choix=click; //choix prend la valeur a prendre

    }
}
