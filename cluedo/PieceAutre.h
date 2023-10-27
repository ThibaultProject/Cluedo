#ifndef PIECEAUTRE_H_INCLUDED
#define PIECEAUTRE_H_INCLUDED

#include "Abstract_Case.h"

//classe piece autre
class PieceAutre : public Abstract_Case{
public:
    //constructeur et destructeur
    PieceAutre();
    ~PieceAutre();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // PIECEAUTRE_H_INCLUDED
