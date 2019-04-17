#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "graphe.h"
#include <vector>

void afficher_allegro(std::vector<graphe*> Liste);
void afficher_allegro(graphe g);
void afficherFrontierePareto_allegro(graphe g);

#endif // AFFICHAGE_H_INCLUDED
