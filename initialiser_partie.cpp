#include "header.h"
#include "Jeu.h"
#include "joueur.h"
#include "carte.h"
#include "enveloppe.h"

using std::cout;
using std::endl;
using std::string;

///Sous programme permettant d'initialiser une partie de jeu
void initialiser_partie(Ressources & m_ressources, Jeu & m_jeu)
{
    //initialiser un Jeu
    m_jeu.afficher_cartes();

    //creer l'enveloppe
    m_jeu.creer_enveloppe();

    cout << m_jeu.getEnveloppe().getArme().getNom() << endl;
    cout << m_jeu.getEnveloppe().getSalle().getNom() << endl;
    cout << m_jeu.getEnveloppe().getEnnemi().getNom() << endl;

    //Mettre les cartes restantes dans m_pioche
    m_jeu.remplir_pioche();

    //choisir le nombre de joueurs
    choix_nbr_joueurs(m_jeu,m_ressources);

    //si on joue avec une intelligence artificielle
    if(jouer_bot(m_ressources)==true)
    {
        choix_nbr_joueurs_ordinateurs(m_jeu, m_ressources);
    }

    //on nomme les joueurs ordinateur
    for(int i=0; i<m_jeu.get_nb_joueur_ordinateur(); i++)
    {
        m_jeu.get_joueurs()[i].set_joueur_ordinateur(true);
        m_jeu.get_joueurs()[i].setNom("Ordinateur");
    }

    //ajouter ou selectionner un joueur en fonction du nombre de joueur dans la partie
    for (int i=0; i<m_jeu.get_nb_joueur(); i++)
    {
        //on entre das la partie un nouveau joueur
        rentrer_joueurs(m_jeu, i,m_ressources);

        //Initialisation du point de départ du personnages quirrel
        if(m_jeu.get_joueurs()[i].get_personnage()=="quirrel")
        {
            m_jeu.get_joueurs()[i].set_pos_initiale_x(1);
            m_jeu.get_joueurs()[i].set_pos_initiale_y(6);
        }

        //Initialisation du point de départ du personnages tiso
        if(m_jeu.get_joueurs()[i].get_personnage()=="tiso")
        {
            m_jeu.get_joueurs()[i].set_pos_initiale_x(22);
            m_jeu.get_joueurs()[i].set_pos_initiale_y(18);
        }

        //Initialisation du point de départ du personnages knight
        if(m_jeu.get_joueurs()[i].get_personnage()=="knight")
        {
            m_jeu.get_joueurs()[i].set_pos_initiale_x(14);
            m_jeu.get_joueurs()[i].set_pos_initiale_y(25);
        }

        //Initialisation du point de départ du personnages cloth
        if(m_jeu.get_joueurs()[i].get_personnage()=="cloth")
        {
            m_jeu.get_joueurs()[i].set_pos_initiale_x(25);
            m_jeu.get_joueurs()[i].set_pos_initiale_y(4);
        }

        //Initialisation du point de départ du personnages zote
        if(m_jeu.get_joueurs()[i].get_personnage()=="zote")
        {
            m_jeu.get_joueurs()[i].set_pos_initiale_x(17);
            m_jeu.get_joueurs()[i].set_pos_initiale_y(1);
        }

        //Initialisation du point de départ du personnages hornet
        if(m_jeu.get_joueurs()[i].get_personnage()=="hornet")
        {
            m_jeu.get_joueurs()[i].set_pos_initiale_x(1);
            m_jeu.get_joueurs()[i].set_pos_initiale_y(18);
        }

        m_jeu.get_joueurs()[i].setPositionX(m_jeu.get_joueurs()[i].get_pos_initiale_x());
        m_jeu.get_joueurs()[i].setPositionY(m_jeu.get_joueurs()[i].get_pos_initiale_y());
    }

    //on distribue les cartes au différents joueurs de la partie
    distribution_cartes_joueur(m_jeu);
}

