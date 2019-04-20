#ifndef ARETE_H
#define ARETE_H
#include <unordered_map>
#include <iostream>
#include "sommet.h"
#include <vector>

class Sommet;
class arete
{
    public:
        ///CONSTRUCTEURS
        arete();
        arete(int,std::vector<float>,Sommet*, Sommet*);
        arete(int,float,float,Sommet*,Sommet*);
        arete(int, Sommet*, Sommet*);
        ~arete();

        ///GET
        std::vector<Sommet*> getm_extremites() const;
        std::vector<float> getm_poids() const;
        int getm_id() const;

        ///AFFICHAGE CONSOLE
        void afficher() const;

        ///SET
        void set_poids(float);

        void afficher_les_prim();

    private:
        std::vector<Sommet*> m_extremites;
        std::vector<float> m_poids;
        int m_id;

};

#endif // ARETE_H
