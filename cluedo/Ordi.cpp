#include "Ordi.h"

/// Constructeur par defaut
Ordi :: Ordi(){}

/// Destructeur
Ordi :: ~Ordi(){}

/// Méthodes

//saisie du pseudo
void Ordi :: saisir_pseudo(BITMAP *&page, int langue, int lumin, int presence, int rang)
{
    //Déclaration des ressources
    char name[12]="ordinateur ";

    name[10]=41+rang;//on écrit dans le nom le rang de l'ordi
    setNom(name);//on ecrit son nom
}

//saisie du pion
void Ordi::saisir_pion(BITMAP *&page, int langue, int lumin, int tab[6], Pion p[6], int rang, int &valid, int frond)
{
    //Declaration des ressources
    string name[6]={"mario","luigi","gluigi","prof","ectochien","roi_boo"};
    int saisie=0;

    //l'ordi choisit un pion aleatoirement
    while(valid==-1)
    {
        saisie=rand()%6;//nombre aleatoire compris entre 0 et 5

        if(tab[saisie]==-1)//pion non saisie ?
            valid=1;//pion saisi !
    }

    valid=saisie;//valeur de la saisie
}

//retourne les cartes du joueur
void Ordi ::retourner_cartes(BITMAP *&page, int langue, int lumin, bool affiche[6], unsigned int &nbretour, int frond)
{
    //rien a mettre : c'est pour mettre le joueur devant l'ecran au courant de ses cartes en possession
}

int Ordi :: deplacer(map<int , Abstract_Case*> const&cases, int pionsPl[6][2])
{
    //Declaration des ressources
    //int portes[11][2]={{4,7} , {9,8} , {14,8} , {18,5} , {,} , {,} , {,} , {,} , {,} , {,} , {,}};
    //{172,201,206,138,390,438,419,420,233,400,497};
    int x=0;
    int y=0;
    int reussi;

    if(getPionPoseX()<5)//trop sur la gauche
    {
        x=1;
        y=0;
    }
    else if(getPionPoseX()>18)//trop sur la droite
    {
        x=-1;
        y=0;
    }
    else if(getPionPoseY()<5)//trop  haut
    {
        x=0;
        y=1;
    }
    else if(getPionPoseY()>19)//trop  bas
    {
        x=0;
        y=-1;
    }

    reussi=m_pion.test_deplacement(cases, x, y, pionsPl);//verification pour deplacer le pion

    if(0==reussi)
    {
        //random !
        do{
            x=rand()%(3)-1;
            y=rand()%(3)-1;
        }while((x+y)!=1 && (x+y)!=-1);

        reussi=m_pion.test_deplacement(cases, x, y, pionsPl);//verification pour deplacer le pion
    }

    return reussi;//on retourne si on a bien reussi le deplacement
}

//l'ordi accuse
int Ordi :: accuser(BITMAP *&page, int langue, int lumin, int turn[4], int frond, int valid, char *a, char *b, char *c, Enveloppe env)
{
    //Déclaration des ressources
    char texte[3][2][20]={{"Dommage...", "Too bad..."},{"Victoire !","You win !"},{"Suivant", "Next"}};
    int pos1[4][4] ={{455,90,555,105} , {455,90,555,105} , {467,700,533,720} , {415,200,585,245}};
    int ret=5;

    for(int i=0; i<2; i++)//affiche les textes
    {
        m_alleg.rectfont(page, langue, lumin, false, false, pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1], pos1[i*2+(i==0)*valid][2], pos1[i*2+(i==0)*valid][3], pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1], pos1[i*2+(i==0)*valid][2], pos1[i*2+(i==0)*valid][3]); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, texte[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1], texte[i*2+(i==0)*valid][1], pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1]);//texte
    }

    m_alleg.rectfont(page, langue, lumin, false, false, pos1[3][0], pos1[3][1], pos1[3][2], pos1[3][3], pos1[3][0], pos1[3][1], pos1[3][2], pos1[3][3]);//affiche les fonds des textes
    m_alleg.txtlangue(page, langue, lumin, a, pos1[3][0], pos1[3][1], a, pos1[3][0], pos1[3][1]);//texte
    m_alleg.txtlangue(page, langue, lumin, b, pos1[3][0], pos1[3][1]+15, b, pos1[3][0], pos1[3][1]+15);//texte
    m_alleg.txtlangue(page, langue, lumin, c, pos1[3][0], pos1[3][1]+30, c, pos1[3][0], pos1[3][1]+30);//texte

    //affiche l'enveloppe avec les cartes
    env.display(page, lumin, 1, 175, 380);//affiche l'enveloppe
    env.getLieux().lire(page, lumin, 250, 300);//affiche les cartes +75 + 87
    env.getSuspect().lire(page, lumin, 410, 300);//affiche les cartes +75 + 87
    env.getArme().lire(page, lumin, 570, 300);//affiche les cartes +75 + 87
    env.display(page, lumin, 2, 175, 380);//affiche l'enveloppe

    if(increment_cpt())//click gauche de l'ordi pour passer a la suite ?
    {
        if(valid)
        {
            turn[0]=102;//retour ecran titre car victoire
            setPgagnees(getPgagnees()+1);//+1 partie gagnee
            m_compte.reecrit_statut();//reecrit le statut du joueur
        }
        else
        {
            ret=3;//c'est au tour du joueur suivant
            setBonus(-100);//le joueur a perdu : il ne peut plus jouer
        }
    }

    return ret;//retourne la nouvelle page
}

