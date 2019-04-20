#include "affichage.h"
#include <iostream>
#include <unordered_map>

void afficher_allegro_prim(graphe &g)
{
    graphe aAfficher;
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    for(int i=0;i<2;++i)
    {
        aAfficher=g.prim(i);
        aAfficher.poidsTotaux();
        aAfficher.afficher_allegro(page, i);
    }
    blit(page, screen,0,0,0,0, 800,600);
    while (!key[KEY_ESC])
    {

    }
    //destroy_bitmap(page);
}

void afficherFrontierePareto_allegro(const graphe &g, const bool &dist, const t_coef &mesCoef) //Affiche la frontier du graphe
{
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    g.afficher_frontierePareto(page, dist, mesCoef);
    blit(page, screen,0,0,0,0, 800,600);
    while (!key[KEY_ESC])
    {

    }
    std::cout <<" Adios";
    destroy_bitmap(page);

}
