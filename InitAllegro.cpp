#include "InitAllegro.h"
#include <iostream>

void init_Allegro()
{
    ///Initialistion d'Allegro, du clavier, de la souris et des chiffres aléatoires
    allegro_init();
    install_keyboard();
    install_mouse();
    ///Initialisation des variables

    set_color_depth(desktop_color_depth()); //Initialisation des couleurs
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0) //Initialisation du mode graphique, si il ne marche pas on entre dans le if et on affiche une erreur puis on quitte le programme
    {
        allegro_message("Probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);
}
