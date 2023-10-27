#include "Case_verte.h"

//constructeur et destructeur
//constructeur par defaut
Case_verte::Case_verte(){
    m_nom="verte";//ecriture du nom
    m_affiche=1;//on doit afficher cette case
    for(int i=0; i<4; i++)//ecriture des murs
        m_murs[i].init(false);
}

//destructeur
Case_verte::~Case_verte(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int Case_verte::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    //Déclaration des ressources
    char texte[7][2][60]={{"Bon evenement", "Good event"}, {"Relancer les des","Roll the dice again"}, {"Echange de place","Switch places"}, {"+ 4 cases au prochain lancer","+ 4 boxes on next roll"}, {"+ 1 de au prochain lancer","+ 1 dice on next roll"}, {"Arreter la roulette","Stop the wheel"} , {"Suite","Next"}};
    int rec[6][4] ={{443,90,557,105} , {375,200,625,275} , {375,275,625,350} , {375,350,625,425} , {375,425,625,500} , {415,600,585,645}};
    int txt[7][4]={{443,90,455,90} , {426,230,419,230} , {431,305,443,305} , {383,380,407,380} , {395,455,411,455} , {419,615,439,615} , {475,615,479,615}};
    int myrand=rand()%(20);
    int ret=0;

    if(m_etape<2)//si on n'a pas arrêter la roulette d'evenements
    {
        for(int i=0; i<5; i++) //affiche tous les textes
        {
            m_alleg.rectfont(page, langue, lumin, false, (m_roulette+1)==i, rec[i][0], rec[i][1], rec[i][2], rec[i][3], rec[i][0], rec[i][1], rec[i][2], rec[i][3]); //fond du texte
            m_alleg.txtlangue(page, langue, lumin, texte[i][0], txt[i][0], txt[i][1], texte[i][1], txt[i][2], txt[i][3]);//texte
        }
        m_alleg.rectfont(page, langue, lumin, true, false, rec[5][0], rec[5][1], rec[5][2], rec[5][3], rec[5][0], rec[5][1], rec[5][2], rec[5][3]); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, texte[5+m_etape][0], txt[5+m_etape][0], txt[5+m_etape][1], texte[5+m_etape][1], txt[5+m_etape][2], txt[5+m_etape][3]);//texte

        m_roulette=(m_roulette+1*(1-m_etape))%4;//la roulette tourne

        if((m_outils.verifclick(0, frond, 1, rec[5][0], rec[5][1], rec[5][2], rec[5][3], 1) && rang<nbplay) || (rang>=nbplay && 0==myrand))//on demande d'arreter la roulette ?
        {
            m_etape++;//on passe a l'etape suivante
        }
    }
    else if(m_etape==2)//sinon l'effet de l'evenement est applique
    {
        ret=1;

        if(m_roulette==0)
            ret=-2;//on relance les des
        else if(m_roulette==2)
            newBonus=4;//+4 cases au prochain lancer
        else if(m_roulette==3)
            newNbDes+=1;//+1 de au prochain lancer
        else
            ret=10;
    }

    return ret;//retourne la nouvelle page
}
