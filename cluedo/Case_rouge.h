#ifndef CASE_ROUGE_H_INCLUDED
#define CASE_ROUGE_H_INCLUDED

#include "Abstract_Case.h"

//classe case verte
class Case_rouge : public Abstract_Case{
public:
    //constructeur et destructeur
    Case_rouge();
    ~Case_rouge();

    //methodes
    int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay);//effet de la case
};

#endif // CASE_ROUGE_H_INCLUDED
