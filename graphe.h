#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string);
        ~graphe();
        void afficher() const;
        ///lance un parcours en largeur � partir du sommet d'identifiant id
        //void parcoursBFS(std::string) const;
        std::unordered_set<std::string> parcoursBFS(std::string,std::unordered_set<std::string>) const;
        ///lance et affiche le parcours en largeur � partir du sommet d'identifiant id
        void afficherBFS(std::string) const;
         ///lance un parcours en profondeur � partir du sommet d'identifiant id
        void parcoursDFS(std::string) const;
        ///lance et affiche le parcours en profondeur � partir du sommet d'identifiant id
        void afficherDFS(std::string) const;
        ///recherche et affiche les composantes connexes
        ///retourne le nombre de composantes connexes
        void rechercher_afficherToutesCC() const;
        ///retourne 0,1,2 cycle,chaine eul, rien
        int isEulerien() const;
        ///Non impl�ment�
        void afficherEulerien(int) const;

    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H