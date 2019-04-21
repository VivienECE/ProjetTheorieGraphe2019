#include "graphe.h"
#include <queue>
#include <stack>
#include "math.h"
#include <algorithm>
#include <set>
#include "time.h"
#include "affichage.h"

class prioritize{public: bool operator ()(std::pair<int, float>&p1 ,std::pair<int, float>&p2){return p1.second>p2.second;}};
graphe::~graphe()
{

}

graphe::graphe()
{
    //ctor
}

std::vector<float> graphe::getm_poids(){return m_poidsTotaux;}

graphe::graphe(const int &valeur, const graphe &g)
{
    for(const auto & s_o_m : g.m_sommets)
    {
        m_sommets.insert({s_o_m.first,
                         new Sommet {s_o_m.second->getm_id(),
                                    s_o_m.second->getm_x(),
                                    s_o_m.second->getm_y()}});
    }

    for(size_t num_arete=0;num_arete<g.m_aretes.size();num_arete++)
    {
        int i=pow(2,num_arete);
        if(valeur&i)
        {
            m_aretes.insert({g.m_aretes.find((int)num_arete)->first,
                            new arete{  (int)num_arete,
                                        g.m_aretes.find((int)num_arete)->second->getm_poids(),
                                        m_sommets.find(g.m_aretes.find((int)num_arete)->second->getm_extremites()[0]->getm_id())->second,
                                        m_sommets.find(g.m_aretes.find((int)num_arete)->second->getm_extremites()[1]->getm_id())->second}});

            m_sommets.find(m_aretes.find(num_arete)->second->getm_extremites()[0]->getm_id())->second
            ->ajouterArete(m_aretes.find(num_arete)->second->getm_extremites()[1]->getm_id(),m_aretes.find(num_arete)->second);

             m_sommets.find(m_aretes.find(num_arete)->second->getm_extremites()[1]->getm_id())->second
            ->ajouterArete(m_aretes.find(num_arete)->second->getm_extremites()[0]->getm_id(),m_aretes.find(num_arete)->second);
        }
    }
}

graphe::graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
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
    int id_voisin;
    int id_arete;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
         m_aretes.insert({id_arete,new arete{id_arete,(m_sommets.find(id))->second,(m_sommets.find(id_voisin))->second}});
         //Ajout de l'arete au 2 sommets m_aretes.find(id_arete);
         (m_sommets.find(id))->second->ajouterArete(id_voisin,m_aretes.find(id_arete)->second);
         (m_sommets.find(id_voisin))->second->ajouterArete(id,m_aretes.find(id_arete)->second);

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
            m_aretes.find(i)->second->set_poids(poids);
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
    std::cout<<std::endl;
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

void graphe::poidsTotaux()
{
    int prems=1;
    for(const auto &a : m_aretes)
    {
        for(size_t i=0; i<a.second->getm_poids().size(); ++i)
        {
            if(prems==1)
                m_poidsTotaux.resize(a.second->getm_poids().size(),0);
            m_poidsTotaux[i]+=a.second->getm_poids()[i];
            prems=0;
        }
    }
}

graphe graphe::prim(int poids)
{
    std::cout << "je rentre dans prim" << std::endl;
    graphe ArbreCouvrant;
    ArbreCouvrant.m_sommets.insert({m_sommets.begin()->first, new Sommet   {m_sommets.begin()->second->getm_id(),
                                                                            m_sommets.begin()->second->getm_x(),
                                                                            m_sommets.begin()->second->getm_y()}});
    float tampon=0, newtampon=0;
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
                if((((a.second->getm_extremites()[0]->getm_id()==s.first)&&
                        (ArbreCouvrant.m_aretes.count(a.second->getm_id())==0))
                        ||((a.second->getm_extremites()[1]->getm_id()==s.first)&&
                        (ArbreCouvrant.m_aretes.count(a.second->getm_id())==0)))
                    &&(((ArbreCouvrant.m_sommets.count(a.second->getm_extremites()[0]->getm_id())==0) &&
                        (ArbreCouvrant.m_sommets.count(a.second->getm_extremites()[1]->getm_id())==1))||
                        ((ArbreCouvrant.m_sommets.count(a.second->getm_extremites()[0]->getm_id())==1) &&
                        (ArbreCouvrant.m_sommets.count(a.second->getm_extremites()[1]->getm_id())==0))))
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
            if((candidat1->getm_poids()[poids]>candidat2->getm_poids()[poids])&&(prems==0))
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
    std::cout << "je sors de prim" << std::endl;
    return ArbreCouvrant;
}