//l'ordi emet une hypothese
void Ordi :: soupconner(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape)
{
    //Déclaration des ressources
    char texte[2][20]={"Hypothese", "Hypothesis"};
    int posfr[4] ={459,90,541,105};
    char txt2[2][20]={"Suivant", "Next"};
    int pose2[4] ={467,700,533,720};
    char txt1[21][21]={"Cuisine", "Hall_d_entree", "Balcon", "Chambre", "Salle_de_billard", "Bibliotheque", "Salon", "Reception", "Salle_de_bain", "Luigi", "Prof_K_Tastroff", "Ectochien", "Roi_Boo", "Mario", "Gluigi", "Ectoblast", "Aspira_coeur", "Reveloscope", "Ventouse", "Lampe_torche", "Bombe"};
    int rec1[4]={270+150,150,430+150,175};

    //choix de l'hypothese s'il n'en a pas fait : aleatoire
    if(-1==tab[0])
    {
        tab[0]=m_pion.position();//pour l'hypothese
        for(int i=1-(tab[0]==-1); i<3; i++)
        {
            do{
                tab[i]=rand()%(9-3*(i!=0))+9*(i!=0)+6*(i==2);
            }while(m_enquete.getTab(i,tab[i])==true);
        }
    }

    m_alleg.rectfont(page, langue, lumin, false, false, posfr[0], posfr[1], posfr[2], posfr[3], posfr[0], posfr[1], posfr[2], posfr[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, texte[0], posfr[0], posfr[1], texte[1], posfr[0], posfr[1]);//texte

    for(int i=0; i<21; i++)//affiche les 21 noms de cartes
    {
        m_alleg.rectfont(page, langue, lumin, false, (tab[0]==i || tab[1]==i || tab[2]==i), rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, txt1[i], rec1[0]+5, rec1[1]+5+25*i, txt1[i], rec1[0]+5, rec1[1]+5+25*i);//texte
    }

    m_alleg.rectfont(page, langue, lumin, false, false, pose2[0], pose2[1], pose2[2], pose2[3], pose2[0], pose2[1], pose2[2], pose2[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, txt2[0], pose2[0], pose2[1], txt2[1], pose2[0], pose2[1]);//texte

    if(increment_cpt())//temps d'attente pour passer a la suite
        etape++;//etape suivante
}

//le joueur montre une carte a celui qui emet une hypothese
void Ordi :: montrer_carte(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape, int turn[4])
{
    string txtcds[21]={"Cuisine", "Hall_d_entree", "Balcon", "Chambre", "Salle_de_billard", "Bibliotheque", "Salon", "Reception", "Salle_de_bain", "Luigi", "Prof_K_Tastroff", "Ectochien", "Roi_Boo", "Mario", "Gluigi", "Ectoblast", "Aspira_coeur", "Reveloscope", "Ventouse", "Lampe_torche", "Bombe"};
    char txt[6][2][50]={{"Montrer une carte","Show one card"},{"A votre tour,","It's your turn,"},{"Suivant","Next"},{"",""},{"Aucune carte interessante","No interesting card"},{"Selectionnez une carte a montrer.","Select a card to show."}};
    int rec[5][4]={{427,90,573,105} , {435,190,565,220} , {400,400,600,455} , {380,400,620,455} , {363,190,637,205}};
    int posetxt[5][4]={{427,90,439,90} , {443,190,435,190} , {467,420,479,420} , {443,205,443,205} , {395,420,419,420}};
    char txt2[3][2][50]={{"Une carte interessante,","One interesting card,"},{"vous la montrer.","you show it."},{"Suivant","Next"}};
    int rec2[3][4]={{403,190,597,205} , {403,205,597,220} , {400,400,600,455}};
    int posetxt2[4][4]={{403,190,411,190} , {403,205,411,220} , {467,420,479,420}};
    char txt3[3][2][50]={{"Visualisation de la carte par","Visualization of the map by the"},{"celui qui a emis l'hypothese.","one who gave the hypothese."},{"Suivant","Next"}};
    int rec3[3][4]={{371,190,629,205} , {371,205,629,220} , {400,730,600,785}};
    int posetxt3[4][4]={{371,190,371,190} , {371,205,371,220} , {467,750,479,750}};
    int presence=0, rang, posepqt[4]={503-(int)getNbCards()*83, 250, 503-(int)getNbCards()*83+160, 479};

    //affichage du texte et des rectangles
    for(int i=0; i<2+(turn[1]==0); i++)
    {
        m_alleg.rectfont(page, langue, lumin, false, false, rec[i][0], rec[i][1], rec[i][2], rec[i][3], rec[i][0], rec[i][1], rec[i][2], rec[i][3]);//fond du texte
        m_alleg.txtlangue(page, langue, lumin, txt[i][0], posetxt[i][0], posetxt[i][1], txt[i][1], posetxt[i][0], posetxt[i][1]);//texte
    }

    m_alleg.txtlangue(page, langue, lumin, getNom(), posetxt[3][0], posetxt[3][1], getNom(), posetxt[3][0], posetxt[3][1]);//affiche le pseudo du joueur concerne

    if(0 == turn[1])//on s'assure que le joueur concernee montre une carte a celui qui emet l'hypothese
    {
        turn[3]=-1;//reinit du numero montre
        if(increment_cpt())//click gauche sur le rectangle pour passer a la suite
            turn[1]=1;
    }
    else if(1 == turn[1])//le joueur concerne montre une de ses cartes a celui qui a emis l'hypothese s'il en possede au moins une
    {
        for(unsigned int i=0; i<getNbCards(); i++)//on verifie toutes les cartes du joueur concerne
        {
            for(int j=0; j<3; j++)//parcours du tableau de noms
            {
                if(txtcds[tab[j]]==m_cartes[i].getNom())//carte mis en hypothese ?
                {
                    presence++; //c'est bien le cas !
                    rang=i;//rang de la carte trouvee
                }
            }
        }

        if(0 == presence)//aucune carte interessante ?
        {
            m_alleg.rectfont(page, langue, lumin, false, false, rec[3][0], rec[3][1], rec[3][2], rec[3][3], rec[3][0], rec[3][1], rec[3][2], rec[3][3]);//fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt[4][0], posetxt[4][0], posetxt[4][1], txt[4][1], posetxt[4][0], posetxt[4][1]);//texte

            if(increment_cpt())//click gauche sur le rectangle pour passer a la suite
            {
                turn[0]++;//on passe au prochain joueur
                turn[1]=0;//etape 0 : le joueur confirme sa presence
            }
        }
        else if(1 == presence)//seulement une carte interessante en possession ?
        {
            //affichage du texte et des rectangles
            for(int i=0; i<3; i++)
            {
                m_alleg.rectfont(page, langue, lumin, false, false, rec2[i][0], rec2[i][1], rec2[i][2], rec2[i][3], rec2[i][0], rec2[i][1], rec2[i][2], rec2[i][3]);//fond du texte
                m_alleg.txtlangue(page, langue, lumin, txt2[i][0], posetxt2[i][0], posetxt2[i][1], txt2[i][1], posetxt2[i][0], posetxt2[i][1]);//texte
            }

            if(increment_cpt())//click gauche sur le rectangle pour passer a la suite
                turn[1]=2+rang;
        }
        else//sinon il en a plusieurs : il en choisi une a montrer
        {
            m_alleg.rectfont(page, langue, lumin, false, false, rec[4][0], rec[4][1], rec[4][2], rec[4][3], rec[4][0], rec[4][1], rec[4][2], rec[4][3]);//fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt[5][0], rec[4][0], rec[4][1], txt[5][1], rec[4][0], rec[4][1]);//texte

            for(unsigned int i=0; i<getNbCards(); i++)//affiche toutes les cartes du joueur
            {
                m_cartes[i].lire(page, lumin, posepqt[0]+165*i, posepqt[1]);//affiche la carte face visible

                if(m_cartes[i].getNom()==txtcds[tab[0]] || m_cartes[i].getNom()==txtcds[tab[1]] || m_cartes[i].getNom()==txtcds[tab[2]])//click gauche sur une des cartes liées a l'hypothese ?
                    turn[1]=2+i;//cette carte sera montree
            }
        }
    }
    else//le joueur qui a emis l'hypothese voit la carte
    {
        //affichage du texte et des rectangles
        for(int i=0; i<3; i++)
        {
            m_alleg.rectfont(page, langue, lumin, false, false, rec3[i][0], rec3[i][1], rec3[i][2], rec3[i][3], rec3[i][0], rec3[i][1], rec3[i][2], rec3[i][3]);//fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt3[i][0], posetxt3[i][0], posetxt3[i][1], txt3[i][1], posetxt3[i][0], posetxt3[i][1]);//texte
        }

        m_cartes[turn[1]-2].lire(page, lumin, 420, 350);//affichage de la carte

        if(increment_cpt())//click gauche sur le rectangle pour passer a la suite
        {
            //l'ordi sauegarde la carte vue
            if(m_cartes[turn[1]-2].getNom()==txtcds[tab[0]])//est-ce un lieu ?
                turn[3]=tab[0];//sauvegarde du numero vu
            else if(m_cartes[turn[1]-2].getNom()==txtcds[tab[1]])//un personnage ?
                turn[3]=tab[1];//sauvegarde du numero vu
            else if(m_cartes[turn[1]-2].getNom()==txtcds[tab[2]])//ou une arme ?
                turn[3]=tab[2];//sauvegarde du numero vu

            turn[0]++;//on passe au prochain joueur
            turn[1]=0;//etape 0 : le joueur confirme sa presence
        }
    }
}
