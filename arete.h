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
        arete(int,const Sommet*,const Sommet*);
        void afficher() const;
        ~arete();
        void ajouter_poids(float);

    private:
        std::vector<const Sommet*> m_extremites;
        std::vector<float> m_poids;
        int m_id;

};

#endif // ARETE_H
