#include "Ppiece.h"

//constructeur et destructeur
//constructeur par defaut
Ppiece::Ppiece(){ init(); }

//destructeur
Ppiece::~Ppiece(){}

//methodes
//cree le paquet de carte
void Ppiece::init()
{
    //Déclaration des ressources
    char chemin[9][50]={"images/cartes/Piece/Cuisine.bmp", "images/cartes/Piece/Hall_d_entree.bmp", "images/cartes/Piece/Balcon.bmp", "images/cartes/Piece/Chambre.bmp", "images/cartes/Piece/Salle_de_billard.bmp", "images/cartes/Piece/Bibliotheque.bmp", "images/cartes/Piece/Salon.bmp", "images/cartes/Piece/Reception.bmp", "images/cartes/Piece/Salle_de_bain.bmp"};
    vector<string> tab = {"Piece", "Cuisine", "Hall_d_entree", "Balcon", "Chambre", "Salle_de_billard", "Bibliotheque", "Salon", "Reception", "Salle_de_bain"};
    vector<BITMAP *> lieux;
    char txt[6][50]={"images/cartes/dos.bmp","","","","",""};
    vector<BITMAP *> dos;

    //chargement des images (taille pixel 177:253)
    for(int i=0; i<9; i++)
    {
        lieux.push_back(m_paquet.top().charge_cartes(chemin[i],160,229, tab[i+1]));//charge l'image de la face de la carte
        dos.push_back(m_paquet.top().charge_cartes(txt[0],160,229, "none"));//charge celle du dos
    }

    //melange et cree le paquet : faire passer en parametre le vector de BITMAP
    melanger(tab, lieux, dos);
}
