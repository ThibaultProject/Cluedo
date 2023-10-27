#ifndef FEUILLE_REGLES_H_INCLUDED
#define FEUILLE_REGLES_H_INCLUDED

#include "Paquet.h"

//classe de feuille des regles du jeu
class Feuille_regles{
private:
    //attributs
    Allegfct m_alleg;        //les fonctions allegro
    char m_txt[34][2][100];  //texte des regles du jeu

public:
    //constructeur et destructeur
    Feuille_regles();
    ~Feuille_regles();

    //methodes
    void display(BITMAP *&page, int langue, int lumin);//affichage des regles du jeu
};

#endif // FEUILLE_REGLES_H_INCLUDED
