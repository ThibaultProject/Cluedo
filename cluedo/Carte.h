#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED

class Carte{
//attributs
private:
    //Allegfct m_alleg;
    string m_nom;        //le nom de la carte
    string m_type;       //son type
    BITMAP *m_img_carte; //image de la face
    BITMAP *m_img_dos;   //image du dos

//methodes
public:
    //constructeurs et destructeur
    Carte();
    Carte(string _nom, string _type, BITMAP *card, BITMAP *dos);
    Carte(string _nom, string _type, BITMAP *card);
    Carte(Carte const& c);
    ~Carte();

    //methodes
    void detruire();//detruit les images d'une carte
    BITMAP* charge_cartes(char *chemin, int tx, int ty, string name);//charge les images d'une carte
    void rassembler_cartes(vector< vector <Carte>> &cards);//permet de rassembler toutes les cartes pour la collection
    void lire(BITMAP *&page, int lumin, int x, int y);//lire une carte
    void affiche_dos(BITMAP *&page, int lumin, int x, int y);//affiche le dos d'une carte
    void save(ofstream &file);//sauvegarde de la carte
    Carte load(ifstream &file, string &receveur);//charge les elements de la carte

    //accesseurs
    string getNom() const;//getter
    string getType() const;//getter
    BITMAP *getImg() const;
    BITMAP *getDos() const;
    void setNom(string _nom);//setter
    void setType(string _type);//setter
    void setImg_carte(BITMAP *card);
    void setDos(BITMAP *dos);
};

#endif // CARTE_H_INCLUDED
