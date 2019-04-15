#include <fstream>
#include <iostream>
#include "graphe.h"
#include <queue>
#include <stack>

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
    }
}
void graphe::afficher() const{
    std::cout<<"graphe : "<<std::endl
            <<"  ordre : "<<std::endl;

    for (const auto i:m_sommets)
    {
        std::cout<<"sommet : ";
        i.second->afficherData();
        i.second->afficherVoisins();
    }
}

std::unordered_set<std::string> graphe::parcoursBFS(std::string id, std::unordered_set<std::string> sommets_parcourus) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
    for(const auto i:l_pred)
    {
        if(sommets_parcourus.count(i.first)==0)
            sommets_parcourus.emplace(i.first);
        if(sommets_parcourus.count(i.second)==0)
            sommets_parcourus.emplace(i.second);
    }
    return sommets_parcourus;

}
void graphe::afficherBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
/*int graphe::rechercher_afficherToutesCC() const{
    int i=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set <std::string> sommets_parcourus;
    std::unordered_set <std::string> liste_sommets_connexes;
    int nbr=0;
    for(const auto x:m_sommets)
    if(sommets_parcourus.count(x.first)==0)
    {
        sommets_parcourus.emplace(x.first);
        sommets_parcourus=parcoursBFS(x.first,sommets_parcourus);
        liste_sommets_connexes.emplace(x.first);
        liste_sommets_connexes=parcoursBFS(x.first, liste_sommets_connexes);
        nbr++;
        std::cout<<"cc"<<nbr<<std::endl;
        for(const auto y:liste_sommets_connexes)
            std::cout <<"    "<< y ;
        std::cout<<std::endl;
        liste_sommets_connexes.clear();
    }
    return i;
}*/

void graphe::rechercher_afficherToutesCC() const{
    int i=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_map<std::string,std::string> sommets_parcourus; //Liste des sommets du graphe parcourus par la boucle.
    std::unordered_map<std::string,std::string> parcours;
    std::unordered_set<std::string> liste_sommets_connexes; //Sommets connexes à afficher
    //Utili° map car les fonctions retournent des maps, ça ne pose finalement pas de prob à l'affichage.
    for(const auto x:m_sommets) //Parcours tout les sommets du graphe
        if(sommets_parcourus.count(x.first)==0)//Si n° du sommet n'est pas dans la liste des sommets parcourus.
        {
            parcours=x.second->parcoursBFS(); //Parcours le graphe
            //liste_sommets_connexes.emplace(x.first); //Rajoute le sommet de départ, cas ou 1 seul sommet
            i++;
            std::cout<<"cc"<<i<<std::endl;
            for(const auto y:parcours) //Affichage des composantes connexes et actualisation de la liste des sommets parcourus.
            {
                liste_sommets_connexes.emplace(y.first);
                sommets_parcourus.emplace(y.first,y.first);
            }
            for(const auto z:liste_sommets_connexes) //Affichage des composantes connexes et actualisation de la liste des sommets parcourus.
                std::cout <<"    "<< z ; //Normalement, pas de doublon à l'affichage si graphe correctement parcourus map(X,Y)
            std::cout<<std::endl;
            liste_sommets_connexes.clear();//Vide la liste des sommets connexes pour la prochaie boucle
        }
    return;
}
graphe::~graphe()
{
    //dtor
}

int graphe::isEulerien() const //SI LE COURS EST MOINS CLAIR C ENCORE MIEUX SVP
{
    //2 CYCLE EULERIEN TT SOMMETS PAIRS
    //1 CHAINE 0 ou 2 SOMMET IMPAIRS
    //0 SINON
    int valeur_retour=2,nb_impairs=0;
    for(const auto i:m_sommets) //Parcours tout les sommets du graphe
    {
        if (i.second->getDegre()!=2) //Si sommet non pairs, pas de cycle
            valeur_retour=0;
        if (i.second->getDegre()%2!=0) //Compte le nb de sommet impairs.
            nb_impairs++;
    }
    if (nb_impairs==0||nb_impairs==2) //Detecte chaine eulerienne
        valeur_retour=1;
    std::cout << "Sous_Programme EULER: " << valeur_retour << std::endl;
    return valeur_retour;
}

void graphe::afficherEulerien(int valeur) const
{
    if (valeur==1) //DONC CHAINE EULER, AFFICHE LE PARCOURS ENTRE LES 2 EXTREMITES, 2 sommets impairs
    {

    }
    else if (valeur==2)//DONC CYCLE, DONC AFFICHE TOUT LE GRAPHE
        this->afficher();
}
