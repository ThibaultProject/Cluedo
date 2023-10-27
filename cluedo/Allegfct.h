#ifndef ALLEGFCT_H_INCLUDED
#define ALLEGFCT_H_INCLUDED

#include "Paquet.h"

class Allegfct{
public:
    //constructeur et destructeur
    Allegfct();
    ~Allegfct();

    //methodes
    BITMAP *mycreate_bitmap(int width, int height); //creer un bitmap
    void myclear_to_color(BITMAP *&bitmap, int color);            //effacer un bitmap
    void myallegro_exit();                          //sortir d'allegro
    void myexit();                                  //sortie par erreur
    void myallegro_message(const char* message);    //afficher un message
    void myblit(BITMAP *source, BITMAP *&dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);//afficher une image
    void myrest(unsigned int tyme);//pause
    void myrectfill(BITMAP *&dest, int x1, int y1, int x2, int y2, int red, int green, int blue);//dessine l'interieur dun rectangle
    void myrect(BITMAP *&dest, int x1, int y1, int x2, int y2, int red, int green, int blue);//dessine les contours dun rectangle
    void mydestroy_sample(SAMPLE *&s);//detruit musique
    void mydestroy_bitmap(BITMAP *&s);//detruit image
    void mytextout_ex(BITMAP *&page, FONT *font, char *txtfr, int xfr, int yfr, int color);//ecrire du texte
    void myplay_sample(const SAMPLE* spl, int vol, int pan, int freq, int loop);//jouer une musique
    void mystop_sample(const SAMPLE* spl);//arreter une musique
    void mystretch_sprite(BITMAP *&arrivee, BITMAP *depart, int x, int y, int w, int h);//modifie la taille d'une image
    void load_one_sound(SAMPLE *&sa_musique, char *chemin);//charge une musique
    BITMAP *load_img(char *chemin);//charge une image
    void create_page(BITMAP *&page, int x, int y, int color);//cree la page d'affichage
    void luminosite(BITMAP *&page, BITMAP *const&picture, int lumin, int posex, int posey);//permet de modifier la luminosité d'une image
    void change_rvb(int &color);//couleur doit etre entre 0 et 255
    void myStrToChar(char txt[100], string str);//converti string en char*
    void myCharToStr(string &str, char txt[100]);//converti char* en string
    int verifpseudo(char *txt1, char *txt2);//verifie si un nom n'a pas deja ete saisi
    void txtlangue(BITMAP *&page, int langue, int lumin, char *txtfr, int xfr, int yfr, char *txteng, int xeng, int yeng);//permet d'afficher le texte correspondant au chois de la langue
    int colorcte(int lumin, int color);//permet de calculer la luminosité d'un texte et de son rectangle, dont l'écart reste le même (max 255)
    void drawrect(BITMAP *&page, int lumin, bool demande, bool force, int x1, int y1, int x2, int y2);//contour ou rectangle plein en fonction de la souris
    void rectfont(BITMAP *&page, int langue, int lumin, bool demande, bool force, int xf1, int yf1, int xf2, int yf2, int xe1, int ye1, int xe2, int ye2);//rectangle de position differentes en fonction de la langue
    int collimouse(int x1, int y1, int x2, int y2);//permet d'observer une collision de la souris avec un rectangle 0:non 1:oui
    //void echange(T &a, T &b);//echange deux valeurs

    //getter
    int getMouseX() const;
    int getMouseY() const;
    int getSCREEN_W() const;
    int getSCREEN_H() const;
};

#endif // ALLEGFCT_H_INCLUDED
