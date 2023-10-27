#include "PieceCentre.h"

//constructeur et destructeur
//constructeur par defaut
PieceCentre::PieceCentre(){
    m_nom="centre";//ecriture du nom
    for(int i=0; i<4; i++)//ecriture des murs
        m_murs[i].init(false);
}

//destructeur
PieceCentre::~PieceCentre(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int PieceCentre::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    return 2;//se dirige vers la methode pour emettre l'accusation
}
