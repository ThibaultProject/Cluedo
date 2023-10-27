#include "PieceAutre.h"

//constructeur et destructeur
//constructeur par defaut
PieceAutre::PieceAutre(){
    m_nom="piece";//ecriture du nom
    for(int i=0; i<4; i++)//ecriture des murs
        m_murs[i].init(false);
}

//destructeur
PieceAutre::~PieceAutre(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int PieceAutre::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    return 4;//on se dirige directement vers la methode permettant au joueur d'emettre une hypothese
}