void graphe::pareto(BITMAP*page, const bool &dist, const t_coef &mesCoef) const
{
    clock_t t1, t2;
    //TOUT AFFICHER+SURLIGNER FRONTIERE
    std::vector <unsigned int> espace_recherche_int;
    std::vector <unsigned int> future_frontiere;
    std::vector <unsigned int> frontiere;
    std::unordered_map <unsigned int, std::vector<float>> frontiere_dist;

    if(dist==false)
    {
        espace_recherche_int=bruteforce();
        t1=clock();
        frontiere=frontierePareto(espace_recherche_int);
    }
    else
    {
        espace_recherche_int=bruteforce_dist();
        frontiere=espace_recherche_int;
        t1=clock();
        frontiere_dist=frontierePareto_dist(frontiere);
    }
    t2=clock();

    std::cout<< "jai fini pareto" << std::endl;
    std::cout << "temps de compilation de pareto : " << (double) (t2-t1)/1000 << std::endl;
    std::cout   << "espace_recherche_int " << espace_recherche_int.size() << std::endl
                << "frontiere "<< frontiere.size() << std::endl;
    boucleAffichagePareto(espace_recherche_int, frontiere, frontiere_dist, *this, mesCoef, dist, page);
}

std::vector <unsigned int> graphe::bruteforce() const
{
    clock_t t1, t2;
    t1=clock();
    Sommet *s0 = m_sommets.begin()->second;
    std::vector <unsigned int> espace_recherche_int;
    std::set <int> sommetParcourus;
    std::string a;
    int exp=0, puis=0;
    std::vector <int> mesPos;
    for(unsigned int i=0; i<m_aretes.size()-m_sommets.size()+1; i++)
    {
        a+="0";
    }
    for(unsigned int i =0; i< m_sommets.size()-1; i++)
    {
        a+="1";
    }
    do {
        //++i;
        for(const auto &b : a)
        {
            if(b=='1')
            {
                puis+=(int)pow(2,exp);
            }
            exp++;
        }
        s0->rechercherCC(sommetParcourus, puis);
        if(sommetParcourus.size()==m_sommets.size())
        {
            espace_recherche_int.push_back(puis);
        }
        sommetParcourus.clear();
        puis=0;
        exp=0;
    } while(std::next_permutation(a.begin(), a.end()));
    std::cout << "jai fini bruteforce" << std::endl;
    std::cout << "taille de espace_recherche_int " << espace_recherche_int.size() << std::endl;
    t2=clock();
    std::cout << "temps de compilation de brutefroce : " << (float)(t2 -t1)/1000 << std::endl;
    return espace_recherche_int;    // Pour finir, je retourne l'unordered_map qui contient mes combinaisons et les poids qui leurs sont associées
}

