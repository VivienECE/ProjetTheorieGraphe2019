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
#define LONGEURAXE 400
#define LONGUEURGRAD 100
#define LONGUEURGRAD2 50
#define COEFFICIENT 0.1
#define NBGRAD 4000

#define origine_x 200
#define origine_y 200
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
        std::vector <unsigned int> frontierePareto_dist(std::vector <unsigned int>) const;

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
