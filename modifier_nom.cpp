#include "header.h"

using std::cout;
using std::endl;
using std::string;

///Sous programme permettant de modifier du texte sous allegro
void modifier_nom(string & _nom)
{
    //va prendre la valeur de la touche presse
    int touche;

    if(_nom.length()>0) //si il y a du texte a enlever
    {
        if(key[KEY_BACKSPACE]) //si retour en arriere
        {
            rest(100); // faire une pause pr le buffer
            _nom.erase(_nom.end()-1); //effacer le dernier caractere
        }
    }

    else
    {
        //vider le buffer;
        clear_keybuf();
        rest(100);
    }

    if(_nom.length()<10) //si la taille du nom est inferieur a 10
    {
        //si je clique sur une touche
        if(keypressed())
        {
            touche=readkey()& 0xff; //prendre sa valeur

            rest(100);

            if(touche>='A' && touche<='Z' )
            {
                _nom+=touche;
            }

            else if(touche>='a' && touche<='z')
            {
                _nom+=touche;
            }
            else if(touche>='0' && touche<='9')
            {
                _nom+=touche;
            }
        }
    }

    else if(_nom.length()==10) // si la taille du nom est de 10
    {
        if(key[KEY_BACKSPACE])
        {
            rest(100); // faire une pause pr le buffer
            _nom.erase(_nom.end()-1); //effacer le dernier caractere
        }

        else clear_keybuf();
    }

    else //sinon
    {
        //vider le buffer;
        clear_keybuf();
        rest(100);
    }

}
