#include "CaseNeutre.h"

//constructeur et destructeur
//constructeur par defaut
CaseNeutre::CaseNeutre(){
    m_nom="neutre";//ecrit le nom
    for(int i=0; i<4; i++)//ecrit les murs
        m_murs[i].init(false);
}

//destructeur
CaseNeutre::~CaseNeutre(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int CaseNeutre::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    return 1;//rien ne se passe
}