std::vector<unsigned int> graphe::frontierePareto(std::vector<unsigned int> espace_recherche_int) const//RENVOIE LA FRONTIERE
{
    // On aura ici deux unordered_map du même type que notre espace de recherche :
    // - Une stockant tous les sommets qui ne sont pas à la frontière 'NONfrontiere'
    // - Une stockant tous les sommets qui sont à la frontière 'frontiere'
    // L'interet et que je rempli 'frontiere' en mettant tout ce qui n'est pas 'NONfrontiere'
    std::vector <float> poids_aComp1, poids_aComp2;
    int incrementBoucle2=0, incrementBoucle1=0, paspossible=0, reste=0;
    size_t marqueur1,marqueur2=0;
    do
    {
        /// Cette boucle for me permet de parcourir chaque combinaison de 'espace_recherche_int
        /// en créant et deletant un nouveau graphe pour chaque combinaison et en la comparant
        /// deux à deux avec les autres combinaisons.
        poids_aComp1 = this->poidsTotaux(espace_recherche_int[incrementBoucle1]);
        do
        {
            if(espace_recherche_int[incrementBoucle2]!=espace_recherche_int[incrementBoucle1])    // Si on ne parle pas du même sommet
            {
                /// Je créé le graphe
                poids_aComp2 = this->poidsTotaux(espace_recherche_int[incrementBoucle2]);
                for(size_t i=0;i<poids_aComp1.size();i++)   // Je parcours tous les poids
                {
                    if(poids_aComp1[i]<poids_aComp2[i]) // Je compare la stricte supériorité
                        marqueur1++;
                    if(poids_aComp1[i]<=poids_aComp2[i])// Je compare la supériorité
                        marqueur2++;
                }
                if( (marqueur1>=1) && (marqueur2 == poids_aComp1.size()))    // Si j'ai un élément strictement meilleur et les deux éléments au moins meilleurs
                {
                    espace_recherche_int.erase(espace_recherche_int.cbegin()+incrementBoucle2);   // Le sommet est dominé, je le supprime donc de mon espace
                    reste++;
                }
                else if(marqueur1==0)   // Si rien n'est meilleur chez comp_1
                {
                    espace_recherche_int.erase(espace_recherche_int.cbegin()+incrementBoucle1) ;   // Je le supprime
                    incrementBoucle2=espace_recherche_int.size();   // et je termine le while pour passer au comp_1 suivant
                    paspossible++;
                    incrementBoucle1--;
                }
                marqueur1=0;    // Remise à zéro des marqueurs
                marqueur2=0;
            }
            if((incrementBoucle2!=(int)espace_recherche_int.size()) && (reste==0))
                incrementBoucle2++; // J'incrémente l'incrément de mon comp_2
            paspossible=0;
            reste=0;
        }while(incrementBoucle2!=(int)espace_recherche_int.size()); // Et je fais tourner ma boucle tant que l'incrément n'arrive pas au bout d'espace_recherche
        incrementBoucle2=0;
        incrementBoucle1++;
    }while(incrementBoucle1!=(int)espace_recherche_int.size());

    return espace_recherche_int;   // Je retourne enfin la frontiere, i.e. toutes les combinaisons dominantes avec leurs poids.
    /// Je retourne maintenant tranquillement dans 'pareto()'...
}

std::vector<float> graphe::poidsTotaux(unsigned int i) const
{
    int puis=0;
    std::vector <float> aRendre;
    aRendre.resize(m_poidsTotaux.size(),0);
    for(const auto &ar : m_aretes)
    {
        puis=pow(2,ar.second->getm_id());
        if(puis&i)
        {
            for(size_t i=0; i<m_poidsTotaux.size(); ++i)
            {
                aRendre[i]+=ar.second->getm_poids()[i];
            }
        }
    }
    return aRendre;
}

std::vector <unsigned int> graphe::bruteforce_dist() const
{
    std::cout << "je rentre dans bruteforce_dist" << std::endl;
    clock_t t1, t2;
    t1=clock();
    Sommet *s0 = m_sommets.begin()->second;
    std::vector <unsigned int> espace_recherche_int;
    std::set <int> sommetParcourus;
    std::string a;
    int exp=0, puis=0;
    size_t maxS = m_sommets.size();
    for (size_t max_temp=maxS; max_temp<=m_aretes.size()+1; max_temp++)
    {
        std::cout << "nombre d'element dans espace_recherche_int " << espace_recherche_int.size() << std::endl;
        std::cout   << "a la combinaison "
                    << max_temp-1 << " parmi " << m_aretes.size() << std::endl;
        for(unsigned int i=0; i<m_aretes.size()-max_temp+1; i++)
        {
            a+="0";
        }
        for(unsigned int i =0; i< max_temp-1; i++)
        {
            a+="1";
        }
        do
        {
            //++i;
            for(const auto &b : a)
            {
                if(b=='1')
                {
                    puis+=(int)pow(2,exp);
                }
                exp++;
            }
            s0->rechercherCC(sommetParcourus, puis);
            if(sommetParcourus.size()==m_sommets.size())
            {
                espace_recherche_int.push_back(puis);
            }
            sommetParcourus.clear();
            puis=0;
            exp=0;
        } while(std::next_permutation(a.begin(), a.end()));
        a.clear();
    }
    std::cout << "jai fini bruteforce" << std::endl;
    std::cout << "taille de espace_recherche_int " << espace_recherche_int.size() << std::endl;
    t2=clock();
    std::cout << "temps de compilation de brutefroce : " << (float)(t2 -t1)/1000 << std::endl;
    return espace_recherche_int;    // Pour finir, je retourne l'unordered_map qui contient mes combinaisons et les poids qui leurs sont associées
}

