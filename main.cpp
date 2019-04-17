#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"
#include "affichage.h"

int main()
{
    init_Allegro();
    graphe g{"broadway.txt"};
    g.lire_poids("broadway_weights_0.txt");
    //afficher_allegro(g);
    //afficher_allegro(g.prim(0));
    afficher_allegro(g.bruteforce());
    //afficher_allegro(g.prim(0));
    //afficher_allegro(g.prim(1));
    //afficher_allegro(g.bruteforce());
    afficherFrontierePareto_allegro(g);
    return 0;
}
END_OF_MAIN();
