#include "arete.h"

arete::arete()
{
    //ctor
}

arete::~arete()
{

}

std::vector<Sommet*> arete::getm_extremites() const {return m_extremites;}

std::vector<float> arete::getm_poids() const {return m_poids;}

int arete::getm_id() const {return m_id;}

arete::arete(int id,float P1,float P2 ,Sommet* S1, Sommet* S2):m_id(id)
{
    m_poids.push_back(P1);
    m_poids.push_back(P2);
    m_extremites.push_back(S1);
    m_extremites.push_back(S2);
}

arete::arete(int id,std::vector<float> poids ,Sommet* S1, Sommet* S2):m_id(id)
{
    for(const auto i:poids)
        m_poids.push_back(i);
    m_extremites.push_back(S1);
    m_extremites.push_back(S2);
}



arete::arete(int id,  Sommet* debut,  Sommet* fin):m_id(id)
{
    m_extremites.push_back(debut);
    m_extremites.push_back(fin);
}

void arete::set_poids(float poids)
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
