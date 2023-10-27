#ifndef PAQUET_H_INCLUDED
#define PAQUET_H_INCLUDED

#include <iostream>
#include <time.h>
#include <stack>
#include <vector>
#include <map>
#include <fstream>
#include <allegro.h>

using namespace std;

#include "Carte.h"
#include "Allegfct.h"

class Paquet{
//attributs
protected:
    stack<Carte> m_paquet; //le paquet de cartes (pile de cartes)

//methodes
public:
    //constructeur et destructeur
    Paquet();
    virtual ~Paquet();

    //methodes
    virtual void init()=0;//cree le paquet de carte
    void display(BITMAP *&page, int lumin, int x, int y);//affiche le dos du paquet de carte
    void melanger(vector<string> tab, vector<BITMAP *> &tab_img, vector<BITMAP *> &tab2);//melange un paquet
    void piocher(vector<Carte> &cards);//piocher une carte
    void piocher(Carte &card);//piocher une carte
    void creer_carte(string a, string b, BITMAP *c, BITMAP *d, vector<Carte> &paket);//cree une carte
};

#endif // PAQUET_H_INCLUDED
