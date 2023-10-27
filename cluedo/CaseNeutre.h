#ifndef CASENEUTRE_H_INCLUDED
#define CASENEUTRE_H_INCLUDED

#include "Paquet.h"
#include "Abstract_Case.h"

//classe d'une case neutre
class CaseNeutre : public Abstract_Case{
public:
    //constructeur et destructeur
    CaseNeutre();
    ~CaseNeutre();

    //methodes
   int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // CASENEUTRE_H_INCLUDED