///Sous programme permettant de lancer le jeu d'une partie
void lancer_jeu (Ressources & m_ressources, Jeu &m_jeu)
{

    BITMAP * buffer_fin=create_bitmap(W,H);
    //Variable
    int joueur_mort = 0;

    //on commence une partie
    m_jeu.set_fin_partie(0);

    int choix=0;

    float compte=0;

    do
    {
        //compter le nombre de joueurs mort
        joueur_mort=0;

        //on regarde le nombre de joueur
        for(int k=0; k<m_jeu.get_nb_joueur(); k++)
        {
            //si il est plus en vie
            if( m_jeu.get_joueurs()[k].getAlive()==false)
            {
                //on incrémente le compteur
                joueur_mort++;
            }

        }

        //si tous les joueurs sont mort, finir la partie
        if(joueur_mort == m_jeu.get_nb_joueur())
        {
            m_jeu.set_fin_partie(1);
        }

        //si le joueur actuel est en vie
        if(m_jeu.get_joueurs()[m_jeu.get_tour()].getAlive() == true)
        {
            ///lancer un tour pour se joueur
            tour(m_ressources,m_jeu);

            if(m_jeu.get_fin_partie()==0)
                m_jeu.set_tour(m_jeu.get_tour()+1);
        }

        else  m_jeu.set_tour(m_jeu.get_tour()+1);


    }

    while(m_jeu.get_fin_partie()==0); //on boucle tant que la partie n'est pas finie

    cout << "etat fin: " << m_jeu.get_fin_partie() << endl;

    ///afficher ecran de fin de partie
    //cout << "gagnant: " << m_jeu.get_joueurs()[m_jeu.get_tour()].getNom() << endl;

    if(m_jeu.get_fin_partie()==1) // personne a gagné
    {
        do
        {

            compte+=0.1;

            if(compte==432) compte=0;

            blit(m_ressources.get_imgs().get_img("fin"),buffer_fin,0,0,0,0,W,H);

            for (int i=0; i<m_jeu.get_nb_joueur(); i++)
            {
                //masked_blit(m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte),buffer_fin,0,0,310*i,900-m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte)->h*4,64,64);
                masked_stretch_blit(m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte),buffer_fin, 0, 0, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte)->w, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte)->h, 310*i+170, 900-m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte)->h*4, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte)->w*4, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[i].get_personnage(),(int)compte)->h*4);
            }

            textprintf_centre_ex(buffer_fin,m_ressources.get_fnts().get_fnt("T40"),W/2,200,makecol(255,255,255),-1,"Personne n'a gagne!");

            text_button_ex(&buffer_fin,m_ressources.get_fnts().get_fnt("T30"),"Confirmer",1,W/2,H-200,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);

            show_mouse(buffer_fin);

            blit(buffer_fin,screen,0,0,0,0,W,H);

        }
        while (choix==0);
    }

    else if (m_jeu.get_fin_partie()==2) // x a gagné
    {

        do
        {

            compte+=0.1;

            if(compte==432) compte=0;

            blit(m_ressources.get_imgs().get_img("fin"),buffer_fin,0,0,0,0,W,H);

            masked_stretch_blit(m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte),buffer_fin, 0, 0, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte)->w, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte)->h, W/2-m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte)->w*2, 900-m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte)->h*4, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte)->w*4, m_ressources.get_anims().get_frame_perso(m_jeu.get_joueurs()[m_jeu.get_tour()].get_personnage(),(int)compte)->h*4);

            textprintf_centre_ex(buffer_fin,m_ressources.get_fnts().get_fnt("T40"),W/2,200,makecol(255,255,255),-1,"%s a gagne!",m_jeu.get_joueurs()[m_jeu.get_tour()].getNom().c_str());

            text_button_ex(&buffer_fin,m_ressources.get_fnts().get_fnt("T30"),"Confirmer",1,W/2,H-200,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);

            show_mouse(buffer_fin);

            blit(buffer_fin,screen,0,0,0,0,W,H);

            //m_jeu.get_joueurs()[m_jeu.get_tour()].getNom();

        }
        while (choix==0);

        //charger les nouveaux scores
        fin_partie_compte(m_jeu);

        show_mouse(NULL);

        destroy_bitmap(buffer_fin);

    }
}

