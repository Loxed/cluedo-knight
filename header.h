#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <cmath>

//c++ standard
#include <iostream>
#include <map>
#include <vector>

//equivalent sprintf, utile pour charger des anims (perso1.bmp, perso2.bmp etc..)
#include <sstream> // pour ostringstream
#include <cstring> // pour strcpy, essentiel pour allegro

//lecture de fichier
#include <fstream>

//allegro
#include <allegro.h>

//aleatoire avec time
#include <time.h>

//musique en ogg pour prendre moins de place peut etre
#include <logg.h>

//class
#include "ressources.h"
#include "carte.h"
#include "joueur.h"
#include "enveloppe.h"
#include "Jeu.h"


///================ALLEGRO ET MENU PRINCIPAL=========================///

///Sous programme d'initialisation d'allegro
void init_alleg();

///Sous programme permettant de quitter allegro
void exit_alleg();

///Sous programme du menu principal qui g�re le lancement du jeu
void menu_principal(Ressources & m_ressources);

///================INITIALISATION D'UNE PARTIE===========================///

///Sous programme permettant d'initialiser une partie de jeu
void initialiser_partie(Ressources & m_ressources, Jeu &m_jeu);

///Sous programme permettant de choisir le nombre de joueur dans une partie
void choix_nbr_joueurs(Jeu & _jeu,Ressources & m_ressources);

///Sours programme permettant de faire le choix du nom du joueur sous allegro
string choix_nom_joueurs(int i, Ressources & m_ressources);

///Sous programme permettant de modifier du texte sous allegro
void modifier_nom(std::string & _nom);

///Sous programme permettant de cr�er un nouveau joueur ou d'utiliser un joueur d�j� cr�er
void rentrer_joueurs(Jeu & _jeu, int _i, Ressources & m_ressources);

///Sous programmes permettant de cr�er un joueur
Joueur creer_joueur(int _i, Ressources & m_ressources);

///Sous programme permettant de choisir un joueur d�ja pr�sent dans les comptes du jeu
void selectionner_joueur(Jeu &_jeu, int i, Ressources & m_ressources);

///Sous programme permettant de sauvegarder dans les comptes un nouveau joueur
void sauver_joueur(string _nom);

///Sous programmes permettant de charger depuis un fichier les joueurs
std::vector<Joueur> charger_joueurs();

///Sous programme permettant de savoir si on joue avc une ia ou non
bool jouer_bot(Ressources & m_ressources);

///Sous programme permettant de choisir le nombre de joueur ia
void choix_nbr_joueurs_ordinateurs(Jeu & _jeu,Ressources & m_ressources);


///========================PARTIE===================================///

///Sous programme permettant de distribuer al�atoirement les cartes au diff�rents joueurs
void distribution_cartes_joueur(Jeu & _jeu);

///Sous programme permettant de lancer le jeu d'une partie
void lancer_jeu (Ressources & m_ressources, Jeu &m_jeu);

///Sous programme permettant de g�rer les tour dans une partie
void tour(Ressources & m_ressources, Jeu & _jeu);

///Sous programme permettant d'afficher le plateau
void affichage_plateau( Jeu & m_jeu, BITMAP * & buffer_plateau ,Ressources & m_ressources);

///Sous programme permettant de v�rtifier la pr�sence d'un joueur dans une salle
string presence_salle(char salle);
string hypothese_arme(int arme);
string hypothese_ennemi(int ennemi);
string hypothese_salle(int salle);

///Sous programme permettant de g�rer les d�placement
bool gerer_deplacement(int dir_x, int dir_y, Jeu & m_jeu, Ressources & m_ressources,int _num_joueur);

///Sous programme pour l'affichage pendant une partie
void afficher_partie(Ressources & m_ressources, Jeu & _jeu, BITMAP *  &retour);

///Sous programme permettant � un joueur de se t�l�porter sur le plateau de jeu
void teleportation (Joueur &joueur);

///Sous programme permettant de faire une r�ponse � une hypoth�se
void reponse_hypothese (int num_joueur, Jeu &_jeu, string salle, string ennemi, string arme,Jeu & m_jeu, Ressources & m_ressources);

///Sous programme permettant de v�rifier si une accusation est juste ou non
bool verification_accusation(Jeu &m_jeu, string arme, string salle, string ennemi);

///Sours programme permettant de mettre a jour les compte en fin de partie
void fin_partie_compte(Jeu &_jeu);

///=====================SAUVEGARDE==========================///

///Sous programme permettant de sauvegarder une partie
void sauvegarder_partie(Jeu &_jeu, int num_joueur);

///Sous programme permettant de charger une partie sauvegard�e
void charger_partie(Jeu &_jeu, int *num_joueur);

///====================REGLES=======================///

///Sous programme permettant d'afficher les r�gles du jeu
void regles (Ressources & m_ressources);

///====================PARAMETRES COMPTES===============================///

///Sous programme permettant de g�rer les param�tres pour les comptes des joueurs
void parametres_comptes(Ressources & m_ressources);

///Sous programme permettant de v�rifie si le joueur � d�ja un compte ou non
bool verification_compte_joueur(string nom_joueurs);

///Sous programme permettant d'afficher les statistiques d'un compte
void affichage_statistiques_comptes(Ressources & m_ressources, string nom_joueur);

///Sous programme permettant de choisir le compte d'un joueur pr�sent
string choix_compte_joueurs(Ressources & m_ressources);

///Sous programme permettant de supprimer tous les comptes
void supprimer_tout_compte(Ressources & m_ressources);

///Sous programmes permettant de supprimer un compte
void supprimer_compte(Ressources & m_ressources, string nom_joueur);

///========================BOUTONS ALLEGRO==========================///

///Sous programme permettant de cr�er des botuons via du texte sous allegro
void text_button_ex(BITMAP * *destination,FONT * police, std::string _string, int placement, int pos_x, int pos_y, int col, int bg_col, int col_click, int bg_col_click, int * choix, int valeur_a_prendre);

///Sous programme pour les boutons sur les cartes de la partie
void text_card_ex(Ressources & m_ressources,Jeu & m_jeu, BITMAP * *destination, std::string nom_image, int pos_x, int pos_y, int * choix, int valeur_a_prendre); //bouton de carte

void parametres_musique(Ressources & m_ressources); //pour savoir a quel menu retourner, et ne pas arreter la partie en cours

#endif // HEADER_H_INCLUDED
