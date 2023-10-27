#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED

#include "Musiques.h"
#include "Allegfct.h"
#include "Souris.h"
#include "Outils.h"
#include "Compte.h"
#include "Plateau.h"
#include "Feuille_regles.h"
#include "Clavier.h"
#include "Abstract_Joueur.h"

class Hotel{
private:
    //attributs
    Allegfct m_alleg;                   //les fonctions allegro
    Musiques m_music;                   //les musiques
    Souris m_souris;                    //la souris
    Outils m_outils;                    //les fonctions outils
    Plateau m_plat;                     //le plateau de jeu
    Feuille_regles m_regles;            //feuille de regles du jeu
    Clavier m_clavier;                  //clavier
    vector<Abstract_Joueur*> m_joueurs; //les joueurs
    int m_nb_players=0;                 //nombre de joueurs humains
    int m_nb_ordis=0;                   //nombre d'ordinateurs
    bool m_langue=0;                    //langue de l'hotel
    int m_luminosite=0;                 //luminosite de l'hotel
    int m_son=150;                      //le son de l'hotel
    int m_curseur=0;                    //etape actuelle dans l'hotel
    int m_diff=0;                       //difficulte de l'hotel
    BITMAP *m_page;                     //page affiche
    BITMAP *m_fond[5];                  //images de fond
    BITMAP *m_img_param[12];            //images des parametres
public:
    //constructeur et destructeur
    Hotel();
    ~Hotel();

    //methodes
    void detruire();//detruit les elements de l'hotel
    void init_all();//initialise tout
    void init_allegro();//initialise allegro
    void init_sound();//initialise le son
    void init_all_img();//charge toutes les images
    void change_luigi(int i);//modifie la couleur des luigis
    int print_fleches(int myfront, int mygoto[3], int validite, int cdt);//on affiche les deux flèches
    void affichage_fleche(int x);//on affiche une fleche avec son rectangle

    void thegame();//la fonction principale

    void ecran_titre(int page);//ecran titre
    void regles_jeu(int page);//affichage des regles du jeu
    void menu_principal(int page);//menu principal
    void parametres(int page, int page_avant);//parametres
    void collection(int page);//affichage de toutes les cartes
    void saisie_nbjh(int page);//saisie du nombre de joueurs humains
    void saisie_nbordi(int page);//saisie du nombre d'oedinateur
    void print_choix_joueur(int page); //affichage de la selection des joueurs
    void saisir_pseudo(int page);//saisie des pseudos
    void print_choix_pseudo(int page);//affiche le choix des pseudos des joueurs
    void saisir_pion(int page, int tab[6]);//saisie du pion des joueurs
    void print_choix_pion(int page);//affiche le choix des pseudos et pions des joueurs
    void choix_difficulte(int page);//permet le choix du niveau de difficulte
    void creation_env(int page);//permet la creation de l'enveloppe
    void distribution_cartes(int page);//permet la distribution des cartes
    void print_choix_carte(int page);//permet l'affichage des cartes de chaque joueurt
    void time_to_play(int page);//les joueurs jouent
    int restart();//rejoue une partie
    void display_enquete();//affiche la feuille d'enquete d'un joueur
    void menu_pause(int page);//le menu pause

    void refresh_game();//rafraichit l'ecran

    void save_all_statut();//sauvegarde tous les statuts
    void ajout_player(vector<Player> &all_player, ifstream &file, string &receveur);//ajoute un joueur charge
    int verifpseudo(int rang);//verifie si un pseudo n'a pas deja ete saisi
    void load_all_statut(vector<Compte> &tab, bool afficher);//charge tous les statuts
    void demarrage_load_statut();//charge tous les statuts pour le demarrage
    void afficher_statuts(int page, int page_avant);//affiche les statuts de tous les joueurs
    void create_player();//crée un joueur
    void create_ordi();//crée un ordi
    Compte create_personne(ifstream &file, string &receveur);//cree une personne
    Compte create_personne(string _nom, string _statut, int _p_jouees, int _p_gagnees);//cree une personne
    void save_game();//sauvegarde le jeu
    void load_game();//charge le jeu

    // Accesseur
    // Getter
    bool getLangue()const;
    int getLuminosite()const;
    int getSon() const;
    int getCurseur() const;
    int getNbPlayer() const;
    int getNbOrdi() const;
    int getDiff() const;
    Souris getSouris() const;

    // Setter
    void setLangue(bool language);
    void setLuminosite(int lux);
    void setSon(int son);
    void setCurseur(int curseur);
    void setNbPlayer(int nb);
    void setNbOrdi(int nb);
    void setDiff(int diff);
};

#endif // HOTEL_H_INCLUDED
