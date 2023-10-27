#include "Abstract_Joueur.h"

/// Constructeur par defaut
Abstract_Joueur :: Abstract_Joueur() {}

Abstract_Joueur :: ~Abstract_Joueur() {}

/// Methodes
void Abstract_Joueur::detruire()//detruit les elements
{
    for(unsigned int i=0; i<m_cartes.size(); i++)
    {
        m_cartes[i].detruire();
    }

    m_clavier.detruire();
}

//reinitialisation d'un joueur
void Abstract_Joueur :: reinit()
{
    retour_depart();//retour a la case depart
    setBonus(0);//aucun bonus
    setNbDes(2);//2 des à disposition
    m_enquete.reinit();//reinitialise la feuille d'enquete

    while(!m_cartes.empty())//tant que le paquet n'est pas vide
    {
        m_cartes.pop_back();//on retire une carte en plus
    }
}

//sauvegarde les caracteristiques d'un joueur
void Abstract_Joueur :: save_one_joueur(ofstream &file)
{
    //Declaration des ressources
    int nbcartes=getNbCards();

    //sauvegarde des caracteristiques du joueur
    m_compte.save_one_statut(file);                  //sauvegarde le compte
    m_pion.save(file);                               //sauvegarde le pion
    m_enquete.save(file);                            //sauvegarde la feuille d'enquete
    file << getNbDes() << endl << getBonus() << endl;//sauvegarde le nombre de des et le bonus

    //sauvegarde des cartes
    file << nbcartes << endl;//ecrit le nombre de cartes
    for(int i=0; i<nbcartes; i++)//sauvegarde de toutes les cartes
        m_cartes[i].save(file);

}

//charge les caracteristiques d'un joueur
void Abstract_Joueur :: load_one_joueur(ifstream &file, string &receveur)
{
    //Déclaration des ressource
    int numero, nbcartes;
    Carte c;

    //ecriture des caracteristiques du joueur
    m_compte.load_one_statut(file, receveur);//charge le compte du joueur
    m_pion.load(file, receveur);//charge le pion du joueur
    m_enquete.load(file, receveur);//charge la feuille d'enquete du joueur

    file >> receveur;//recoit le nombre de des
    numero=stoi(receveur);//converti str en int
    setNbDes(numero);//nombre de des

    file >> receveur;//recoit le bonus du joueur
    numero=stoi(receveur);//converti str en int
    setBonus(numero);//bonus

    file >> receveur;//recoit le nombre de cartes du  joueur
    nbcartes=stoi(receveur);//converti str en int pour le nomre de cartes

    //chargement des cartes
    for(int i=0; i<nbcartes; i++)
        m_cartes.push_back(c.load(file, receveur));

    //initialise le pion
    m_pion.load_img_pion(); //chargement des ressources necessaires
    m_pion.load_sound_pion(); //chargement du son
}

//permet de recuperer une carte du plateau de jeu
void Abstract_Joueur :: recuperer_carte(vector<Carte> &tab)
{
    //Declaration des ressources
    int rang=tab.size()-1;//rang de la carte a prendre

    //le joueur recupere la derniere carte
    m_cartes.push_back(tab[rang]);

    //detruit la carte prise
    tab.pop_back();
}

//permet de changer le nom et le chargement des images du pion
void Abstract_Joueur :: create_pion(string _name)
{
    m_pion.setName(_name); //ecriture du nom
    m_pion.load_img_pion(); //chargement des ressources necessaires
    m_pion.load_sound_pion(); //chargement du son
    m_pion.init_depart(); //initialise le depart du pion
}

//permet de modifier la valeur du timer d'affichage et de retourner le pion
BITMAP *Abstract_Joueur :: timer_pion(int speed)
{
    return m_pion.getImgPion(speed);//reactualise le timer et retourne l'image
}

//permet de modifier la valeur du timer d'affichage et de retourner le logo
BITMAP *Abstract_Joueur :: timer_logo(int speed)
{
    return m_pion.getImgLogo(speed);//reactualise le timer et retourne l'image
}
//lire une carte
void Abstract_Joueur::lire(BITMAP *&page, int lumin, unsigned int rang, int x, int y)
{/*
    if(0 <= rang && rang < m_cartes.size())///pas de depassement du tableau ?
        m_cartes[rang].lire(page, lumin, x ,y);//affiche la carte
*/
    try{
        if(rang<0 && rang<m_cartes.size()+1)//case hors du tableau ?
            throw string("Case hors du tableau !");
        m_cartes[rang].lire(page, lumin, x ,y);//affiche la carte
    }
    catch(string e){
        cerr << e <<endl;//message erreur
    }

}

