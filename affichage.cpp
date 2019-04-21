#include "affichage.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

float real_x(float x, float coef)
{
    return x*coef+ORX;
}

float real_y(float y, float coef)
{
    return ORY-y*coef;
}

void afficher_allegro_prim(graphe &g)
{
    graphe aAfficher;
    BITMAP*page;
    std::vector <float> mesPoids;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    for(int i=0;i<2;++i)
    {
        aAfficher=g.prim(i);
        aAfficher.poidsTotaux();
        mesPoids=aAfficher.getm_poids();
        //std::cout << "poids : " << mesPoids[0] << " " << mesPoids[1] << std::endl;
        //system("pause");
        //std::cout << "je rentre dans la partie affichage" << std::endl;
        aAfficher.afficher_allegro(page, i, mesPoids);
        //std::cout << "je sors de la partie arffichage" << std::endl;
    }
    blit(page, screen,0,0,0,0, 800,600);
    while (!key[KEY_ESC])
    {

    }
    //destroy_bitmap(page);
}

void afficherFrontierePareto_allegro(graphe &g, const bool &dist, const t_coef &mesCoef) //Affiche la frontier du graphe
{
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    g.pareto(page, dist, mesCoef);
    destroy_bitmap(page);
}

void boucleAffichagePareto(const std::vector <unsigned int> &espace_recherche_int, const std::vector <unsigned int> &frontiere, const std::unordered_map <unsigned int, std::vector<float>> &frontiere_dist, graphe &grapheRef, const t_coef &mesCoef, const bool &dist, BITMAP* page)
{
    std::vector <float> mesPoids;

    float longueurX=0, longueurY=0;
    int incrementGrapheAA=0;

    if(grapheRef.getm_poids().size()>2) /// L'installation du logiciel gnuplot est nécessaire pour exécuter ce if
    {

        std::ofstream fichierDom("mescoordsDom.txt", std::ios::out | std::ios::trunc);  //déclaration du flux et ouverture du fichier
        std::ofstream fichierFront("mescoordsFront.txt", std::ios::out | std::ios::trunc);  //déclaration du flux et ouverture du fichier

        if((!fichierDom)||(!fichierFront))  // si l'ouverture a réussi
        {
            std::cerr << "Erreur à l'ouverture de mes fichiers de coord!" << std::endl;
        }
        if(espace_recherche_int.size()>6000)
        {
            for(size_t i=0; i<espace_recherche_int.size(); i+=10)
            {
                for(const auto &p : grapheRef.poidsTotaux(espace_recherche_int[i]))
                {
                    fichierDom << p << " ";
                }
                fichierDom << "\n";
            }
        }
        else
        {
            for(const auto &comb : espace_recherche_int)
            {
                for(const auto &p : grapheRef.poidsTotaux(comb))
                {
                    fichierDom << p << " ";
                }
                fichierDom << "\n";
            }
        }
        std::cout << "fichierDom filled successfully" << std::endl;
        for(const auto &comb : frontiere)
        {
            for(const auto &p : grapheRef.poidsTotaux(comb))
            {
                fichierFront << p << " ";
            }
            fichierFront << "\n";
        }
        std::cout << "fichierFront filled successfully" << std::endl;
        char const *gnuname = "scriptPareto.gnu";
        FILE *f = fopen(gnuname, "w");
        fprintf(f, "set xlabel \"poids0\"\n");
        fprintf(f, "set ylabel \"poids1\"\n");
        fprintf(f, "set zlabel \"poids2\"\n");
        fprintf(f, "set title \"Representation 3D des poids du graphe\"\n");
        if (f != NULL)
        {
            if(espace_recherche_int.size()<6000)
                fprintf(f, "splot './/mescoordsDom.txt' title \"Domines\" lt rgb \"black\" lw 2 pt 5, './/mescoordsFront.txt' t \"Frontieres\" lt rgb \"violet\" lw 10 pt 10\n");
            else fprintf(f, "splot './/mescoordsDom.txt' title \"Domines\" lt rgb \"black\" lw 2 pt 5, './/mescoordsFront.txt' t \"Frontieres\" lt rgb \"violet\" lw 10 pt 10\n");
        }
        std::cout <<"je vais appeler gnu" << std::endl;
        system("start gnuplot -persist -e \" load './/scriptPareto.gnu'\"");
        fclose(f);
        fichierDom.close();
        fichierFront.close();
    }
    else
    {
        BITMAP *buffer, *page2;
        buffer=create_bitmap(800, 600);
        page2=create_bitmap(800,600);

        for(const auto &i:espace_recherche_int)
        {
            if(dist==false)
                mesPoids=grapheRef.poidsTotaux(i);
            else mesPoids = frontiere_dist.find(i)->second;
            circle(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 1 , makecol(255,255,255));
        }
        for(const auto &i:frontiere) //FRONTIERE
        {
            if(dist==false)
                mesPoids=grapheRef.poidsTotaux(i);
            else mesPoids = frontiere_dist.find(i)->second;
            circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(0,255,0));
        }

        longueurX=(mesCoef.nbGrad_X)*mesCoef.coefficient_X;
        longueurY=(mesCoef.nbGrad_Y)*mesCoef.coefficient_Y;

        line(page, ORX,ORY,ORX,ORY-longueurY,makecol(255,255,255));
        line(page, ORX,ORY,ORX+longueurX,ORY,makecol(255,255,255));

        for(int i=0; i<mesCoef.nbGrad_X; i+=mesCoef.pas_X2)
        {
            if(i%mesCoef.pas_X1==0)
            {
                line(page, real_x(i, mesCoef.coefficient_X), ORY+LONGUEURGRAD, real_x(i, mesCoef.coefficient_X), ORY-LONGUEURGRAD, makecol(200,200,200));
            }
            line(page, real_x(i, mesCoef.coefficient_X), ORY+LONGUEURGRAD2, real_x(i, mesCoef.coefficient_X), ORY-LONGUEURGRAD2, makecol(200,200,200));
        }
        for(int i=0; i<mesCoef.nbGrad_Y; i+=mesCoef.pas_Y2)
        {
            if(i%mesCoef.pas_Y1==0)
            {
                line(page, ORX-LONGUEURGRAD, real_y(i, mesCoef.coefficient_Y), ORX+LONGUEURGRAD, real_y(i, mesCoef.coefficient_Y), makecol(200,200,200));
            }
            line(page, ORX-LONGUEURGRAD2, real_y(i, mesCoef.coefficient_Y), ORX+LONGUEURGRAD2, real_y(i, mesCoef.coefficient_Y), makecol(200,200,200));
        }

        while (!key[KEY_ESC])
        {
            if(key[KEY_RIGHT])
            {
                clear(page2);
                while(key[KEY_RIGHT]){}

                /// j'eteins le point correspondant precedent
                if((dist==false)&&((incrementGrapheAA!=0)&&(incrementGrapheAA!=frontiere.size())))
                    mesPoids=grapheRef.poidsTotaux(frontiere[incrementGrapheAA-1]);
                else if ((dist==true)&&((incrementGrapheAA!=0)&&(incrementGrapheAA!=frontiere.size())))
                    mesPoids = frontiere_dist.find(frontiere[incrementGrapheAA-1])->second;
                circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(0,255,0));

                /// J'allume le point correspondant
                if(dist==false)
                    mesPoids=grapheRef.poidsTotaux(frontiere[incrementGrapheAA]);
                else mesPoids = frontiere_dist.find(frontiere[incrementGrapheAA])->second;
                circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(255,0,255));

                graphe aAfficher={frontiere[incrementGrapheAA], grapheRef};
                aAfficher.afficher_allegro(page2, 0, mesPoids);
                if(incrementGrapheAA==0)
                {
                    if(dist==false)
                        mesPoids=grapheRef.poidsTotaux(frontiere[frontiere.size()-1]);
                    else mesPoids = frontiere_dist.find(frontiere[frontiere.size()-1])->second;
                    circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(0,255,0));
                }
                incrementGrapheAA++;
                if(incrementGrapheAA==frontiere.size())
                {
                    incrementGrapheAA--;
                    if(dist==false)
                        mesPoids=grapheRef.poidsTotaux(frontiere[incrementGrapheAA-1]);
                    else mesPoids = frontiere_dist.find(frontiere[incrementGrapheAA-1])->second;
                    circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(0,255,0));
                    incrementGrapheAA=0;
                }
            }
            while(key[KEY_SPACE])
            {
                clear(buffer);
                stretch_blit(page, buffer,0,0,800,600, -50, 600-480, 640,480);
                blit(buffer, screen, 0, 0, 0, 0, 800, 600);
            }
            stretch_blit(page, buffer,0,0,800,600, -50, 600-480, 640,480);
            stretch_blit(page2, buffer, 0, 0, 800, 600, 500, 0, 640, 480);
            blit(buffer, screen, 0, 0, 0, 0, 800, 600);
        }
    }
}
