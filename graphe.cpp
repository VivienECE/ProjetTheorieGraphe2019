#include <fstream>
#include <iostream>
#include "graphe.h"
#include <queue>
#include <stack>

graphe::~graphe()
{
    //dtor
}

graphe::graphe()
{
    //ctor
}

graphe::graphe(std::string nomFichier){
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extr�mit�s
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extr�mit� � la liste des voisins de l'autre (graphe non orient�)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orient�
         m_aretes.insert({i,new arete{i,(m_sommets.find(id))->second,(m_sommets.find(id_voisin))->second}}); ///AJOUT ARRETE PROB
    }
}

void graphe::lire_poids(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int ponderation;
    float poids;
    std::string id;
    ifs >> ponderation;
    for (int i=0; i<taille; ++i)
    {
        ifs >> id;
        for(int j=0; j<ponderation; ++j)
        {
            ifs >> poids;
            m_aretes.find(i)->second->ajouter_poids(poids);
        }
    }


}

void graphe::afficher() const
{
    for (const auto i:m_sommets)
    {
        std::cout<<"sommets : ";
        i.second->afficherData();
        i.second->afficherVoisins();
    }
    for (const auto i:m_aretes)
    {
        std::cout<<"aretes : ";
        i.second->afficher();
    }
}
