#include "Pperso.h"

//constructeur et destructeur
//constructeur par defaut
Pperso::Pperso(){ init(); }

//destructeur
Pperso::~Pperso(){}

//methodes
//cree le paquet de carte
void Pperso::init()
{
    //Déclaration des ressources
    char chemin[6][70]={"images/cartes/Personnage/Luigi.bmp", "images/cartes/Personnage/Prof_K_Tastroff.bmp", "images/cartes/Personnage/Ectochien.bmp", "images/cartes/Personnage/Roi_Boo.bmp", "images/cartes/Personnage/Mario.bmp", "images/cartes/Personnage/Gluigi.bmp"};
    vector<string> tab = {"Personnage", "Luigi", "Prof_K_Tastroff", "Ectochien", "Roi_Boo", "Mario", "Gluigi"};
    vector<BITMAP *> pers;
    char txt[6][50]={"images/cartes/dos.bmp","","","","",""};
    vector<BITMAP *> dos;

    //chargement des images (taille pixel 177:253)
    for(int i=0; i<6; i++)
    {
        pers.push_back(m_paquet.top().charge_cartes(chemin[i],160,229, tab[i+1]));//charge l'image de la face de la carte
        dos.push_back(m_paquet.top().charge_cartes(txt[0],160,229, "none"));//charge celle du dos de carte
    }

    //melange et cree le paquet
    melanger(tab, pers, dos);
}
