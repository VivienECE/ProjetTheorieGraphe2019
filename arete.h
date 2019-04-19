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
        arete();
        arete(int,std::vector<float>,Sommet*, Sommet*);
        arete(int,float,float,Sommet*,Sommet*);
        arete(int, Sommet*, Sommet*);
        void afficher() const;
        ~arete();
        void ajouter_poids(float);
        std::vector<Sommet*> getm_extremites() const;
        std::vector<float> getm_poids() const;
        int getm_id() const;
        Sommet* getm_extremite(int) const;
        float getm_distance(int, int) const; //renvoi la distance si bon id correct, 0 sinon

    private:
        std::vector<Sommet*> m_extremites;
        std::vector<float> m_poids;
        int m_id;

};

#endif // ARETE_H
