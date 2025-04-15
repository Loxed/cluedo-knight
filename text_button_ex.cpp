#include "header.h"
#include <vector>

///Sous programme permettant de créer des botuons via du texte sous allegro
void text_button_ex(BITMAP * *destination,FONT * police, std::string _string, int placement, int pos_x, int pos_y, int col, int bg_col, int col_click, int bg_col_click, int * choix, int valeur_a_prendre) //bouton de texte
{
    //convertir string en chaine
    std::vector<char> _chaine;

    //Variable
    int click=0;

    for(auto & x:_string)
    {
        _chaine.push_back(x);
    }
    _chaine.push_back('\0');

    switch (placement)
    {
    case 1: //milieu

        if( mouse_x>=pos_x-text_length(police,&*_chaine.begin())/2 && mouse_x<=pos_x+text_length(police,&*_chaine.begin())/2 && mouse_y>=pos_y && mouse_y<=pos_y+text_height(police) )
        {
            textout_centre_ex(*destination,police,&*_chaine.begin(),pos_x,pos_y,col_click,bg_col_click);

            if(mouse_b==1)
            {
                rest(250);
                click=valeur_a_prendre;
                cout << "CLICK " << _string << endl;
            }
        }
        else
        {
            textout_centre_ex(*destination,police,&*_chaine.begin(),pos_x,pos_y,col,bg_col);
        }

        break;

    case 2: //droite

        if(mouse_x>=pos_x-text_length(police,&*_chaine.begin()) && mouse_x<=pos_x && mouse_y>=pos_y && mouse_y<=pos_y+text_height(police))
        {
            textout_right_ex(*destination,police,&*_chaine.begin(),pos_x,pos_y,col_click,bg_col_click);

            if(mouse_b==1)
            {
                rest(150);
                click=valeur_a_prendre;
            }

        }
        else textout_right_ex(*destination,police,&*_chaine.begin(),pos_x,pos_y,col,bg_col);

        break;

    default: //texte a gauche

        if(mouse_x>=pos_x&&mouse_x<=pos_x+text_length(police,&*_chaine.begin())&&mouse_y>=pos_y&&mouse_y<=pos_y+text_height(police))
        {
            textout_ex(*destination,police,&*_chaine.begin(),pos_x,pos_y,col_click,bg_col_click);

            if(mouse_b==1)
            {
                rest(150);
                click=valeur_a_prendre;
            }

        }
        else textout_ex(*destination,police,&*_chaine.begin(),pos_x,pos_y,col,bg_col);

        break;
    }

    if(click!=0) //si j'appuie sur le bouton
    {
        *choix=click; //choix prend la valeur a prendre
    }
}
