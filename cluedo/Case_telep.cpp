#include "Case_telep.h"

//constructeur et destructeur
//constructeur par defaut
Case_telep::Case_telep(){
    m_nom="telep";//ecriture du nom
    for(int i=0; i<4; i++)//ecriture des murs
        m_murs[i].init(false);
}

//destructeur
Case_telep::~Case_telep(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int Case_telep::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    //Déclaration des ressources
    int tab[9][6][2]={{{1,1},{2,2},{3,1},{4,2},{1,3},{2,4}} , {{10,0},{11,0},{12,0},{10,1},{11,1},{12,1}} , {{19,1},{20,2},{21,1},{22,2},{19,3},{20,4}} , {{0,10},{1,10},{2,10},{3,10},{4,10},{5,10}} , {{18,8},{19,8},{20,8},{21,8},{22,8},{23,8}} , {{18,14},{19,14},{20,14},{21,14},{22,14},{23,15}} , {{1,20},{2,21},{3,20},{4,21},{5,20},{1,22}} , {{9,24},{10,24},{11,24},{12,24},{13,24},{14,24}} , {{18,22},{19,23},{20,22},{21,23},{22,22},{22,23}}};
    char texte[2][20]={"Teleportation", "Teleportation"};
    int posfr[4] ={443,90,557,105};
    char txt1[9][21]={"Cuisine", "Hall d'entree", "Balcon", "Chambre", "Salle de billard", "Bibliotheque", "Salon", "Reception", "Salle de bain"};
    int rec1[4]={270+150,150,430+150,175};
    int selec=-1;

    m_alleg.rectfont(page, langue, lumin, false, false, posfr[0], posfr[1], posfr[2], posfr[3], posfr[0], posfr[1], posfr[2], posfr[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, texte[0], posfr[0], posfr[1], texte[1], posfr[0], posfr[1]);//texte

    for(int i=0; i<9; i++)//affiche les 21 noms de cartes
    {
        m_alleg.rectfont(page, langue, lumin, true, false, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, txt1[i], rec1[0]+5, rec1[1]+5+25*i, txt1[i], rec1[0]+5, rec1[1]+5+25*i);//texte
        if(m_outils.verifclick(1, frond, 1, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, 1))//click gauche sur l'un des pions possibles ?
        {
            selec=i;//selection faite
        }
    }

    //selection faite ?
    if(selec!=-1)
    {
        //teleportation du pion vers la salle associee
        pionsPl[rang][0]=tab[selec][rang][0];
        pionsPl[rang][1]=tab[selec][rang][1];
    }

    return 0;
}

