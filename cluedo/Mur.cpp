#include "Mur.h"

//constructeur et destructeur
//constructeur par defaut
Mur::Mur(){}

//destructeur
Mur::~Mur(){}

//initialise le mur
void Mur::init(bool value)
{
    m_presence=value;//initialise la presence du mur
}

//Accesseurs
//getter
bool Mur::getPresence() const{ return m_presence; }
