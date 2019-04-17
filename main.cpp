#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"
#include "affichage.h"

int main()
{
    init_Allegro();
    graphe g{"cubetown.txt"};
    g.lire_poids("cubetown_weights_0.txt");
    //graphe g{"broadway.txt"};
    //g.lire_poids("broadway_weights_0.txt");
    afficher_allegro(g);
    afficher_allegro(g.prim(0));
    std::cout << "prim 1 fini go prim2" << std::endl;
    system("pause");
    afficher_allegro(g.prim(1));
    std::cout << "prim 2 fini go bruteforce" << std::endl;
    system("pause");
    afficher_allegro(g.bruteforce());
    std::cout << "bruteforce fini go frontiere" << std::endl;
    //afficher_allegro(g.prim(0));
    //afficher_allegro(g.prim(1));
    //afficher_allegro(g.bruteforce());
    afficherFrontierePareto_allegro(g);
    return 0;
}
END_OF_MAIN();
