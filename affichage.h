#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "graphe.h"
#include <vector>
#include <unordered_map>

void afficher_allegro(const std::unordered_map <int, std::vector<float>> &espace_recherche_int, const graphe &g_base);
void afficher_allegro_prim(graphe &g);
void afficherFrontierePareto_allegro(const graphe &g, bool dist);
double convert(double);

#endif // AFFICHAGE_H_INCLUDED
