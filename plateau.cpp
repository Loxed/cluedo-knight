#include "header.h"
#include "plateau.h"
#include "ressources.h"

using std::cout;
using std::endl;
using std::string;

///Sous programme permettant d'afficher le plateau
void affichage_plateau( Jeu & m_jeu, BITMAP * & buffer_plateau, Ressources & m_ressources)
{
    //augmenter compte anim
    m_jeu.set_compte_anim(m_jeu.get_compte_anim()+0.1);
    if(m_jeu.get_compte_anim()>=432)m_jeu.set_compte_anim(0);

    //buffer
    BITMAP * buffer_zones=create_bitmap(840,840);

    //rectangle magenta transparent
    rectfill(buffer_zones,0,0,840,840,m_ressources.get_clrs().get_clr("magic pink"));

    //afficher cases
    blit(m_jeu.get_Plateau().get_plateau(),buffer_zones,0,0,20,20,800,800);

    //afficher salles au dessus
    masked_blit(m_ressources.get_imgs().get_img("plateau"),buffer_zones,0,0,20,20,W,H);

    //afficher zone de stag au dessus
    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*0+20,32*9+20,32,64); //gauche (1,11)
    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*24+20,32*10+20,32,64); //droite (25,12)
    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*18+20,32*0+20,32,64); // haut (19,2)
    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*17+20,32*23+20,32,64); // bas (18,25)


    for(int i=0; i<m_jeu.get_nb_joueur(); i++)
    {
        //si joueur en vie
        if(m_jeu.get_joueurs()[i].getAlive()==true)
        {
        //mettre la frame au bon endroit
        m_jeu.get_joueurs()[i].set_img_joueur(m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),m_jeu.get_compte_anim()));

        //afficher joueurs sur plateau
        masked_blit(m_jeu.get_joueurs()[i].get_img_joueur(),buffer_zones,0,0,m_jeu.get_joueurs()[i].getPositionX()*32-16-m_jeu.get_joueurs()[i].get_img_joueur()->w/2+20,m_jeu.get_joueurs()[i].getPositionY()*32-8-m_jeu.get_joueurs()[i].get_img_joueur()->h-2+20,m_jeu.get_joueurs()[i].get_img_joueur()->w,m_jeu.get_joueurs()[i].get_img_joueur()->h);
        }
    }

    //on affiche le plateau
    masked_blit(buffer_zones,buffer_plateau,0,0,540,240,840,840);

    //on détruit la bitmap pour eviter les failles memoires
    destroy_bitmap(buffer_zones);
}

///Sous programme permettant de gérer les déplacement
bool gerer_deplacement(int dir_x, int dir_y, Jeu & m_jeu, Ressources & m_ressources,int _num_joueur)
{
    //pos x et y du joueur pr faire des check
    int x=m_jeu.get_joueurs()[_num_joueur].getPositionX();
    int y=m_jeu.get_joueurs()[_num_joueur].getPositionY();

    //blindage pour ne pas sortir de lecran
    if((x+(int)dir_x>=1&&x+(int)dir_x<=25) && (y+(int)dir_y>=1&&y+(int)dir_y<=25)) // si x+diff et y+diff compris dans les bornes
    {
        //si on est sur un chemin,stag ou spawn: acces au chemins, portes, stag, spawn
        if(m_ressources.get_map()[y][x] =='0' || m_ressources.get_map()[y][x] =='c' || m_ressources.get_map()[y][x] == 'd')
        {
            //mouvement case sur chemin, porte, stag ou spawn (!PAS LIEUX!)
            if( (m_ressources.get_map()[y+dir_y][x+dir_x] >='b' && m_ressources.get_map()[y+dir_y][x+dir_x] <= 'd') || m_ressources.get_map()[y+dir_y][x+dir_x]=='0') //chemins, portes, stag, spawn
            {
                //bouger
                m_jeu.get_joueurs()[_num_joueur].setPositionX( m_jeu.get_joueurs()[_num_joueur].getPositionX()+dir_x);
                m_jeu.get_joueurs()[_num_joueur].setPositionY( m_jeu.get_joueurs()[_num_joueur].getPositionY()+dir_y);
            }

            else return false;
            clear_keybuf();
        }

        //si on est dans une salle: avoir acces aux portes et aux salles (vu qu'elles ne sont pas collees c'est pas un probleme)
        else if(m_ressources.get_map()[y][x]>='1'&&m_ressources.get_map()[y][x]<='9') // lieux
        {
            //case quelconque
            if( (m_ressources.get_map()[y+dir_y][x+dir_x]>='1'&& m_ressources.get_map()[y+dir_y][x+dir_x] <='9') || m_ressources.get_map()[y+dir_y][x+dir_x]=='b') //lieux, porte
            {
                //bouger
                m_jeu.get_joueurs()[_num_joueur].setPositionX( m_jeu.get_joueurs()[_num_joueur].getPositionX()+dir_x);
                m_jeu.get_joueurs()[_num_joueur].setPositionY( m_jeu.get_joueurs()[_num_joueur].getPositionY()+dir_y);
            }
            else return false;
            clear_keybuf();
        }

        //si on est sur une porte, acces a tout
        else if(m_ressources.get_map()[y][x] == 'b') //porte
        {
            //bouger
            m_jeu.get_joueurs()[_num_joueur].setPositionX( m_jeu.get_joueurs()[_num_joueur].getPositionX()+dir_x);
            m_jeu.get_joueurs()[_num_joueur].setPositionY( m_jeu.get_joueurs()[_num_joueur].getPositionY()+dir_y);

            //clear key
            clear_keybuf();

        }

        else
        {
            return false;
        }

        //vider key
        key[KEY_UP]=0;
        key[KEY_DOWN]=0;
        key[KEY_LEFT]=0;
        key[KEY_RIGHT]=0;

        return true;
    }

    clear_keybuf();
    return false;
}
