#include "graphe.h"

class prioritize{public: bool operator ()(std::pair<int, float>&p1 ,std::pair<int, float>&p2){return p1.second>p2.second;}};
graphe::~graphe()
{
    //std::cout << "je détruis" << std::endl;
    for(auto &s : m_sommets)
        delete s.second;
    /*std::cout << "je détruis encore" << std::endl;
    for(auto &s : m_aretes)
        delete s.second;*/
    //std::cout << "je détruis toujours" << std::endl;
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
            //std::cout<< "DEBUG CONSTRUCTEUR" <<std::endl;
            m_aretes.insert({g.m_aretes.find(num_arete)->first,
                            new arete{  num_arete,
                                        g.m_aretes.find(num_arete)->second->getm_poids(),
                                        m_sommets.find(g.m_aretes.find(num_arete)->second->getm_extremites()[0]->getm_id())->second,
                                        m_sommets.find(g.m_aretes.find(num_arete)->second->getm_extremites()[1]->getm_id())->second}});

            //Met à jour les aretes des 2 sommets (extremités de l'arete selectionné)
            m_sommets.find(m_aretes.find(num_arete)->second->getm_extremites()[0]->getm_id())->second
            ->ajouterArete(m_aretes.find(num_arete)->second);

             m_sommets.find(m_aretes.find(num_arete)->second->getm_extremites()[1]->getm_id())->second
            ->ajouterArete(m_aretes.find(num_arete)->second);
        }
    }
       // this->afficher();
}

graphe::graphe(std::vector<bool> vect, const graphe &g)
{
    for(const auto & s_o_m : g.m_sommets)
    {
        m_sommets.insert({s_o_m.first,
                         new Sommet {s_o_m.second->getm_id(),
                                    s_o_m.second->getm_x(),
                                    s_o_m.second->getm_y()}});
    }
    int num_arete=0;
    for(const auto &i:vect)
    {
        if(i==true)
        {
            m_aretes.insert({g.m_aretes.find(num_arete)->first,
                            new arete{  num_arete,
                                        g.m_aretes.find(num_arete)->second->getm_poids(),
                                        m_sommets.find(g.m_aretes.find(num_arete)->second->getm_extremites()[0]->getm_id())->second,
                                        m_sommets.find(g.m_aretes.find(num_arete)->second->getm_extremites()[1]->getm_id())->second}});

            //Met à jour les aretes des 2 sommets (extremités de l'arete selectionné)
            m_sommets.find(m_aretes.find(num_arete)->second->getm_extremites()[0]->getm_id())->second
            ->ajouterArete(m_aretes.find(num_arete)->second);

             m_sommets.find(m_aretes.find(num_arete)->second->getm_extremites()[1]->getm_id())->second
            ->ajouterArete(m_aretes.find(num_arete)->second);
        }
        num_arete++;
    }
}


