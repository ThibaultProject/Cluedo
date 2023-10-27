#ifndef PIECECENTRE_H_INCLUDED
#define PIECECENTRE_H_INCLUDED

#include "Abstract_Case.h"

//classe piece centre
class PieceCentre : public Abstract_Case{
public:
    //constructeur et destructeur
    PieceCentre();
    ~PieceCentre();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // PIECECENTRE_H_INCLUDED
