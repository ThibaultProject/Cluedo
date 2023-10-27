#ifndef PARME_H_INCLUDED
#define PARME_H_INCLUDED

#include "Paquet.h"

class Parme : public Paquet{
//methodes
public:
    //constructeur et destructeur
    Parme();
    ~Parme();

    //methodes
    void init();//cree le paquet de carte
};

#endif // PARME_H_INCLUDED
