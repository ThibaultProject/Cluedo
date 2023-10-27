#ifndef MUR_H_INCLUDED
#define MUR_H_INCLUDED

#include "Paquet.h"

//classe d'un mur
class Mur{
private:
    //attributs
    bool m_presence;//presence du mur

public:
    //constructeur et destructeur
    Mur();
    ~Mur();

    //initialise le mur
    void init(bool value);

    //Accesseurs
    //getter
    bool getPresence() const;
};

#endif // MUR_H_INCLUDED
