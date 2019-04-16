#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"
#include "affichage.h"

std::vector<const graphe*> retirerCnC(std::vector<const graphe*> listeGrapheAChanger)
{
    std::vector<const graphe*> listeGrapheARendre;
    for (const auto &g : listeGrapheAChanger)
    {
        if(g->rechercher_CC_graphe()==1)
            listeGrapheARendre.push_back(g);
    }
    return listeGrapheARendre;
}

int main()
{
    init_Allegro();
    std::vector <const graphe*> espace_recherche;
    std::vector <const graphe*> Liste;
    graphe g{"broadway.txt"};
    g.lire_poids("broadway_weights_0.txt");
    afficher_liste_allegro(retirerCnC(g.bruteforce()));


    return 0;
}
END_OF_MAIN();
