#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"

int main()
{
   // init_Allegro();
    graphe g{"broadway.txt"};
    g.lire_poids("broadway_weights_0.txt");
    graphe pri;
    pri=g.prim(0);
    pri.afficher();
    //g.afficher();
    return 0;
}
END_OF_MAIN();
