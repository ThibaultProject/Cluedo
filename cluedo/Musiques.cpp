#include "Musiques.h"

//constructeur et destructeur
//constructeur par defaut
Musiques::Musiques(){
    //charge toutes les musiques
    load_all_sound();
}

//destructeur
Musiques::~Musiques(){

}

//charge toutes les musiques
//detruit les elements
void Musiques::detruire()
{
    //detruit toutes les musiques
    m_alleg.mydestroy_sample( m_ecran_titre);
    m_alleg.mydestroy_sample( m_demarrage);
    m_alleg.mydestroy_sample( m_partie);
    m_alleg.mydestroy_sample( m_menu_pause);
    m_alleg.mydestroy_sample( m_victoire);
}

//charge toutes les musiques
void Musiques::load_all_sound()
{
    //Déclaration des ressources
    char chemin[5][50]={"musiques/ecran_titre.WAV", "musiques/demarrage.WAV", "musiques/partie.WAV", "musiques/menu_pause.WAV", "musiques/victoire.WAV"};

    //charger les musiques
    m_alleg.load_one_sound(m_ecran_titre, chemin[0]);
    m_alleg.load_one_sound(m_demarrage, chemin[1]);
    m_alleg.load_one_sound(m_partie, chemin[2]);
    m_alleg.load_one_sound(m_menu_pause, chemin[3]);
    m_alleg.load_one_sound(m_victoire, chemin[4]);

}

//joue la musique de l'ecran titre
void Musiques::play_ecran_titre(int vol)
{
    //joue de la musique
    m_alleg.myplay_sample(m_ecran_titre, vol, 128, 1000, 1);
}

//arrete la musique de l'ecran titre
void Musiques::stop_ecran_titre()
{
    //arret de la musique
    m_alleg.mystop_sample(m_ecran_titre);
}

//joue la musique de demarrage
void Musiques::play_demarrage(int vol)
{
    //joue de la musique
    m_alleg.myplay_sample(m_demarrage, vol, 128, 1000, 1);
}

//arrete la musique de demarrage
void Musiques::stop_demarrage()
{
    //arret de la musique
    m_alleg.mystop_sample(m_demarrage);
}

//joue la musique de partie
void Musiques::play_partie(int vol)
{
    //joue de la musique
    m_alleg.myplay_sample(m_partie, vol, 128, 1000, 1);
}

//arrete la musique de partie
void Musiques::stop_partie()
{
    //arret de la musique
    m_alleg.mystop_sample(m_partie);
}

//joue la musique de menu pause
void Musiques::play_menu_pause(int vol)
{
    //joue de la musique
    m_alleg.myplay_sample(m_menu_pause, vol, 128, 1000, 1);
}

//arrete la musique de menu pause
void Musiques::stop_menu_pause()
{
    //arret de la musique
    m_alleg.mystop_sample(m_menu_pause);
}

//joue la musique de victoire
void Musiques::play_victoire(int vol)
{
    //joue de la musique
    m_alleg.myplay_sample(m_victoire, vol, 128, 1000, 1);
}

//arrete la musique de victoire
void Musiques::stop_victoire()
{
    //arret de la musique
    m_alleg.mystop_sample(m_victoire);
}
