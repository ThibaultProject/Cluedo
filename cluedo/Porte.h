#ifndef PORTE_H_INCLUDED
#define PORTE_H_INCLUDED

#include "Abstract_Case.h"

//classe porte
class Porte : public Abstract_Case{
public:
    //constructeur et destructeur
    Porte();
    ~Porte();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // PORTE_H_INCLUDED
