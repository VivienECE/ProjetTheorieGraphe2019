#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include <algorithm>
#include "sommet.h"
#include <stack>
Sommet::Sommet()
{

}

Sommet::Sommet(int id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}

void Sommet::ajouterVoisin(Sommet* voisin){
    m_voisins.push_back(voisin);
}

void Sommet::resetConnexite(){
    for(const auto &v : m_voisins)
        delete v;
    for(const auto &a : m_arete)
        delete a;
    m_voisins.clear();
    m_arete.clear();
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

void Sommet::connexite(){
    for(const auto i:m_arete) //PARCOURS Toutes les aretes du sommet
        for(const auto j:i->getm_extremites()) //PARCOURS les extremites de l'arete aretes du sommet
            if(j->getm_id()!=m_id)
                ajouterVoisin(j);
}
/*
void Sommet::rechercherCC(std::unordered_set<int> &cc) const
{
    cc.insert(m_id);                                        /// je met le sommet dans le tableau des sommets explores
    //std::cout << m_id << "   " << std::endl;                /// je l'affiche dans la console
    //this->afficherVoisins();
    //std::cout << std::endl;
    for(const auto &it : m_voisins)                         /// je regarde les voisins du sommet
    {
        if(cc.count(it->m_id)==0)                           /// un blindage qui verifie que le voisin n'est pas deja dans le tableau cc
            it->rechercherCC(cc);                           /// j'explore tous les voisins en utilisant la recursivite
    }
}*/

void Sommet::rechercherCC(std::unordered_set<int> &cc) const
{
    cc.insert(m_id);

    std::stack <const Sommet*> file_sommets_explores;
    file_sommets_explores.push(this);
    const Sommet* s;


    while(!(file_sommets_explores.empty()))
    {
        s=file_sommets_explores.top();
        file_sommets_explores.pop();

        for(const auto &it : s->m_voisins)
        {
            if( (cc.find(it->m_id)==cc.end()) && (it != this))
            {
                file_sommets_explores.push(it);
                cc.insert({it->m_id, s->m_id});
            }
        }

    }
}

int Sommet::getm_id() const {return m_id;}

double Sommet::getm_x() const {return m_x;}

double Sommet::getm_y() const {return m_y;}

Sommet::~Sommet()
{/*
    for(auto it : m_voisins)
        delete it;
    std::cout << "arthur a envie de fr caca" << std::endl;*/
    for(auto it : m_arete)
        delete it;
}

void Sommet::ajouterArete(arete*a)
{
    m_arete.push_back(a);
}

float Sommet::calcul_distance(int id_voisin) const
{
    int i=0;
    float distance=0;
    while(distance==0)
    {
        distance=(int)m_arete[i]->getm_distance(m_id, id_voisin);
        i++;
    }
    //std::cout<< " DEBUGG POIDS:" << distance<<std::endl;
    return distance;
}

std::vector<Sommet*> Sommet::getm_voisins() const {return m_voisins;}

/*
std::pair<int,float> Sommet::cout_min(std::unordered_set<int> s_marque) const
{
    float coutMin=m_arete[0]->getm_poids()[m_arete[0]->getm_poids().size()-1];
    int id=id_adjacent(m_arete[0]->getm_id());

    for(const auto i:m_arete)
    {
        if(i->getm_poids()[i->getm_poids().size()-1]<coutMin && s_marque.count(id_adjacent(i->getm_id()))==0)
        {
            id=id_adjacent(i->getm_id());
            coutMin=i->getm_poids()[i->getm_poids().size()-1];
        }
    }
    std::pair<int,float> retour(id,coutMin);
    std::cout<< retour.first <<":"<<retour.second<<std::endl<<std::endl;
    return retour;
}

/*
int Sommet::id_adjacent(int id_arete) const
{
    for(const auto i:m_arete)
    {
        if(i->getm_id()==id_arete)
            if(m_id != i->getm_extremites()[0]->getm_id())
                return i->getm_extremites()[0]->getm_id();
            else
                return i->getm_extremites()[1]->getm_id();
    }
}*/
