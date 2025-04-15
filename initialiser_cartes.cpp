#include "header.h"
#include "joueur.h"
#include <sstream>

using std::cout;
using std::endl;
using std::string;

///Sous programme permettant de créer un nouveau joueur ou d'utiliser un joueur déjà créer
void rentrer_joueurs(Jeu & _jeu, int _i, Ressources & m_ressources)
{
    //Buffer
    BITMAP * buffer=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);

    //Variables
    int choix=0;
    int cycle_perso;
    int prev_cycle;
    float i;

    if(_jeu.get_joueurs()[_i].get_joueur_ordinateur()==false)
    {
        do
        {
            //fond d'ecran
            blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer,0,0,0,0,W,H);

            //particules
            m_ressources.afficher_particules(buffer_part);
            masked_blit(buffer_part,buffer,0,0,0,0,W,H);

            //choix du joueur
            textout_centre_ex(buffer,m_ressources.get_fnts().get_fnt("T40"),"Choix du joueur:",W/2,100,makecol(255,255,255),-1);

            //bouton creer un joueur
            text_button_ex(&buffer,m_ressources.get_fnts().get_fnt("T20"),"Creer un nouveau joueur",1,W/2,300,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);

            //bouton utiliser un joueur
            text_button_ex(&buffer,m_ressources.get_fnts().get_fnt("T20"),"Utiliser un joueur deja inscrit",1,W/2,400,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,2);

            //souris
            show_mouse(buffer);

            //blit le buffer sur le screen
            blit(buffer,screen,0,0,0,0,W,H);

        }
        while (choix==0); //boucle tant que l'on a pas appuyer sur un des boutons disponibles sur l'ecran

        switch (choix)
        {
        case 1: //rentrer un nouveau joueur

            //mettre le nom
            _jeu.set_joueur(creer_joueur(_i, m_ressources),_i);

            //sauvegarder le joueur dans le fichier
            sauver_joueur( _jeu.get_joueurs()[_i].getNom());

            break;

        case 2: //choisir un joueur déja créé

            //Comparer le nom choisi au tableau de joueur voir si il a déjà été créé et le choisir
            selectionner_joueur(_jeu, _i, m_ressources);

            break;
        }

    }


    //choisir une image pour le joueur
    choix=0;
    cycle_perso=0;

    do
    {
        //Pour le choix et l'affichage des différents personnages
        i+=0.25;
        if(cycle_perso!=prev_cycle) i=0;
        if(i>m_ressources.get_anims().get_nb_frames(_jeu.get_m_perso_joueur()[cycle_perso])) i=0;
        prev_cycle=cycle_perso;

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer,0,0,0,0,W,H);

        //afficher "choisir un personnage"
        textprintf_centre_ex(buffer,m_ressources.get_fnts().get_fnt("T40"),W/2,230,m_ressources.get_clrs().get_clr("white"),-1,"Choisir un personnage: %d",cycle_perso);

        //afficher nom du perso et son numéro
        textprintf_centre_ex(buffer,m_ressources.get_fnts().get_fnt("T20"),W/2,300,m_ressources.get_clrs().get_clr("white"),-1,"%s, %d",_jeu.get_m_perso_joueur()[cycle_perso].c_str(),(int)_jeu.get_m_perso_joueur().size()-1);

        //fleche gauche pr diminuer
        text_button_ex(&buffer,m_ressources.get_fnts().get_fnt("F40"),"<",1,W/2-text_length(m_ressources.get_fnts().get_fnt("T40"),"Nombre de joueurs: 8")/2-85,160,makecol(255,255,255),-1,makecol(128,128,128),-1,&cycle_perso,cycle_perso-1);

        //fleche droite pour incrementer
        text_button_ex(&buffer,m_ressources.get_fnts().get_fnt("F40"),">",1,W/2+text_length(m_ressources.get_fnts().get_fnt("T40"),"Nombre de joueurs: 8")/2+85,160,makecol(255,255,255),-1,makecol(128,128,128),-1,&cycle_perso,cycle_perso+1);

        //bouton confirmer
        text_button_ex(&buffer,m_ressources.get_fnts().get_fnt("T30"),"Confirmer",1,W/2,900,makecol(255,255,255),-1,makecol(128,128,128),-1,&choix,1);


        ///CYCLE PERSO A 1 BUG POUR DESCENDRE
        //blinder cycle
        if(cycle_perso>(int)_jeu.get_m_perso_joueur().size()-1) cycle_perso=0;
        if(cycle_perso<0) cycle_perso=_jeu.get_m_perso_joueur().size()-1;

        //afficher le perso associé au nom
        masked_stretch_blit(m_ressources.get_anims().get_frame_perso(_jeu.get_m_perso_joueur()[cycle_perso],i),buffer,0,0,m_ressources.get_anims().get_frame_perso(_jeu.get_m_perso_joueur()[cycle_perso],i)->w,m_ressources.get_anims().get_frame_perso(_jeu.get_m_perso_joueur()[cycle_perso],i)->h,900,500,m_ressources.get_anims().get_frame_perso(_jeu.get_m_perso_joueur()[cycle_perso],i)->w*4,m_ressources.get_anims().get_frame_perso(_jeu.get_m_perso_joueur()[cycle_perso],i)->h*4);

        //souris
        show_mouse(buffer);

        //affichage de l'ensemble du buffer sur l'ecran
        blit(buffer,screen,0,0,0,0,W,H);
    }
    while (choix==0); // on boucle tant qu'on a pas fait de choix

    //mettre le personnage dans le joueur
    _jeu.get_joueurs()[_i].set_personnage(_jeu.get_m_perso_joueur()[cycle_perso]);

    //enlever le personnage du vecteur de personnages
    _jeu.get_m_perso_joueur().erase(_jeu.get_m_perso_joueur().begin()+cycle_perso);

    //on passe la souris a null pour eviter les failles memoires
    show_mouse(NULL);

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer);
    destroy_bitmap(buffer_part);
}

