#ifndef ENQUETE_H_INCLUDED
#define ENQUETE_H_INCLUDED

#include "Allegfct.h"

//classe enquete
class Enquete{
private:
    //attributs
    Allegfct m_alleg;      //les fonctions allegro
    bool m_tab[6][21];     //le tableau d'enquete
    BITMAP *m_img_enq[2];  //image de l'enveloppe de l'enquete

public:
    //constructeur et destructeur
    Enquete();
    ~Enquete();

    //methodes
    void init();//initialise la feuille d'enquete
    void reinit();//reinitialise le tableau
    void display_enq(BITMAP *&page, int langue, int lumin, int state);//affiche la feuille d'enquete
    void save(ofstream &file);//sauvegarde la feille d'enquete
    void load(ifstream &file, string &receveur);//charge la feille d'enquete

    //accesseurs
    //getter
    bool getTab(int rang1, int rang2);
    //setter
    void setTab(int rang1, int rang2, bool value);
    void setOuvert(bool value);
};


#endif // ENQUETE_H_INCLUDED
