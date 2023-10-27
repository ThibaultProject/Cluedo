#ifndef CHRONO_H_INCLUDED
#define CHRONO_H_INCLUDED

#include "Allegfct.h"
#include "Outils.h"

//classe du chrono
class Chrono{
private:
    //attributs
    Allegfct m_alleg; //les fonctions allegro
    int m_FPS=17;     //nombre d'images par seconde
    int m_cpt=0;      //le compteur du chrono

public:
    //constructeurs et destructeur
    Chrono();
    ~Chrono();

    //methodes
    void initChrono();//reinitialise le chrono
    void increment(int &minutes, int &sec);//incremente le chrono : calcul minutes et secondes
    void print_chrono(BITMAP *&page, int lumin);//affiche le chrono
    void convert(char txt[8], int rang, int &timer);//permet de convertir un nombre en char
    void save(ofstream &file);//sauvegarde du pion
    void load(ifstream &file, string &receveur);//charge les elements du pion
};

#endif // CHRONO_H_INCLUDED
