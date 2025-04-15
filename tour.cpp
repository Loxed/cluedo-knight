#include "header.h"

using std::cout;
using std::endl;
using std::string;

///Sous programme permettant de gérer les tour dans une partie
void tour(Ressources & m_ressources, Jeu & _jeu)
{
    cout << _jeu.getEnveloppe().getArme().getNom() << _jeu.getEnveloppe().getEnnemi().getNom() << _jeu.getEnveloppe().getSalle().getNom()<< endl;
    //Variables
    int choix_tour=0;
    int choix = 0;
    int lancer_de=0;
    int confirm=0;
    char case_plateau;
    //bool autorisation_deplacement= false;
    bool autorisation_accusation = false;
    int i=0, j=0;
    float bouge;
    int tour_fini =0;
    string choix_salles;
    int choix_salles1 =0;
    int choix_ennemis=0;
    int choix_armes=0;
    int passe=0;
    string salles;
    string armes;
    string ennemis;

    //buffer
    BITMAP * buffer_tour=create_bitmap(W,H);

    BITMAP * buffer_part=create_bitmap(W,H);

    //string et chaine pr conversion to char *
    string temp;
    std::vector<char> chaine;

    temp= _jeu.get_joueurs()[_jeu.get_tour()].getNom();

    tour_fini = 0;

    _jeu.set_compte_anim(0);


    do
    {
        do
        {
            //clear buffer
            clear_bitmap(buffer_tour);

            //on appelle tous les affichages
            afficher_partie(m_ressources, _jeu, buffer_tour);

            //afficher les boutons
            textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());

            //boutons pour jouer
            //text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T30"),"Regarder le plateau",1,280,270,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix_tour,1);
            textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),40,260,m_ressources.get_clrs().get_clr("white"),-1,"Action:");
            text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T30"),"Lancer le de",1,280,320,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix_tour,2);
            text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T30"),"Sauvegarder partie",1,280,370,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix_tour,4);

            //souris
            show_mouse(buffer_tour);

            //on affiche le buffer sur l'ecran
            blit(buffer_tour,screen,0,0,0,0,W,H);

        }
        while (choix_tour==0); //boucle tant que l'on a pas fait de choix

        switch (choix_tour)
        {
        case 1: //regarder le plateau
            break;

        case 2: // lancer le dé et bouger
            j=0;

            //lancer du de
            lancer_de = rand()%18+1;
            //lancer_de = 20;

            //pour passer au tour suivant, si on joue
            _jeu.get_joueurs()[_jeu.get_tour()].setDeplacementDe(lancer_de);

            //clear buffer
            clear_bitmap(buffer_tour);

            if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
            {

                //affichage
                clear_bitmap(buffer_tour);

                afficher_partie(m_ressources, _jeu, buffer_tour);

                textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());


                textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());
                textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,70,makecol(255,255,255),-1,"deplacement restant: %d",_jeu.get_joueurs()[_jeu.get_tour()].getDeplacementDe());

                //afficher pos x et y du joueur
                textprintf_ex(buffer_tour,font,30,270,makecol(255,255,255),-1,"x: %d",_jeu.get_joueurs()[_jeu.get_tour()].getPositionX());
                textprintf_ex(buffer_tour,font,30,290,makecol(255,255,255),-1,"y: %d",_jeu.get_joueurs()[_jeu.get_tour()].getPositionY());

            }

            //souris
            show_mouse(buffer_tour);
            //ecran
            blit(buffer_tour,screen,0,0,0,0,W,H);

            /// ------------------------------------------ blinder deplacement ------------------------------------------ ///

            do
            {
                ///deplacements, plateau.cpp
                if(key[KEY_LEFT])
                {
                    bouge=gerer_deplacement(-1,0,_jeu,m_ressources,_jeu.get_tour());

                    i+=bouge;

                    for (int k=0; k<27; k++)
                    {
                        for (int l=0; l<27; l++)
                        {
                            cout << m_ressources.get_map()[k][l];
                        }
                        cout << endl;
                    }


                    case_plateau=m_ressources.get_map()[_jeu.get_joueurs()[_jeu.get_tour()].getPositionY()][_jeu.get_joueurs()[_jeu.get_tour()].getPositionX()];

                    cout <<"case: " << case_plateau << endl;

                    //peut que se teleporter si on bouge bien
                    if(case_plateau=='c' &&j==0 && bouge==1)
                    {
                        teleportation(_jeu.get_joueurs()[_jeu.get_tour()]);
                        j++;
                    }

                }

                if(key[KEY_RIGHT])
                {
                    bouge=gerer_deplacement(1,0,_jeu,m_ressources,_jeu.get_tour());

                    i+=bouge;

                    case_plateau=m_ressources.get_map()[_jeu.get_joueurs()[_jeu.get_tour()].getPositionY()][_jeu.get_joueurs()[_jeu.get_tour()].getPositionX()];

                    cout <<"case: " << case_plateau << endl;

                    if(case_plateau=='c'&&j==0  && bouge==1)
                    {
                        teleportation(_jeu.get_joueurs()[_jeu.get_tour()]);
                        j++;
                    }
                }

                if(key[KEY_UP])
                {
                    bouge=gerer_deplacement(0,-1,_jeu,m_ressources,_jeu.get_tour());

                    i+=bouge;

                    case_plateau=m_ressources.get_map()[_jeu.get_joueurs()[_jeu.get_tour()].getPositionY()][_jeu.get_joueurs()[_jeu.get_tour()].getPositionX()];

                    cout <<"case: " << case_plateau << endl;

                    if(case_plateau=='c'&&j==0 && bouge==1)
                    {
                        teleportation(_jeu.get_joueurs()[_jeu.get_tour()]);
                        j++;
                    }
                }

                if(key[KEY_DOWN])
                {
                    bouge=gerer_deplacement(0,1,_jeu,m_ressources,_jeu.get_tour());

                    i+=bouge;

                    case_plateau=m_ressources.get_map()[_jeu.get_joueurs()[_jeu.get_tour()].getPositionY()][_jeu.get_joueurs()[_jeu.get_tour()].getPositionX()];

                    cout <<"case: " << case_plateau << endl;

                    if(case_plateau=='c'&&j==0 && bouge==1)
                    {
                        teleportation(_jeu.get_joueurs()[_jeu.get_tour()]);
                        j++;
                    }
                }

                ///affichage
                clear_bitmap(buffer_tour);

                afficher_partie(m_ressources, _jeu, buffer_tour);

                textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());

                textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,70,makecol(255,255,255),-1,"deplacement restant: %d",_jeu.get_joueurs()[_jeu.get_tour()].getDeplacementDe()-i);
                //souris
                show_mouse(buffer_tour);
                //ecran
                blit(buffer_tour,screen,0,0,0,0,W,H);

            }
            while(i<lancer_de);


            /// ------------------------------------------ blinder (hypothese) ------------------------------------------ ///

            choix_salles = presence_salle(case_plateau);


            //si on est dans une salle (sauf centre) on peut formuler une hypothese
            if( (case_plateau>='1' && case_plateau<='4') || (case_plateau>='6' && case_plateau<='9') || case_plateau=='a')
            {
                do
                {
                    ///affichage
                    clear_bitmap(buffer_tour);

                    afficher_partie(m_ressources, _jeu, buffer_tour);

                    textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());

                    //bouton confirmer
                    confirm=0;


                    ///HYPOTHESE
                    textprintf_centre_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T30"),1380+520/2,280,m_ressources.get_clrs().get_clr("white"),-1,"Faire une hypothese:");

                    //ennemi
                    textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),1400,350,m_ressources.get_clrs().get_clr("white"),-1,"Suspect:%s",ennemis.c_str());

                    if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
                    {

                        //choix de l'ennemi de l'hypothese
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Knight",1500,400,&choix_ennemis,1);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Zote",1600,400,&choix_ennemis,2);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Tiso",1700,400,&choix_ennemis,3);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Hornet",1500,520,&choix_ennemis,4);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Quirrel",1600,520,&choix_ennemis,5);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Cloth",1700,520,&choix_ennemis,6);


                    }
                    //armes
                    textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),1400,650,m_ressources.get_clrs().get_clr("white"),-1,"Arme:%s",armes.c_str());

                    if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
                    {
                        //choix de l'arme de l'hypothese
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Aiguillon",1500,700,&choix_armes,1);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Lance",1600,700,&choix_armes,2);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Griffe",1700,700,&choix_armes,3);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Aiguille",1500,820,&choix_armes,4);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Faux",1600,820,&choix_armes,5);
                        text_card_ex(m_ressources,_jeu,&buffer_tour,"Massue",1700,820,&choix_armes,6);

                    }

                    if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==true&&passe==0)
                    {

                        choix_armes= rand()%6+1;
                        choix_ennemis = rand()%6+1;
                        armes = hypothese_arme(choix_armes);
                        ennemis = hypothese_ennemi(choix_ennemis);
                        passe=1;

                    }

                    //lieu
                    textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),1400,950,m_ressources.get_clrs().get_clr("white"),-1,"Lieu:%s",choix_salles.c_str());

                    if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
                    {
                        armes = hypothese_arme(choix_armes);
                        ennemis = hypothese_ennemi(choix_ennemis);
                    }


                    //bouton confirmer
                    text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T40"),"Confirmer",1,1640,260+800-70,makecol(255,255,255),-1,makecol(128,128,128),-1,&confirm,1);

                    //souris
                    show_mouse(buffer_tour);
                    //affichage du plateau et des joueurs sur la plateau
                    blit(buffer_tour,screen,0,0,0,0,W,H);


                }
                while(choix_armes == 0 || choix_ennemis == 0  || confirm==0);

                armes = hypothese_arme(choix_armes);
                ennemis = hypothese_ennemi(choix_ennemis);

                reponse_hypothese(_jeu.get_tour(), _jeu, choix_salles, ennemis, armes,_jeu,m_ressources);

            }


            /// ------------------------------------------ blinder (accusation) ------------------------------------------ ///

            //si on est sur la case centrale on peut emettre une acccusation ou passser son tour
            if(case_plateau== '5')
            {
                choix = 0;
                //choix de l'accusation ou de passser son tour
                do
                {
                    ///affichage
                    clear_bitmap(buffer_tour);

                    afficher_partie(m_ressources, _jeu, buffer_tour);

                    textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());

                    textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),40,260,m_ressources.get_clrs().get_clr("white"),-1,"Voulez vous:");
                    text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T30"),"Faire une Accusation",1,280,320,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);
                    text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T30"),"Passer le tour",1,280,370,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,2);

                    //souris
                    show_mouse(buffer_tour);
                    blit(buffer_tour,screen,0,0,0,0,W,H);

                }
                while(choix==0);

                switch(choix)
                {

                case 1:

                    confirm=0;

                    do
                    {
                        ///affichage
                        clear_bitmap(buffer_tour);

                        textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),230,30,makecol(255,255,255),-1,"tour du joueur: %s",_jeu.get_joueurs()[_jeu.get_tour()].getNom().c_str());

                        afficher_partie(m_ressources, _jeu, buffer_tour);
                        textprintf_centre_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T40"),20+260,310,m_ressources.get_clrs().get_clr("white"),-1,"Accusation");


                        //choix de l'ennemi de l'accusation
                        textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),1400,350,m_ressources.get_clrs().get_clr("white"),-1,"Suspect:%s",ennemis.c_str());

                        if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
                        {
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Knight",1500,400,&choix_ennemis,1);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Zote",1600,400,&choix_ennemis,2);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Tiso",1700,400,&choix_ennemis,3);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Hornet",1500,520,&choix_ennemis,4);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Quirrel",1600,520,&choix_ennemis,5);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Cloth",1700,520,&choix_ennemis,6);

                        }

                        //choix de l'arme de l'accusation
                        textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),1400,650,m_ressources.get_clrs().get_clr("white"),-1,"Arme:%s",armes.c_str());

                        if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
                        {
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Aiguillon",1500,700,&choix_armes,1);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Lance",1600,700,&choix_armes,2);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Griffe",1700,700,&choix_armes,3);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Aiguille",1500,820,&choix_armes,4);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Faux",1600,820,&choix_armes,5);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Massue",1700,820,&choix_armes,6);

                        }

                        //choix de la salle de l'accusation
                        textprintf_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T20"),40,480,m_ressources.get_clrs().get_clr("white"),-1,"Lieu:%s",salles.c_str());

                        if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==false)
                        {

                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Falaises Hurlantes",140,530,&choix_salles1,1);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Dirtmouth",240,530,&choix_salles1,2);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Mont Cristal",340,530,&choix_salles1,3);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Vertchemin",140,650,&choix_salles1,4);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Jardins de la Reine",240,650,&choix_salles1,5);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Frontieres du Royaume",340,650,&choix_salles1,9);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Nid-profond",140,770,&choix_salles1,6);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"Bassin Ancestral",240,770,&choix_salles1,7);
                            text_card_ex(m_ressources,_jeu,&buffer_tour,"La Ruche",340,770,&choix_salles1,8);

                        }

                        if(_jeu.get_joueurs()[_jeu.get_tour()].get_joueur_ordinateur()==true&&passe==0)
                        {

                            choix_armes= rand()%6+1;
                            choix_ennemis = rand()%6+1;
                            choix_salles1 = rand()%9+1;
                            passe=1;

                        }

                        text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T40"),"Confirmer",1,1640,260+800-70,makecol(255,255,255),-1,makecol(128,128,128),-1,&confirm,1);


                        //souris
                        show_mouse(buffer_tour);
                        blit(buffer_tour,screen,0,0,0,0,W,H);


                        armes = hypothese_arme(choix_armes);
                        ennemis = hypothese_ennemi(choix_ennemis);
                        salles = hypothese_salle(choix_salles1);
                    }
                    while(choix_ennemis==0||choix_salles1==0||choix_armes==0||confirm==0);

                    //verification de l'accusation
                    autorisation_accusation = verification_accusation(_jeu, armes,salles, ennemis);

                    //si l'accusation est vraie, fin de partie
                    if(autorisation_accusation == true)
                    {
                        _jeu.set_fin_partie(2);

                        for(int l=0; l<_jeu.get_nb_joueur(); l++)
                        {
                            if(l!=_jeu.get_tour())
                            {
                                _jeu.get_joueurs()[l].setAlive(false);
                            }
                        }

                        confirm=0;

                        do
                        {
                            clear_bitmap(buffer_tour);

                            blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_tour,0,0,0,0,W,H);

                            ///particules
                            m_ressources.afficher_particules(buffer_part);

                            masked_blit(buffer_part,buffer_tour,0,0,0,0,W,H);

                            textprintf_centre_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"L'accusation est correcte, vous etes le gagnant!");

                            //bouton confirmer
                            text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T40"),"Continuer",1,1640,260+800-70,makecol(255,255,255),-1,makecol(128,128,128),-1,&confirm,1);

                            //souris
                            show_mouse(buffer_tour);
                            //affichage du plateau et des joueurs sur la plateau
                            blit(buffer_tour,screen,0,0,0,0,W,H);


                        }
                        while (confirm==0);

                        cout << "gagnant: " << _jeu.get_joueurs()[_jeu.get_tour()].getNom() << endl;
                    }

                    else
                    {
                        confirm=0;

                        do
                        {
                            clear_bitmap(buffer_tour);

                            blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_tour,0,0,0,0,W,H);

                            ///particules
                            m_ressources.afficher_particules(buffer_part);

                            masked_blit(buffer_part,buffer_tour,0,0,0,0,W,H);

                            textprintf_centre_ex(buffer_tour,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"L'accusation est incorrecte, vous etes elimine!");

                            //bouton confirmer
                            text_button_ex(&buffer_tour,m_ressources.get_fnts().get_fnt("T40"),"Continuer",1,1640,260+800-70,makecol(255,255,255),-1,makecol(128,128,128),-1,&confirm,1);

                            //souris
                            show_mouse(buffer_tour);
                            //affichage du plateau et des joueurs sur la plateau
                            blit(buffer_tour,screen,0,0,0,0,W,H);


                        }
                        while (confirm==0);
                        _jeu.get_joueurs()[_jeu.get_tour()].setAlive(false);
                    }
                    break;

                case 2:
                    tour_fini = 1;
                    break;

                }
            }

            cout << "Suspect: " << ennemis << endl;
            cout << "arme: " << armes << endl;
            cout << "salle: " << choix_salles << endl;

            tour_fini = 1;

            break;

        case 3: // regarder le carnet
            cout << "regarder le carnet" << endl;

            break;

        case 4: //sauvegarder partie
            cout << "SAUVEGARDER PARTIE" << endl;

            sauvegarder_partie(_jeu, _jeu.get_tour());
            _jeu.set_fin_partie(1);
            tour_fini=1;
            break;
        }

    }
    while (tour_fini==0);

    show_mouse(NULL);

    destroy_bitmap(buffer_part);

    destroy_bitmap(buffer_tour);
}


