#include "header.h"
#include "ressources.h"
#include "joueur.h"
#include "enveloppe.h"
#include "Jeu.h"
#include <sstream>

using std::cout;
using std::endl;
using std::string;

///Sous programme permettant de sauvegarder une partie
void sauvegarder_partie(Jeu &_jeu, int num_joueur)
{
    //fichier
    string const nomFichier("sauvegarde.txt");
    std::ofstream FILE_sauvegarde(nomFichier.c_str());

    if(FILE_sauvegarde.is_open())//blindage
    {
        //On sauvegarde tous les éléments nécessaire pour pouvoir reprendre une partie par la suite
        FILE_sauvegarde << num_joueur << endl;
        FILE_sauvegarde << _jeu.get_nb_joueur() << endl;

        for(int j=0; j<_jeu.get_nb_joueur(); j++)
        {
            FILE_sauvegarde << _jeu.get_joueurs()[j].getNom() << endl;
            FILE_sauvegarde << _jeu.get_joueurs()[j].get_personnage() << endl;
            FILE_sauvegarde << _jeu.get_joueurs()[j].get_joueur_ordinateur() << endl;
            FILE_sauvegarde << _jeu.get_joueurs()[j].getNiveau() << endl;
            FILE_sauvegarde << _jeu.get_joueurs()[j].getPositionX() << endl;
            FILE_sauvegarde << _jeu.get_joueurs()[j].getPositionY() << endl;
            FILE_sauvegarde << _jeu.get_joueurs()[j].getAlive() << endl;

            FILE_sauvegarde << _jeu.get_joueurs()[j].getTaille() << endl;

            for(unsigned int i=0; i<_jeu.get_joueurs()[j].getTaille(); i++)
            {
                FILE_sauvegarde << _jeu.get_joueurs()[j].getCarte(i).getNom() << endl;
            }
        }

        FILE_sauvegarde << _jeu.getEnveloppe().getArme().getNom() << endl;
        FILE_sauvegarde << _jeu.getEnveloppe().getEnnemi().getNom() << endl;
        FILE_sauvegarde << _jeu.getEnveloppe().getSalle().getNom() << endl;

        FILE_sauvegarde.close();
    }
    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }
}

///Sous programme permettant de charger une partie sauvegardée
void charger_partie(Jeu &_jeu, int *num_joueur)
{
    //fichier
    string const nomFichier("sauvegarde.txt");
    std::ifstream FILE_sauvegarde(nomFichier.c_str());

    //Variable
    string temp;
    string salle;
    string arme;
    string ennemi;
    string chaine;
    int nb_cartes;

    Carte carte;

    if(FILE_sauvegarde.is_open())//blindage
    {
        //on regarde tout le fichier
        while(!FILE_sauvegarde.eof())
        {

            getline(FILE_sauvegarde, temp);
            *num_joueur = std::stoi(temp);
            getline(FILE_sauvegarde, temp);
            _jeu.set_nb_joueur(std::stoi(temp));


            for(int i=0; i<_jeu.get_nb_joueur();i++)
            {
                //recuperation nom
                getline(FILE_sauvegarde,chaine);
                _jeu.get_joueurs()[i].setNom(chaine);

                //recuperation personnage
                getline(FILE_sauvegarde,chaine);
                _jeu.get_joueurs()[i].set_personnage(chaine);

                //recuperation joueur ordinateur ou non
                getline(FILE_sauvegarde, temp);
                _jeu.get_joueurs()[i].set_joueur_ordinateur(std::stoi(temp));

                //recuperation score
                getline(FILE_sauvegarde, temp);
                _jeu.get_joueurs()[i].setNiveau(std::stoi(temp));

                //recuperation posX
                getline(FILE_sauvegarde, temp);
                _jeu.get_joueurs()[i].setPositionX(std::stoi(temp));

                //recuperation posY
                getline(FILE_sauvegarde, temp);
                _jeu.get_joueurs()[i].setPositionY(std::stoi(temp));

                //recuperation alive
                getline(FILE_sauvegarde, temp);
                _jeu.get_joueurs()[i].setAlive(std::stoi(temp));

                //recuperation nombre carte
                getline(FILE_sauvegarde, temp);
                nb_cartes = std::stoi(temp);

                for(int j=0;j<nb_cartes;j++)
                {
                    getline(FILE_sauvegarde,chaine);
                    carte.setNom(chaine);
                    _jeu.get_joueurs()[i].setCarte(carte);
                }
            }

            //recuperer enveloppe
            getline(FILE_sauvegarde, arme);
            getline(FILE_sauvegarde, ennemi);
            getline(FILE_sauvegarde, salle);
            getline(FILE_sauvegarde, chaine);
            //charger enveloppe
            _jeu.charger_enveloppe(arme, ennemi, salle);
        }
        //on ferme le fichier
        FILE_sauvegarde.close();
    }

    else
    {
        cout << "Erreur d'ouverture du fichier" << endl;
    }
}
