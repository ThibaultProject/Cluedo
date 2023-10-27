#include "Paquet.h"
#include "Carte.h"
#include "Parme.h"
#include "Pperso.h"
#include "Ppiece.h"

//constructeurs et destructeur
//constructeur par defaut
Carte::Carte(){}

//constructeur surcharge 1
Carte::Carte(string _nom, string _type, BITMAP *card, BITMAP *dos):m_nom(_nom), m_type(_type), m_img_carte(card), m_img_dos(dos){}

//constructeur surcharge 2
Carte::Carte(string _nom, string _type, BITMAP *card):m_nom(_nom), m_type(_type), m_img_carte(card){}

//constructeur par copie
Carte::Carte(Carte const& c)
{
    m_nom=c.getNom();
    m_type=c.getType();
    m_img_carte=c.getImg();
    m_img_dos=c.getDos();
}

//destructeur
Carte::~Carte(){
}

//methodes

//detruit les images d'une carte
void Carte::detruire()
{
    Allegfct m_alleg;
    //detruit les 2 images
    m_alleg.mydestroy_bitmap(m_img_carte);
    m_alleg.mydestroy_bitmap(m_img_dos);
}

//charge les images d'une carte
BITMAP* Carte::charge_cartes(char *chemin, int tx, int ty, string name)
{
    //Déclaration des ressources
    char chemin2[50]="images/cartes/contour.bmp";
    BITMAP *image, *img_petit, *img_contour;
    char nom[20];
    int taille=name.size();
    Allegfct m_alleg;

    //transforme string en char*
    for(int i=0; i<taille+1; i++)
        nom[i]=name[i];

    image=m_alleg.load_img(chemin);//chargement de l'image de la carte
    img_contour=m_alleg.load_img(chemin2);//chargement de l'image du contour de la carte
    m_alleg.luminosite(image, img_contour, 0, 0, 0);//pose le contour sur la carte

    m_alleg.create_page(img_petit, tx, ty, makecol(255,0,255));//cree le double buffer
    m_alleg.mystretch_sprite(img_petit, image, 0, 0, tx, ty);//rapetit la carte !

    if(name!="none")//si ce n'est pas un dos de carte
    {
        m_alleg.drawrect(img_petit, 0, 0, 0, 80-5-taille*4, 190, 80+5+taille*4, 205);//rectangle de fond de texte
        m_alleg.mytextout_ex(img_petit, font, nom, 80-taille*4, 195, makecol(150,150,150));//texte
    }

    //retourne l'image petite
    return img_petit;
}

//permet de rassembler toutes les cartes pour la collection
void Carte::rassembler_cartes(vector< vector <Carte>> &cards)
{
    //Declaration des ressources
    vector<Carte> c1, c2, c3;
    Ppiece pieces;
    Parme armes;
    Pperso persos;

    //on pioche toutes les cartes de tous les paquets
    for(unsigned int i=0; i<9; i++)
        pieces.piocher(c1);//pioche des cartes du paquet des pieces
    for(unsigned int i=0; i<6; i++)
        persos.piocher(c2);//pioche des cartes du paquet des personnages
    for(unsigned int i=0; i<6; i++)
        armes.piocher(c3);//pioche des cartes du paquet des armes

    cards.push_back(c1);//on rassembles toutes les cartes du paquet des pieces
    cards.push_back(c2);//on rassembles toutes les cartes du paquet des personnages
    cards.push_back(c3);//on rassembles toutes les cartes du paquet des armes
}

//lire une carte
void Carte::lire(BITMAP *&page, int lumin, int x, int y)
{
    Allegfct m_alleg;
    //affiche la carte
    m_alleg.luminosite(page, getImg(), lumin, x ,y);
}

//affiche le dos d'une carte
void Carte::affiche_dos(BITMAP *&page, int lumin, int x, int y)
{
    Allegfct m_alleg;
    //affiche la carte
    m_alleg.luminosite(page, getDos(), lumin, x ,y);
}

//sauvegarde une carte
void Carte::save(ofstream &file)
{
    //sauegarde des elemnts du pion
    file << getNom() << endl << getType() << endl;//sauvegarde du nom et du type de la carte
}

//charge les elemnts de la carte
Carte Carte::load(ifstream &file, string &receveur)
{
    //Declaration des ressources
    Carte newcarte;
    Allegfct m_alleg;
    char txt[50]="images/cartes/dos.bmp";
    char chemin[60];
    string chemin_str;

    file >> receveur;//charge le nom
    newcarte.setNom(receveur);//ecrit le nom

    file >> receveur;//charge le type
    newcarte.setType(receveur);//ecrit le type

    //charge les images de la carte
    chemin_str="images/cartes/"+newcarte.getType()+"/"+newcarte.getNom()+".bmp";
    m_alleg.myStrToChar(chemin, chemin_str);//converti le string en char*

    newcarte.m_img_carte=newcarte.charge_cartes(chemin,160,229, newcarte.getNom());//charge la face de la carte
    newcarte.m_img_dos=newcarte.charge_cartes(txt,160,229, "none");//charge le dos de la carte

    return newcarte;//retourne la carte
}

//accesseurs
//getter
string Carte::getNom() const{ return m_nom; }
string Carte::getType() const{ return m_type; }
BITMAP *Carte::getImg() const{ return m_img_carte; }
BITMAP *Carte::getDos() const{ return m_img_dos; }

//setter
void Carte::setNom(string _nom){ m_nom=_nom; }
void Carte::setType(string _type){ m_type=_type; }
void Carte::setImg_carte(BITMAP *card){ m_img_carte=card; }
void Carte::setDos(BITMAP *dos){ m_img_dos=dos; }
