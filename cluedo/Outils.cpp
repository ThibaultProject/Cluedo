#include "Outils.h"

//constructeur et destructeur
//constructeur par defaut
Outils::Outils(){ init(); }

//destructeur
Outils::~Outils(){
}

//initialise le son de selection
//detruit les elements
void Outils::detruire()
{
    //detruit les sons
    for(int i=0; i<2; i++)
    {
        m_alleg.mydestroy_sample(m_sound[i]);
    }
}

void Outils::init()
{
    //Déclaration des ressources
    char chemin[2][50]={"musiques/bruits/ok.WAV","musiques/bruits/collision.WAV"};

    //charge tous les effets sonores
    for(int i=0; i<2; i++)
        m_alleg.load_one_sound(m_sound[i],chemin[i]);//charge le son
}

//permet la condition de click ou de relachement de click sur un rectangle
int Outils::verifclick(int sound, int _front, int ask_front, int x1, int y1, int x2, int y2, int cdt)
{
    //Déclaration des ressources
    int valid;

    //si collision de la souris avec le rectangle lors d'un front montant ou descendant, c'est validé !
    if((1 == m_alleg.collimouse(x1, y1, x2, y2)) && (_front == ask_front))
    {
        if(cdt && sound==0)//si on est autorise de lancer le son
            m_alleg.myplay_sample(m_sound[sound], 255, 128, 1000, 0);//son qui confirme le click gauche sur un rectangle
        valid=1;//click valide
    }
    //non valide
    else
    {
        //si on n'a pas de collision avec l'ancien rectangle de collision
        if((1 == m_alleg.collimouse(x1, y1, x2, y2)) && (0 == m_alleg.collimouse(m_old[0], m_old[1], m_old[2], m_old[3])))
        {
            if(cdt)//si on est autorise de lancer le son
                m_alleg.myplay_sample(m_sound[1], 255, 128, 1000, 0);//son qui confirme la collision avec un rectangle
            //sauvegarde du nouveau rectangle de collision
            m_old[0]=x1;
            m_old[1]=y1;
            m_old[2]=x2;
            m_old[3]=y2;
        }
        else if((0 == m_alleg.collimouse(m_old[0], m_old[1], m_old[2], m_old[3])))
        {
            //reinitialise l'ancien rectangle
            for(int i=0; i<4; i++)
                m_old[i]=0;
        }

        valid=0;//click non valide
    }

    return valid;//retourne la valeur de "click gauche valide ? 1 oui 0 non"
}