///Sous programmes permettant de créer un joueur
Joueur creer_joueur(int _i,Ressources & m_ressources)
{
    //creer un joueur, le constructeur va tout initialiser a 0
    Joueur m_joueur;

    //ecrire un nouveau nom pr le joueur
    m_joueur.setNom(choix_nom_joueurs(_i,m_ressources));

    return m_joueur;
}

///Sous programme permettant de choisir un joueur déja présent dans les comptes du jeu
void selectionner_joueur(Jeu &_jeu, int _i, Ressources & m_ressources)
{
    // vecteur de joueurs
    std::vector<Joueur> v_joueurs_load=charger_joueurs();

    //Variables
    int joueur_present=0;
    int joueur_utilise=0;

    //buffer
    BITMAP * buffer_selection;
    buffer_selection=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);
    BITMAP * zone_nom=create_bitmap(text_length(font,"MMMMMMMMMM")+10,text_height(font));;

    //string de base pour le nom du joueur
    string nom_joueurs="Player";
    std::vector<char> chaine;

    do
    {
        //clear le buffer
        clear_bitmap(buffer_selection);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_selection,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_selection,0,0,0,0,W,H);

        //lancer modifier nom
        modifier_nom(nom_joueurs);

        //Si le nom existe
        if(verification_compte_joueur(nom_joueurs)== true)
        {
            modifier_nom(nom_joueurs);
        }
        else
        {
            //sinon on affcihe que le joueur ayant ce nom n'a pas de compte
            textout_centre_ex(buffer_selection,m_ressources.get_fnts().get_fnt("T40"),"Ce joueur n'a pas de compte",W/2,100,makecol(255,255,255),-1);
        }

        //On vérifie si le joueur choisit est déja utilisé ou non
        for (int k=0; k<_jeu.get_nb_joueur(); k++)
        {
            if(nom_joueurs==_jeu.get_joueurs()[k].getNom())
            {
                cout << "impossible, le joueur est deja pris" << endl;
                joueur_utilise =1;
                k=_jeu.get_nb_joueur();

            }
            else
            {
                joueur_utilise =0;
            }
        }

        //si déjà utilise
        if(joueur_utilise==1)
        {
            //on affiche qu'il est déjà utilisé
            textout_centre_ex(buffer_selection,m_ressources.get_fnts().get_fnt("T40"),"Ce joueur est deja utilise",W/2,100,makecol(255,255,255),-1);
        }

        //convertir string en char*
        chaine.clear();
        std::copy(nom_joueurs.begin(), nom_joueurs.end(), std::back_inserter(chaine));
        chaine.push_back('\0');

        //afficher le texte
        textprintf_centre_ex(buffer_selection,m_ressources.get_fnts().get_fnt("T40"),W/2,250,m_ressources.get_clrs().get_clr("white"),-1,"%s", &*chaine.begin());        //si le nom est vide, afficher un nom de remplacement en rouge

        //souris
        show_mouse(buffer_selection);

        //afficher le buffer
        blit(buffer_selection,screen,0,0,0,0,W,H);

    }
    while (!key[KEY_ENTER]);  //boucle tant qu'on a pas appuyé sur la touche entrée

    //vérification que le joueur est présent dans les comptes
    for (int k=0; k<(int)v_joueurs_load.size()-1; k++)
    {
        if(v_joueurs_load[k].getNom()==nom_joueurs)
        {
            cout<< "Le joueur est bien present dans les comptes deja creer"<<endl;
            joueur_present=1;
            k=(int)v_joueurs_load.size()-1;

        }
        else
        {
            cout<<"le joueur est pas present"<<endl;
            joueur_present=0;

        }

    }

    //Si le joueur a déja un compte on peut avoir des infomations sur le compte
    if(joueur_utilise==0&&joueur_present==1)
    {
        _jeu.get_joueurs()[_i].setNom(nom_joueurs);

        for (int k=0; k<(int)v_joueurs_load.size()-1; k++)
        {
            if(v_joueurs_load[k].getNom()==nom_joueurs)
            {
                _jeu.get_joueurs()[_i].setNiveau(v_joueurs_load[k].getNiveau());
                _jeu.get_joueurs()[_i].setNbrPartie(v_joueurs_load[k].getNbrPartie());
                _jeu.get_joueurs()[_i].setNbrVictoire(v_joueurs_load[k].getNbrVictoire());
                _jeu.get_joueurs()[_i].setNbrDefaite(v_joueurs_load[k].getNbrDefaite());
            }
        }
    }

    //si le joueur n'est pas present on le laisse retaper son nom
    if (joueur_present==0||joueur_utilise==1)
    {
        selectionner_joueur(_jeu, _i, m_ressources);
    }

    //souris a null pour éviter les failles memoires
    show_mouse(NULL);

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(zone_nom);
    destroy_bitmap(buffer_selection);
    destroy_bitmap(buffer_part);

}

