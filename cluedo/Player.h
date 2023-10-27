#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Paquet.h"
#include "Abstract_Joueur.h"

/// Définition de la classe "Player"
class Player : public Abstract_Joueur
{
public :
    /// Constructeur & Destructeur
    Player();
    ~Player();
    /// Accesseur

    /// Méthodes
    void saisir_pseudo(BITMAP *&page, int langue, int lumin, int presence, int rang);//saisie du pseudo
    void saisir_pion(BITMAP *&page, int langue, int lumin, int tab[6], Pion p[6], int rang, int &valid, int frond);//saisie du pion
    void retourner_cartes(BITMAP *&page, int langue, int lumin, bool affiche[6], unsigned int &nbretour, int frond);//retourne les cartes du joueur
    int deplacer(map<int , Abstract_Case*> const&cases, int pionsPl[6][2]);//deplacer le pion
    int accuser(BITMAP *&page, int langue, int lumin, int turn[4], int frond, int valid, char *a, char *b, char *c, Enveloppe env);//accusation
    void soupconner(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape);//hypothese
    void montrer_carte(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape, int turn[4]);//le joueur montre une carte a celui qui emet une hypothese
};

#endif // PLAYER_H_INCLUDED
