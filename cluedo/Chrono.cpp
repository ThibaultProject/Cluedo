#include "Chrono.h"

//constructeurs et destructeur
//constructeur par defaut
Chrono::Chrono(){}
//destructeur
Chrono::~Chrono(){}

//methodes
//reinitialise le chrono
void Chrono::initChrono()
{
    m_cpt=0;//met le compteur a 0
}

//incremente le chrono : calcul minutes et secondes
void Chrono::increment(int &minutes, int &sec)
{
    m_cpt++;//chrono +1

    //converti le compteur en minutes et secondes
    minutes=((m_cpt/m_FPS)/60);//calcul les minutes
    sec=(m_cpt/m_FPS)%60;    //calcul les secondes
}

//affiche le chrono
void Chrono::print_chrono(BITMAP *&page, int lumin)
{
    //Déclaration des ressources
    int minutes=0, sec=0;
    char txt[8]="00 : 00";

    increment(minutes, sec);//reactualise l'horloge

    //ecrit le chrono
    convert(txt, 0, minutes);//ecrit les minutes
    convert(txt, 5, sec);    //ecrit les secondes

    //affiche le chrono
    m_alleg.rectfont(page, 0, lumin, false, false, 32, 10, 98, 25, 32, 10, 98, 25); //fond du texte
    m_alleg.txtlangue(page, 0, lumin, txt, 32, 10, txt, 32, 10);//affichage du chrono

}

//permet de convertir un nombre en char
void Chrono::convert(char txt[8], int rang, int &timer)
{
    if(timer < 10)//si le nombre est inferieur a 10
        txt[rang+1]=48+timer;//on ecrit ce nombre dans la chaine de caractere
    else//sinon
    {
        txt[rang]=48+int(timer/10);//on recupere d'abord la dizaine
        txt[rang+1]=48+timer%10;//puis les unites
    }
}

//sauvegarde du chrono
void Chrono::save(ofstream &file)
{
    //sauegarde du compteur du chrono
    file << m_cpt << endl;
}

//charge les elemnts du chrono
void Chrono::load(ifstream &file, string &receveur)
{
    //Declaration des ressources
    int numero;

    //chargement du chrono
    file >> receveur;//recoit la valeur en str
    numero=stoi(receveur);//convert str en int
    m_cpt=numero;//charge le compteur du chrono
}