//affiche le dos d'une carte
void Abstract_Joueur::affiche_dos(BITMAP *&page, int lumin, unsigned int rang, int x, int y)
{/*
    if(0 <= rang && rang < m_cartes.size())///pas de depassement du tableau ?
        m_cartes[rang].affiche_dos(page, lumin, x ,y);//affiche le dos de la carte
*/
    try{
        if(rang<0 && rang<m_cartes.size()+1)//case hors du tableau ?
            throw string("Case hors du tableau !");
        m_cartes[rang].affiche_dos(page, lumin, x ,y);//affiche le dos de la carte
    }
    catch(string e){
        cerr << e <<endl;//message erreur
    }
}

//affiche la feuille d'enquete
void Abstract_Joueur::display_enq(BITMAP *&page, int langue, int lumin, int state)
{
    //affiche l'enveloppe de feuille d'enquete
    m_enquete.display_enq(page, langue, lumin, state);
}

//affiche le pino du joueur
void Abstract_Joueur::affiche_pion(BITMAP *&page, int lumin)
{
    m_pion.affiche_pion(page, lumin);//affichage du pion
}

//retour a la case depart
void Abstract_Joueur::retour_depart()
{
    m_pion.setPoseX(m_pion.getDepartX());//retour a la case depart position en abcsisse x
    m_pion.setPoseY(m_pion.getDepartY());//retour a la case depart position en ordonnee y
}

//effet sonore du pion
void Abstract_Joueur::PionEffetSonore()
{
    m_pion.effet_sonore();//joue l'effet sonore du pion
}

//reecrit le statut du joueur
void Abstract_Joueur::reecrit_statut()
{
    m_compte.reecrit_statut();
}

//increment du compteur pour affichage
int Abstract_Joueur::increment_cpt()
{
    //Declaration des ressources
    int valid=0;

    m_cpt++;//increment du compteur
    if(m_cpt==40)//max atteint ?
    {
        m_cpt=0;//reinitialisation
        valid=1;//on peut passer z lz suite
    }

    //on retourne le résultat
    return valid;
}

/// Accesseurs
//getter
Pion Abstract_Joueur :: getPion() const{ return m_pion; }
int Abstract_Joueur :: getPionPoseX() const{ return m_pion.getPoseX(); }
int Abstract_Joueur :: getPionPoseY() const{ return m_pion.getPoseY(); }
Compte Abstract_Joueur :: getCompte() const{ return m_compte; }
// Getter
char* Abstract_Joueur :: getNom(){ return m_compte.getNom();}
int Abstract_Joueur :: getDernier() const{ return m_compte.getDernier(); }
string Abstract_Joueur :: getStatut() const{ return m_compte.getStatut(); }
int Abstract_Joueur :: getPjouees() const{ return m_compte.getPjouees(); }
int Abstract_Joueur :: getPgagnees() const{ return m_compte.getPgagnees(); }
//taille du vecteur de cartes
unsigned int Abstract_Joueur::getNbCards() const{ return m_cartes.size(); }
int Abstract_Joueur::getNbDes() const{ return m_nb_des; }
int Abstract_Joueur::getBonus() const{ return m_bonus; }
bool Abstract_Joueur::getTab(int rang1, int rang2){ return m_enquete.getTab(rang1, rang2); }

// Setter
void Abstract_Joueur :: setNom(string _nom){ m_compte.setNom(_nom); }
void Abstract_Joueur :: setDernier(int _dernier){ m_compte.setDernier(_dernier);}
void Abstract_Joueur :: setStatut(string _statut){ m_compte.setStatut(_statut); }
void Abstract_Joueur :: setPjouees(int _p_jouees){ m_compte.setPjouees(_p_jouees); }
void Abstract_Joueur :: setPgagnees(int _p_gagnees){ m_compte.setPgagnees(_p_gagnees); }
void Abstract_Joueur :: setBonus(int _bonus){ m_bonus = _bonus; }
void Abstract_Joueur :: setNbDes(int _value){ m_nb_des = _value; }
void Abstract_Joueur :: setTab(int rang1, int rang2, bool value){ m_enquete.setTab(rang1, rang2, value); }
void Abstract_Joueur :: setPionPoseX(int value){ m_pion.setPoseX(value); }
void Abstract_Joueur :: setPionPoseY(int value){ m_pion.setPoseY(value); }
