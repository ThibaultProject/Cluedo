#include "Enveloppe.h"

//constructeurs et destructeurs
//constructeur par defaut
Enveloppe::Enveloppe(){}

//destructeur
Enveloppe::~Enveloppe(){

}

//methodes
//detruit les elements
void Enveloppe::detruire()
{
    //detruit les iamges
    for(int i=0; i<3; i++)
        m_alleg.mydestroy_bitmap(m_img_env[i]);
}

//charge les images de l'enveloppe
void Enveloppe::init()
{
    //Déclaration des resources
    char chemin[30]="images/enveloppe/_.bmp";

    //charge les trois images
    for(int i=0; i<3; i++)
    {
        chemin[17]=49+i;//ecrit le rang du chemin
        m_img_env[i]=m_alleg.load_img(chemin);//charge l'image
    }
}

//cree l'enveloppe
void Enveloppe::creation(Ppiece &pieces, Parme &armes, Pperso &persos)
{
    //on tire une carte de chaque paquet pour creer l'enveloppe
    armes.piocher(m_arme);//on pioche une carte du paquet des armes
    pieces.piocher(m_lieux);//on pioche une carte du paquet des pieces
    persos.piocher(m_suspect);//on pioche une carte du paquet des personnages
}

void Enveloppe::display(BITMAP *&page, int lumin, int rang, int x, int y)
{
    //affiche la carte
    m_alleg.luminosite(page, getImg(rang), lumin, x ,y);
}

//sauvegarde de l'enveloppe
void Enveloppe::save(ofstream &file)
{
    //sauvegarde des cartes
    m_lieux.save(file);//sauvegarde de la carte lieu
    m_suspect.save(file);//sauvegarde de la carte personnage
    m_arme.save(file);//sauvegarde de la carte arme
}

//charge l'enveloppe
void Enveloppe::load(ifstream &file, string &receveur)
{
    //chargement des cartes
    m_lieux=m_lieux.load(file, receveur);//chargement de la carte lieu
    m_suspect=m_suspect.load(file, receveur);//chargement de la carte personnage
    m_arme=m_arme.load(file, receveur);//chargement de la carte arme
}

//Accesseurs
BITMAP *Enveloppe::getImg(int rang)
{
    /*if(rang<0 || rang>3)///dans l'intervalle ?
    {
        m_alleg.myallegro_message("Le rang est en dehors du tableau d'images de l'enveloppe !");
        return m_img_env[0];
    }
    else//c'est bon
        return m_img_env[rang];*/

    try{
        if(rang<0 || rang>3)//case hors du tableau ?
            throw string("Case hors du tableau !");
        return m_img_env[rang];
    }
    catch(string e){
        cerr << e <<endl;//message erreur
        return m_img_env[0];
    }
}

//getter et setter
Carte Enveloppe::getArme() const{ return m_arme; }
string Enveloppe::getArmeName() const{ return m_arme.getNom(); }
void Enveloppe::setArme(Carte val){ m_arme=val; }

Carte Enveloppe::getLieux() const{ return m_lieux; }
string Enveloppe::getLieuxName() const{ return m_lieux.getNom(); }
void Enveloppe::setLieux(Carte val){ m_lieux=val; }

Carte Enveloppe::getSuspect() const{ return m_suspect; }
string Enveloppe::getSuspectName() const{ return m_suspect.getNom(); }
void Enveloppe::setSuspect(Carte val){ m_suspect=val; }
