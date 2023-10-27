#ifndef PIECECOIN_H_INCLUDED
#define PIECECOIN_H_INCLUDED

#include "Abstract_Case.h"

//classe piece coin
class PieceCoin : public Abstract_Case{
public:
    //constructeur et destructeur
    PieceCoin();
    ~PieceCoin();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // PIECECOIN_H_INCLUDED
