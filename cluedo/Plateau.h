#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "Paquet.h"
#include "Enveloppe.h"
#include "Player.h"
#include "Ordi.h"
#include "Chrono.h"
#include "Allegfct.h"
#include "De.h"
#include "Abstract_Case.h"
#include "CaseNeutre.h"
#include "PieceAutre.h"
#include "PieceCoin.h"
#include "PieceCentre.h"
#include "Porte.h"
#include "Case_telep.h"
#include "Case_verte.h"
#include "Case_rouge.h"

//classe du plateau du jeu
class Plateau{
private:
    //attributs
    Allegfct m_alleg;                   //les fonctions allegro
    Outils m_outils;                    //les fonctions outils
    vector<Carte> m_cartes;             //les cartes defaussees
    Carte m_small_c;                    //leur petit dos de carte
    Enveloppe m_env;                    //l'enveloppe
    Chrono m_chrono;                    //le chrono
    De m_des[3];                        //les des
    map<int , Abstract_Case*> m_cases;  //les cases du plateau
    int m_tour=0;                       //a qui le tour de jouer ?
    int m_etape=0;                      //etape de jeu pour le joueur concerne
    int m_state=0;                      //state
    BITMAP *m_img_plat;                 //image du plateau
    BITMAP *m_img_pause;                //image pour acceder au menu pause

public:
    //constructeur et destructeur
    Plateau();
    ~Plateau();

    //methodes
    void detruire();//detruit les elements
    void init();//charge les images de l'enveloppe et du plateau
    void init_cards(Ppiece &pieces, Pperso &persos, Parme &armes);//permet de creer l'enveloppe et de tout melanger
    void init_cases(int diff, bool load_create, int tab[60]);//cree toutes les cases
    void create_cases(int diff, bool load_create, int tab[60]);//cree les cases evenements
    void cases_coin();//cree toutes les cases pieces coin
    void pieces_autre();//cree toutes les cases pieces autre
    void pieceCentre();//cree la case piece centre
    Abstract_Case* creer_case_porte();//cree une case porte
    Abstract_Case* creer_case_neutre();//cree une case neutre
    Abstract_Case* creer_piece_coin();//cree une case piece coin
    Abstract_Case* creer_piece_autre();//cree une case autre
    Abstract_Case* creer_piece_centre();//cree une case centre
    Abstract_Case* creer_case_telep();//cree une case teleportation
    Abstract_Case* creer_case_verte();//cree une case verte
    Abstract_Case* creer_case_rouge();//cree une case verte
    void init_murs();//initialise les murs
    void remplir_cases(int cases[16][4], int *tab, int place, int rang);//remplit les murs des cases
    void distribution_cards(vector<Abstract_Joueur*> &joueurs, int lenP, int lenO, int &posee);//permet de recuperer une carte du paquet
    void display_env(BITMAP *&page, int lumin, int rang, int x, int y);//affiche l'enveloppe
    void display_dos_carte(BITMAP *&page, int lumin, int x, int y);//affiche le dos d'une carte
    void display_petit_dos(BITMAP *&page, int lumin);//affiche le dos d'une petite carte
    void display_img_carte(BITMAP *&page, int lumin, unsigned int rang, int x, int y);//affiche l'image d'une carte
    void print_chrono(BITMAP *&page, int lumin);//affiche le chrono
    void time_to_play(BITMAP *&page, int langue, int lumin, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd, int frond, int hyp[3], int turn[4]);//le coeur du jeu
    void print_all(BITMAP *&page, int langue, int lumin, int taille, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd, int frond);//affiche tous les elements du plateau
    void print_cases(BITMAP *&page, int lumin);//affiche les cases du plateau
    void initChrono();//reinitialise le chrono
    void lancer_de(int nbdes);//lance un certain nombre de des
    void print_des(BITMAP *&page, int lumin, int taille); //affiche les des
    void reinit();//reinitialise le plateau
    void print_img_pause(BITMAP *&page, int lumin);//affiche le bloc menu pause
    void lancer_all_dice(BITMAP *&page, int langue, int lumin, int nbdes, int frond, int nbplayer, int bonus);//lancer tous les des
    void display_joueurs(BITMAP *&page, int langue, int lumin, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd, int frond);//affiche les caracteristiques de tous les joueurs
    void display_joueur(BITMAP *&page, int langue, int lumin, int rang, int x, int y, vector<Abstract_Joueur*> &joueurs, int frond);//affiche les caracteristiques d'un joueur
    void display_etape(BITMAP *&page, int langue, int lumin);//affiche l'etape actuelle
    void affiche_cartes_j(BITMAP *&page, int lumin, vector<Abstract_Joueur*> &joueurs);//affiche les cartes du joueur et celles defaussees
    int telep(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int lenPl);//teleportation
    void echange_place(BITMAP *&page, int langue, int lumin, int frond, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd);//echange la place de 2 joueurs
    void save(ofstream &file);//sauvegarde du plateau
    void load(ifstream &file, string &receveur, int diff);//charge les elements du plateau

    //accesseurs
    //getter
    Enveloppe getEnv() const;//retourne l'Enveloppe
    BITMAP * getImgPlat() const;//retourne l'image du plateau
    unsigned int getNbCards() const;//taille du vecteur de cartes
    unsigned int getNbDes() const;//taille du vecteur de des
    int getTour() const;
    int getEtape() const;
    int getState() const;

    //setter
    void setTour(int _tour);
    void setEtape(int _etape);
    void setState(int _state);
};

#endif // PLATEAU_H_INCLUDED
