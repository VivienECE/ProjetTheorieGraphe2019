#include "affichage.h"

void afficher_liste_allegro(std::vector<const graphe*> Liste)
{
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    while (!key[KEY_ESC])
    {
        for (const auto i:Liste)
        {
            i->afficher_allegro(page);
            blit(page, screen,0,0,0,0, 800,600);
            while (!key[KEY_ENTER])
            {
                if (key[KEY_ESC]) //Option quitter si la liste est longue
                    return;
            }
            clear(page);
            clear(screen);
        }
    }
}
