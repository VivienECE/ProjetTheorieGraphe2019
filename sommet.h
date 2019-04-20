#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "arete.h"
#include "graphe.h"
#include <string>

class arete;
class graphe;
class Sommet
{
    public:
        ///CONSTRUCTEUR
        Sommet();
        ~Sommet();
        Sommet(int,double,double);

        ///ADD
        void ajouterVoisin(Sommet*);
        void ajouterArete(int id,arete*a);

        ///GET
        std::vector<Sommet*> getm_voisins() const;
        int getm_id() const;
        double getm_x() const;
        double getm_y() const;
        std::unordered_map<int,arete*> getm_arete() const;

        ///AFFICHAGE CONSOLE
        void afficherData() const;
        void afficherVoisins() const;

        ///RECHERCHE COMP CONNEXES
        void rechercherCC(std::unordered_set<int> &sommetParcourus, const unsigned int &i, const graphe &g, int stop) const;
        void rechercherCC(std::set<int> &sommetParcourus, const unsigned int &i) const;

        ///RECREER LA CONNEXITE D'UN GRAPHE VIERGE
        void connexite();

        ///DETRUIT TOUTE LES CONNEXIONS
        void resetConnexite();

        ///RENVOIE DISTANCE
        float calcul_distance(int) const; //Calcul la distance avec le sommet entrée en parametre, uniquement distance avec sommet adj.

        ///RENVOIE ID ARETE
        int id_arete(int id_sommet) const;

    private:

        std::vector<Sommet*> m_voisins;
        std::unordered_map<int,arete*> m_arete;
        int m_id;
        double m_x, m_y;

};

#endif // SOMMET_H
