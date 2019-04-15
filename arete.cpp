#include "arete.h"

arete::arete()
{
    //ctor
}

arete::~arete()
{

}

arete::arete(int id, const Sommet* debut, const Sommet* fin):m_id(id)
{

}

void arete::ajouter_poids(float poids)
{
    m_poids.push_back(poids);
}

void arete::afficher() const
{
    std::cout<< m_id;
    for(auto i:m_extremites)
        i->afficherData();
    std::cout<<" -> ";
    for (auto j:m_poids)
        std::cout<< j << "-";
    std::cout<< std::endl;
}
