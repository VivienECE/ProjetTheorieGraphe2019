#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"
#include "allegro.h"
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
#define LONGUEURGRAD 5
#define LONGUEURGRAD2 2
#define COEFFICIENT 10
#define NBGRAD 30

#define origine_x 200
#define origine_y 200

class graphe
{
    public:
        graphe(std::string);
        graphe();
        ///Cr�er un nouveau graphe en fonction du vecteur booleen et des sommets du graphe
        graphe(std::vector<bool>, const graphe &g);
        graphe(const int &I, const graphe &g);
        void lire_poids(std::string nomFichier);
        ~graphe();
        void afficher() const;
        void ajouter_arete(int,float,float, Sommet*, Sommet*);
        graphe prim(int poids) ;
        void afficher_allegro(BITMAP*) const;
        std::vector <unsigned int> bruteforce()const;
        int rechercher_CC_graphe() const;
        void poidsTotaux(); //Calcul du poids total
        std::vector<float> getm_poids();
        void ajouter_connexite() const;
        std::vector <unsigned int> frontierePareto(std::vector <unsigned int>) const;
        void afficher_frontierePareto(BITMAP*page) const;//ONLY 2D ou 1D
        std::vector<float> poidsTotauxDjikstra(const unsigned int &I); //retourne les poids total+ total des distances
        float** Djikstra_sommet(int,const unsigned int &i) const; //retourne 1 tableau remplit de djikstra


    private:
        std::unordered_map<int,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,arete*> m_aretes;
        std::vector <float> m_poidsTotaux;
};

std::vector<bool> add(const std::vector<bool>& a, const std::vector<bool>& b);

std::vector<graphe*> retirerCnC(std::vector<graphe*> listeGrapheAChanger);

float real_x(float x);
float real_y(float y);

#endif // GRAPHE_H
