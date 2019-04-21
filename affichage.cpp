#include "affichage.h"
#include <iostream>
#include <unordered_map>

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
        aAfficher=g.prim(i);/*
        std::cout << " affichage des aretes dans affichage.ccp" << std::endl;
        for(const auto &ar : aAfficher.m_aretes)
        {
            ar.second->afficher()
        }
        system("pause");*/
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

void afficherFrontierePareto_allegro(const graphe &g, const bool &dist, const t_coef &mesCoef) //Affiche la frontier du graphe
{
    BITMAP*page;
    //PARTIE AFFICHAGE
    page=create_bitmap(800,600);
    g.pareto(page, dist, mesCoef);
    destroy_bitmap(page);
}

void boucleAffichagePareto(const std::vector <unsigned int> &espace_recherche_int, const std::vector <unsigned int> &frontiere, const std::unordered_map <unsigned int, std::vector<float>> &frontiere_dist, const graphe &grapheRef, const t_coef &mesCoef, const bool &dist, BITMAP* page)
{
    std::vector <float> mesPoids;

    float longueurX=0, longueurY=0;
    int incrementGrapheAA=0;

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
            if((dist==false)&&((incrementGrapheAA!=0)&&(incrementGrapheAA!=(int)frontiere.size())))
                mesPoids=grapheRef.poidsTotaux(frontiere[incrementGrapheAA-1]);
            else if ((dist==true)&&((incrementGrapheAA!=0)&&(incrementGrapheAA!=(int)frontiere.size())))
                mesPoids = frontiere_dist.find(frontiere[incrementGrapheAA-1])->second;
            circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(0,255,0));

            /// J'allume le point correspondant
            if(dist==false)
                mesPoids=grapheRef.poidsTotaux(frontiere[incrementGrapheAA]);
            else mesPoids = frontiere_dist.find(frontiere[incrementGrapheAA])->second;
            circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(255,0,255));

            graphe aAfficher={(int)frontiere[incrementGrapheAA], grapheRef};
            aAfficher.afficher_allegro(page2, 0, mesPoids);
            if(incrementGrapheAA==0)
            {
                if(dist==false)
                    mesPoids=grapheRef.poidsTotaux(frontiere[frontiere.size()-1]);
                else mesPoids = frontiere_dist.find(frontiere[frontiere.size()-1])->second;
                circlefill(page, real_x(mesPoids[0], mesCoef.coefficient_X),real_y(mesPoids[1], mesCoef.coefficient_Y), 2 , makecol(0,255,0));
            }
            incrementGrapheAA++;
            if((size_t)incrementGrapheAA==frontiere.size())
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
