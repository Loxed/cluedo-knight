#include "header.h"

///Sous programme permettant de gérer les paramètres pour les comptes des joueurs
void parametres_comptes(Ressources & m_ressources)
{
    //Variable
    string nom_joueur;
    int choix=0;

    //buffer
    BITMAP * buffer_compte=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);

    do
    {
        //clear buffer
        clear_bitmap(buffer_compte);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_compte,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_compte,0,0,0,0,W,H);

        //retour menu principal
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,10,10,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);

        //creer un compte
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T30"),"Creer un compte",1,W/2,200,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,2);

        //afficher les stats d'un compte
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T30"),"Afficher les statistiques d'un compte",1,W/2,300,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,3);

        //effacer un compte
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T30"),"Effacer un compte",1,W/2,400,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,4);

        //effacer tous les comptes
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T30"),"Effacer tous les comptes",1,W/2,500,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,5);

        //souris
        show_mouse(buffer_compte);

        //afficher sur le buffer
        blit(buffer_compte,screen,0,0,0,0,W,H);

    }
    while (choix==0); //boucle tant que l'on a pas appuyé sur un bouton

    switch (choix)
    {
    case 1:
        //retour au menu principal
        menu_principal(m_ressources);

    case 2:
        //on écrit le nom du joueur
        nom_joueur = choix_nom_joueurs(0, m_ressources);

        //on sauvegarde le joueur dans un fichier
        sauver_joueur(nom_joueur);

        //on revienbt au parametre des comptes
        parametres_comptes(m_ressources);
        break;

    case 3:
        //on écrit le nom du joueur
        nom_joueur = choix_compte_joueurs( m_ressources);

        //on affiche les statistiques
        affichage_statistiques_comptes(m_ressources, nom_joueur);

        //on revient au parametre des comptes
        parametres_comptes(m_ressources);
        break;

    case 4:
        //on écrit le nom du joueur
        nom_joueur = choix_compte_joueurs( m_ressources);

        //on supprime un compte
        supprimer_compte(m_ressources, nom_joueur);

        //on revient au parametre des comptes
        parametres_comptes(m_ressources);
        break;

    case 5:
        //on efface tous les comptes
        supprimer_tout_compte(m_ressources);

        //on revient au parametre des comptes
        parametres_comptes(m_ressources);
        break;

    default:
        parametres_comptes(m_ressources);

        break;
    }

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_compte);
    destroy_bitmap(buffer_part);

}

///Sous programme permettant d'afficher les statistiques d'un compte
void affichage_statistiques_comptes(Ressources & m_ressources, string nom_joueur)
{
    //Variable
    string nom;
    int retour=0;
    string niveau, nbr_parties, nbr_defaites, nbr_victoires;
    std::vector<char> chaine;
    string temp;

    //buffer
    BITMAP * buffer_compte=create_bitmap(W,H);;
    BITMAP * buffer_part=create_bitmap(W,H);

    //fichier
    string const nomFichier("joueurs.txt");
    std::ifstream FILE_joueurs(nomFichier.c_str());

    if(FILE_joueurs.is_open())//blindage
    {
        //on lit le fichier entier
        while(!FILE_joueurs.eof())
        {
            getline(FILE_joueurs,nom);
            //si le nom entré existe dans le fichier
            if(nom==nom_joueur)
            {
                getline(FILE_joueurs,nbr_parties);
                getline(FILE_joueurs,nbr_victoires);
                getline(FILE_joueurs,nbr_defaites);
                getline(FILE_joueurs,niveau);

                do
                {
                    //clear buffer
                    clear_bitmap(buffer_compte);

                    //fond d'ecran
                    blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_compte,0,0,0,0,W,H);

                    //particules
                    m_ressources.afficher_particules(buffer_part);
                    masked_blit(buffer_part,buffer_compte,0,0,0,0,W,H);

                    //on affiche les differentes statistiques
                    text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,10,10,makecol(255,255,255),-1,makecol(128,128,128),-1,&retour,1);
                    temp = nom_joueur;
                    chaine.clear();
                    std::copy(temp.begin(),temp.end(),std::back_inserter(chaine));
                    chaine.push_back('\0');
                    textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,300,m_ressources.get_clrs().get_clr("white"),-1,"Statistiques de: %s",&*chaine.begin());
                    temp = niveau;
                    chaine.clear();
                    std::copy(temp.begin(),temp.end(),std::back_inserter(chaine));
                    chaine.push_back('\0');
                    textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,400,m_ressources.get_clrs().get_clr("white"),-1,"Niveau: %s",&*chaine.begin());
                    temp = nbr_parties;
                    chaine.clear();
                    std::copy(temp.begin(),temp.end(),std::back_inserter(chaine));
                    chaine.push_back('\0');
                    textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,500,m_ressources.get_clrs().get_clr("white"),-1,"Nombre de parties: %s",&*chaine.begin());
                    temp = nbr_victoires;
                    chaine.clear();
                    std::copy(temp.begin(),temp.end(),std::back_inserter(chaine));
                    chaine.push_back('\0');
                    textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,600,m_ressources.get_clrs().get_clr("white"),-1,"Nombre de victoires: %s",&*chaine.begin());
                    temp = nbr_defaites;
                    chaine.clear();
                    std::copy(temp.begin(),temp.end(),std::back_inserter(chaine));
                    chaine.push_back('\0');
                    textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,700,m_ressources.get_clrs().get_clr("white"),-1,"Nombre de defaites: %s",&*chaine.begin());

                    //souris
                    show_mouse(buffer_compte);

                    //on affiche le buffer
                    blit(buffer_compte,screen,0,0,0,0,W,H);

                }
                while(retour == 0); //boucle tant que l'on a pas appuyé sur le bouton retour
            }
        }
        //on ferme le fichier
        FILE_joueurs.close();
    }

    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_compte);
    destroy_bitmap(buffer_part);

}

