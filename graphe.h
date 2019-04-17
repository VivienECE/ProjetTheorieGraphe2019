#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"
#include "allegro.h"

#define origine_x 200
#define origine_y 200

class graphe
{
    public:
        graphe(std::string);
        graphe();
        ///Créer un nouveau graphe en fonction du vecteur booleen et des sommets du graphe
        graphe(std::vector<bool>, const graphe &g);
        graphe(int, const graphe &g);
        void lire_poids(std::string nomFichier);
        ~graphe();
        void afficher() const;
        void ajouter_arete(int,float,float, Sommet*, Sommet*);
        graphe prim(int poids) ;
        void afficher_allegro(BITMAP*) const;
        std::vector<graphe*> bruteforce();
        int rechercher_CC_graphe() const;
        void poidsTotaux(); //Calcul du poids total
        std::vector<float> getm_poids();
        void ajouter_connexite() const;
        std::vector <graphe*> frontierePareto(const std::vector <graphe*> &espace_recherche); //RENVOIE LES GRAPHES FRONTIERE
        void afficher_frontierePareto(BITMAP*page); //ONLY 2D ou 1D

    private:
        std::unordered_map<int,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,arete*> m_aretes;
        std::vector <float> m_poidsTotaux;
};

std::vector<bool> add(const std::vector<bool>& a, const std::vector<bool>& b);

std::vector<graphe*> retirerCnC(std::vector<graphe*> listeGrapheAChanger);

float real_x(float x);
float real_y(float y);

#endif // GRAPHE_H
