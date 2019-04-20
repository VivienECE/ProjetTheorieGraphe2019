#include "affichage.h"
#include <iostream>
#include <unordered_map>

void afficher_allegro(const std::unordered_map <int, std::vector<float>> &espace_recherche_int, const graphe &g_base) //AFFICHE LISTE GRAPHE
{
    BITMAP* page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    graphe* grapheTemp;
    while (!key[KEY_ESC])
    {
        for (const auto &i : espace_recherche_int)
        {
            grapheTemp = new graphe {i.first, g_base};
            /*
            for(const auto &s : grapheTemp->m_sommets)
                s->second->connexite();*/
            grapheTemp->poidsTotaux();
            grapheTemp->afficher_allegro(page, 0);
            blit(page, screen,0,0,0,0, 800,600);
            while (!key[KEY_ENTER])
            {
                if (key[KEY_ESC]) //Option quitter si la liste est longue
                    return;
            }
            clear(page);
            clear(screen);
            delete(grapheTemp);
        }
    }
}

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
    destroy_bitmap(page);
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
}


void afficher_allegro2(const graphe &g_base,const std::vector<unsigned int> espace_recherche_int) //AFFICHE LISTE GRAPHE
{
    BITMAP* page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    graphe* grapheTemp;
    while (!key[KEY_ESC])
    {
        for (const auto &i : espace_recherche_int)
        {
            grapheTemp = new graphe {i, g_base};
            grapheTemp->poidsTotaux();
            grapheTemp->afficher_allegro(page, i);
            blit(page, screen,0,0,0,0, 800,600);
            while (!key[KEY_ENTER])
            {
                if (key[KEY_ESC]) //Option quitter si la liste est longue
                    return;
            }
            clear(page);
            clear(screen);
            delete(grapheTemp);
        }
    }
    return;
}
