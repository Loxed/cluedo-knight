#include "header.h"

void parametres_musique(Ressources & m_ressources) //pour savoir a quel menu retourner, et ne pas arreter la partie en cours
{
    BITMAP * buffer_parametres=create_bitmap(W,H);

    BITMAP * buffer_part=create_bitmap(W,H);

    int choix=0;

    while(choix==0)
    {
        if(key[KEY_ESC]) choix=1;

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_parametres,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_parametres,0,0,0,0,W,H);

        //texte
        textout_centre_ex(buffer_parametres,m_ressources.get_fnts().get_fnt("T30"), "Regler le volume sonore",SCREEN_W/2,100,m_ressources.get_clrs().get_clr("white"),-1);

        ///musique

        textprintf_centre_ex(buffer_parametres,m_ressources.get_fnts().get_fnt("T20"),SCREEN_W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"Musique: %d",m_ressources.get_volume_msc());
        textprintf_centre_ex(buffer_parametres,m_ressources.get_fnts().get_fnt("T20"),SCREEN_W/2,250,m_ressources.get_clrs().get_clr("white"),-1,"Utilisez les fleches");

        ///bouton retour
        text_button_ex(&buffer_parametres,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,20,20,m_ressources.get_clrs().get_clr("white"),-1,makecol(128,128,128),-1,&choix,1);

        //souris custom
        show_mouse(buffer_parametres);

        //afficher buffer sur lecran
        blit(buffer_parametres,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        if(key[KEY_LEFT]) m_ressources.set_volume_fx(m_ressources.get_volume_msc()--);
        if(key[KEY_RIGHT]) m_ressources.set_volume_fx(m_ressources.get_volume_msc()++);

        if(m_ressources.get_volume_msc()>255)m_ressources.set_volume_msc(255);
        if(m_ressources.get_volume_msc()<=0)m_ressources.set_volume_msc(0);

        ///menu principal
        adjust_sample(m_ressources.get_mscs().get_msc("Main Menu"),m_ressources.get_volume_msc(),128,1000,1);

    }

    show_mouse(NULL);

    destroy_bitmap(buffer_parametres);

    destroy_bitmap(buffer_part);

}
