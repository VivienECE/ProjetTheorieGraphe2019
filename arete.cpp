#include "arete.h"

arete::arete()
{
    //ctor
}

arete::~arete()
{

}

arete::arete(int id,float P1,float P2 ,const Sommet* S1,const Sommet* S2):m_id(id)
{
    m_poids.push_back(P1);
    m_poids.push_back(P2);
    m_extremites.push_back(S1);
    m_extremites.push_back(S2);
}

arete::arete(int id, const Sommet* debut, const Sommet* fin):m_id(id)
{
    m_extremites.push_back(debut);
    m_extremites.push_back(fin);
}


void arete::ajouter_poids(float poids)
{
    m_poids.push_back(poids);
}

void arete::afficher() const
{
    std::cout<< m_id << std::endl;
    for(auto i:m_extremites)
        i->afficherData();
    std::cout<<"Poids";
    for (auto j:m_poids)
        std::cout<< " : "<< j ;
    std::cout<< std::endl;
}

const Sommet* arete::get_extremite(int id)
{
    return m_extremites[id];
}
