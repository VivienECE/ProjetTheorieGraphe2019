#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }
void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
    }
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const{
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set <std::string> sommets_parcourus;
    sommets_parcourus.emplace(m_id);
    std::queue <const Sommet*> file;
    file.push(this);
    const Sommet*s;
    while(file.size()!=0)
    {
        s=file.front();
        file.pop(); //Ejecte de la pile
        for(const auto i:s->m_voisins) //Rajoute sommets adjacent non parcourus
        {
            if(sommets_parcourus.count(i->m_id)==0)
            {
                file.push(i);
                l_pred.emplace(i->m_id,s->m_id);
                sommets_parcourus.emplace(i->m_id);
            }
        }
    }
    return l_pred;
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS(std::unordered_set <std::string> verif,std::unordered_map<std::string,std::string> file) const{
    if (verif.count(m_id)==0)
    {
        verif.emplace(m_id);
        for(const auto i:m_voisins) //Rajoute tt ces voisins non parcourus
            if(verif.count(i->m_id)==0)
                file.emplace(i->m_id,m_id);

        for(const auto i:m_voisins) //Prends un voisin, recursif.
            if(verif.count(i->m_id)==0)
                file=i->parcoursBFS(verif,file);
    }
    return file;
}
std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const{
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set <std::string> sommets_parcourus;
    sommets_parcourus.emplace(m_id);
    std::stack <const Sommet*> pile;
    pile.push(this);
    const Sommet*s;
    while(pile.size()!=0)
    {
        s=pile.top();
        pile.pop(); //Ejecte de la pile
        for(const auto i:s->m_voisins) //Rajoute sommets adjacent non parcourus
        {
            if(sommets_parcourus.count(i->m_id)==0)
            {
                pile.push(i);
                l_pred.emplace(i->m_id,s->m_id);
                sommets_parcourus.emplace(i->m_id);
            }
        }
    }
    return l_pred;
}
std::unordered_set<std::string> Sommet::rechercherCC() const{
    std::unordered_set<std::string> cc;
    std::cout<<"rechercherCC a coder"<<std::endl;
    return cc;
}
Sommet::~Sommet()
{
    //dtor
}

Sommet::getDegre() const
{
    int degre=0;
    for (size_t i=0;i<m_voisins.size();i++)
        degre++;
    return degre;
}