graphe::graphe(std::string nomFichier){
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
         (m_sommets.find(id))->second->ajouterArete(m_aretes.find(id_arete)->second);
         (m_sommets.find(id_voisin))->second->ajouterArete(m_aretes.find(id_arete)->second);

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
            m_aretes.find(i)->second->ajouter_poids(poids);
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

graphe graphe::prim(int poids)
{
    graphe ArbreCouvrant;
    ArbreCouvrant.m_sommets.insert({m_sommets.begin()->first, new Sommet   {m_sommets.begin()->second->getm_id(),
                                                                            m_sommets.begin()->second->getm_x(),
                                                                            m_sommets.begin()->second->getm_y()}});/*
    std::cout << "voila l'arbre couvrant au début..." << std::endl;
    ArbreCouvrant.afficher();
    system("pause");*/
    float tampon, newtampon;
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
                {/*
                    std::cout << "voila une arete interessante" << std::endl << std::endl;
                    a.second->afficher();
                    system("pause");*/
                    /// Si l'arete que j'explore a d'un coté un sommet du nouveau graphe
                    /// et de l'autre un sommet non present dans le nouveau graphe

                    newtampon=a.second->getm_poids()[poids];    // Je stocke dans une valeur tampon le poids de l'arete
                    if(dems==1)
                    {
                        /// Si c'est la première fois que je passe, je stocke dans mon tampon de poids le plus faible
                        /// le poids de l'arete pour avoir un élèment de comparaison à la boucle suivante

                        tampon=newtampon;
                        candidat2=a.second;    // Je stocke le premier candidat au cas où on n'ai qu'une seule arete candidate
                    }/*
                    std::cout << "voila le tampon " << tampon << " et le newtampon " << newtampon << std::endl << std::endl;*/
                    if((newtampon<tampon)&&(dems==0))
                    {
                        /// Si le poids de la nouvelle arete étudiée est moins lourd, je stocke dans mon tampon le nouveau poids
                        tampon=newtampon;
                        candidat2=a.second;    // Et je met à jour le candidat
                    }/*
                    std::cout << "voila le nouveau tampon " << tampon << std::endl << std::endl;
                    system("pause");*/
                    if(prems==1)
                        candidat1=candidat2;
                    dems=0;
                    prems=0;
                }
            }/*
            std::cout << "voila le candidat 1" << std::endl << std::endl;
            candidat1->afficher();
            std::cout << "voila le candidat 2" << std::endl << std::endl;
            candidat2->afficher();*/
            /// Il faut maintenant comparer l'arete 'n-1' candidate précédemment étudiée
            /// voisine de 's-1' avec l'arete qu'on vient d'etudier
            if((candidat1->getm_poids()[poids]>candidat2->getm_poids()[poids])&&(prems==0))
                candidat1=candidat2;    // Et le tour est joué ! :)
            /*
            std::cout << "voila le nouveau candidat 1" << std::endl << std::endl;
            candidat1->afficher();
            system("pause");*/
        }/*
        std::cout << "jai fait toutes les aretes" << std::endl << std::endl;*/
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
        /*
        std::cout << "voila l'arbre couvrant !" << std::endl << std::endl;
        ArbreCouvrant.afficher();*/

    }while(ArbreCouvrant.m_sommets.size()!=m_sommets.size());

    return ArbreCouvrant;
}

std::vector<bool> add(const std::vector<bool>& a, const std::vector<bool>& b)
{
        bool c;
        std::vector<bool> result;
        for(size_t i = 0; i < a.size() ; i++){
                result.push_back(false);
                result[i] = ((a[i] ^ b[i]) ^ c); // c is carry
                c = ((a[i] & b[i]) | (a[i] & c)) | (b[i] & c);
        }
        return result;
}


std::vector<graphe*> retirerCnC(std::vector<graphe*> listeGrapheAChanger)
{
    std::vector<graphe*> listeGrapheARendre;
    for (const auto &g : listeGrapheAChanger)
    {
        //g->afficher();
        if(g->rechercher_CC_graphe()==1)
        {
            listeGrapheARendre.push_back(g);
            g->poidsTotaux();
        }
    }
    return listeGrapheARendre;
}

