#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "graphe.h"
#include <vector>
#include <unordered_map>

#define ORX 100
#define ORY 550
#define LONGUEURGRAD 5
#define LONGUEURGRAD2 2
#define NBGRADX 4000
#define NBGRADY 150
#define PASY1 10
#define PASY2 5
#define PASX1 200
#define PASX2 50

typedef struct coefAlleg
{
    int coefficient_X, coefficient_Y, pas_X1, pas_X2, pas_Y1, pas_Y2, nbGrad_X, nbGrad_Y;
}t_coef;

class graphe;

///Affiche les 2 arbres couvrant minimum
void afficher_allegro_prim(graphe &g);

///Affiche la frontiere de Pareto
void afficherFrontierePareto_allegro(const graphe &g, const bool &dist, const t_coef &mesCoefs);

///Fonction debuggage, affiche les graphes.
void afficher_allegro2(const graphe &g_base,const std::vector<unsigned int> espace_recherche_int);
#endif // AFFICHAGE_H_INCLUDED
