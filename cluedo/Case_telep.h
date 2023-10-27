#ifndef CASE_TELEP_H_INCLUDED
#define CASE_TELEP_H_INCLUDED

#include "Abstract_Case.h"

//classe piece coin
class Case_telep : public Abstract_Case{
public:
    //constructeur et destructeur
    Case_telep();
    ~Case_telep();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // CASE_TELEP_H_INCLUDED