std::vector <unsigned int> graphe::bruteforce() const
{
    int aaa = 50000;
    int bbb = 200000;
    int mmm = 700000;
    int www = 1200000;
    int lll = 1500000;
    int ooo = 5000000;
    int iii = 10000000;
    int ppp = 15000000;
    int qqq = 16000000;
    int hhh = 16774703;
    std::cout << "je rentre dans bruteforce" << std::endl;
    int taille=m_aretes.size();
    int debut=0, fin=0;
    for (int i=0; i<m_sommets.size()-1; ++i)
    {
        debut+=pow(2,i);
    }
    for (int i=m_aretes.size()-1; i>=m_aretes.size()-m_sommets.size()+1;--i)
    {
        fin+=pow(2,i);
    }
    std::cout << m_sommets.size() << std::endl;
    std::cout<< debut << std::endl;
    //system("pause");
    std::vector <unsigned int> espace_recherche_int;
    std::vector <Sommet*> ptrTest;
    size_t compteur=0;
    int indice =0;
    int a=0;
    graphe *verifConnex;    // Ce graphe servira de graphe temporaire pour vérifier la connexité des combinaisons.

    for(unsigned int i=debut;i<=fin;i++)
    {
        if(i==aaa) std::cout<<"i = "<<i<<std::endl;
        if(i==bbb) std::cout<<"i = "<<i<<std::endl;
        if(i==mmm) std::cout<<"i = "<<i<<std::endl;
        if(i==www) std::cout<<"i = "<<i<<std::endl;
        if(i==lll) std::cout<<"i = "<<i<<std::endl;
        if(i==ooo) std::cout<<"i = "<<i<<std::endl;
        if(i==iii) std::cout<<"i = "<<i<<std::endl;
        if(i==ppp) std::cout<<"i = "<<i<<std::endl;
        if(i==qqq) std::cout<<"i = "<<i<<std::endl;
        if(i==hhh) std::cout<<"i = "<<i<<std::endl;
        /// Première boucle for qui parcours de 0 à 2^n, avec n la taille du graphe,
        /// ce qui correspond à toutes les combinaisons d'aretes possibles.
        for(int comp=0;comp<taille;comp++)
        {
            /// Cette boucle permet de réaliser l'opération logique de base AND
            /// en comparant notre combinaison bit à bit avec les puissances de 2.
            a=pow(2,comp);

            if(i&a)         // Si l'opération logique AND ne renvoie pas 0
               compteur++;  // J'incrémente un compteur qui compte les bit à l'état haut.
        }
        if(compteur==m_sommets.size()-1) //Si autant d'aretes que ordre -1
        {
            //std::cout << "suis la" << std::endl;
            verifConnex=new graphe{i,*this};    // Je créé un graphe temporaire qui permettra de vérifier la connexité
            //verifConnex->afficher();
            //std::cout << "suis la2" << std::endl;
            for(const auto &j:verifConnex->m_sommets)
            {
                /// Cette boucle for permet d'initialiser chacun des sommets à partir des aretes
                /// Afin de pouvoir utiliser le programme de vérification de la connexité correctement.
                /*j.second->afficherData();
                j.second->afficherVoisins();*/
                j.second->connexite();
                /*j.second->afficherData();
                j.second->afficherVoisins();
                //ptrTest.push_back(j.second);*/
            }
            //system("pause");
            if(verifConnex->rechercher_CC_graphe()==1){ // S'il n'y a qu'une seule composante connexe
                espace_recherche_int.push_back(i); // Et j'insère uniquement la combinaison qui a permis d'obtenir ce graphe ainsi que le vecteur de poids
            }
            delete verifConnex;
            //delete verifConnex;    // Enfin, je libère l'espace occupé par l'endroit ou pointait verifConnex.
            //std::cout << ++indice << std::endl;*/
            //espace_recherche.push_back(new graphe{i,*this});
            /*
            for(const auto &ptr : ptrTest)
                ptr->afficherVoisins();
            system("pause");*/
        }
        compteur=0; // Enfin je réinitialise mon compteur à 0
        /*if(espace_recherche_int.size()>0)
            std::cout << sizeof(espace_recherche_int)*espace_recherche_int.size() << " " << espace_recherche_int.size() << std::endl;*/
    }
    //std::cout << "FIN DETECTION" << std::endl;
    /*
    for(auto i:espace_recherche){
        i->afficher();
        system("pause");
    }*/
    //std::cout << "DEBUG3" << std::endl;
    /*
    for(auto i : espace_recherche)
        for(auto j:i->m_sommets)
        {
            j.second->connexite();
        }
    espace_recherche=retirerCnC(espace_recherche);*//*
    for (const auto &it:espace_recherche_int)
        std::cout << it << std::endl;
    system("pause");*/
    std::cout << "jai fini bruteforce" << std::endl;
    std::cout << "taille du graphe " << espace_recherche_int.size() << std::endl;
    //system("pause");
    return espace_recherche_int;    // Pour finir, je retourne l'unordered_map qui contient mes combinaisons et les poids qui leurs sont associées
}

