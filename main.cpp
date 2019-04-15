#include <iostream>
#include "graphe.h"
#include "allegro.h"

int main()
{
    graphe g{"broadway.txt"};
    g.lire_poids("broadway_weights_0.txt");
    g.afficher();
    return 0;
}

END_OF_MAIN();


