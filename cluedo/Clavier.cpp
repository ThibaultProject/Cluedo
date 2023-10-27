#include "Clavier.h"

//constructeur et destructeur
//constructeur par defaut
Clavier::Clavier(){
    //Declaration des ressources
    char chemin[50]="musiques/bruits/clavier.WAV";

    m_alleg.load_one_sound(m_sound, chemin);//charge le son
}

//destructeur
Clavier::~Clavier(){

}

//detruit le clavier
void Clavier::detruire()
{
    m_alleg.mydestroy_sample(m_sound);//detruit le son
}

//le joueur saisit son pseudo grâce au clavier
void Clavier::clavier(char pseudo[21], int &dernier)
{
    //lecture de la lettre au clavier si on n'avait appuyé sur aucune touche : que des minuscules
    //clavier qwerty
    if(key[KEY_Q])//si on appuie sur Q
        ajout_lettre(pseudo, dernier, 'a');//ecriture de la lettre a (clavier qwerty)
    else if(key[KEY_B])//si on appuie sur b
        ajout_lettre(pseudo, dernier, 'b');//ecriture de la lettre b
    else if(key[KEY_C])//si on appuie sur ...
        ajout_lettre(pseudo, dernier, 'c');//ecriture de la lettre ...
    else if(key[KEY_D])
        ajout_lettre(pseudo, dernier, 'd');
    else if(key[KEY_E])
        ajout_lettre(pseudo, dernier, 'e');
    else if(key[KEY_F])
        ajout_lettre(pseudo, dernier, 'f');
    else if(key[KEY_G])
        ajout_lettre(pseudo, dernier, 'g');
    else if(key[KEY_H])
        ajout_lettre(pseudo, dernier, 'h');
    else if(key[KEY_I])
        ajout_lettre(pseudo, dernier, 'i');
    else if(key[KEY_J])
        ajout_lettre(pseudo, dernier, 'j');
    else if(key[KEY_K])
        ajout_lettre(pseudo, dernier, 'k');
    else if(key[KEY_L])
        ajout_lettre(pseudo, dernier, 'l');
    else if(key[KEY_SEMICOLON])//si on appuie sur la touche ;
        ajout_lettre(pseudo, dernier, 'm');//ecriture de la lettre m (clavier qwerty)
    else if(key[KEY_N])
        ajout_lettre(pseudo, dernier, 'n');
    else if(key[KEY_O])
        ajout_lettre(pseudo, dernier, 'o');
    else if(key[KEY_P])
        ajout_lettre(pseudo, dernier, 'p');
    else if(key[KEY_A])
        ajout_lettre(pseudo, dernier, 'q');
    else if(key[KEY_R])
        ajout_lettre(pseudo, dernier, 'r');
    else if(key[KEY_S])
        ajout_lettre(pseudo, dernier, 's');
    else if(key[KEY_T])
        ajout_lettre(pseudo, dernier, 't');
    else if(key[KEY_U])
        ajout_lettre(pseudo, dernier, 'u');
    else if(key[KEY_V])
        ajout_lettre(pseudo, dernier, 'v');
    else if(key[KEY_Z])
        ajout_lettre(pseudo, dernier, 'w');
    else if(key[KEY_X])
        ajout_lettre(pseudo, dernier, 'x');
    else if(key[KEY_Y])
        ajout_lettre(pseudo, dernier, 'y');
    else if(key[KEY_W])
        ajout_lettre(pseudo, dernier, 'z');
    else if(key[KEY_SPACE])
        ajout_lettre(pseudo, dernier, ' ');
    else if(key[KEY_BACKSPACE])//appuie sur la touche backspace
        supprimer_lettre(pseudo, dernier);//on efface la derniere lettre saisie
    else
        setFrappe(0);//on n'appuie sur aucune touche
}

//permet d'ajouter une lettre au pseudo
void Clavier::ajout_lettre(char pseudo[21], int &dernier, char lettre)
{
    //si on n'a pas frappé sur une touche
    if(0 == getFrappe())
    {
        setFrappe(1); //on viens de frapper sur une touche

        //on peut ajouter une lettre si le rang du dernier caractère est différent de 20
        if(16 != dernier)
        {
            effet_sonore();//son d'une touche du clavier
            pseudo[dernier]=lettre; //ajout de la dernière lettre
            dernier++; //on augmente de 1 le rang de la dernière lettre
            pseudo[dernier]='\0'; //on y écrit le caractère de fin de mot
        }
    }
}

//permet de supprimer une lettre
void Clavier::supprimer_lettre(char pseudo[21], int &dernier)
{
    //si on n'a pas frappé sur une touche
    if(0 == getFrappe())
    {
        setFrappe(1);  //on viens de frapper sur une touche

        //on peut supprimer une lettre si le rang du dernier caractère est différent de 0
        if(0 != dernier)
        {
            effet_sonore();//son d'une touche du clavier
            pseudo[dernier]=' '; //suppression de la dernière lettre
            dernier--; //on diminue de 1 le rang de la dernière lettre
            pseudo[dernier]='\0';//on y écrit le caractère de fin de mot
        }
    }
}

//permet la saisie des deplacements des pions sur le plateau
void Clavier::mini_clavier(int &x, int &y)
{
    if(key[KEY_UP])//si on appuie sur la touche haut
        saisie_confirme(x, y, 0, -1);//deplacement vers le haut
    else if(key[KEY_DOWN])//si on appuie sur la touche bas
        saisie_confirme(x, y, 0, 1);//deplacement vers le bas
    else if(key[KEY_LEFT])//si on appuie sur la touche gauche
        saisie_confirme(x, y, -1, 0);//deplacement vers le gauche
    else if(key[KEY_RIGHT])//si on appuie sur la touche droite
        saisie_confirme(x, y, 1, 0);//deplacement vers le droite
    else
        setFrappe(0);//aucune frappe effectuee
}

//deplacement autorise
void Clavier::saisie_confirme(int &x, int &y, int newx, int newy)
{
    if(0==getFrappe())//si on n'avait frappe sur aucune touche
    {
        setFrappe(1);//onn vient de frapper sur une touche

        x=newx;//prend les nouvelles valeurs
        y=newy;
        effet_sonore(); //confirme la saisie au clavier grace a un son emis
    }
}


//lance l'effet sonore
void Clavier::effet_sonore()
{
    m_alleg.myplay_sample(m_sound, 255, 128, 1000, 0);//son qui confirme l'appui d'une touche du clavier
}

//accesseurs
//getter
int Clavier::getFrappe() const{ return m_frappe; }

//setter
void Clavier::setFrappe(int _frappe){ m_frappe = _frappe; }
