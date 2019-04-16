#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet()
{

}

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

std::string Sommet::getm_id() const {return m_id;}

double Sommet::getm_x() const {return m_x;}

double Sommet::getm_y() const {return m_y;}

Sommet::~Sommet()
{
    //dtor
}
