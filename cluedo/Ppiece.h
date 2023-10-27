#ifndef PPIECE_H_INCLUDED
#define PPIECE_H_INCLUDED

#include "Paquet.h"

class Ppiece : public Paquet{
//methodes
public:
    //constructeur et destructeur
    Ppiece();
    ~Ppiece();

    //methodes
    void init();//cree le paquet de carte
};

#endif // PPIECE_H_INCLUDED
