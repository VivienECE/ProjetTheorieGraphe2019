#include <iostream>
#include "graphe.h"

int main()
{
    graphe g{"graphe_1.txt"};
    g.afficher();
    g.afficherBFS("1");
    g.afficherDFS("1");
    g.rechercher_afficherToutesCC();
    g.isEulerien();
    return 0;
}
