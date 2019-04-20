#include <iostream>
#include "graphe.h"
#include "InitAllegro.h"
#include "affichage.h"
#define PRIM 1
#define BROADWAY 1
#define CUBETOWN 2
#define TRIVILLE 3
#define MANHATTAN 4
#define QUITTER 0
#define PARETO 2
#define PARETO_DIST 3



int saisie(const int& borneInf, const int& borneSup);


int main()
{
    init_Allegro();
    /*
    graphe g{"broadway.txt"};
    g.lire_poids("broadway_weights_0.txt");
    std::vector<unsigned int> Liste=g.bruteforce_dist();
    afficher_allegro2(g,Liste);
    std::cout << Liste.size() <<std::endl;*/
    graphe g;
    unsigned int choixAlgo=0, choixFich=0, choixP=0;
    std::string fichier, fichierP;
    do
    {
        std::cout   << "Quel graphe voulez-vous tracer ?"  <<std::endl
                    << "<1> broadway" << std::endl
                    << "<2> cubetown" << std::endl
                    << "<3> triville" << std::endl
                    << "<4> manhattan"<< std::endl
                    << "<0> quitter"  << std::endl;
        choixFich=saisie(QUITTER,MANHATTAN);
        switch(choixFich)
        {
        case BROADWAY:
            fichier="broadway.txt";
            std::cout   << "Quel fichier de poids ?" << std::endl
                        << "<0>     <1>     <2>" << std::endl;
            choixP=saisie(0,2);
            fichierP += "broadway_weights_" + std::to_string(choixP) + ".txt";
            break;
        case CUBETOWN :
            fichier="cubetown.txt";
            fichierP="cubetown_weights_0.txt";
            break;
        case TRIVILLE :
            fichier="triville.txt";
            std::cout   << "Quel fichier de poids ?" << std::endl
                        << "<0>     <1>" << std::endl;
            choixP=saisie(0,1);
            fichierP += "triville_weights_" + std::to_string(choixP) + ".txt";
            break;
        case MANHATTAN :
            fichier="manhattan.txt";
            std::cout   << "Quel fichier de poids ?" << std::endl
                        << "<0>     <1>     <2>" << std::endl;
            choixP=saisie(0,2);
            fichierP += "manhattan_weights_" + std::to_string(choixP) + ".txt";
            break;
        case QUITTER :
            exit(EXIT_SUCCESS);
        default :
            break;
        }
        graphe g{fichier};
        g.lire_poids(fichierP);
        fichier.clear();
        fichierP.clear();
        g.poidsTotaux();
        system("cls");
        std::cout   << "Quel algorithme voulez-vous utiliser ?"  <<std::endl
                    << "<1> prim" << std::endl
                    << "<2> pareto arbre couvrant double pondération, obtimisation bi-objectif" << std::endl
                    << "<3> pareto optimisation double objectif poids//distance" << std::endl
                    << "<0> quitter" << std::endl;
        choixAlgo=saisie(QUITTER, PARETO_DIST);
        switch(choixAlgo)
        {
        case PRIM :
            afficher_allegro_prim(g);
            break;
        case PARETO :
            afficherFrontierePareto_allegro(g, false);
            break;
        case PARETO_DIST :
            afficherFrontierePareto_allegro(g, true);
            break;
        case QUITTER :
            exit(EXIT_SUCCESS);
        default :
            break;
        }
        system("cls");
    }while (choixAlgo !=0);
    return 0;
}


// Code inspiré de cpp.developpez.com
int saisie(const int& borneInf, const int& borneSup)
{
    int choix = 0;
    std::cout << std::endl << "Selectionnez votre choix entre " << borneInf <<" et " << borneSup << " : ";
    while ( ! ( std::cin >> choix ) || choix< borneInf || choix > borneSup )
    {
        if ( std::cin.fail() )
        {
            std::cout << "Saisie incorrecte, recommencez : ";
            std::cin.clear();                                                       // Efface les bits d'erreur
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );   // Supprime la ligne erronée dans le buffer
        }
        else
            std::cout << "Votre choix doit etre compris entre " << borneInf << " et " << borneSup << ", recommencez :";
    }
    return choix;
}

END_OF_MAIN();
