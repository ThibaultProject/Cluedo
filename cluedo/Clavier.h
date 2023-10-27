#ifndef CLAVIER_H_INCLUDED
#define CLAVIER_H_INCLUDED

#include "Allegfct.h"
#include "Pion.h"

class Clavier{
private:
    //attributs
    Allegfct m_alleg; //les fonctions allegro
    SAMPLE *m_sound;  //le son d'une touche du clavier
    int m_frappe=0;   //frappe sur une touche

public:
    //constructeur et destructeur
    Clavier();
    ~Clavier();

    //methodes
    void detruire();//detruit les elements
    void clavier(char pseudo[21], int &dernier);//le joueur saisit son pseudo grâce au clavier
    void ajout_lettre(char pseudo[21], int &dernier, char lettre);//permet d'ajouter une lettre au pseudo
    void supprimer_lettre(char pseudo[21], int &dernier);//permet de supprimer une lettre
    void effet_sonore();//lance l'effet sonore
    void mini_clavier(int &x, int &y);//permet la saisie des deplacements des pions sur le plateau
    void saisie_confirme(int &x, int &y, int newx, int newy);//deplacement autorise

    //accesseurs
    //getter
    int getFrappe() const;
    //setter
    void setFrappe(int _frappe);
};

#endif // CLAVIER_H_INCLUDED