///Sous programme permettant de choisir le nombre de joueur dans une partie
void choix_nbr_joueurs(Jeu & _jeu,Ressources & m_ressources)
{
    //buffer
    BITMAP * buffer_choix=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);

    //Variable
    int _nb_joueurs=_jeu.get_nb_joueur();

    do
    {
        //clear le buffer
        clear_bitmap(buffer_choix);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_choix,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_choix,0,0,0,0,W,H);

        //afficher nombre de joueurs
        textprintf_centre_ex(buffer_choix,m_ressources.get_fnts().get_fnt("T40"),W/2,230,m_ressources.get_clrs().get_clr("white"),-1,"Nombre de joueurs: %d",_nb_joueurs);

        //fleche gauche pr diminuer
        text_button_ex(&buffer_choix,m_ressources.get_fnts().get_fnt("F40"),"<",1,W/2-text_length(m_ressources.get_fnts().get_fnt("T40"),"Nombre de joueurs: 8")/2-65,160,makecol(255,255,255),-1,makecol(128,128,128),-1,&_nb_joueurs,_nb_joueurs-1);

        //fleche droite pour incrementer
        text_button_ex(&buffer_choix,m_ressources.get_fnts().get_fnt("F40"),">",1,W/2+text_length(m_ressources.get_fnts().get_fnt("T40"),"Nombre de joueurs: 8")/2+65,160,makecol(255,255,255),-1,makecol(128,128,128),-1,&_nb_joueurs,_nb_joueurs+1);

        //blinder nombre de joueurs
        if(_nb_joueurs<3) _nb_joueurs=3;
        if(_nb_joueurs>6) _nb_joueurs=6;

        //on set le nombre de joueur
        _jeu.set_nb_joueur(_nb_joueurs);

        //souris
        show_mouse(buffer_choix);

        //afficher le buffer
        blit(buffer_choix,screen,0,0,0,0,W,H);

    }
    while (!key[KEY_ENTER]); //on boucle tant qu'on a pas appuy sur la touche entrée

    //souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on détruit les bitmps pour eviter les failles memoires
    destroy_bitmap(buffer_choix);
    destroy_bitmap(buffer_part);
}

///Sous programme permettant de savoir si on joue avc une ia ou non
bool jouer_bot(Ressources & m_ressources)
{
    //buffer
    BITMAP * buffer_choix=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);

    //Variable
    int choix1 = 0;
    bool choix = false;

    do
    {
        //clear le buffer choix
        clear_bitmap(buffer_choix);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_choix,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_choix,0,0,0,0,W,H);

        //afficher si on veut jouer avec des ordinateurs
        textprintf_centre_ex(buffer_choix,m_ressources.get_fnts().get_fnt("T40"),W/2,230,m_ressources.get_clrs().get_clr("white"),-1,"Jouer avec des joueurs ordinateurs: ");

        //bouton oui
        text_button_ex(&buffer_choix,m_ressources.get_fnts().get_fnt("T20"),"OUI",1,W/2,400,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix1,1);

        //bouton non
        text_button_ex(&buffer_choix,m_ressources.get_fnts().get_fnt("T20"),"NON",1,W/2,500,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix1,2);

        //souris
        show_mouse(buffer_choix);

        //on affiche le buffer
        blit(buffer_choix,screen,0,0,0,0,W,H);

    }
    while (choix1==0); //on boucle tant qu'on a pas appuyé sur un des 2 boutons

    //on organise les choix
    if(choix1==1) (choix =true);
    if(choix1==2) (choix =false);

    //souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on détruit les bitmpas pour eviter les failles memoires
    destroy_bitmap(buffer_choix);
    destroy_bitmap(buffer_part);

    //on retourne au programme appelant le choix fait
    return choix;
}

///Sous programme permettant de choisir le nombre de joueur ia
void choix_nbr_joueurs_ordinateurs(Jeu & _jeu,Ressources & m_ressources)
{
    //buffer
    BITMAP * buffer_choix=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);

    //Variable
    int _nb_joueurs= 1;

    do
    {
        //clear le buffer
        clear_bitmap(buffer_choix);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_choix,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_choix,0,0,0,0,W,H);

        //afficher nombre de joueurs ordinateurs
        textprintf_centre_ex(buffer_choix,m_ressources.get_fnts().get_fnt("T40"),W/2,230,m_ressources.get_clrs().get_clr("white"),-1,"Nombre de joueurs ordinateur: %d",_nb_joueurs);

        //fleche gauche pr diminuer
        text_button_ex(&buffer_choix,m_ressources.get_fnts().get_fnt("F40"),"<",1,W/2-text_length(m_ressources.get_fnts().get_fnt("T40"),"Nombre de joueurs ordinateur: 8")/2-65,160,makecol(255,255,255),-1,makecol(128,128,128),-1,&_nb_joueurs,_nb_joueurs-1);

        //fleche droite pour incrementer
        text_button_ex(&buffer_choix,m_ressources.get_fnts().get_fnt("F40"),">",1,W/2+text_length(m_ressources.get_fnts().get_fnt("T40"),"Nombre de joueurs ordinateur: 8")/2+65,160,makecol(255,255,255),-1,makecol(128,128,128),-1,&_nb_joueurs,_nb_joueurs+1);

        //blinder nombre de joueurs
        if(_nb_joueurs>_jeu.get_nb_joueur()) _nb_joueurs=_jeu.get_nb_joueur();
        if(_nb_joueurs<0) _nb_joueurs=0;

        //on set le nombre de joueur ordinateur
        _jeu.set_nb_joueur_ordinateur(_nb_joueurs);

        //souris
        show_mouse(buffer_choix);

        //on affiche le buffer
        blit(buffer_choix,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_ENTER]); //on boucle tant qu'on a pas appuyé sur la touche entrée

    //souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on déteuit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_choix);
    destroy_bitmap(buffer_part);
}

