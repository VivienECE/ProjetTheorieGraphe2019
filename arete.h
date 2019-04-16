#ifndef ARETE_H
#define ARETE_H
#include <unordered_map>
#include <iostream>
#include "sommet.h"
#include <vector>

class arete
{
    public:
        arete();
        arete(int,float,float,Sommet*,Sommet*);
        arete(int, Sommet*, Sommet*);
        void afficher() const;
        ~arete();
        void ajouter_poids(float);
        std::vector<Sommet*> getm_extremites() const;
        std::vector<float> getm_poids() const;
        int getm_id() const;

    private:
        std::vector<Sommet*> m_extremites;
        std::vector<float> m_poids;
        int m_id;

};

#endif // ARETE_H
