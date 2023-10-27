#include "Souris.h"

//constructeur et destructeur
//constructeur par efaut
Souris::Souris(){}

//destructeur
Souris::~Souris(){

}

//methodes
//detruit les elements
void Souris::detruire()
{
    //desalloue les images
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<2; j++)
        {
            m_alleg.mydestroy_bitmap(m_img_souris[i][j]);
        }
    }
}

//initialise la souris
void Souris::init_souris()
{
    //Déclaration des ressources
    char chemin2[6][50]={"images/souris/standard1.bmp", "images/souris/standard2.bmp", "images/souris/pioche1.bmp", "images/souris/pioche2.bmp", "images/souris/marteau1.bmp", "images/souris/marteau2.bmp"};
    int place[3][2]={{0,0},{-4,-16},{-3,-14}};
    int x, y;

    //on initialise le tableau de coordonnées
    for(y=0; y<3; y++)
    {
        for(x=0; x<2; x++)
            m_place[y][x]=place[y][x];
    }
    //on charge les différentes images de la souris
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<2; j++)
        {
            m_img_souris[i][j]=m_alleg.load_img(chemin2[i*2+j]);
        }
    }
}

//gere les appuis boutons de la souris
void Souris::gere_souris(int type)
{
    //si on fait click gauche ou droite (en fonction de la demande)
    if(mouse_b & type)
    {
        //si on n'avait pas fait click gauche, on détecte un front montant
        if(0 == m_front[type-1])
        {
            m_front[type-1]=1;
        }
        //sinon on avait déjà un front montant
        else
        {
            m_front[type-1]=2;
        }
    }
    //sinon on ne fait pas click
    else
    {
        //si on avait fait click gauche, on détecte un front desendant
        if(2 == m_front[type-1])
        {
            m_front[type-1]=3;
        }
        //sinon on avait déjà un front desendant
        else
        {
            m_front[type-1]=0;
        }
    }
}

//affiche la souris
void Souris::display(BITMAP *&page, int lumin)
{
    //l'affichage de la souris dépend du choix de l'image de la souris et du click gauche de la souris
    m_alleg.luminosite(page, getImgMouse(getType(), mouse_b & 1), lumin, m_alleg.getMouseX()+getPlace(getType(),0), m_alleg.getMouseY()+getPlace(getType(),1));
}

//sauvegarde de la souris
void Souris::save(ofstream &file)
{
    //sauegarde des elemnts du pion
    file << getType() << endl;
}

//charge la souris
void Souris::load(ifstream &file, string &receveur)
{
    //Declaration des ressources
    int numero;

    file >> receveur;//chargement
    numero=stoi(receveur);//convertion str en int
    setType(numero);//ecrit le numero
}

//accesseurs
//getter
int Souris::getType() const{ return m_type; }

int Souris::getPlace(int x, int y)//recupere une case du tableau de positions
{
    ///bien compris dans l'intervalle ?
    if(x<0 || x>3 || y<0 || y>2)
    {
        //erreur
        m_alleg.myallegro_message("Case du tableau invalide !");
        return m_place[0][0];//invalide
    }
    else
    {
        return m_place[x][y];//valide
    }
}

BITMAP *Souris::getImgMouse(int x, int y)
{
    ///bien compris dans l'intervalle ?
    /*if(x<0 || x>3 || y<0 || y>2)
    {
        //erreur
        m_alleg.myallegro_message("Case du tableau invalide ! Affichage de celle de debut !");
        return m_img_souris[0][0];
    }
    else
    {
        return m_img_souris[x][y];//valide
    }*/

    try{
        if(x<0 || x>3 || y<0 || y>2)//case hors du tableau ?
            throw string("la case est hors du tableau !");
        return m_img_souris[x][y];//valide
    }
    catch(string e){
        cerr << e <<endl;//message erreur
        return 0;
    }
}

//getter
int Souris::getFront(int place) const{ return m_front[place]; }

//setter
void Souris::setType(int _type){ m_type=_type; }
