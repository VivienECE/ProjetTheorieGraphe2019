#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"
#include "affichage.h"

int main()
{
    init_Allegro();
    graphe g{"manhattan.txt"};
    g.lire_poids("manhattan_weights_0.txt");

    //graphe g{"cubetown.txt"};
    //g.lire_poids("cubetown_weights_0.txt");

    //graphe g{"broadway.txt"};
    //g.lire_poids("broadway_weights_0.txt");

    g.poidsTotaux();

    afficherFrontierePareto_allegro(g);
    system("pause");

    std::cout << "pareto fini go terminer" << std::endl;
    return 0;
}
END_OF_MAIN();
