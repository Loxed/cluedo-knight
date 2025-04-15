#include "header.h"
#include "ressources.h"
#include "Jeu.h"

using std::cout;
using std::endl;
using std::string;

///Sous programme du menu principal qui gère le lancement du jeu
void menu_principal (Ressources & m_ressources)
{
    //Variables
    int choix = 0;
    int temp;

    //buffer
    BITMAP * buffer_principal=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);
    BITMAP * buffer_text=create_bitmap(W,H);

    temp=m_ressources.get_volume_msc();
    //musique, set volume a 0 au debut
    m_ressources.set_volume_msc(0);

    cout << "vol: " << m_ressources.get_volume_msc()<< endl;
    cout << "temp: " << temp << endl;

    stop_sample(m_ressources.get_mscs().get_msc("Main Menu"));

    play_sample(m_ressources.get_mscs().get_msc("Main Menu"),m_ressources.get_volume_msc(),128,1000,1); //lancer la musique du buffer principal




    //AFFICHER LE MENU AVEC LES OPTIONS
    do
    {
        if(temp!=0)
        {

            //Son, monter progressivement musique si elle est pas au max
            for (int i=0; i<temp; i+=5)
            {
                blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_principal,0,0,0,0,W,H);


                //particules
                m_ressources.afficher_particules(buffer_part);
                masked_blit(buffer_part,buffer_principal,0,0,0,0,W,H);

                //augmenter de 1
                if(i<temp)
                    m_ressources.set_volume_msc(i);
                else
                    m_ressources.set_volume_msc(temp);

                //ajuster son
                adjust_sample(m_ressources.get_mscs().get_msc("Main Menu"),m_ressources.get_volume_msc(),128,1000,1);

                blit(buffer_principal,screen,0,0,0,0,W,H);


            }
            temp=0;
        }

        //clear buffer
        clear_bitmap(buffer_principal);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_principal,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_principal,0,0,0,0,W,H);

        //titre
        rectfill(buffer_text,0,0,W,H,m_ressources.get_clrs().get_clr("magic pink"));
        textout_centre_ex(buffer_text,m_ressources.get_fnts().get_fnt("T40"),"Cluedow Knight",W/2,100,m_ressources.get_clrs().get_clr("white"),-1);

        //choix
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Lancer une nouvelle partie",1,W/2,300,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Charger une partie",1,W/2,400,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,2);
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Afficher les regles",1,W/2,500,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,3);
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Quitter le jeu",1,W/2,600,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,4);

        //parametres
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Param musiques",1,W/2,700,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,5);
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Credits",1,W/2,800,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,6);
        text_button_ex(&buffer_text,m_ressources.get_fnts().get_fnt("T20"),"Compte",1,W/2,900,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,7);

        //afficher texte
        masked_blit(buffer_text,buffer_principal,0,0,0,0,W,H);

        //souris
        show_mouse(buffer_principal);

        //afficher le buffer
        blit(buffer_principal,screen,0,0,0,0,W,H);

    }
    while(choix<1 || choix>7); //on boucle tant qu'on a pas appuyé sur un des boutons

    //transition de fin
    for (int k=0; k<H; k+=15)
    {
        //clear buffer
        clear_bitmap(buffer_principal);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_principal,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_principal,0,0,0,0,W,H);

        //affichage texte
        masked_blit(buffer_text,buffer_principal,0,0,0,0,W,H-k);

        //afficher sur le buffer
        blit(buffer_principal,screen,0,0,0,0,W,H);
    }

    //arreter la musique
    stop_sample(m_ressources.get_mscs().get_msc("Forgotten Crossroads"));

    //souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_principal);
    destroy_bitmap(buffer_part);
    destroy_bitmap(buffer_text);

    clear_keybuf();

    //lancer une nouvelle partie
    if(choix== 1)
    {
        //on crée un nouveau jeu
        Jeu _jeu;

        //clear bitmap
        clear_bitmap(screen);

        //on initialise la partie
        initialiser_partie(m_ressources, _jeu);

        //on lance une nouvelle partie
        lancer_jeu(m_ressources, _jeu);
    }

    //lancer une partie sauvegardee
    if(choix==2)
    {
        //on cré un jeu
        Jeu _jeu;

        //Variable
        int num_joueur;

        //on charge une partie sauvegardée
        charger_partie(_jeu, &num_joueur);

        //on set le tour en fonction du nombre de joueur
        _jeu.set_tour(num_joueur);

        //on lance la partie
        lancer_jeu(m_ressources, _jeu);

    }

    //Regle du jeu
    if(choix==3)
    {
        //on affiche les règles
        regles(m_ressources);
    }

    //Quitter le jeu
    if(choix==4)
    {
        //buffer
        BITMAP * buffer_part=create_bitmap(W,H);
        BITMAP * buffer_quitter=create_bitmap(W,H);

        do
        {
            //clear buffer
            clear_bitmap(buffer_quitter);

            //fond d'ecran
            blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_quitter,0,0,0,0,W,H);

            //particules
            m_ressources.afficher_particules(buffer_part);
            masked_blit(buffer_part,buffer_quitter,0,0,0,0,W,H);

            //titre
            textout_centre_ex(buffer_quitter,m_ressources.get_fnts().get_fnt("T30"),"Appuyer sur ECHAP pour quitter le jeu",W/2,H/2,m_ressources.get_clrs().get_clr("white"),-1);

            //souris
            show_mouse(buffer_quitter);

            //afficher le buffer
            blit(buffer_quitter,screen,0,0,0,0,W,H);

        }
        while(!key[KEY_ESC]);  //tant qu'on a pas appuyé sur la touche echap

        //souris a null pour eviter les failles memoires
        show_mouse(NULL);

        //on détruit les bitmaps pour eviter les failles memoires
        destroy_bitmap(buffer_part);
        destroy_bitmap(buffer_quitter);
    }

    //Paramètre musique
    if(choix==5)
    {

        parametres_musique(m_ressources);
        //on revient au menu principal
    }

    //Credits du jeu
    if(choix==6)
    {
        //buffer
        BITMAP * buffer_part=create_bitmap(W,H);
        BITMAP * buffer_credits=create_bitmap(W,H);
        int retour =0;

        do
        {
            //clear buffer
            clear_bitmap(buffer_credits);

            //fond d'ecran
            blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_credits,0,0,0,0,W,H);

            //particules
            m_ressources.afficher_particules(buffer_part);
            masked_blit(buffer_part,buffer_credits,0,0,0,0,W,H);

            //bouton retour
            text_button_ex(&buffer_credits,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,10,10,makecol(255,255,255),-1,makecol(128,128,128),-1,&retour,1);

            //titre
            textout_centre_ex(buffer_credits,m_ressources.get_fnts().get_fnt("T40"),"Jeu realise par :",W/2,300,m_ressources.get_clrs().get_clr("white"),-1);
            textout_centre_ex(buffer_credits,m_ressources.get_fnts().get_fnt("T30"),"Valentine MORGANT",W/2,H/2,m_ressources.get_clrs().get_clr("white"),-1);
            textout_centre_ex(buffer_credits,m_ressources.get_fnts().get_fnt("T30"),"Leopold ROMBAUT",W/2,H/2+100,m_ressources.get_clrs().get_clr("white"),-1);
            textout_centre_ex(buffer_credits,m_ressources.get_fnts().get_fnt("T30"),"Killian DECHAMPS",W/2,H/2+200,m_ressources.get_clrs().get_clr("white"),-1);

            //souris
            show_mouse(buffer_credits);

            //afficher le buffer
            blit(buffer_credits,screen,0,0,0,0,W,H);

        }
        while(retour==0);  //boucle tant qu'on a pas appyé sur le bouton retour

        //souris a null pour eviter les failles memoires
        show_mouse(NULL);

        //on détruit les biutmaps pour eviter les failles memoires
        destroy_bitmap(buffer_part);
        destroy_bitmap(buffer_credits);

    }

    //Comptes
    if(choix==7)
    {
        //on lance le sous programme pour gérer les comptes
        parametres_comptes(m_ressources);

    }
    if(choix!=4)
        menu_principal(m_ressources);

}
