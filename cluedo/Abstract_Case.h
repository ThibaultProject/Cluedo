#ifndef ABSTRACT_CASE_H_INCLUDED
#define ABSTRACT_CASE_H_INCLUDED

#include "paquet.h"
#include "Mur.h"
#include "outils.h"

//classe d'une case
class Abstract_Case{
protected:
    //attributs
    Allegfct m_alleg; //les fonctions allegro
    Outils m_outils;  //les fonctions outils
    Mur m_murs[4];    //les 4 murs de la case
    string m_nom;     //le nom de la case
    int m_numero;     //le numero de la case
    int m_etape=0;    //l'etape de la case
    int m_roulette=0; //la roulette
    int m_affiche=0;  //affichage de la case

public:
    //constructeur et destructeur
    Abstract_Case();
    virtual ~Abstract_Case()=0;

    //methodes
    void detruire();//detruit les elements de la classe
    void init(int murs[4]);//initialisation
    virtual int effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)=0;//effet de la case
    void save(ofstream &file);//sauvegarde de la case
    void load(ifstream &file, string &receveur, int tab[60], int i);//charge les elements de la case

    //accesseurs
    //getter
    bool getMur(int rang) const;
    int getNumero() const;
    int getEtape() const;
    int getAffiche() const;
    string getNom() const;
    //setter
    void setNumero(int numero);
    void setEtape(int etape);
    void setAffiche(int affiche);
    void setRoulette(int roulette);
};

#endif // ABSTRACT_CASE_H_INCLUDED
