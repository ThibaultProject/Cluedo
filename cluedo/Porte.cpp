#include "Porte.h"

//constructeur et destructeur
//constructeur par defaut
Porte::Porte(){
    m_nom="porte";
    for(int i=0; i<4; i++)//ecriture des murs
        m_murs[i].init(false);
}

//destructeur
Porte::~Porte(){
    m_outils.~Outils();//detruit les sons des outils
}

//methodes
//effet de la case
int Porte::effect(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int nbplay)
{
    //Declaration des ressources
    int tab1[6][2]={{1,1},{2,2},{3,1},{4,2},{1,3},{2,4}};
    int tab2[6][2]={{19,1},{20,2},{21,1},{22,2},{19,3},{20,4}};
    int tab3[6][2]={{10,0},{11,0},{12,0},{10,1},{11,1},{12,1}};
    int tab4[6][2]={{0,10},{1,10},{2,10},{3,10},{4,10},{5,10}};
    int tab5[6][2]={{18,8},{19,8},{20,8},{21,8},{22,8},{23,8}};
    int tab6[6][2]={{1,20},{2,21},{3,20},{4,21},{5,20},{1,22}};
    int tab7[6][2]={{9,24},{10,24},{11,24},{12,24},{13,24},{14,24}};
    int tab8[6][2]={{18,22},{19,23},{20,22},{21,23},{22,22},{22,23}};
    int tab9[6][2]={{18,14},{19,14},{20,14},{21,14},{22,14},{23,15}};

    //teleportation dans la salle concernee
    if(getNumero()==172)
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab1[rang][0];
        pionsPl[rang][1]=tab1[rang][1];
    }
    else if(getNumero()==138)
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab2[rang][0];
        pionsPl[rang][1]=tab2[rang][1];
    }
    else if((getNumero()==201) || (getNumero()==206))
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab3[rang][0];
        pionsPl[rang][1]=tab3[rang][1];
    }
    else if(getNumero()==390)
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab4[rang][0];
        pionsPl[rang][1]=tab4[rang][1];
    }
    else if(getNumero()==233)
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab5[rang][0];
        pionsPl[rang][1]=tab5[rang][1];
    }
    else if(getNumero()==438)
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab6[rang][0];
        pionsPl[rang][1]=tab6[rang][1];
    }
    else if((getNumero()==419) || (getNumero()==420))
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab7[rang][0];
        pionsPl[rang][1]=tab7[rang][1];
    }
    else if(getNumero()==497)
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab8[rang][0];
        pionsPl[rang][1]=tab8[rang][1];
    }
    else
    {
        //nouvelle position du pion
        pionsPl[rang][0]=tab9[rang][0];
        pionsPl[rang][1]=tab9[rang][1];
    }

    return 0;//l'effet de la salle sera realisee
}
