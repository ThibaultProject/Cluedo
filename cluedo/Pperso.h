#ifndef PPERSO_H_INCLUDED
#define PPERSO_H_INCLUDED

#include "Paquet.h"

class Pperso : public Paquet{
//methodes
public:
    //constructeur et destructeur
    Pperso();
    ~Pperso();

    //methodes
    void init();//cree le paquet de carte
};


#endif // PPERSO_H_INCLUDED
