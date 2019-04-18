#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

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
