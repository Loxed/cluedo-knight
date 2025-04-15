#include "header.h"

///Sous programme permettant d'afficher les règles du jeu
void regles(Ressources & m_ressources)
{
    //buffer
    BITMAP * buffer_regles=create_bitmap(W,H);
    BITMAP * buffer_part=create_bitmap(W,H);

    //Variable
    int retour;

    do
    {
        //clear le buffer
        clear_bitmap(buffer_regles);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_regles,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_regles,0,0,0,0,W,H);

        //texte
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T40"),470,150,m_ressources.get_clrs().get_clr("white"),-1,"Regles du jeu Cluedow Knight");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,350,m_ressources.get_clrs().get_clr("white"),-1,"Introduction : A l'issue d'une reception dans son monde, Le Roi Pale est trouve assassine.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,450,m_ressources.get_clrs().get_clr("white"),-1,"But du jeu : Resoudre, par deduction, l'enigme posee par ce crime.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,550,m_ressources.get_clrs().get_clr("white"),-1,"Gagnant : Pour gagner la partie, il faut retrouver l'enigme complete de ce meurtre.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),360,590,m_ressources.get_clrs().get_clr("white"),-1,"Ainsi, il faudra decouvrir : le meurtrier, l'arme utilisee et le lieu du meurtre.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),1375,1040,m_ressources.get_clrs().get_clr("white"),-1,"Appuyer sur la touche 1 du clavier");

        //souris
        show_mouse(buffer_regles);

        //afficher sur le buffer
        blit(buffer_regles,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_1]); //on boucle tant qu'on a pas appuye sur la touche 1

    do
    {
        //clear le buffer
        clear_bitmap(buffer_regles);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_regles,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_regles,0,0,0,0,W,H);

        //texte
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T40"),W/2-100,150,m_ressources.get_clrs().get_clr("white"),-1,"Materiel :");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,400,m_ressources.get_clrs().get_clr("white"),-1,"6 personnages : Le Chevalier / Hornet / Tiso / Quirrel / Zote le Redoutable / Cloth");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,500,m_ressources.get_clrs().get_clr("white"),-1,"6 armes : Aiguillon / Lance / Griffe / Aiguille / Faux / Massue");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,600,m_ressources.get_clrs().get_clr("white"),-1,"9 pieces : Falaises Hurlantes / Dirtmouth / Mont Cristal / Vertchemin / Jardins de la Reine / Nid-profond /");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),340,640,m_ressources.get_clrs().get_clr("white"),-1,"Bassin Ancestral / La Ruche / Frontiere du Royaume");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),1375,1040,m_ressources.get_clrs().get_clr("white"),-1,"Appuyer sur la touche 2 du clavier");

        //souris
        show_mouse(buffer_regles);

        //on affcihe sur le buffer
        blit(buffer_regles,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_2]); //on boucle tant qu'on a pas appuy sur la touche entrée

    do
    {
        //clear le buffer
        clear_bitmap(buffer_regles);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_regles,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_regles,0,0,0,0,W,H);

        //texte
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T40"),W/2-150,150,m_ressources.get_clrs().get_clr("white"),-1,"Preparation :");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,400,m_ressources.get_clrs().get_clr("white"),-1,"- en fonction du nombre de joueur present dans la partie, les nombre de pions equivalent");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,440,m_ressources.get_clrs().get_clr("white"),-1,"seront initialises sur les cases de depart correspondantes");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,540,m_ressources.get_clrs().get_clr("white"),-1,"- dans la case centrale presente sur le plateau de jeu, se trouve une enveloppe.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,580,m_ressources.get_clrs().get_clr("white"),-1,"Cette enveloppe contient l'enigme de la partie et sera donc composee de maniere aleatoire");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,620,m_ressources.get_clrs().get_clr("white"),-1,"d'un meurtrier, de l'arme du crime, et du nom de la piece ou le meurtre s'est deroule");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,720,m_ressources.get_clrs().get_clr("white"),-1,"- les 18 cartes restantes sont alors melangees");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),1375,1040,m_ressources.get_clrs().get_clr("white"),-1,"Appuyer sur la touche 3 du clavier");

        //souris
        show_mouse(buffer_regles);

        //on affiche sur le buffer
        blit(buffer_regles,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_3]); //on boucle tant qu'on a pas appuy sur la touche entrée

    do
    {
        //clear le buffer
        clear_bitmap(buffer_regles);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_regles,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_regles,0,0,0,0,W,H);

        //texte
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T40"),W/2-100,150,m_ressources.get_clrs().get_clr("white"),-1,"L'enquete :");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,400,m_ressources.get_clrs().get_clr("white"),-1,"- Choix du pion : En debut de partie, chaque joueur choisit le pions qu'il souhaite");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,500,m_ressources.get_clrs().get_clr("white"),-1,"- Avancer : Celui qui joue lance les des et avance dans le couloir, vers la piece de son choix d'autant");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,540,m_ressources.get_clrs().get_clr("white"),-1,"de cases que les des marquent de points");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,640,m_ressources.get_clrs().get_clr("white"),-1,"- Deplacements orthogonaux : Il avance ou recule verticalement ou horizontalement ; jamais en diagonale.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,740,m_ressources.get_clrs().get_clr("white"),-1,"- Entrer dans une piece : Il n'est pas oblige de faire un nombre exact de points pour entrer dans une piece");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,840,m_ressources.get_clrs().get_clr("white"),-1,"- Passages secrets : Quatre passages secrets permettent de se teleporter");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,940,m_ressources.get_clrs().get_clr("white"),-1,"- Deplacement et Hypothese : Le deplacement compte pour un coup mais le joueur peut, sans attendre son");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,980,m_ressources.get_clrs().get_clr("white"),-1,"prochain tour enqueter a partir du lieu ou il est arrive en formulant une hypothese");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),1375,1040,m_ressources.get_clrs().get_clr("white"),-1,"Appuyer sur la touche 4 du clavier");

        //souris
        show_mouse(buffer_regles);

        //on affiche sur le buffer
        blit(buffer_regles,screen,0,0,0,0,W,H);
    }
    while (!key[KEY_4]); //on boucle tant qu'on a pas appuyé sur la touche 4 du clavier

    do
    {
        //clear le buffer
        clear_bitmap(buffer_regles);

        //fond d'ecran
        blit(m_ressources.get_imgs().get_img("fond_menu_principal"),buffer_regles,0,0,0,0,W,H);

        //particules
        m_ressources.afficher_particules(buffer_part);
        masked_blit(buffer_part,buffer_regles,0,0,0,0,W,H);

        //retour menu principal
        text_button_ex(&buffer_regles,m_ressources.get_fnts().get_fnt("T20"),"Retour",0,10,10,makecol(255,255,255),-1,makecol(128,128,128),-1,&retour,1);

        //texte
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T40"),W/2-100,150,m_ressources.get_clrs().get_clr("white"),-1,"L'enquete :");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,400,m_ressources.get_clrs().get_clr("white"),-1,"Lorsque le joueur se situe dans une des 9 salles differentes, ce dernier à la possibilite d'effectuer");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,440,m_ressources.get_clrs().get_clr("white"),-1,"une hypothese. Pour ce faire, il aura la possibilite d'appuyer sur les cartes pour lequel il a un doute.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,540,m_ressources.get_clrs().get_clr("white"),-1,"L'enqueteur detient un carnet de notes ou il peut y entrer les noms des suspects, les armes et");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,580,m_ressources.get_clrs().get_clr("white"),-1,"les lieux qu'il croit devoir eliminer");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,680,m_ressources.get_clrs().get_clr("white"),-1,"L'enqueteur qui croit connaitre les trois cartes de l'enigme, doit se rendre dans la salle qui se situe au");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,720,m_ressources.get_clrs().get_clr("white"),-1,"milieu du plateau de jeu. Il pourra alors formuler une accusation.  Une comparaison automatique se lance");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,760,m_ressources.get_clrs().get_clr("white"),-1,"avec l'enveloppe contenant la reponse. Chaque enqueteur ne peut faire qu'une seule ACCUSATION.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,800,m_ressources.get_clrs().get_clr("white"),-1,"Qu'il la fasse donc a bon escient !Si son accusation est juste, il gagne la partie.");
        textprintf_ex(buffer_regles,m_ressources.get_fnts().get_fnt("T20"),200,840,m_ressources.get_clrs().get_clr("white"),-1,"Cependant si son accusation est fausse, le joueur a perdu et il ne peut plus jouer.");

        //souris
        show_mouse(buffer_regles);

        //on affiche sur le buffer
        blit(buffer_regles,screen,0,0,0,0,W,H);
    }
    while (retour==0); //boucle tant que l'on a pas appuyé sur le bouton retour

    //on revient au menu principal
    menu_principal(m_ressources);

    //on détruit les bitmaps pour eviter les failles memoires
    destroy_bitmap(buffer_part);
    destroy_bitmap(buffer_regles);
}
