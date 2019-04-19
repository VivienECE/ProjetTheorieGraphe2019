#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"
#include "graphe.h"
#include <string>

class arete;
class graphe;
class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet();
        Sommet(int,double,double);
        void ajouterVoisin(Sommet*);
        void resetConnexite();
        void ajouterArete(arete*);
        void afficherData() const;
        void afficherVoisins() const;
        //std::vector<float> min_distance_voisin(std::vector<int>) const; //[id][cout]
        std::vector<Sommet*> getm_voisins() const;
        int getm_id() const;
        double getm_x() const;
        double getm_y() const;
        std::vector<arete*> getm_arete() const;
        void rechercherCC(std::unordered_set<int> &sommetParcourus, const unsigned int &i, const graphe &g) const;
        void rechercherCC(std::unordered_set<int> &cc) const;
        ~Sommet();
        void connexite();
        float calcul_distance(int) const; //Calcul la distance avec le sommet entrée en parametre, uniquement distance avec sommet adj.
        //std::pair<int,float> cout_min(std::unordered_set<int>) const; //Non utulisé finalement
        int id_adjacent(int) const;
        int id_arete(int id_sommet) const;

    private:
        /// Voisinage : liste d'adjacence
        std::vector<Sommet*> m_voisins;
        std::vector<arete*> m_arete;
        //std::unordered_map<int,arete*> m_arete;
        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
