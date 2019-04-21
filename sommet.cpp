#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include <algorithm>
#include "sommet.h"
#include <math.h>
#include <stack>

Sommet::Sommet()
{

}

Sommet::~Sommet()
{
    for(auto &s : m_arete)
        delete s.second;
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
        delete a.second;

    m_voisins.clear();
    m_arete.clear();
}

void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }

void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto &v:m_voisins) {
        v->afficherData();
    }
}

void Sommet::connexite(){
    for(const auto &i:m_arete) //PARCOURS Toutes les aretes du sommet
        for(const auto &j:i.second->getm_extremites()) //PARCOURS les extremites de l'arete aretes du sommet
            if(j->getm_id()!=m_id)
                ajouterVoisin(j);
}

void Sommet::rechercherCC(std::unordered_set<int> &sommetParcourus, const unsigned int &i, const graphe &g, int stop) const
{
    sommetParcourus.insert(m_id);                                        /// je met le sommet dans le tableau des sommets explores
    if(((int)m_arete.size()>1)&&((int)sommetParcourus.size()!=stop))

    {
        for(const auto &ar : m_arete)                         /// je regarde les voisins du sommet
        {
            int id_arete=ar.second->getm_id();
            int id_extr0=ar.second->getm_extremites()[0]->getm_id();
            int id_extr1=ar.second->getm_extremites()[1]->getm_id();
            int puis = pow(2, id_arete);
            if  ((i & puis)&&                         // Et regarde si elle est "activée" dans le potentiel futur graphe
                (((sommetParcourus.count(id_extr0)==0)&&(sommetParcourus.count(id_extr1)==1))||
                ((sommetParcourus.count(id_extr0)==1)&&(sommetParcourus.count(id_extr1)==0))))
            {
                /// Si l'extremité 0 n'est pas dans le tableau, c'est donc elle qu'il faut ajouter
                if  (sommetParcourus.count(id_extr0)==0)
                {
                    sommetParcourus.insert({id_extr0});
                    ar.second->getm_extremites()[0]->rechercherCC(sommetParcourus, i, g, stop);
                }
                else if (sommetParcourus.count(id_extr1)==0)
                {
                    sommetParcourus.insert({id_extr1});
                    ar.second->getm_extremites()[1]->rechercherCC(sommetParcourus, i, g, stop);
                }
            }
        }
    }
}

void Sommet::rechercherCC(std::set<int> &sommetParcourus, const unsigned int &i) const
{
    sommetParcourus.insert(m_id);

    std::stack <const Sommet*> file_sommets_explores;
    file_sommets_explores.push(this);
    const Sommet* s;


    while(!(file_sommets_explores.empty()))
    {
        s=file_sommets_explores.top();
        file_sommets_explores.pop();
        for(const auto &ar : s->m_arete)                         /// je regarde les voisins du sommet
        {
            int id_arete=ar.second->getm_id();
            int id_extr0=ar.second->getm_extremites()[0]->getm_id();
            int id_extr1=ar.second->getm_extremites()[1]->getm_id();
            //std::cout << "id_arete " << id_arete << " id_extr0 " << id_extr0 << " id_extr1 " << id_extr1 << std::endl;
            //system("pause");
            int puis = pow(2, id_arete);
            if  ((i & puis)&&                         // Et regarde si elle est "activée" dans le potentiel futur graphe
                (((sommetParcourus.count(id_extr0)==0)&&(sommetParcourus.count(id_extr1)==1))||
                ((sommetParcourus.count(id_extr0)==1)&&(sommetParcourus.count(id_extr1)==0))))
            {
                /// Si l'extremité 0 n'est pas dans le tableau, c'est donc elle qu'il faut ajouter
                if  (sommetParcourus.count(id_extr0)==0)
                {
                    sommetParcourus.insert({id_extr0});
                    file_sommets_explores.push(ar.second->getm_extremites()[0]);
                }
                else if (sommetParcourus.count(id_extr1)==0)
                {
                    sommetParcourus.insert({id_extr1});
                    file_sommets_explores.push(ar.second->getm_extremites()[1]);
                }
            }
        }
    }
}

int Sommet::getm_id() const {return m_id;}

double Sommet::getm_x() const {return m_x;}

double Sommet::getm_y() const {return m_y;}

std::unordered_map<int,arete*> Sommet::getm_arete() const {return m_arete;}

std::vector<Sommet*> Sommet::getm_voisins() const {return m_voisins;}

void Sommet::ajouterArete(int id,arete*a)
{
    m_arete.emplace(id,a);
}

float Sommet::get_distance(int &id_voisin, int &ponderation) const
{
    return m_arete.find(id_voisin)->second->getm_poids()[ponderation-1];
}

int Sommet::id_arete(int &id_sommet) const
{
    return m_arete.find(id_sommet)->second->getm_id();
}