std::unordered_map <unsigned int, std::vector<float>> graphe::frontierePareto_dist(std::vector<unsigned int> &espace_recherche_int) const//RENVOIE LA FRONTIERE
{
    std::cout << "je rentre dans frontierepareto_dist" << std::endl;
    /// On aura ici deux unordered_map du même type que notre espace de recherche :
    /// - Une stockant tous les sommets qui ne sont pas à la frontière 'NONfrontiere'
    /// - Une stockant tous les sommets qui sont à la frontière 'frontiere'
    /// L'interet et que je rempli 'frontiere' en mettant tout ce qui n'est pas 'NONfrontiere'
    std::unordered_map <unsigned int, std::vector<float>> mesPoids_E_R;
    for(const auto &e_r_i: espace_recherche_int)
    {
        mesPoids_E_R.insert({e_r_i, this->poidsTotauxDjikstra(e_r_i)});
    }
    std::vector <float> poids_aComp1, poids_aComp2;
    int incrementBoucle2=0, incrementBoucle1=0, paspossible=0, reste=0;
    size_t marqueur1,marqueur2=0;
    do
    {
        /// Cette boucle for me permet de parcourir chaque combinaison de 'espace_recherche_int
        /// en créant et deletant un nouveau graphe pour chaque combinaison et en la comparant
        /// deux à deux avec les autres combinaisons.

        poids_aComp1 = mesPoids_E_R.find(espace_recherche_int[incrementBoucle1])->second;


        do
        {
            if(espace_recherche_int[incrementBoucle2]!=espace_recherche_int[incrementBoucle1])    /// Si on ne parle pas du même sommet
            {
                /// Je créé le graphe
                poids_aComp2 = mesPoids_E_R.find(espace_recherche_int[incrementBoucle2])->second;

                for(size_t i=0;i<poids_aComp1.size();i++)   /// Je parcours tous les poids
                {
                    if(poids_aComp1[i]<poids_aComp2[i]) /// Je compare la stricte supériorité
                        marqueur1++;
                    if(poids_aComp1[i]<=poids_aComp2[i])/// Je compare la supériorité
                        marqueur2++;
                }
                if( (marqueur1>=1) && (marqueur2 == poids_aComp1.size()))    /// Si j'ai un élément strictement meilleur et les deux éléments au moins meilleurs
                {
                    espace_recherche_int.erase(espace_recherche_int.cbegin()+incrementBoucle2);   /// Le sommet est dominé, je le supprime donc de mon espace
                    reste++;
                }
                else if(marqueur1==0)   // Si rien n'est meilleur chez comp_1
                {

                    espace_recherche_int.erase(espace_recherche_int.cbegin()+incrementBoucle1) ;   /// Je le supprime

                    incrementBoucle2=espace_recherche_int.size();   /// et je termine le while pour passer au comp_1 suivant
                    paspossible++;
                    incrementBoucle1--;
                }
                marqueur1=0;    /// Remise à zéro des marqueurs
                marqueur2=0;
            }
            if((incrementBoucle2!=(int)espace_recherche_int.size())&&(reste==0))
                incrementBoucle2++; /// J'incrémente l'incrément de mon comp_2
            paspossible=0;
            reste=0;
        }while(incrementBoucle2!=(int)espace_recherche_int.size()); /// Et je fais tourner ma boucle tant que l'incrément n'arrive pas au bout d'espace_recherche
        incrementBoucle2=0;
        incrementBoucle1++;
    }while(incrementBoucle1!=(int)espace_recherche_int.size());

    return mesPoids_E_R;   /// Je retourne enfin la frontiere, i.e. toutes les combinaisons dominantes avec leurs poids.
    /// Je retourne maintenant tranquillement dans 'pareto()'...
}

