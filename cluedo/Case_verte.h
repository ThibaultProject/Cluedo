#ifndef CASE_VERTE_H_INCLUDED
#define CASE_VERTE_H_INCLUDED

#include "Abstract_Case.h"

//classe case verte
class Case_verte : public Abstract_Case{
public:
    //constructeur et destructeur
    Case_verte();
    ~Case_verte();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // CASE_VERTE_H_INCLUDED
