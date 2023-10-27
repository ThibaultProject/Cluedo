#ifndef DE_H_INCLUDED
#define DE_H_INCLUDED

#include "Paquet.h"
#include "Allegfct.h"

//classe du de
class De{
private:
    //attributs
    Allegfct m_alleg;  //les fonctions allegro
    BITMAP *m_img_de;  //l'image du de
    BITMAP *m_img_pt;  //l'image du point d'un de
    int m_value;       //la valeur obtenue apres lancer du de

public:
    //constructeur et destructeur
    De();
    ~De();

    //methodes
    void detruire();//detruit les elements
    void init();//initialise le de
    void lancer(); //permet de lancer le de
    void display(BITMAP *&page, int lumin, int x, int y);//affiche le de et son nombre
    void ecrit_nombre(BITMAP *&page, int lumin, int x, int y);//affiche le nombre du de
    void writeOne(BITMAP *&page, int lumin, int x, int y);//ecrit le nombre 1
    void writeTwo(BITMAP *&page, int lumin, int x, int y);//ecrit le nombre 2
    void writeThree(BITMAP *&page, int lumin, int x, int y);//ecrit le nombre 3
    void writeFour(BITMAP *&page, int lumin, int x, int y);//ecrit le nombre 4
    void writeFive(BITMAP *&page, int lumin, int x, int y);//ecrit le nombre 5
    void writeSix(BITMAP *&page, int lumin, int x, int y);//ecrit le nombre 6

    //accesseurs
    int getValue() const;//getter
    void setValue(int _value);//setter
};

#endif // DE_H_INCLUDED
