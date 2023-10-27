#include "Compte.h"

/// Constructeur
//par defaut
Compte :: Compte() {}
//surcharge
Compte :: Compte(string _nom, string _statut, int _p_jouees, int _p_gagnees):m_statut(_statut), m_p_jouees(_p_jouees), m_p_gagnees(_p_gagnees)
{
    setNom(_nom);
}

/// Destructeur
Compte :: ~Compte() {}

//sauvegarde les caracteristiques d'une Compte
void Compte :: save_one_statut(ofstream &file)
{
    //ecriture des caracteristiques du joueur
    file << getNom();                // ecrit le nom
    file << endl;                    // retour a la ligne
    file << getDernier();            // ecrit la taille du nom
    file << endl;                    // retour a la ligne
    file << getStatut();             // ecrit le statut
    file << endl;                    // retour a la ligne
    file << getPjouees();            // ecrit le nombre de parties jouees
    file << endl;                    // retour a la ligne
    file << getPgagnees();           // ecrit le nombre de parties gagnees
    file << endl;                    // retour a la ligne
}

//charge une Compte
void Compte::load_one_statut(ifstream &file, string &receveur)
{
    //Déclaration des ressources
    int numero;

    // ecrit le nom
    file >> receveur;
    setNom(receveur);

    //ecrit la taille du nom
    file >> receveur;
    numero=stoi(receveur); //convertion str en int
    setDernier(numero);

    // ecrit le statut
    file >> receveur;
    setStatut(receveur);

    // ecrit le nombre de parties jouées
    file >> receveur;
    numero=stoi(receveur); //convertion str en int
    setPjouees(numero);

    // ecrit le nombre de parties gagnées
    file >> receveur;
    numero=stoi(receveur); //convertion str en int
    setPgagnees(numero);

}

//reecrit le statut d'un joueur
void Compte::reecrit_statut()
{
    //Déclaration des resources
    float pourcent = float(getPgagnees())/float(getPjouees());
    string stat="";

    //reecrit le statut en fonction du pourcentage de reussite
    if(0<=pourcent && pourcent<0.20)//inferieur a 20%
        stat="debutant";
    else if(0.20<=pourcent && pourcent<0.40)//compris entre 20 et 40 %
        stat="amateur";
    else if(0.40<=pourcent && pourcent<0.60)//compris entre 40 et 60 %
        stat="intermediaire";
    else//superieur a 60 %
        stat="expert";

    //reactualisation du statut
    setStatut(stat);
}

/// Accesseurs
// Getter
char* Compte :: getNom(){ return m_nom;}
int Compte :: getDernier() const{ return m_dernier; }
string Compte :: getStatut() const{ return m_statut; }
int Compte :: getPjouees() const{ return m_p_jouees; }
int Compte :: getPgagnees() const{ return m_p_gagnees; }

// Setter
void Compte :: setNom(string _nom)
{
    //copie du nom
    for(int i=0; i<21; i++)
        m_nom[i]=_nom[i];
}
void Compte :: setDernier(int _dernier){ m_dernier = _dernier;}
void Compte :: setStatut(string _statut){ m_statut = _statut; }
void Compte :: setPjouees(int _p_jouees){ m_p_jouees = _p_jouees; }
void Compte :: setPgagnees(int _p_gagnees){ m_p_gagnees = _p_gagnees; }
