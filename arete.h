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
        arete(std::string,const Sommet*,const Sommet*);
        void afficher() const;
        ~arete();

    private:
        std::vector<const Sommet*> m_extremites;
        std::string m_id;
        float m_poids;

};

#endif // ARETE_H
