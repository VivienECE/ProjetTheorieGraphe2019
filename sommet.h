#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet();
        Sommet(std::string,double,double);
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        std::string getm_id() const;
        ~Sommet();

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
