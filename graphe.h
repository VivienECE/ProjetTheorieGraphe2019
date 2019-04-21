#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"
#include "allegro.h"
#include "affichage.h"
#include "sommet.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
#include "math.h"
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

class Sommet;
class arete;
class graphe
{
    public:
        ///CONSTRUCTEURS
        graphe(std::string);
        graphe();
        graphe(const int &I, const graphe &g);
        ~graphe();

        ///LECTURE 2nd FICHIER, MET A JOUR LES POIDS
        void lire_poids(std::string nomFichier);

        ///AFFICHAGE CONSOLE
        void afficher() const;

        ///AFFICHAGE GRAPHE SUR LA BITPMAP
        void afficher_allegro(BITMAP*, const int &i, const std::vector<float> &mesPoids) const;

        ///AFFICHAGE FRONTIERE SUR LA BITPMAP, dist-> Normale ou Opti poids/distance, coefAlleg->Coeff pour conserver affichage milieu page
        void pareto(BITMAP*page, const bool &dist, const struct coefAlleg &mesCoef) ;//ONLY 2D ou 1D

        ///ADD ARETE
        void ajouter_arete(int,float,float, Sommet*, Sommet*);

        ///ALGORITHME PRIM
        graphe prim(int poids);

        ///Determine l'espace de recherche
        ///RENVOIE LES GRAPHES CONNEXES (De taille  =  ordre-1) SOUS FORMES D'ENTIER
        std::vector <unsigned int> bruteforce()const;

        ///Determine l'espace de recherche cout/dist
        ///RENVOIE LES GRAPHES CONNEXES (De taille >=  ordre-1)SOUS FORMES D'ENTIER
        std::vector <unsigned int> bruteforce_dist()const;

        ///Calcul du poids total
        void poidsTotaux();

        ///GET
        std::vector<float> getm_poids();
        std::vector<Sommet*> getm_voisins(int &id) const;

        ///Tri l'espace de recherche et renvoie les graphes de la frontiere de pareto
        ///Appel les algos de djikstra
        ///Parametres: Espace de recherche
        ///Renvoie tout les graphes de la frontiere sous forme d'entier
        std::vector <unsigned int> frontierePareto(std::vector <unsigned int>) const;

        ///Tri l'espace de recherche et renvoie les graphes de la frontiere de pareto
        ///Appel les algos de djikstra, bi-objectifs somme des couts et distances
        ///Parametres: Espace de recherche
        ///Renvoie tout les graphes de la frontiere sous forme d'entier
        std::unordered_map <unsigned int, std::vector<float>> frontierePareto_dist(std::vector <unsigned int> &espace_recherche_int) const;

        ///Parcours djikstra pour tout les sommets du graphe
        ///Parametres: le num du graphe, l'ordre, le nbr de poids
        ///Renvoie un TAB 2D, tab[0] somme des couts, tab[1] somme des distances
        std::vector<float> poidsTotauxDjikstra(const unsigned int &I,int &ordre, int &ponderation) const; //retourne les poids total+ total des distances

        ///Parcours djikstra pour 1 sommet de départ
        ///Parametres: ID sommet départ, graphe sous forme d'entier
        ///Renvoie la somme des coûts des distances pout le sommet de départ.
        float Djikstra_sommet(int id_debut,const unsigned int &i,int &ponderation) const; //retourne somme des djisktra pour le sommet -symetrie

        ///ADDITIONNE LES POIDS
        std::vector<float> poidsTotaux(unsigned int i) const;


    private:
        std::unordered_map<int,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,arete*> m_aretes;
        std::vector <float> m_poidsTotaux;
};

///Priority queue
class prioritize;

#endif // GRAPHE_H
