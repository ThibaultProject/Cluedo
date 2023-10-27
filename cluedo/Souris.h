#ifndef SOURIS_H_INCLUDED
#define SOURIS_H_INCLUDED

#include "Paquet.h"

class Souris{
private:
    //attributs
    Allegfct m_alleg;           //les fonctions allegro
    BITMAP *m_img_souris[3][2]; //images de la souris
    int m_place[3][2];          //place de l'affichage de la souris
    int m_type=0;               //choix de l'image de la souris
    int m_front[2];             //front montant ? (passage de non appui gauche à appui gauche)

public:
    //constructeur et destructeur
    Souris();
    ~Souris();

    //methodes
    void detruire();//detruit les elements
    void init_souris();//initialise la souris
    void gere_souris(int type);//gere les appuis boutons de la souris
    void display(BITMAP *&page, int lumin);//affiche la souris
    void save(ofstream &file);//sauvegarde de la souris
    void load(ifstream &file, string &receveur);//charge les elements de la souris

    //accesseurs
    //getter
    int getType() const;
    int getPlace(int x, int y);
    BITMAP *getImgMouse(int x, int y);
    int getFront(int place) const;

    //setter
    void setType(int _type);
};

#endif // SOURIS_H_INCLUDED
