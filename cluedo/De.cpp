#include "De.h"

//constructeur et destructeur
//constructeur par defaut
De::De(){}

//destructeur
De::~De(){

}

//methodes
void De::detruire()
{
    //detruit les 2 images
    m_alleg.mydestroy_bitmap(m_img_de);
    m_alleg.mydestroy_bitmap(m_img_pt);
}

//initialise le de
void De::init()
{
    //Déclaration des ressources
    char chemin[2][30]={"images/plateau/de.bmp","images/plateau/point.bmp"};

    //charge les 2 images
    m_img_de=m_alleg.load_img(chemin[0]);
    m_img_pt=m_alleg.load_img(chemin[1]);
    //remet sa valeur a 0
    setValue(0);
}

//permet de lancer le de
void De::lancer()
{
    m_value=rand()%(6)+1;//nombre compris entre 1 et 6
}

//affiche le de et son nombre
void De::display(BITMAP *&page, int lumin, int x, int y)
{
    m_alleg.luminosite(page, m_img_de, lumin, x, y);//affiche le de
    ecrit_nombre(page, lumin, x, y);//affiche le nombre
}

//affiche le nombre du de
void De::ecrit_nombre(BITMAP *&page, int lumin, int x, int y)
{
    if(1 == m_value)//si on a un
        writeOne(page, lumin, x, y);//on ecrit 1
    else if(2 == m_value)//si on a deux
        writeTwo(page, lumin, x, y);//on ecrit 2
    else if(3 == m_value)//si on a trois
        writeThree(page, lumin, x, y);//on ecrit 3
    else if(4 == m_value)//si on a quatre
        writeFour(page, lumin, x, y);//on ecrit 4
    else if(5 == m_value)//si on a cinq
        writeFive(page, lumin, x, y);//on ecrit 5
    else if(6 == m_value)//si on a six
        writeSix(page, lumin, x, y);//on ecrit 6
}

//ecrit le nombre 1
void De::writeOne(BITMAP *&page, int lumin, int x, int y)
{
    m_alleg.luminosite(page, m_img_pt, lumin, x+16, y+16);//affiche 1 point
}

//ecrit le nombre 2
void De::writeTwo(BITMAP *&page, int lumin, int x, int y)
{
    //Déclaration des ressources
    int tab[2][2]={{6,26}, {26,6}};

    for(int i=0; i<2; i++)//affiche 2 points
        m_alleg.luminosite(page, m_img_pt, lumin, x+tab[i][0], y+tab[i][1]);
}

//ecrit le nombre 3
void De::writeThree(BITMAP *&page, int lumin, int x, int y)
{
    //Déclaration des ressources
    int tab[3][2]={{6,26}, {16,16}, {26,6}};

    for(int i=0; i<3; i++)//affiche 3 points
        m_alleg.luminosite(page, m_img_pt, lumin, x+tab[i][0], y+tab[i][1]);
}

//ecrit le nombre 4
void De::writeFour(BITMAP *&page, int lumin, int x, int y)
{
    //Déclaration des ressources
    int tab[4][2]={{6,26}, {26,6}, {6,6}, {26,26}};

    for(int i=0; i<4; i++)//affiche 4 points
        m_alleg.luminosite(page, m_img_pt, lumin, x+tab[i][0], y+tab[i][1]);
}

//ecrit le nombre 5
void De::writeFive(BITMAP *&page, int lumin, int x, int y)
{
    //Déclaration des ressources
    int tab[5][2]={{6,26}, {16,16}, {26,6}, {6,6}, {26,26}};

    for(int i=0; i<5; i++)//affiche 5 points
        m_alleg.luminosite(page, m_img_pt, lumin, x+tab[i][0], y+tab[i][1]);
}

//ecrit le nombre 6
void De::writeSix(BITMAP *&page, int lumin, int x, int y)
{
    //Déclaration des ressources
    int tab[6][2]={{6,6}, {6,16}, {6,26}, {26,6}, {26,16}, {26,26}};

    for(int i=0; i<6; i++)//affiche 6 points
        m_alleg.luminosite(page, m_img_pt, lumin, x+tab[i][0], y+tab[i][1]);
}

//accesseurs
//getter
int De::getValue() const{ return m_value; }

//setter
void De::setValue(int _value){ m_value = _value; }