float graphe::Djikstra_sommet(int id_debut, const unsigned int &I) const
{
    //INI
    std::priority_queue<std::pair <int,float>,std::vector<std::pair<int,float>>, prioritize> p_queue; //QUEUE PRIORITAIRE, TRI PAR POIDS DECROISSANT, DEF Ligne 3, graphe.Cpp
    std::unordered_map<int,float> s_marques; s_marques.emplace(id_debut,0);
    p_queue.push(std::make_pair(id_debut,0));

    //PARCOURS BFS PILE PRIORITAIRE, TJR EN PREMIER LE SOMMET AVEC PLUS PETIT POIDS
    while(p_queue.size()!=0)
    {
        int id=p_queue.top().first; //ENREGISTRE LE PREMIER SOMMET ET SA DISTANCE TOTAL AU SOMMET D'ORIGINE
        float poids=p_queue.top().second; //MEMOIRE
        p_queue.pop(); //EJECTE
        for(const auto &i:m_sommets.find(id)->second->getm_voisins()) //Parcours sommets adj
         if(I & (int)pow(2,i->id_arete(id)) )//Si l'arrete existe, evite de recrée un graphe, verif
           // if(s_marques.count(i->getm_id())==0) //Si sommet non marqués
            if(s_marques.find(i->getm_id())==s_marques.end())
                p_queue.push(std::make_pair(i->getm_id(),i->get_distance(id)+poids)); //RAJOUTE A LA PILE PRIORITAIRE

        s_marques.emplace(p_queue.top().first,p_queue.top().second); //MARQUE LE SOMMET DE POIDS PLUS FAIBLE DE LA PILE
    }

    //SOMME LES POIDS DU PARCOURS DE DJIKSTRA
    float somme=0;
    for(const auto &i:s_marques)
        somme+=i.second;

    return somme;
}


std::vector<float> graphe::poidsTotauxDjikstra(const unsigned int &I) const
{
    //INI
    std::vector<float> poidsTotaux;
    float somme_distance=0,somme_cout=0;
    //INI

    //SOMME DES DISTANCES TOTAL
    for(size_t i=0;i<m_sommets.size();i++)
        somme_distance+=Djikstra_sommet((int)i,I);

    //SOMME DES COUTS DES ARETES
    for(const auto &i:m_aretes)
        if(I & (int)pow(2,i.second->getm_id()) )
            for(const auto &j:i.second->getm_poids())
                if(j!=i.second->getm_poids().back())
                    somme_cout+=j;
    //PUSH VECTEUR FLOAT
    poidsTotaux.push_back(somme_cout);
    poidsTotaux.push_back(somme_distance);

    return poidsTotaux;
}

void graphe::afficher_allegro(BITMAP*page, const int &i, const std::vector<float> &mesPoids) const
{
    size_t increment=0;
    int posx = 0;
    std::string msg ;
    const char *msgf;
    msg += "( ";
    for(const auto &p : mesPoids)
    {
        std::cout << p << std::endl;
        msg+=std::to_string(p);
        if(increment !=mesPoids.size()-1)
            msg += " ; ";
        increment++;
    }
    msg += " )";
    if(i==1)
        posx = 400;
    msgf=msg.c_str();
    textprintf_centre_ex(page, font, 200+posx, 20, makecol(255, 255, 255), -1, msgf);
    for(const auto &i:m_sommets)
        circle(page,i.second->getm_x()-50+posx,i.second->getm_y(), 10, makecol(255,0,0));
    for(const auto &j:m_aretes)
    {
        line(page,j.second->getm_extremites()[0]->getm_x()+posx-50,j.second->getm_extremites()[0]->getm_y(),j.second->getm_extremites()[1]->getm_x()+posx-50,j.second->getm_extremites()[1]->getm_y(), makecol(255,30,30));
    }
}
