#ifndef ABSTRACT_JOUEUR_H_INCLUDED
#define ABSTRACT_JOUEUR_H_INCLUDED

#include "Paquet.h"
#include "Compte.h"
#include "Enquete.h"
#include "Clavier.h"
#include "Abstract_Case.h"
#include "Allegfct.h"
#include "Outils.h"
#include "Pion.h"
#include "Enveloppe.h"

/// Définition de la classe abstraite "Joueur"
class Abstract_Joueur{
protected :
    /// Attribut
    Allegfct m_alleg;       //les fonctions allegro
    Clavier m_clavier;      //clavier
    Outils m_outils;        //les fonctions outils
    Pion m_pion;            //le pion du joueur
    Compte m_compte;        //le compte du joueur
    Enquete m_enquete;      //la feuille d'enquete
    vector<Carte> m_cartes; //les cartes du joueur
    int m_nb_des=2;         //le nombre de des du joueur
    int m_bonus=0;          //le bonus
    int m_cpt=0;            //compteur du joueur

public :
    /// Constructeur & Destructeur
    Abstract_Joueur();
    virtual ~Abstract_Joueur();

    ///Methodes
    void detruire();//detruit les elements
    void reinit();//reinitialisation d'un joueur
    void save_one_joueur(ofstream &file);//sauve un joueur
    void load_one_joueur(ifstream &file, string &receveur);//charge un joueur
    void create_pion(string _name);//permet de changer le nom et le chargement des images du pion
    void recuperer_carte(vector<Carte> &tab);//permet de recuperer une carte du plateau de jeu
    BITMAP *timer_pion(int speed);//permet de modifier la valeur du timer d'affichage
    BITMAP *timer_logo(int speed);//permet de modifier la valeur du timer d'affichage
    void lire(BITMAP *&page, int lumin, unsigned int rang, int x, int y);//affiche une carte
    void affiche_dos(BITMAP *&page, int lumin, unsigned int rang, int x, int y);//affiche le dos d'une carte
    void display_enq(BITMAP *&page, int langue, int lumin, int state);//affiche la feuille d'enquete
    void affiche_pion(BITMAP *&page, int lumin);//affiche le pion du joueur
    void retour_depart();//retour a la case depart
    void PionEffetSonore();//effet sonore du pion
    void reecrit_statut();//reecrit le statut du joueur
    int increment_cpt();//increment du compteur pour affichage

    /// Méthodes
    virtual void saisir_pseudo(BITMAP *&page, int langue, int lumin, int presence, int rang)=0;//saisie du pseudo
    virtual void saisir_pion(BITMAP *&page, int langue, int lumin, int tab[6], Pion p[6], int rang, int &valid, int frond)=0;//saisie du pion
    virtual void retourner_cartes(BITMAP *&page, int langue, int lumin, bool affiche[6], unsigned int &nbretour, int frond)=0;//retourne les cartes du joueur
    virtual int deplacer(map<int , Abstract_Case*> const&cases, int pionsPl[6][2])=0;
    virtual int accuser(BITMAP *&page, int langue, int lumin, int turn[4], int frond, int valid, char *a, char *b, char *c, Enveloppe env)=0;
    virtual void soupconner(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape)=0;
    virtual void montrer_carte(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape, int turn[4])=0;//le joueur montre une carte a celui qui emet une hypothese

    ///Accesseurs
    //getter
    Pion getPion() const;
    int getPionPoseX() const;
    int getPionPoseY() const;
    Compte getCompte() const;
    char* getNom();
    int getDernier() const;
    string getStatut() const;
    int getPjouees() const;
    int getPgagnees() const;
    unsigned int getNbCards() const;//taille du vecteur de cartes
    int getNbDes() const;
    int getBonus() const;
    bool getTab(int rang1, int rang2);

    // Setter
    void setNom(string _nom);
    void setDernier(int _dernier);
    void setStatut(string _statut);
    void setPjouees(int _p_jouees);
    void setPgagnees(int _p_gagnees);
    void setBonus(int _bonus);
    void setNbDes(int _value);
    void setTab(int rang1, int rang2, bool value);
    void setPionPoseX(int value);
    void setPionPoseY(int value);
};

#endif // ABSTRACT_JOUEUR_H_INCLUDED
