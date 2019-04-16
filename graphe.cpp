#include <fstream>
#include <iostream>
#include "graphe.h"
#include <queue>
#include <stack>
#include "math.h"

graphe::~graphe()
{
    //dtor
}

graphe::graphe()
{
    //ctor
}

graphe::graphe(std::vector<bool> vect,graphe g)
{
    m_sommets=g.m_sommets; //Prob arete, va également copier les voisins/arete que possede les sommets
    int num_arete=0;
    for(const auto i:vect)
    {
        if(i==true)
            m_aretes.emplace(g.m_aretes.find(num_arete)->first,g.m_aretes.find(num_arete)->second);
        num_arete++;
    }
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
    int id_arete;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
         m_aretes.insert({id_arete,new arete{id_arete,(m_sommets.find(id))->second,(m_sommets.find(id_voisin))->second}});
         //Ajout de l'arete au 2 sommets
         (m_sommets.find(id))->second->ajouterArete(new arete{id_arete,(m_sommets.find(id))->second,(m_sommets.find(id_voisin))->second});
         (m_sommets.find(id_voisin))->second->ajouterArete(new arete{id_arete,(m_sommets.find(id))->second,(m_sommets.find(id_voisin))->second});

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
    ArbreCouvrant.m_sommets.insert({m_sommets.begin()->first, new Sommet   {m_sommets.begin()->second->getm_id(),
                                                                            m_sommets.begin()->second->getm_x(),
                                                                            m_sommets.begin()->second->getm_y()}});
    float tampon, newtampon;
    arete *candidat1, *candidat2;
    int prems=1, dems=1;
    do
    {
        for(auto &s : ArbreCouvrant.m_sommets)
        {
            /// Je parcours tous les sommets de mon nouvel arbre
            for(auto &a : m_aretes)
            {
                /// Je cherche les meilleurs candidats (poids le plus faible). Autrement dit, je regarde tous les voisins de mon graphe
                /// et donc tous les voisins des sommets qui le constituent
                /// On aura ici le meilleur candidat pour l'un des sommets 's' du nouveau graphe
                if(((a.second->getm_extremites()[0]->getm_id()==s.first)&&
                        (ArbreCouvrant.m_aretes.count(a.second->getm_id())==0))
                   ||((a.second->getm_extremites()[1]->getm_id()==s.first)&&
                        (ArbreCouvrant.m_aretes.count(a.second->getm_id())==0)))
                {
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
                    if((newtampon<tampon)&&(dems==0))
                    {
                        /// Si le poids de la nouvelle arete étudiée est moins lourd, je stocke dans mon tampon le nouveau poids
                        tampon=newtampon;
                        candidat2=a.second;    // Et je met à jour le candidat
                    }
                    if(prems==1)
                        candidat1=candidat2;
                    dems=0;
                    prems=0;
                }
            }
            /// Il faut maintenant comparer l'arete 'n-1' candidate précédemment étudiée
            /// voisine de 's-1' avec l'arete qu'on vient d'etudier
            if((candidat1->getm_poids()>candidat2->getm_poids())&&(prems==0))
                candidat1=candidat2;    // Et le tour est joué ! :)
        }
        dems=1;
        prems=1;
        ArbreCouvrant.m_aretes.insert({candidat1->getm_id(), candidat1});
        if(ArbreCouvrant.m_sommets.count(candidat1->getm_extremites()[0]->getm_id())==0)
        {
            ArbreCouvrant.m_sommets.find(candidat1->getm_extremites()[1]->getm_id())->second->ajouterVoisin(candidat1->getm_extremites()[0]);
            ArbreCouvrant.m_sommets.insert({candidat1->getm_extremites()[0]->getm_id(),
                                           new Sommet{candidat1->getm_extremites()[0]->getm_id(),
                                           candidat1->getm_extremites()[0]->getm_x(),
                                           candidat1->getm_extremites()[0]->getm_y()}});
            ArbreCouvrant.m_sommets.find(candidat1->getm_extremites()[0]->getm_id())->second->ajouterVoisin(candidat1->getm_extremites()[1]);
        }
        else
        {
            ArbreCouvrant.m_sommets.find(candidat1->getm_extremites()[0]->getm_id())->second->ajouterVoisin(candidat1->getm_extremites()[1]);
            ArbreCouvrant.m_sommets.insert({candidat1->getm_extremites()[1]->getm_id(),
                                           new Sommet{candidat1->getm_extremites()[1]->getm_id(),
                                           candidat1->getm_extremites()[1]->getm_x(),
                                           candidat1->getm_extremites()[1]->getm_y()}});
            ArbreCouvrant.m_sommets.find(candidat1->getm_extremites()[1]->getm_id())->second->ajouterVoisin(candidat1->getm_extremites()[0]);
        }

    }while(ArbreCouvrant.m_sommets.size()!=m_sommets.size());

    return ArbreCouvrant;
}

std::vector<bool> add(const std::vector<bool>& a, const std::vector<bool>& b)
{
        bool c;
        std::vector<bool> result;
        for(size_t i = 0; i < a.size() ; i++){
                result.push_back(false);
                result[i] = ((a[i] ^ b[i]) ^ c); // c is carry
                c = ((a[i] & b[i]) | (a[i] & c)) | (b[i] & c);
        }
        return result;
}

std::vector<const graphe*> graphe::bruteforce()
{
    int taille=m_aretes.size();
    std::vector <bool> nb_bool,bin_1; //bin 1 est le chiffre binaire 1
    bin_1.push_back(true);
    for(int i=0; i<taille;++i) //initialise à 0 nb_bool, à 1 bin_1
    {
        nb_bool.push_back(false);
        bin_1.push_back(false);
    }
    bin_1.pop_back();

    std::vector <const graphe*> espace_recherche;
    size_t compteur=0;
    for(int i=0; i<pow(2,taille);++i) //Boucle de 0 à 2^taille
    {
        nb_bool=add(nb_bool,bin_1);//Incremente en chiffre binaire
        for(const auto i:nb_bool)
            if(i==true)
                compteur++;

        if(compteur==m_sommets.size()-1) //Si combinaison ordre-1 arete
        {
            espace_recherche.push_back(new graphe{nb_bool,*this}); //Rajoute un graphe en fonction du num bool.
        }
        compteur=0;
    }
    //espace_recherche=connexe(espace_recherche); //A coder, renvoie que les graphes connexes
    return espace_recherche;
}

void graphe::afficher_allegro(BITMAP*page) const
{
    for(const auto i:m_sommets)
        circle(page,i.second->getm_x(),i.second->getm_y(), 10, makecol(255,0,0));

    for(const auto j:m_aretes)
    {
        line(page,j.second->getm_extremites()[0]->getm_x(),j.second->getm_extremites()[0]->getm_y(),j.second->getm_extremites()[1]->getm_x(),j.second->getm_extremites()[1]->getm_y(), makecol(255,30,30));
        //std::cout << "num:" << j.first << " " << j.second->get_extremite(0)->get_x() << " " << j.second->get_extremite(0)->get_y() << " " << j.second->get_extremite(1)->get_x() << " " <<j.second->get_extremite(1)->get_y() << std::endl;
    }
    //rectfill(page, 100, 200, 200,200,makecol(209,130,30));
}