///Sous programme permettant de sauvegarder dans les comptes un nouveau joueur
void sauver_joueur(string _nom)
{
    //charger un fichier dans lequel ecrire
    string const nomFichier("joueurs.txt");
    std::ofstream FILE_joueurs(nomFichier.c_str(), std::ios_base::app);

    //blindage
    if(FILE_joueurs.is_open())
    {
        //nom
        FILE_joueurs << _nom << endl;

        //tous les résultats initiliser a 0
        for(int j=0; j<4; j++)
            FILE_joueurs << 0 << endl;

        FILE_joueurs.close();
    }
    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

}

///Sous programmes permettant de charger depuis un fichier les joueurs
std::vector<Joueur> charger_joueurs()
{

    //vecteur de joueur qu'on va renvoyer pr selectioner un joueur a charger dans partie
    std::vector<Joueur> m_joueurs_dispo;

    //ouverture du fichier
    string const nomFichier("joueurs.txt");
    std::ifstream FILE_joueurs(nomFichier.c_str());

    //parametres d'un joueur
    string nom_joueur;
    string temp;

    //joueur a rentrer dans le vecteur
    Joueur joueur_temp;

    //blindage
    if(FILE_joueurs.is_open())
    {
        //tant qu'on a pas fini de lire le fichier
        while(!FILE_joueurs.eof())
        {
            //rentrer le nom
            getline(FILE_joueurs,nom_joueur);
            joueur_temp.setNom(nom_joueur);

            //rentrer le niveau
            getline(FILE_joueurs, temp);
            joueur_temp.setNiveau(std::stoi(temp));

            //rentrer le nb de parties
            getline(FILE_joueurs, temp);
            joueur_temp.setNbrPartie(std::stoi(temp));

            //rentrer le nb de vitoires
            getline(FILE_joueurs, temp);
            joueur_temp.setNbrVictoire(std::stoi(temp));

            //rentre le nb de defaites
            getline(FILE_joueurs, temp);
            joueur_temp.setNbrDefaite(std::stoi(temp));

            m_joueurs_dispo.push_back(joueur_temp);
        }
        //on ferme le fichier
        FILE_joueurs.close();
    }

    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }

    //on retourne au programme appelant un joueur disponible
    return m_joueurs_dispo;
}

