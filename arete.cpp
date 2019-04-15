#include "arete.h"

arete::arete()
{
    //ctor
}

arete::~arete()
{

}

arete::arete(std::string id ,const Sommet* debut,const Sommet* fin):m_id(id)
{

}

void arete::afficher() const
{
    std::cout<<"  arrete : "<< m_id<< std::endl;
    for(auto i:m_extremites) {
        i->afficherData();
    }
}
