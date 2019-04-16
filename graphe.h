#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"
#include "allegro.h"

class graphe
{
    public:
        graphe(std::string);
        graphe();
        ///Créer un nouveau graphe en fonction du vecteur booleen et des sommets du graphe
        graphe(std::vector<bool>,graphe);
        void lire_poids(std::string nomFichier);
        ~graphe();
        void afficher() const;
        void ajouter_arete(int,float,float, Sommet*, Sommet*);
        graphe prim(int poids) ;
        void afficher_allegro(BITMAP*) const;
        std::vector<graphe*> bruteforce();
        int rechercher_CC_graphe() const;

    private:
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<int,arete*> m_aretes;
};

std::vector<bool> add(const std::vector<bool>& a, const std::vector<bool>& b);

#endif // GRAPHE_H