/// ------------------------ PRESENCE SALLE ------------------------ ///

/*
0:case

1: howling cliffs
2: dirtmouth
3: crystal peaks
4: greenpath
5: the city of tears
6: queen's gardens
7: kingdom's edge
8: deepnest
9:ancient basin
a:the hive

b:portes
c:stag
d:spawn
*/

///Sous programme permettant de vértifier la présence d'un joueur dans une salle
string presence_salle(char salle)
{
    string lieu;

    if(salle=='1')
        lieu =  "Falaises Hurlantes";
    if(salle=='2')
        lieu =  "Dirtmouth";
    if(salle=='3')
        lieu =  "Mont Cristal";
    if(salle=='4')
        lieu =  "Vertchemin";
    //if(salle=='5')
    //lieu =  "Cité des Larmes";
    if(salle=='6')
        lieu =  "Jardins de la Reine";
    if(salle=='7')
        lieu =  "Frontieres du Royaume";
    if(salle=='8')
        lieu =  "Nid-profond";
    if(salle=='9')
        lieu =  "Bassin Ancestral";
    if(salle=='a')
        lieu =  "La Ruche";

    return lieu;

}

string hypothese_ennemi(int ennemi)
{
    string choix_ennemi;

    if(ennemi==1)
        choix_ennemi =  "Knight";
    if(ennemi==2)
        choix_ennemi =  "Zote";
    if(ennemi==3)
        choix_ennemi =  "Tiso";
    if(ennemi==4)
        choix_ennemi =  "Hornet";
    if(ennemi==5)
        choix_ennemi =  "Quirrel";
    if(ennemi==6)
        choix_ennemi =  "Cloth";

    return choix_ennemi;

}

