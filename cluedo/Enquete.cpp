#include "Enquete.h"

//constructeur et destructeur
//constructeur par defaut
Enquete::Enquete(){ init();}

//destructeur
Enquete::~Enquete(){
    //detruit les images
    for(int i=0; i<2; i++)
        m_alleg.mydestroy_bitmap(m_img_enq[i]);
}

//methodes
//initialise la feuille d'enquete
void Enquete::init()
{
    //Déclaration des resources
    char chemin[30]="images/plateau/enquete_.bmp";

    //charge les trois images
    for(int i=0; i<2; i++)
    {
        chemin[22]=49+i;//ecrit le rang du chemin
        m_img_enq[i]=m_alleg.load_img(chemin);//charge l'image
    }

    //reinitialise le tableau
    reinit();
}

//reinitialise le tableau
void Enquete::reinit()
{
    //reinitialise le tableau
    for(int x=0; x<6; x++)
    {
        for(int y=0; y<21; y++)
            m_tab[x][y]=false;//on ecrit rien dans le tableau
    }
}

//affiche la feuille d'enquete
void Enquete::display_enq(BITMAP *&page, int langue, int lumin, int state)
{
    //Déclaration des ressources
    char txt1[21][21]={"Cuisine", "Hall d'entree", "Balcon", "Chambre", "Salle de billard", "Bibliotheque", "Salon", "Reception", "Salle de bain", "Luigi", "Prof K.Tastroff", "Ectochien", "Roi Boo", "Mario", "Gluigi", "Ectoblast", "Aspira coeur", "Reveloscope", "Ventouse", "Lampe torche", "Bombe"};
    char txt2[2][3]={"J_","P_"};
    int rec1[4]={270,150,430,175};
    int rec2[4]={430,125,480,150};

    //affiche l'enveloppe de feuille d'enquete
    m_alleg.luminosite(page, m_img_enq[(state==2)], lumin, 24, 492);

    //on affiche la feuille d'enquete ?
    if(2 == state)
    {
        for(int i=0; i<21; i++)//affiche les 21 noms de cartes
        {
            m_alleg.rectfont(page, langue, lumin, false, false, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i); //fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt1[i], rec1[0]+5, rec1[1]+5+25*i, txt1[i], rec1[0]+5, rec1[1]+5+25*i);//texte
        }

        for(int i=0; i<6; i++)//affiche les 6 colonnes de joueurs
        {
            txt2[0][1]=49+i;//ecrit le rang du joueur
            txt2[1][1]=49+i;
            m_alleg.rectfont(page, langue, lumin, false, false, rec2[0]+50*i, rec2[1], rec2[2]+50*i, rec2[3], rec2[0]+50*i, rec2[1], rec2[2]+50*i, rec2[3]); //fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt2[0], rec2[0]+11+50*i, rec2[1]+5, txt2[1], rec2[0]+11+50*i, rec2[1]+5);//texte
        }

        for(int x=0; x<6; x++)//affichage des cases
        {
            for(int y=0; y<21; y++)
                m_alleg.rectfont(page, langue, lumin, true, m_tab[x][y], rec2[0]+50*x, rec1[1]+25*y, rec2[2]+50*x, rec1[3]+25*y, rec2[0]+50*x, rec1[1]+25*y, rec2[2]+50*x, rec1[3]+25*y); //rectangle
        }
    }
}

//sauvegarde la feuille d'enquete
void Enquete::save(ofstream &file)
{
    //Declaration des ressources
    int numero;

    //sauvegarde toute la feuille d'enquete
    for(int x=0; x<6; x++)//affichage des cases
    {
        for(int y=0; y<21; y++)
        {
            numero=getTab(x, y);//conversion du bool en int
            file << numero << endl;//sauvegarde
        }
    }

}

//sauvegarde la feuille d'enquete
void Enquete::load(ifstream &file, string &receveur)
{
    //Declaration des ressources
    int numero;

    //sauvegarde toute la feuille d'enquete
    for(int x=0; x<6; x++)//affichage des cases
    {
        for(int y=0; y<21; y++)
        {
            file >> receveur;//charge
            numero=stoi(receveur);//converti str en int
            setTab(x, y, numero);//ecrit la valeur dans la feuille d'enquete
        }
    }

}

//accesseurs
//getter
bool Enquete::getTab(int rang1, int rang2)
{
    //Declaration des ressources
    bool value;
/*
    ///rang compris dans le tableau ?
    if(0<=rang1 && rang1<6 && 0<=rang2 && rang2<21)
        value=m_tab[rang1][rang2];
*/
    try{
        if(0>rang1 || rang1>=6 || 0>rang2 || rang2>=21)//case hors du tableau ?
            throw string("Case hors du tableau !");
        value=m_tab[rang1][rang2];//retourne la valeur souhaitee
    }
    catch(string e){
        cerr << e <<endl;//message erreur
        value=0;
    }

    //retourne la valeur
    return value;
}

//setter
void Enquete::setTab(int rang1, int rang2, bool value)
{
    ///rang compris dans le tableau ?
/*    if(0<=rang1 && rang1<6 && 0<=rang2 && rang2<21)
        m_tab[rang1][rang2]=value;
*/
    try{
        if(0>rang1 || rang1>=6 || 0>rang2 || rang2>=21)//case hors du tableau ?
            throw string("Case hors du tableau !");
        m_tab[rang1][rang2]=value;//retourne la valeur souhaitee
    }
    catch(string e){
        cerr << e <<endl;//message erreur
        value=0;
    }
}

