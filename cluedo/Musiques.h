#ifndef MUSIQUES_H_INCLUDED
#define MUSIQUES_H_INCLUDED

#include "Paquet.h"

//classe de la musique
class Musiques{
private:
    //attributs
    Allegfct m_alleg;       //les fonctions allegro
    SAMPLE *m_ecran_titre;  //musique de l'ecran titre
    SAMPLE *m_demarrage;    //musique de demarrage
    SAMPLE *m_partie;       //musique de la partie
    SAMPLE *m_menu_pause;   //muqique de menu pause
    SAMPLE *m_victoire;     //musique de victoire

public:
    //constructeur et destructeur
    Musiques();
    ~Musiques();

    //methodes
    void detruire();//detruit les elements
    void load_all_sound();//charge toutes les musiques
    void play_ecran_titre(int vol);//joue la musique de l'ecran titre
    void stop_ecran_titre();//arrete la musique de l'ecran titre
    void play_demarrage(int vol);//joue la musique de demarrage
    void stop_demarrage();//arrete la musique de demarrage
    void play_partie(int vol);//joue la musique de partie
    void stop_partie();//arrete la musique de partie
    void play_menu_pause(int vol);//joue la musique de menu_pause
    void stop_menu_pause();//arrete la musique de menu_pause
    void play_victoire(int vol);//joue la musique de victoire
    void stop_victoire();//arrete la musique de victoire
};

#endif // MUSIQUES_H_INCLUDED