///Sours programme permettant de faire le choix du nom du joueur sous allegro
string choix_nom_joueurs(int i, Ressources & m_ressources)
{
    //buffer
    BITMAP * buffer_nom=create_bitmap(W,H);;
    BITMAP * zone_nom=create_bitmap(text_length(font,"MMMMMMMMMM")+10,text_height(font));;
    BITMAP * buffer_part=create_bitmap(W,H);

    string nom_joueurs="Player";
    nom_joueurs+=i+'1';
    std::vector<char> chaine;
    cout << nom_joueurs<<endl;

    do
    {
        //clear le buffer
        clear_bitmap(buffer_nom);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_nom,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_nom,0,0,0,0,W,H);

        //lancer modifier nom
        modifier_nom(nom_joueurs);

        //si le nom du joueur n'existe pas
        if(verification_compte_joueur(nom_joueurs)== false)
        {
            modifier_nom(nom_joueurs);
        }
        else
        {
            //si le nom du joueur est deja utilisé
            textprintf_centre_ex(buffer_nom,m_ressources.get_fnts().get_fnt("T40"),W/2,750,m_ressources.get_clrs().get_clr("white"),-1,"Nom deja utilise");
        }

        //convertir string en char*
        chaine.clear();
        std::copy(nom_joueurs.begin(), nom_joueurs.end(), std::back_inserter(chaine));
        chaine.push_back('\0');

        //afficher le texte
        textprintf_centre_ex(buffer_nom,m_ressources.get_fnts().get_fnt("T40"),W/2,250,m_ressources.get_clrs().get_clr("white"),-1,"%s", &*chaine.begin());

        //souris
        show_mouse(buffer_nom);

        //afficher le buffer
        blit(buffer_nom,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_ENTER]||verification_compte_joueur(nom_joueurs)== true); //on boucle tant qu'on a pas appuyé sur entrée et qu'on a pas bien choisi le nom du joeuur

    //souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_nom);
    destroy_bitmap(buffer_part);
    destroy_bitmap(zone_nom);

    //on retourne au programme appelant le nom du joueur
    return nom_joueurs;
}

///Sous programme permettant de vérifie si le joueur à déja un compte ou non
bool verification_compte_joueur(string nom_joueurs)
{
    //Variable
    string nom;
    bool j=false;

    //fichier
    string const nomFichier("joueurs.txt");
    std::ifstream FILE_joueurs(nomFichier.c_str());

    if(FILE_joueurs.is_open())//blindage
    {
        //on regarde tout le fichier
        while(!FILE_joueurs.eof())
        {
            getline(FILE_joueurs,nom);
            if(nom==nom_joueurs) //si le nom est déja présent
            {
                j=true;
            }

        }
        //on ferme le fichier
        FILE_joueurs.close();
    }

    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

    //on retourne vrai ou faux si le nom est présent ou pas
    return j;

}

