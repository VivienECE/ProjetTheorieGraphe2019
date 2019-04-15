#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"

class graphe
{
    public:
        graphe(std::string);
        graphe();
        void lire_poids(std::string nomFichier);
        ~graphe();
        void afficher() const;
    private:
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,arete*> m_aretes;
};

#endif // GRAPHE_H