///Sous programme permettant de distribuer aléatoirement les cartes au différents joueurs
void  distribution_cartes_joueur(Jeu &_jeu)
{
    //Variables
    int j, nombre, k=18;
    int joueur;

    //si partie lancée à 3 joueurs on distribue aléatoirement, tous les joueurs on le même nombre de cartes
    if(_jeu.get_nb_joueur() == 3)
    {
        for(int i=0; i<3; i++)
        {
            for(j=0; j<6; j++)
            {
                nombre = rand()%(k-j);
                _jeu.get_joueurs()[i].setCarte(_jeu.get_pioche()[nombre]);
                _jeu.supp_carte_pioche(nombre);
            }
            k = k-6;
        }
    }

    //si partie lancée à 4 joueurs on distribue aléatoirement certains joueurs ont plus de cartes que d'autres
    if(_jeu.get_nb_joueur() == 4)
    {
        joueur = rand()%(3);

        cout << "joueur = " << joueur <<  endl;
        for(j=0; j<5; j++)
        {
            nombre = rand()%(18-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur ++;
        if (joueur>3)
        {
            joueur=0;
        }

        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<5; j++)
        {
            nombre = rand()%(13-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur++;
        if (joueur>3)
        {
            joueur=0;
        }

        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<4; j++)
        {
            nombre = rand()%(8-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur++;
        if (joueur>3)
        {
            joueur=0;
        }

        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<4; j++)
        {
            nombre = rand()%(4-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
    }

    //si partie lancée à 5 joueurs on distribue aléatoirement, certaines joueurs on plus de cartes que d'autres
    if(_jeu.get_nb_joueur() == 5)
    {
        joueur = rand()%(4);

        cout << "joueur = " << joueur <<  endl;
        for(j=0; j<4; j++)
        {
            nombre = rand()%(18-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur ++;
        if (joueur>4)
        {
            joueur=0;
        }

        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<4; j++)
        {
            nombre = rand()%(14-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur++;
        if (joueur>4)
        {
            joueur=0;
        }

        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<4; j++)
        {
            nombre = rand()%(10-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur++;
        if (joueur>4)
        {
            joueur=0;
        }
        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<3; j++)
        {
            nombre = rand()%(6-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
        joueur++;
        if (joueur>4)
        {
            joueur=0;
        }
        cout << "joueur = " << joueur<<  endl;
        for(j=0; j<3; j++)
        {
            nombre = rand()%(3-j);
            _jeu.get_joueurs()[joueur].setCarte(_jeu.get_pioche()[nombre]);
            _jeu.supp_carte_pioche(nombre);
        }
    }

    //si partie lancée à 3 joueurs on distribue aléatoirement
    if(_jeu.get_nb_joueur() == 6)
    {
        for(int i=0; i<6; i++)
        {
            for(j=0; j<3; j++)
            {
                nombre = rand()%(k-j);
                _jeu.get_joueurs()[i].setCarte(_jeu.get_pioche()[nombre]);
                _jeu.supp_carte_pioche(nombre);
            }
            k = k-3;
        }
    }
}