string hypothese_arme(int arme)
{
    string choix_arme;

    if(arme==1)
        choix_arme =  "Aiguillon";
    if(arme==2)
        choix_arme =  "Lance";
    if(arme==3)
        choix_arme =  "Griffe";
    if(arme==4)
        choix_arme =  "Aiguille";
    if(arme==5)
        choix_arme =  "Faux";
    if(arme==6)
        choix_arme =  "Massue";

    return choix_arme;

}

string hypothese_salle(int salle)
{
    string choix_salle;

    if(salle==1)
        choix_salle =  "Falaises Hurlantes";
    if(salle==2)
        choix_salle =  "Dirtmouth";
    if(salle==3)
        choix_salle =  "Mont Cristal";
    if(salle==4)
        choix_salle =  "Vertchemin";
    if(salle==5)
        choix_salle =  "Jardins de la Reine";
    if(salle==6)
        choix_salle =  "Nid-profond";
    if(salle==7)
        choix_salle =  "Bassin Ancestral";
    if(salle==8)
        choix_salle =  "La Ruche";
    if(salle==9)
        choix_salle =  "Frontieres du Royaume";

    return choix_salle;

}

///Sous programme permettant de vérifier si une accusation est juste ou non
bool verification_accusation(Jeu &m_jeu, string arme, string salle, string ennemi)
{

    if( arme==m_jeu.getEnveloppe().getArme().getNom() && salle==m_jeu.getEnveloppe().getSalle().getNom() && ennemi==m_jeu.getEnveloppe().getEnnemi().getNom() )
    {
        cout << "enveloppe ok" << endl;
        return true;
    }
    return false;
}