int graphe::rechercher_CC_graphe() const
{
    int i=0;
    /*std::cout<< std::endl<< std::endl << "Composantes connexes :"
    <<std::endl<<std::endl<<std::endl;*/
    std::unordered_set<int> cc;                                 /// id des sommets
    for(const auto &it : m_sommets)                                     /// boucle pour voir les sommets
    {
        if(cc.count(it.second->getm_id())==0)                           /// si le sommet n'est pas dans la liste des sommets découverts
        {
            ++i;                                                        /// j'implémante la variable du nombre de composante connexes
            it.second->rechercherCC(cc);

            /*std::cout <<"Composante connexe n : " << i << std::endl;                          /// et je rentre dans un programme recursif qui rempli le tableau des sommets decouverts
            std::cout << std::endl << std::endl;
            std::cout<<"g fini"<<std::endl;*/
        }
    }

    return i;
}

void graphe::poidsTotaux()
{
    int prems=1;
    //std::cout << "-------DEBUG POIDS INI---------" << std::endl;
    /*
    for(auto i:m_aretes)
    {
        for(size_t j=0; j<i.second->getm_poids().size(); ++j)
           std::cout << " " << i.second->getm_poids()[j] <<std::endl;
    }*/
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

float real_x(float x)
{
    return x*COEFFICIENT+ORX;
}

float real_y(float y)
{
    return ORY-y*COEFFICIENT;
}

void graphe::afficher_frontierePareto(BITMAP*page) const
{
    //TOUT AFFICHER+SURLIGNER FRONTIERE
    std::vector <unsigned int> espace_recherche_int=bruteforce();
    std::vector <unsigned int> frontiere=frontierePareto(espace_recherche_int);
    std::cout<< "jai fini pareto" << std::endl;
    graphe *grapheTemp;
    //std::cout << "ji me tlouve prisontement don affichi frontier" << std::endl;
    for(const auto &i:espace_recherche_int)
    {
        grapheTemp=new graphe{i, *this};
        grapheTemp->poidsTotaux();
        circle(page, real_x(grapheTemp->getm_poids()[0]),real_y(grapheTemp->getm_poids()[1]), 2 , makecol(255,255,255));
        delete(grapheTemp);
    }
    //std::cout << "ji me tlouve prisontement don affichi frontier2" << std::endl;
    for(const auto &i:frontiere) //FRONTIERE
    {
        grapheTemp=new graphe{i, *this};
        grapheTemp->poidsTotaux();
        circlefill(page, real_x(grapheTemp->getm_poids()[0]),real_y(grapheTemp->getm_poids()[1]), 2 , makecol(0,255,0));
        delete(grapheTemp);
    }

    //std::cout << "ji me tlouve prisontement don affichi frontier3" << std::endl;
    line(page, ORX,ORY,ORX,ORY-LONGEURAXE*COEFFICIENT,makecol(255,255,255));
    line(page, ORX,ORY,ORX+LONGEURAXE*COEFFICIENT,ORY,makecol(255,255,255));
    for(int i=0; i<NBGRAD; i+=2)
    {
        if(i%10==0)
        {
            line(page, real_x(i), ORY+LONGUEURGRAD, real_x(i), ORY-LONGUEURGRAD, makecol(200,200,200));
            line(page, ORX-LONGUEURGRAD, real_y(i), ORX+LONGUEURGRAD, real_y(i), makecol(200,200,200));
        }
        line(page, real_x(i), ORY+LONGUEURGRAD2, real_x(i), ORY-LONGUEURGRAD2, makecol(200,200,200));
        line(page, ORX-LONGUEURGRAD2, real_y(i), ORX+LONGUEURGRAD2, real_y(i), makecol(200,200,200));
    }
}

std::vector<unsigned int> graphe::frontierePareto(std::vector<unsigned int> espace_recherche_int) const//RENVOIE LA FRONTIERE
{
    // On aura ici deux unordered_map du même type que notre espace de recherche :
    // - Une stockant tous les sommets qui ne sont pas à la frontière 'NONfrontiere'
    // - Une stockant tous les sommets qui sont à la frontière 'frontiere'
    // L'interet et que je rempli 'frontiere' en mettant tout ce qui n'est pas 'NONfrontiere'
    std::unordered_map <unsigned int, std::vector<float>> NONfrontiere, frontiere;
    int increment=0;
    size_t marqueur1,marqueur2=0, memeadresse=0;
    graphe *comp_1, *comp_2;/*
    for(const auto &a : espace_recherche_int)
        std::cout << a << std::endl;
    system("pause");*/
    //this->afficher();
    //system("pause");
    for(const auto &a:espace_recherche_int)
    {
        /// Cette double boucle for imbriquée me permet de parcourir deux à deux chaque combinaison
        /// et vecteur de poids afin de les comparer et de remplir 'NONfrontiere'
        //std::cout<< "je suis la" << std::endl;
        comp_1=new graphe{a, *this};
        comp_1->poidsTotaux();
        //comp_1->afficher();
        //std::cout << comp_1->getm_poids()[0] << " " << comp_1->getm_poids()[1] << std::endl;
        //system("pause");
        for(const auto &b:espace_recherche_int)
        {/*
            std::cout << std::endl << std::endl << arthur++ << std::endl << std::endl;
            std::cout<< "je suis la avec art" << std::endl;
            std::cout << b << std::endl;*/
            if(b!=a)
            {
                comp_2=new graphe{b,*this};
                comp_2->poidsTotaux();
                //comp_2->afficher();
                //std::cout << comp_2->getm_poids()[0] << " " << comp_2->getm_poids()[1] << std::endl;*/
                //system("pause");
                for(size_t i=0;i<comp_1->getm_poids().size();i++)
                {
                    if(comp_1->getm_poids()[i]<comp_2->getm_poids()[i])
                        marqueur1++;
                    if(comp_1->getm_poids()[i]<=comp_2->getm_poids()[i])
                        marqueur2++;
                }
                if( (marqueur1>1) && (marqueur2 == comp_1->getm_poids().size())) //PROB
                {
                    NONfrontiere.insert({b, comp_2->getm_poids()});
                    espace_recherche_int.erase(espace_recherche_int.begin()+increment);
                    increment--;
                }
                    /*
                for (const auto &a : NONfrontiere)
                {
                    std::cout << "identifiant "<< a.first << std::endl;
                    std::cout << "( " << a.second[0] << " ; " << a.second[1] << " )" << std::endl;
                }*/
                //system("pause");
                marqueur1=0;
                marqueur2=0;
                delete(comp_2);
            }
            increment++;
            //std::cout << "arthur fait caca tous les jours matin et soir" << std::endl;
        }
        increment=0;
        delete(comp_1);
        //std::cout << "papa" << std::endl;
    }/*
    for(const auto &i : espace_recherche_int)
        std::cout << i << std::endl;
    system("pause");*/
    //std::cout << "je fini de trouver nonfrontiere" << std::endl;
    //system("pause");
    /*
    for(const auto &adE_R : espace_recherche_int)
    {
        /// 'NONfrontiere' etant rempli, il s'agit maintenant de parcourir espace_recherche_int
        /// et de comparer chacun de ses elements à 'NONfrontiere'.
        /// Si on ne retrouve pas un élément chez l'autre, c'est qui est à la frontiere !
        for(const auto &adN_F : NONfrontiere)
        {
            if(adE_R==adN_F.first)
            {
                memeadresse++;
            }
        }
        if(memeadresse==0)
        {
            //std::cout << "quelle belle barbe" << std::endl;
            comp_1 = new graphe{adE_R, *this};
            comp_1->poidsTotaux();
            frontiere.insert({adE_R, comp_1->getm_poids()});
            delete(comp_1);
        }
        memeadresse=0;
    }*/
    //std::cout << "je retourne la frontiere" << std::endl;
    //system("pause");
    /*
    for(const auto &it : espace_recherche_int)
    {
        graphe_frontiere.push_back(new{it.first, *this});
    }*/
    return espace_recherche_int;   // Je retourne enfin la frontiere, i.e. toutes les combinaisons dominantes avec leurs poids.
    /// Je retourne maintenant tranquillement dans 'afficher_frontierePareto()'...
}


void graphe::afficher_allegro(BITMAP*page) const
{
    size_t increment=0;
    std::string msg ;
    const char *msgf;
    msg += "( ";
    for(const auto &p : m_poidsTotaux)
    {
        msg+=std::to_string(p);
        if(increment !=m_poidsTotaux.size()-1)
            msg += " ; ";
        increment++;
    }
    msg += " )";

    msgf=msg.c_str();
    textprintf_centre_ex(page, font, 100, 20, makecol(255, 255, 255), -1, msgf);
    for(const auto i:m_sommets)
        circle(page,i.second->getm_x(),i.second->getm_y(), 10, makecol(255,0,0));

    for(const auto j:m_aretes)
    {
        line(page,j.second->getm_extremites()[0]->getm_x(),j.second->getm_extremites()[0]->getm_y(),j.second->getm_extremites()[1]->getm_x(),j.second->getm_extremites()[1]->getm_y(), makecol(255,30,30));
    }
}

/*std::vector <unsigned int> graphe::algoDjikstra(std::vector <unsigned int> espace_recherche) const
{
    graphe *g;
    int taille=m_sommets.size();
    std::vector<int> s_marques;
    float tableau[taille][taille];
    for(const auto &a:espace_recherche) //
    {
        //Djikstra
        g=new graphe{a, *this};
        for(size_t i=0;i<m_sommets.size();i++) //Pour chaque sommet
        {
            tableau[i][(g->m_sommets.find(i)->second)->getm_voisins()->)]
        }
    }
}*/

float** graphe::Djikstra_sommet(int id_debut, const unsigned int &I) const
{
    //INI
    std::cout<< "DEBUG 1" << std::endl;
    float **tab;
    tab=(float**)malloc(sizeof(float*)*m_sommets.size());
    for(size_t i=0;i<m_sommets.size();i++)
        tab[i]=((float*)malloc(sizeof(float)*m_sommets.size()));

    std::priority_queue<std::pair <int,float>,std::vector<std::pair<int,float>>, prioritize> p_queue; //QUEUE PRIORITAIRE, TRI PAR POIDS DECROISSANT, DEF Ligne 3, graphe.Cpp
    std::unordered_map<int,float> s_marques; s_marques.emplace(id_debut,0);
    int id;float poids;
    p_queue.push(std::make_pair(id_debut,0));
    //INI
    while(p_queue.size()!=0) //PARCOURS BFS PILE PRIORITAIRE, TJR EN PREMIER LE SOMMET AVEC PLUS PETIT POIDS
    {
        id=p_queue.top().first; //ENREGISTRE LE PREMIER SOMMET ET SA DISTANCE TOTAL AU SOMMET D'ORIGINE
        poids=p_queue.top().second;
        p_queue.pop(); //EJECTE
        for(const auto i:m_sommets.find(id)->second->getm_voisins()) //Rajoute sommets adjacent non parcourus
         if(I & (int)pow(2,i->id_arete(id)) )//SI l'arrete existe
            if(s_marques.count(i->getm_id())==0) //SI NON PARCOURU
                p_queue.push(std::make_pair(i->getm_id(),i->calcul_distance(id)+poids)); //RAJOUTE A LA PILE PRIORITAIRE

        s_marques.emplace(p_queue.top().first,p_queue.top().second); //MARQUE LE SOMMET DE POIDS PLUS FAIBLE DE LA PILE
        //tab[p_queue.top().first][id_debut]=p_queue.top().second;
        //tab[id_debut][p_queue.top().first]=p_queue.top().second;
    }
    for(const auto i:s_marques) //AFFICHE DJIKSTRA DEPUIS LE SOMMET MIS EN PARAMETRE id_debut
        std::cout<< "id :" << i.first << " Distance :" << i.second << std::endl;

    system("pause");
    return tab;
}

std::vector<float> graphe::poidsTotauxDjikstra(const unsigned int &I)
{
    std::vector<float> poidsTotaux;
    float** tabDjikstra=Djikstra_sommet(0,I);
    //poidsTotaux.push_back()
    return poidsTotaux;
}
