#ifndef OUTILS_H_INCLUDED
#define OUTILS_H_INCLUDED

#include "Paquet.h"
#include "Allegfct.h"

class Outils{
private:
    //attributs
    Allegfct m_alleg;       //les fonctions allegro
    SAMPLE *m_sound[2];     //les effets sonores
    int m_old[4]={0,0,0,0}; //ancien rectangle en collision
public:
    //constructeur et destructeur
    Outils();
    ~Outils();

    //methodes
    void detruire();//detruit les elements
    void init();//initialise le son de selection
    int verifclick(int sound, int _front, int ask_front, int x1, int y1, int x2, int y2, int cdt);//permet la condition de click ou de relachement de click sur un rectangle
};

#endif // OUTILS_H_INCLUDED
