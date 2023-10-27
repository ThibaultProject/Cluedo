#include "Parme.h"

//constructeur et destructeur
//constructeur par defaut
Parme::Parme(){ init(); }

//destructeur
Parme::~Parme(){}

//methodes
//cree le paquet de carte
void Parme::init()
{
    //Déclaration des ressources
    char chemin[6][50]={"images/cartes/Arme/Ectoblast.bmp", "images/cartes/Arme/Aspira_coeur.bmp", "images/cartes/Arme/Reveloscope.bmp", "images/cartes/Arme/Ventouse.bmp", "images/cartes/Arme/Lampe_torche.bmp", "images/cartes/Arme/Bombe.bmp"};
    vector<string> tab = {"Arme", "Ectoblast", "Aspira_coeur", "Reveloscope", "Ventouse", "Lampe_torche", "Bombe"};
    vector<BITMAP *> arme;
    char txt[6][50]={"images/cartes/dos.bmp","","","","",""};
    vector<BITMAP *> dos;

    //chargement des images (taille pixel 177:253)
    for(int i=0; i<6; i++)
    {
        arme.push_back(m_paquet.top().charge_cartes(chemin[i],160,229, tab[i+1]));//charge la face de la carte
        dos.push_back(m_paquet.top().charge_cartes(txt[0],160,229, "none"));//charge le dos de la carte
    }

    //melange et cree le paquet
    melanger(tab, arme, dos);
}
