#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"
#include "graphe.h"

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
        int getm_id() const;
        double getm_x() const;
        double getm_y() const;
        std::vector<arete*> getm_arete() const;
        void rechercherCC(std::unordered_set<int> &sommetParcourus, const unsigned int &i, const graphe &g) const;
        void rechercherCC(std::unordered_set<int> &cc) const;
        ~Sommet();
        void connexite();

    private:
        /// Voisinage : liste d'adjacence
        std::vector<Sommet*> m_voisins;
        std::vector<arete*> m_arete;
        /// Données spécifiques du sommet
        int m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
