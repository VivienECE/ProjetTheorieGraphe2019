#include "affichage.h"
#include <iostream>
#include <unordered_map>

void afficher_allegro(const std::unordered_map <int, std::vector<float>> &espace_recherche_int, const graphe &g_base) //AFFICHE LISTE GRAPHE
{
    BITMAP*page;
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
            grapheTemp->afficher_allegro(page);
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

void afficher_allegro(graphe g)
{
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    g.poidsTotaux();
    g.afficher_allegro(page);
    blit(page, screen,0,0,0,0, 800,600);
    while (!key[KEY_ESC])
    {

    }
}

void afficherFrontierePareto_allegro(const graphe &g) //Affiche la frontier du graphe
{
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    g.afficher_frontierePareto(page);
    blit(page, screen,0,0,0,0, 800,600);
    while (!key[KEY_ESC])
    {

    }
}
