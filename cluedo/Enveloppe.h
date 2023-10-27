#ifndef ENVELOPPE_H_INCLUDED
#define ENVELOPPE_H_INCLUDED

#include "Paquet.h"
#include "Pperso.h"
#include "Ppiece.h"
#include "Parme.h"
#include "Allegfct.h"

//classe enveloppe
class Enveloppe
{
//attributs
private:
    Allegfct m_alleg;     //les fonctions allegro
    Carte m_arme;         //carte arme
    Carte m_lieux;        //carte lieu
    Carte m_suspect;      //carte suspect
    BITMAP *m_img_env[3]; //les images de l'enveloppe
    int m_state=0;        //etat actuelle de l'enveloppe

//methodes
public:

    //constructeurs et destructeur
    Enveloppe();
    ~Enveloppe();

    //methodes
    void detruire();//detruit les elements
    void init();//charge les images de l'enveloppe
    void creation(Ppiece &pieces, Parme &armes, Pperso &persos);//cree l'enveloppe
    void display(BITMAP *&page, int lumin, int rang, int x, int y);//afficher l'enveloppe
    void save(ofstream &file);//sauvegarde du pion
    void load(ifstream &file, string &receveur);//charge les elements du pion

    //accesseurs
    BITMAP *getImg(int rang);
    Carte getArme() const;
    string getArmeName() const;
    void setArme(Carte val);
    Carte getLieux() const;
    string getLieuxName() const;
    void setLieux(Carte val);
    Carte getSuspect() const;
    string getSuspectName() const;
    void setSuspect(Carte val);
};

#endif // ENVELOPPE_H_INCLUDED
