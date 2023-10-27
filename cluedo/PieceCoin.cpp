#include "PieceCoin.h"

//constructeur et destructeur
//constructeur par defaut
PieceCoin::PieceCoin(){
    m_nom="coin";//ecriture du nom
    for(int i=0; i<4; i++)//ecriture des murs
        m_murs[i].init(false);
}

//destructeur
PieceCoin::~PieceCoin(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int PieceCoin::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    return 4;//se dirige vers la methode du joueur pour emettre une hypothese
}
