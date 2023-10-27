#include "Paquet.h"

//constructeur et destructeur
//constructeur par defaut
Paquet::Paquet(){}

//destructeur
Paquet::~Paquet(){
    //détruit toutes les cartes
    while(!m_paquet.empty())
    {
        m_paquet.pop();//depile le paquet
    }
}

//methodes
//melange un paquet
void Paquet::melanger(vector<string> tab, vector<BITMAP *> &tab_img, vector<BITMAP *> &tab2)
{
    //Déclaration des ressources
    vector<Carte> paket;
    unsigned int rang=0;

    //crée les cartes
    for(rang=0; rang<tab.size()-1; rang++)
    {
        creer_carte(tab[rang+1], tab[0], tab_img[rang],tab2[rang], paket);//ajoute une nouvelle carte
    }

    //empile de maniere aleatoire le paquet tant qu'il n'est pas vide
    while(paket.empty()==0)
    {
        //case aleatoire du tableau compris dans l'intervalle souhaité
        rang=rand()%(paket.size());

        //empile le paquet
        m_paquet.push(paket[rang]);

        //enleve la case concernee
        paket.erase(paket.begin()+rang);
    }
}

//piocher une carte et la recevoir dans un tableau
void Paquet::piocher(vector<Carte> &cards)
{
    //Déclaration des ressources : construit une carte par copie
    Carte c(m_paquet.top());

    //depile une carte
    m_paquet.pop();

    //retourne la carte depilee
    cards.push_back(c);
}

//piocher une carte et la recevoir seule
void Paquet::piocher(Carte &card)
{
    //construit une carte par copie
    card=m_paquet.top();

    //depile une carte
    m_paquet.pop();
}

//cree une carte
void Paquet::creer_carte(string a, string b, BITMAP *c, BITMAP *d, vector<Carte> &paket)
{
    //Declaration des ressources
    Carte card(a,b,c,d);

    //ajoute la carte dans le paquet
    paket.push_back(card);
}

//affiche le dos du paquet de carte
void Paquet::display(BITMAP *&page, int lumin, int x, int y)
{
    Allegfct m_alleg;

    /*if(m_paquet.empty() == 0)///paquet non vide ?
    {
        m_paquet.top().affiche_dos(page, lumin, x, y);//affiche le dos de la carte
    }
    else
    {
        m_alleg.myallegro_message("Le paquet est vide !");//message erreur
    }*/

    try{
        if(m_paquet.empty() != 0)//case hors du tableau ?
            throw string("le tableau est vide !");
        m_paquet.top().affiche_dos(page, lumin, x, y);//affiche le dos de la carte
    }
    catch(string e){
        cerr << e <<endl;//message erreur
    }
}