///Sous programmes permettant de supprimer un compte
void supprimer_compte(Ressources & m_ressources, string nom_joueur)
{
    //Variable
    string ligne;
    string temp;
    std::vector<char> chaine;
    string contenu_compte = "";
    int retour =0;

    //buffer
    BITMAP * buffer_compte=create_bitmap(W,H);;
    BITMAP * buffer_part=create_bitmap(W,H);

    //fichier
    string const monFichier("joueurs.txt");
    std::ifstream FILE_joueurs(monFichier.c_str());

    //blindage
    if (FILE_joueurs)
    {
        //on lit le fichier entier
        while(!FILE_joueurs.eof())
        {
            getline( FILE_joueurs, ligne );
            //si il y a un nom pareil entre cdelui ecrit et dans le fichier
            if(ligne==nom_joueur)
            {
                getline(FILE_joueurs, ligne);
                getline(FILE_joueurs, ligne);
                getline(FILE_joueurs, ligne);
                getline(FILE_joueurs, ligne);
            }
            else if(ligne=="")
            {

            }
            else
            {
                contenu_compte += ligne + "\n";
            }
        }
        FILE_joueurs.close();
    }
    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

    std::ofstream FILE_joueurs_ecriture(monFichier.c_str());
    if (FILE_joueurs_ecriture)
    {
        FILE_joueurs_ecriture << contenu_compte;
        FILE_joueurs_ecriture.close();
    }
    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

    do
    {
        //clear buffer
        clear_bitmap(buffer_compte);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_compte,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_compte,0,0,0,0,W,H);

        //bouton retour
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,10,10,makecol(255,255,255),-1,makecol(128,128,128),-1,&retour,1);
        temp = nom_joueur;
        chaine.clear();
        std::copy(temp.begin(),temp.end(),std::back_inserter(chaine));
        chaine.push_back('\0');

        //texte
        textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,H/2,m_ressources.get_clrs().get_clr("white"),-1,"Le compte de %s a bien ete supprime", &*chaine.begin());

        //souris
        show_mouse(buffer_compte);

        //on affiche le buffer
        blit(buffer_compte,screen,0,0,0,0,W,H);

    }
    while(retour==0); //boucle tant que l'on a pas appuyé sur le bouton retour

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_compte);
    destroy_bitmap(buffer_part);
}

///Sous programme permettant de supprimer tous les comptes
void supprimer_tout_compte(Ressources & m_ressources)
{
    //Variable
    int retour=0;

    //supprimer tous les éléments dans le fichier
    std::ofstream FILE_joueurs;
    FILE_joueurs.open ("joueurs.txt", std::ofstream::out );
    FILE_joueurs << "" ;
    FILE_joueurs.close();

    //buffer
    BITMAP * buffer_compte=create_bitmap(W,H);;
    BITMAP * buffer_part=create_bitmap(W,H);

    do
    {
        //clear buffer
        clear_bitmap(buffer_compte);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_compte,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_compte,0,0,0,0,W,H);

        //bouton retour
        text_button_ex(&buffer_compte,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,10,10,makecol(255,255,255),-1,makecol(128,128,128),-1,&retour,1);

        //texte
        textprintf_centre_ex(buffer_compte,m_ressources.get_fnts().get_fnt("T40"),W/2,H/2,m_ressources.get_clrs().get_clr("white"),-1,"Tous les comptes ont ete supprime");

        //souris
        show_mouse(buffer_compte);

        //on affiche le buffer sur l'écran
        blit(buffer_compte,screen,0,0,0,0,W,H);

    }
    while(retour==0); //boucle tant que l'on a pas appuyé sur le bouton retour

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_compte);
    destroy_bitmap(buffer_part);
}
