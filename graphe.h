#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"
#include "allegro.h"

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
#define COEFFICIENTX 0.4
#define COEFFICIENTY 2
#define NBGRADX 4000
#define NBGRADY 100
#define PASY1 10
#define PASY2 5
#define PASX1 200
#define PASX2 50

class Sommet;
class arete;
class graphe
{
    public:
        graphe(std::string);
        graphe();
        graphe(const int &I, const graphe &g);
        ~graphe();

        void lire_poids(std::string nomFichier);

        void afficher() const;
        void afficher_allegro(BITMAP*, const int &i) const;
        void afficher_allegro(BITMAP*) const;
        void afficher_frontierePareto(BITMAP*page, bool dist) const;//ONLY 2D ou 1D

        void ajouter_arete(int,float,float, Sommet*, Sommet*);
        void ajouter_connexite() const;


        graphe prim(int poids);
        std::vector <unsigned int> bruteforce()const;
        std::vector <unsigned int> bruteforce_dist()const;

        void poidsTotaux(); //Calcul du poids total
        std::vector<float> getm_poids();

        std::vector <unsigned int> frontierePareto(std::vector <unsigned int>) const;
        std::unordered_map <unsigned int, std::vector<float>> frontierePareto_dist(std::vector <unsigned int> &futureFront) const;

        std::vector<float> poidsTotauxDjikstra(const unsigned int &I) const; //retourne les poids total+ total des distances
        float Djikstra_sommet(int,const unsigned int &i) const; //retourne somme des djisktra pour le sommet -symetrie
        std::vector<float> poidsTotaux(unsigned int i) const;

    private:
        std::unordered_map<int,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,arete*> m_aretes;
        std::vector <float> m_poidsTotaux;
};

std::vector<bool> add(const std::vector<bool>& a, const std::vector<bool>& b);

float real_x(float x);
float real_y(float y);

#endif // GRAPHE_H
