#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"
#include "affichage.h"

int main()
{
    init_Allegro();
    std::vector <const graphe*> espace_recherche;
    std::vector <const graphe*> Liste;
    graphe g{"broadway.txt"};
    g.lire_poids("broadway_weights_0.txt");
    afficher_liste_allegro(g.bruteforce());

    return 0;
}
END_OF_MAIN();
