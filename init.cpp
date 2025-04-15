#include "header.h"
#include "ressources.h"

///Sous programme d'initialisation d'allegro
void init_alleg()
{
    //Initialiser allegro
     allegro_init();

     //souris + clavier
     install_mouse();
     install_keyboard();

     //son
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) != 0)
    {
        printf("Error initialising sound: %s\n", allegro_error);
    }

    // OUVERTURE MODE GRAPHIQUE (ouverture fenêtre allegro) + blindage
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,W,H,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);

        allegro_exit();

        exit(EXIT_FAILURE);
    }

 }

///Sous programme permettant de quitter allegro
void exit_alleg()
{
    allegro_exit();
}