///Sous programme permettant de choisir le compte d'un joueur présent
string choix_compte_joueurs(Ressources & m_ressources)
{
    //Variable
    int i=0;

    //buffer
    BITMAP * buffer_nom=create_bitmap(W,H);;
    BITMAP * zone_nom=create_bitmap(text_length(font,"MMMMMMMMMM")+10,text_height(font));
    BITMAP * buffer_part=create_bitmap(W,H);

    string nom_joueurs="Player";
    nom_joueurs+=i+'1';
    std::vector<char> chaine;
    cout << nom_joueurs<<endl;

    do
    {
        //clear le buffer
        clear_bitmap(buffer_nom);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_nom,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_nom,0,0,0,0,W,H);

        //lancer modifier nom
        modifier_nom(nom_joueurs);

        //si le joueur a un compte
        if(verification_compte_joueur(nom_joueurs)== true)
        {
            modifier_nom(nom_joueurs);
        }
        else
        {
            //si le joueur n'a pas de compte
            textout_centre_ex(buffer_nom,m_ressources.get_fnts().get_fnt("T40"),"Ce joueur n'a pas de compte",W/2,750,makecol(255,255,255),-1);
        }

        //convertir string en char*
        chaine.clear();
        std::copy(nom_joueurs.begin(), nom_joueurs.end(), std::back_inserter(chaine));
        chaine.push_back('\0');


        //afficher le texte
        textprintf_centre_ex(buffer_nom,m_ressources.get_fnts().get_fnt("T40"),W/2,250,m_ressources.get_clrs().get_clr("white"),-1,"%s", &*chaine.begin());        //si le nom est vide, afficher un nom de remplacement en rouge

        //souris
        show_mouse(buffer_nom);

        //on affiche le buffer
        blit(buffer_nom,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_ENTER]||verification_compte_joueur(nom_joueurs)== false); //on boucle ta,t qu'on a pas appuyé sur la tocuhe entrée et que le joueur n'a pas de compte

    //souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on detruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(zone_nom);
    destroy_bitmap(buffer_nom);
    destroy_bitmap(buffer_part);

    //on retourne le nom du joueur au programme appelant
    return nom_joueurs;
}

///Sours programme permettant de mettre a jour les compte en fin de partie
void fin_partie_compte(Jeu &_jeu)
{
    //Variable
    string ligne;
    string contenu_compte;

    //Mise a jour des comptes
    for(int i=0; i<_jeu.get_nb_joueur(); i++)
    {
        if(_jeu.get_joueurs()[i].getAlive()==true)
        {
            _jeu.get_joueurs()[i].setNbrVictoire(_jeu.get_joueurs()[i].getNbrVictoire()+1);
        }
        else
        {
            _jeu.get_joueurs()[i].setNbrDefaite(_jeu.get_joueurs()[i].getNbrDefaite()+1);
        }

        _jeu.get_joueurs()[i].setNbrPartie(_jeu.get_joueurs()[i].getNbrPartie()+1);

        if(_jeu.get_joueurs()[i].getNbrVictoire()<1)
        {
            _jeu.get_joueurs()[i].setNiveau(0);
        }
        if(_jeu.get_joueurs()[i].getNbrVictoire()>=1&&_jeu.get_joueurs()[i].getNbrVictoire()<3)
        {
            _jeu.get_joueurs()[i].setNiveau(1);
        }
        if(_jeu.get_joueurs()[i].getNbrVictoire()>3&&_jeu.get_joueurs()[i].getNbrVictoire()<10)
        {
            _jeu.get_joueurs()[i].setNiveau(2);
        }
        if(_jeu.get_joueurs()[i].getNbrVictoire()>=10)
        {
            _jeu.get_joueurs()[i].setNiveau(3);

        }
    }

    string const monFichier("joueurs.txt");

    for(int i=0; i<_jeu.get_nb_joueur(); i++)
    {
        contenu_compte="";
        std::ifstream FILE_joueurs(monFichier.c_str());

        if (FILE_joueurs)
        {
            while(!FILE_joueurs.eof())
            {
                getline( FILE_joueurs, ligne );
                if(ligne==_jeu.get_joueurs()[i].getNom())
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

        }
        FILE_joueurs.close();

        std::ofstream FILE_joueurs_ecriture(monFichier.c_str());
        if (FILE_joueurs_ecriture)
        {
            FILE_joueurs_ecriture << contenu_compte;
            FILE_joueurs_ecriture.close();
        }

    }

    std::ofstream FILE_joueurs_ecriture(monFichier.c_str());
    if (FILE_joueurs_ecriture)
    {
        FILE_joueurs_ecriture << contenu_compte;

        for(int i=0; i<_jeu.get_nb_joueur(); i++)
        {
            if(_jeu.get_joueurs()[i].get_joueur_ordinateur()==false)
            {
                FILE_joueurs_ecriture << _jeu.get_joueurs()[i].getNom()<< endl;
                FILE_joueurs_ecriture << _jeu.get_joueurs()[i].getNiveau()<<endl;
                FILE_joueurs_ecriture << _jeu.get_joueurs()[i].getNbrPartie() << endl;
                FILE_joueurs_ecriture << _jeu.get_joueurs()[i].getNbrVictoire() << endl;
                FILE_joueurs_ecriture << _jeu.get_joueurs()[i].getNbrDefaite() << endl;
            }

        }

        FILE_joueurs_ecriture.close();
    }
    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

}
