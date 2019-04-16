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
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
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

void graphe::ajouter_arete(int id,float P1,float P2 , Sommet* S1, Sommet* S2)
{
    m_aretes.insert({id,new arete(id,P1,P2,S1,S2)});
}

graphe graphe::prim(int poids)
{
    graphe ArbreCouvrant;


    ArbreCouvrant.m_sommets.insert({m_sommets.begin()->first, m_sommets.begin()->second});




    float tampon, newtampon;
    arete *candidat1, *candidat2;
    int prems=1, dems=1;
    do
    {
        for(auto &s : ArbreCouvrant.m_sommets)
        {
            /// Je parcours tous les sommets de mon nouvel arbre
            std::cout << ArbreCouvrant.m_sommets.size() << std::endl;
            for(auto &a : m_aretes)
            {
                /// Je cherche les meilleurs candidats (poids le plus faible). Autrement dit, je regarde tous les voisins de mon graphe
                /// et donc tous les voisins des sommets qui le constituent
                /// On aura ici le meilleur candidat pour l'un des sommets 's' du nouveau graphe
                if(((a.second->getm_extremites()[0]->getm_id()==s.first)&&
                        (ArbreCouvrant.m_sommets.count(a.second->getm_extremites()[1]->getm_id())==0))
                   ||((a.second->getm_extremites()[1]->getm_id()==s.first)&&
                        (ArbreCouvrant.m_sommets.count(a.second->getm_extremites()[0]->getm_id())==0)))
                {
                    std::cout<< "dans le if 1" << std::endl;
                    /// Si l'arete que j'explore a d'un coté un sommet du nouveau graphe
                    /// et de l'autre un sommet non present dans le nouveau graphe

                    newtampon=a.second->getm_poids()[poids];    // Je stocke dans une valeur tampon le poids de l'arete
                    if(dems==1)
                    {
                        /// Si c'est la première fois que je passe, je stocke dans mon tampon de poids le plus faible
                        /// le poids de l'arete pour avoir un élèment de comparaison à la boucle suivante

                        tampon=newtampon;
                        candidat2=a.second;    // Je stocke le premier candidat au cas où on n'ai qu'une seule arete candidate
                    }
                    if((newtampon>tampon)&&(dems==0))
                    {
                        /// Si le poids de la nouvelle arete étudiée est moins lourd, je stocke dans mon tampon le nouveau poids
                        tampon=newtampon;
                        candidat2=a.second;    // Et je met à jour le candidat
                    }
                    if(prems==1)
                        candidat1=candidat2;
                    dems=0;
                    prems=0;
                    std::cout << tampon << std::endl;
                    system("pause");
                }
            }
            /// Il faut maintenant comparer l'arete 'n-1' candidate précédemment étudiée
            /// voisine de 's-1' avec l'arete qu'on vient d'etudier
            if(candidat1->getm_poids()>candidat2->getm_poids())
                candidat1=candidat2;    // Et le tour est joué ! :)
        }
        ArbreCouvrant.m_aretes.insert({candidat1->getm_id(), candidat1});
            //new arete(candidat1->getm_id(),candidat1->getm_poids()[0],candidat1->getm_poids()[1],candidat1->getm_extremites()[0],candidat1->getm_extremites()[1]));
        if(ArbreCouvrant.m_sommets.count(candidat1->getm_extremites()[0]->getm_id())==0)
            ArbreCouvrant.m_sommets.insert({candidat1->getm_extremites()[0]->getm_id(),
                                            candidat1->getm_extremites()[0]});
        else ArbreCouvrant.m_sommets.insert({candidat1->getm_extremites()[1]->getm_id(), candidat1->getm_extremites()[1]});

    }while(ArbreCouvrant.m_sommets.size()!=m_sommets.size());

    return ArbreCouvrant;
}



