/*
    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*0,32*9,32,64); //gauche (1,11)

    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*24,32*10,32,64); //droite (25,12)

    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*18,32*0,32,64); // haut (19,2)

    masked_blit(m_ressources.get_imgs().get_img("stag"),buffer_zones,0,0,32*17,32*23,32,64); // bas (18,25)
    */

///Sous programme permettant à un joueur de se téléporter sur le plateau de jeu
void teleportation (Joueur &joueur) //teleporter le joueur a une autre station aléatoirement
{
    int nombre;

    nombre = rand()%(3)+1;


    switch (nombre)
    {
    case 1: //gauche
        joueur.setPositionX(1);
        joueur.setPositionY(11);
        break;

    case 2://droite
        joueur.setPositionX(25);
        joueur.setPositionY(12);
        break;

    case 3://haut
        joueur.setPositionX(19);
        joueur.setPositionY(2);
        break;

    case 4://bas
        joueur.setPositionX(18);
        joueur.setPositionY(25);
        break;

    default:
        break;
    }
}


///Sous programme permettant de faire une réponse à une hypothèse
void reponse_hypothese (int num_joueur, Jeu &_jeu, string salle, string ennemi, string arme,Jeu & m_jeu, Ressources & m_ressources)
{
    BITMAP * buffer_hypo=create_bitmap(W,H);

    BITMAP * buffer_part=create_bitmap(W,H);
    //si plusieurs carte faire choisir
    bool a_salle = false;
    bool a_ennemi = false;
    bool a_arme = false;
    int nombre;
    int j=0;
    int joueur;

    int confirm = 0;

    joueur = num_joueur-1;

    do
    {

        if(num_joueur<_jeu.get_nb_joueur())
        {
            num_joueur = num_joueur +1;
        }
        else
        {
            num_joueur = 0;
        }

        cout << "affichage joueurrrrrrrrrrr" << joueur << endl;

        if(num_joueur!=joueur)
        {

            for(unsigned int i=0; i<_jeu.get_joueurs()[num_joueur].getTaille(); i++)
            {
                if(_jeu.get_joueurs()[num_joueur].getCarte(i).getNom()==salle)
                {
                    a_salle = true;
                }
                if(_jeu.get_joueurs()[num_joueur].getCarte(i).getNom()==ennemi)
                {
                    a_ennemi = true;
                }
                if(_jeu.get_joueurs()[num_joueur].getCarte(i).getNom()==arme)
                {
                    a_arme = true;
                }
            }

        }


        j++;

    }

    while((a_salle == false)&&(a_ennemi==false)&&(a_arme == false)&&(j<_jeu.get_nb_joueur()));

    cout << "carte montreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee: " << endl;

    do
    {

        clear_bitmap(buffer_hypo);

        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_hypo,0,0,0,0,W,H);

        ///particules
        m_ressources.afficher_particules(buffer_part);

        masked_blit(buffer_part,buffer_hypo,0,0,0,0,W,H);

        if(a_arme == true&&a_salle == false &&a_ennemi == false)
        {
            cout << arme << endl;
            cout << "joueur qui a la carte " << num_joueur << endl;
            textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());

            ///montrer la carte
            masked_stretch_blit(m_ressources.get_imgs().afficher_carte(arme),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);

        }
        else if(a_salle == true&&a_arme == false&&a_ennemi==false)
        {
            cout << salle << endl;
            cout << "joueur qui a la carte " << num_joueur << endl;
            textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());

            masked_stretch_blit(m_ressources.get_imgs().afficher_carte(salle),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);

        }
        else if(a_ennemi == true&&a_arme == false && a_salle == false)
        {
            cout << ennemi << endl;
            cout << "joueur qui a la carte " << num_joueur << endl;
            textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
            masked_stretch_blit(m_ressources.get_imgs().afficher_carte(ennemi),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
        }

        else if(a_ennemi==true&&a_salle==true&&a_arme==false)
        {
            nombre = rand()%(1);
            if(nombre==1)
            {
                cout << "ennemi: " << ennemi << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer ennemi
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(ennemi),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
            if(nombre==0)
            {
                cout << "salle: " << salle << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer salle
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(salle),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
        }
        else if(a_ennemi==true&&a_arme==true&&a_salle==false)
        {
            nombre = rand()%(1);
            if(nombre==1)
            {
                cout << "ennemi: " << ennemi << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                //montrer ennemi
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(ennemi),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
            if(nombre==0)
            {
                cout << "arme: " << arme << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer arme
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(arme),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
        }
        else if(a_salle==true&&a_arme==true&& a_ennemi == false)
        {
            nombre = rand()%(1);
            if(nombre==1)
            {
                cout << "salle: " << salle << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer salle
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(salle),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
            if(nombre==0)
            {
                cout << "arme: " << arme << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer arme
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(arme),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
        }
        else if(a_arme ==true && a_salle == true && a_ennemi == true)
        {
            nombre = rand()%(2);
            if(nombre==1)
            {
                cout << "salle: " << salle << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer salle
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(salle),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }
            if(nombre==0)
            {
                cout << "arme: " << arme << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer arme
            }
            if(nombre==2)
            {
                cout << "ennemi: " << ennemi << endl;
                cout << "joueur qui a la carte " << num_joueur << endl;
                textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"%s vous montre la carte suivante:",_jeu.get_joueurs()[num_joueur].getNom().c_str());
                //montrer ennemi
                masked_stretch_blit(m_ressources.get_imgs().afficher_carte(ennemi),buffer_hypo,0,0,80,100,W/2-80,H/2-100,160,200);
            }

        }

        if((a_salle == false)&&(a_ennemi==false)&&(a_arme == false))
        {
            cout << "il n'y a aucune carte a montrer" << endl;
            textprintf_centre_ex(buffer_hypo,m_ressources.get_fnts().get_fnt("T40"),W/2,200,m_ressources.get_clrs().get_clr("white"),-1,"L'hypothese est correcte!");
        }

        //bouton confirmer
        text_button_ex(&buffer_hypo,m_ressources.get_fnts().get_fnt("T30"),"Confirmer",1,W/2,H-200,makecol(255,255,255),-1,makecol(128,128,128),-1,&confirm,1);

        show_mouse(buffer_hypo);

        blit(buffer_hypo,screen,0,0,0,0,W,H);
    }
    while(confirm==0);



    show_mouse(NULL);

    destroy_bitmap(buffer_hypo);

}

