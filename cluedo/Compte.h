#ifndef COMPTE_H_INCLUDED
#define COMPTE_H_INCLUDED

#include "Paquet.h"

// Définition de la classe Compte
class Compte{
protected :
    // Attribut
    char m_nom[21];              //nom
    int m_dernier=0;             //le rang du dernier caractere du nom
    string m_statut="debutant";  //le statut
    int m_p_jouees=0;            //nombre de parties jouees
    int m_p_gagnees=0;           //nombre de parties gagnees

public :
    /// Constructeur & Destructeur
    Compte();
    Compte(string _nom, string _statut, int _p_jouees, int _p_gagnees);
    ~Compte();

    ///Methodes
    void save_one_statut(ofstream &file);//sauvegarde les caracteristiques d'une personne
    void load_one_statut(ifstream &file, string &receveur);//charge le statut d'un joueur
    void reecrit_statut();//reecrit le statut d'un joueur

    /// Accesseur
    // Getter
    char* getNom();
    int getDernier() const;
    string getStatut() const;
    int getPjouees() const;
    int getPgagnees() const;

    // Setter
    void setNom(string _nom);
    void setDernier(int _dernier);
    void setStatut(string _statut);
    void setPjouees(int _p_jouees);
    void setPgagnees(int _p_gagnees);
};

#endif // COMPTE_H_INCLUDED
