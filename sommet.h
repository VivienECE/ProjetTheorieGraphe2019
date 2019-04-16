#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"

class arete;
class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet();
        Sommet(std::string,double,double);
        void ajouterVoisin(Sommet*);
        void ajouterArete(arete*);
        void afficherData() const;
        void afficherVoisins() const;
        std::string getm_id() const;
        double getm_x() const;
        double getm_y() const;
        ~Sommet();

    private:
        /// Voisinage : liste d'adjacence
        std::vector<Sommet*> m_voisins;
        std::vector<arete*> m_arete;
        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
