#include "Abstract_Case.h"

//constructeur et destructeur
//constructeur par defaut
Abstract_Case::Abstract_Case(){m_outils.init();}

//destructeur
Abstract_Case::~Abstract_Case(){}

//methodes
void Abstract_Case::detruire()
{
    m_outils.~Outils();//détruit les sons des outils
}

//initialisation
void Abstract_Case::init(int murs[4])
{
    //initialise les 4 murs de la case
    for(int i=0; i<4; i++)
        m_murs[i].init(murs[i]);
}

//sauvegarde de la case
void Abstract_Case::save(ofstream &file)
{
    //sauegarde des elemnts de la case si case rouge, teleporation ou verte
    if("rouge"==getNom() || "telep"==getNom() || "verte"==getNom())
        file << getNumero() << endl;//ecriture du numero dans le fichier
}

//charge les elemnts de la case
void Abstract_Case::load(ifstream &file, string &receveur, int tab[60], int i)
{
    //Declaration des ressources
    int numero;

    //chargement des elemnts de la case
    file >> receveur;
    numero=stoi(receveur);//converti str en int
    tab[i]=numero;//ecriture de la case
}

//accesseurs
//getter
//getter de mur
bool Abstract_Case::getMur(int rang) const
{
    //Declaration des ressources
    bool value=0;
/*
    if(0<=rang && rang<=3)///le rang est-il dans le domaine [0,3] ?
        value=m_murs[rang].getPresence();
*/

    try{
        if(rang<0 && rang<4)//case hors du tableau ?
            throw string("Case hors du tableau !");
        value=m_murs[rang].getPresence();//retourne la valeur du mur
    }
    catch(string e){
        cerr << e <<endl;//message erreur
        value=0;//on ne retourne rien
    }

    return value;//retourne la valeur
}

//getter de numero
int Abstract_Case::getNumero() const{ return m_numero; }
//etter d'etape
int Abstract_Case::getEtape() const{ return m_etape; }
//getter d'affichage
int Abstract_Case::getAffiche() const{ return m_affiche; }
//getter de nom
string Abstract_Case::getNom() const{ return m_nom; }

//setter
//setter de nom
void Abstract_Case::setNumero(int numero){ m_numero=numero; }
//setter d'etape
void Abstract_Case::setEtape(int etape){ m_etape=etape; }
//stter d'affichage
void Abstract_Case::setAffiche(int affiche){ m_affiche=affiche; }
//setter de roulette
void Abstract_Case::setRoulette(int roulette){ m_roulette=roulette; }
