#include "Player.h"

// Constructeur par defaut
Player :: Player(){}
// Destructeur
Player :: ~Player(){}

// Méthodes

//saisie du pseudo
void Player ::saisir_pseudo(BITMAP *&page, int langue, int lumin, int presence, int rang)
{
    //Déclaration des ressources
    char texte[4][2][50]={{"Saisie des pseudos","Entry of nicknames"} , {"Veuillez saisir votre pseudo, joueur  .","Please enter your nickname, player  ."} , {"Votre pseudo ne peut pas depasser 16 caracteres.","Your nickname can't exceed 16 characters."} , {"Ce pseudo est deja utilise par un autre joueur.","This nickname is already used by another player."}};
    int posRecFr[4][4]={{423,100,582,115} , {340,200,660,215} , {305,500,695,515} , {307,400,693,415}};
    int posRecEn[4][4]={{423,100,582,115} , {349,200,651,215} , {331,500,669,515} , {302,400,698,415}};
    int dernier=0;

    texte[1][0][37]=48+rang-7;//affiche le rang du joueur
    texte[1][1][35]=48+rang-7;

    //affichage du texte et de leur rectangle de fond
    for(int i=0; i<4; i++)
    {
        if((3 != i) || (1 == presence))//si c'est le texte standard ou si c'est celui de lerreur avec l'erreur concernée.
        {
            m_alleg.rectfont(page, langue, lumin, false, false, posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], posRecEn[i][0], posRecEn[i][1], posRecEn[i][2], posRecEn[i][3]); //fond du texte
            m_alleg.txtlangue(page, langue, lumin, texte[i][0], posRecFr[i][0], posRecFr[i][1], texte[i][1], posRecEn[i][0], posRecEn[i][1]);//texte
        }
    }

    dernier=getDernier(); //rang du dernier caractere du pseudo
    m_clavier.clavier(getNom(), dernier); //saisie du pseudo
    setDernier(dernier); //on restaure la valeur
    m_alleg.rectfont(page, langue, lumin, false, false, 400, 330, 600, 370, 400, 330, 600, 370); //fond du texte du pseudo
    m_alleg.txtlangue(page, langue, lumin, getNom(), 415, 345, getNom(), 415, 345);//affiche pseudo
}

//saisie du pion
void Player ::saisir_pion(BITMAP *&page, int langue, int lumin, int tab[6], Pion p[6], int rang, int &valid, int frond)
{
    //Declaration des ressources
    char texte[2][2][50]={{"Choix des pions","Choice of pieces"} , {"Veuillez choisir votre pion,","Please choose your piece,"}};//-9 char
    int posRecFr[3][4]={{435,100,565,115} , {383,200,617,215} , {140,300,260,420}};
    int posRecEn[2][4]={{431,100,565,115} , {389,200,611,215}};
    int number;

    for(int i=0; i<2; i++)//affiche les textes
    {
        number=(i==1)*(getDernier()*4);
        m_alleg.rectfont(page, langue, lumin, false, false, posRecFr[i][0]-number, posRecFr[i][1], posRecFr[i][2]+number, posRecFr[i][3], posRecEn[i][0]-number, posRecEn[i][1], posRecEn[i][2]+number, posRecEn[i][3]); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, texte[i][0], posRecFr[i][0]-number, posRecFr[i][1], texte[i][1], posRecEn[i][0]-number, posRecEn[i][1]);//texte
    }

    m_alleg.txtlangue(page, langue, lumin, getNom(), 610-(getDernier()*4), 200, getNom(), 605-(getDernier()*4), 200);//affiche le pseudo du joueur concerne

    for(int i=0; i<6; i++)//affiche les rectangles de selection et parcours du tableau des saisies
    {
        m_alleg.rectfont(page, langue, lumin, tab[i]==-1, (valid==i || tab[i]==rang), posRecFr[2][0]+120*i, posRecFr[2][1], posRecFr[2][2]+120*i, posRecFr[2][3], posRecFr[2][0]+120*i, posRecFr[2][1], posRecFr[2][2]+120*i, posRecFr[2][3]); //rectangle

        if(tab[i]==-1 || tab[i]==rang)//si le logo n'est pas choisi
        {
            m_alleg.luminosite(page, p[i].getImgLogo(2), lumin, posRecFr[2][0]+120*i, posRecFr[2][1]);//on affiche le logo

            if(m_outils.verifclick(1, frond, 1,posRecFr[2][0]+120*i, posRecFr[2][1], posRecFr[2][2]+120*i, posRecFr[2][3], 1))//click gauche sur l'un des pions possibles ?
            {
                valid=i; //on le saisit !
                p[i].effet_sonore();//effet sonore du pion

                for(int j=0; j<6; j++)//on verifie s'il n'avais pas deja choisi un pion
                {
                    if(tab[j]==rang)//pion saisi ?
                        tab[j]=-1;//pion remis dans le tas
                }
            }
        }
    }
}

//retourne les cartes du joueur
void Player ::retourner_cartes(BITMAP *&page, int langue, int lumin, bool affiche[6], unsigned int &nbretour, int frond)
{
    //Déclaration des ressources
    int taille=getDernier();
    char texte[3][2][60]={{"Decouverte des cartes", "Discovery of the cards"}, {"                    ","                    "} , {"Cliquez sur les cartes pour les retourner.","Click on the cards to return them."}};
    int posfr[3][4] ={{411,90,589,105} , {500-taille*4-5,185,500+taille*4+5,200} , {327,250,673,265}};
    int poseng[3][4]={{407,90,593,105} , {500-taille*4-5,185,500+taille*4+5,200} , {359,250,641,265}};
    unsigned int maxi=getNbCards();

    for(int i=0; i<taille+1; i++)//ecriture du nom
    {
        texte[1][0][i]=getNom()[i];
        texte[1][1][i]=getNom()[i];
    }

    for(int i=0; i<3; i++) //affiche tous les textes et images
    {
        m_alleg.rectfont(page, langue, lumin, false, false, posfr[i][0], posfr[i][1], posfr[i][2], posfr[i][3], poseng[i][0], poseng[i][1], poseng[i][2], poseng[i][3]); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, texte[i][0], posfr[i][0], posfr[i][1], texte[i][1], poseng[i][0], poseng[i][1]);//texte
    }

    //affiche toutes les cartes
    for(unsigned int i=0; i<maxi; i++)
    {
        if(true == affiche[i])//carte retournee ?
            lire(page, lumin, i, 503-maxi*83+165*i, 380);//affiche la carte face visible
        else //sinon la carte est face cachee
            affiche_dos(page, lumin, i, 503-maxi*83+165*i, 380);//affiche la carte face cachee

        if(m_outils.verifclick(0, frond, 1, 503-maxi*83+165*i, 380, 160+503-maxi*83+165*i, 609, false==affiche[i]) && (false == affiche[i]))//click gauche sur une carte retournee ?
        {
            affiche[i]=true;//carte retournee !
            nbretour++;//+1 carte retournee
        }
    }
}

//deplacement du pion d'un joueur
int Player :: deplacer(map<int , Abstract_Case*> const&cases, int pionsPl[6][2])
{
    //Declaration des ressources
    int x=0;
    int y=0;

    m_clavier.mini_clavier(x, y);//utilisation du mini clavier pour le deplacement du pion
    return m_pion.test_deplacement(cases, x, y, pionsPl);//verification pour deplacer le pion
}

//le joueur accuse
int Player :: accuser(BITMAP *&page, int langue, int lumin, int turn[4], int frond, int valid, char *a, char *b, char *c, Enveloppe env)
{
    //Déclaration des ressources
    char texte[3][2][20]={{"Dommage...", "Too bad..."},{"Victoire !","You win !"},{"Suivant", "Next"}};
    int pos1[4][4] ={{455,90,555,105} , {455,90,555,105} , {467,700,533,720} , {415,200,585,245}};
    int ret=5;

    for(int i=0; i<2; i++)//affiche les textes
    {
        m_alleg.rectfont(page, langue, lumin, i>0, false, pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1], pos1[i*2+(i==0)*valid][2], pos1[i*2+(i==0)*valid][3], pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1], pos1[i*2+(i==0)*valid][2], pos1[i*2+(i==0)*valid][3]); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, texte[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1], texte[i*2+(i==0)*valid][1], pos1[i*2+(i==0)*valid][0], pos1[i*2+(i==0)*valid][1]);//texte
    }

    m_alleg.rectfont(page, langue, lumin, false, false, pos1[3][0], pos1[3][1], pos1[3][2], pos1[3][3], pos1[3][0], pos1[3][1], pos1[3][2], pos1[3][3]);//affiche les fonds des textes
    m_alleg.txtlangue(page, langue, lumin, a, pos1[3][0], pos1[3][1], a, pos1[3][0], pos1[3][1]);//texte
    m_alleg.txtlangue(page, langue, lumin, b, pos1[3][0], pos1[3][1]+15, b, pos1[3][0], pos1[3][1]+15);//texte
    m_alleg.txtlangue(page, langue, lumin, c, pos1[3][0], pos1[3][1]+30, c, pos1[3][0], pos1[3][1]+30);//texte

    env.display(page, lumin, 1, 175, 380);//affiche l'enveloppe
    env.getLieux().lire(page, lumin, 250, 300);//affiche les cartes +75 + 87
    env.getSuspect().lire(page, lumin, 410, 300);//affiche les cartes +75 + 87
    env.getArme().lire(page, lumin, 570, 300);//affiche les cartes +75 + 87
    env.display(page, lumin, 2, 175, 380);//affiche l'enveloppe

    if(m_outils.verifclick(0, frond, 1, pos1[2][0], pos1[2][1], pos1[2][2], pos1[2][3], 1))//click gauche pour passer a la suite ?
    {
        if(valid)//si le joueur a gagne
        {
            turn[0]=102;//retour ecran titre car victoire
            setPgagnees(getPgagnees()+1);//+1 partie gagnee
            m_compte.reecrit_statut();//reecrit le statut du joueur
            ret=100;//c'est fini !
        }
        else//sinon le joueuir a perdu
        {
            ret=3;//c'est au tour du joueur suivant
            setBonus(-100);//le joueur a perdu : il ne peut plus jouer
        }
    }

    return ret;//retourne la nouvelle page
}

//le joueur emet une hypothese
void Player :: soupconner(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape)
{
    //Déclaration des ressources
    char texte[2][20]={"Hypothese", "Hypothesis"};
    int posfr[4] ={459,90,541,105};
    char txt2[2][20]={"Suivant", "Next"};
    int pose2[4] ={467,700,533,720};
    char txt1[21][21]={"Cuisine", "Hall_d_entree", "Balcon", "Chambre", "Salle_de_billard", "Bibliotheque", "Salon", "Reception", "Salle_de_bain", "Luigi", "Prof_K_Tastroff", "Ectochien", "Roi_Boo", "Mario", "Gluigi", "Ectoblast", "Aspira_coeur", "Reveloscope", "Ventouse", "Lampe_torche", "Bombe"};
    int rec1[4]={270+150,150,430+150,175};

    m_alleg.rectfont(page, langue, lumin, false, false, posfr[0], posfr[1], posfr[2], posfr[3], posfr[0], posfr[1], posfr[2], posfr[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, texte[0], posfr[0], posfr[1], texte[1], posfr[0], posfr[1]);//texte

    for(int i=0; i<21; i++)//affiche les 21 noms de cartes
    {
        m_alleg.rectfont(page, langue, lumin, (i>8 || i==m_pion.position() || -1==m_pion.position()), (tab[0]==i || tab[1]==i || tab[2]==i), rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, txt1[i], rec1[0]+5, rec1[1]+5+25*i, txt1[i], rec1[0]+5, rec1[1]+5+25*i);//texte
        //la saisie de la piece pour l'hypothese depend de la piece actuelle
        if(m_outils.verifclick(0, frond, 1, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, (i>8 || i==m_pion.position() || -1==m_pion.position())) && (i>8 || i==m_pion.position() || -1==m_pion.position()))//click gauche sur l'un des pions possibles ?
        {
            if(i<9)      { tab[0]=i; }//saisie du lieu
            else if(i<15){ tab[1]=i; }//saisie du personnage
            else         { tab[2]=i; }//saisie de l'arme
        }
    }

    m_alleg.rectfont(page, langue, lumin, (tab[0]!=-1 && tab[1]!=-1 && tab[2]!=-1), false, pose2[0], pose2[1], pose2[2], pose2[3], pose2[0], pose2[1], pose2[2], pose2[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, txt2[0], pose2[0], pose2[1], txt2[1], pose2[0], pose2[1]);//texte

    if(m_outils.verifclick(0, frond, 1, pose2[0], pose2[1], pose2[2], pose2[3], (tab[0]!=-1 && tab[1]!=-1 && tab[2]!=-1)) && (tab[0]!=-1 && tab[1]!=-1 && tab[2]!=-1))//click gauche sur le rectangle pour passer a la suite
        etape++;//etape suivante
}


void Player :: montrer_carte(BITMAP *&page, int langue, int lumin, int tab[3], int frond, int &etape, int turn[4])//le joueur montre une carte a celui qui emet une hypothese
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
        m_alleg.rectfont(page, langue, lumin, i==2, false, rec[i][0], rec[i][1], rec[i][2], rec[i][3], rec[i][0], rec[i][1], rec[i][2], rec[i][3]);//fond du texte
        m_alleg.txtlangue(page, langue, lumin, txt[i][0], posetxt[i][0], posetxt[i][1], txt[i][1], posetxt[i][0], posetxt[i][1]);//texte
    }

    m_alleg.txtlangue(page, langue, lumin, getNom(), posetxt[3][0], posetxt[3][1], getNom(), posetxt[3][0], posetxt[3][1]);//affiche le pseudo du joueur concerne

    if(0 == turn[1])//on s'assure que le joueur concernee montre une carte a celui qui emet l'hypothese
    {
        turn[3]=-1;//reinit du numero montre
        if(m_outils.verifclick(0, frond, 1, rec[2][0], rec[2][1], rec[2][2], rec[2][3], 1))//click gauche sur le rectangle pour passer a la suite
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
            m_alleg.rectfont(page, langue, lumin, true, false, rec[3][0], rec[3][1], rec[3][2], rec[3][3], rec[3][0], rec[3][1], rec[3][2], rec[3][3]);//fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt[4][0], posetxt[4][0], posetxt[4][1], txt[4][1], posetxt[4][0], posetxt[4][1]);//texte

            if(m_outils.verifclick(0, frond, 1, rec[3][0], rec[3][1], rec[3][2], rec[3][3], 1))//click gauche sur le rectangle pour passer a la suite
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
                m_alleg.rectfont(page, langue, lumin, i==2, false, rec2[i][0], rec2[i][1], rec2[i][2], rec2[i][3], rec2[i][0], rec2[i][1], rec2[i][2], rec2[i][3]);//fond du texte
                m_alleg.txtlangue(page, langue, lumin, txt2[i][0], posetxt2[i][0], posetxt2[i][1], txt2[i][1], posetxt2[i][0], posetxt2[i][1]);//texte
            }

            if(m_outils.verifclick(0, frond, 1, rec2[2][0], rec2[2][1], rec2[2][2], rec2[2][3], 1))//click gauche sur le rectangle pour passer a la suite
                turn[1]=2+rang;
        }
        else//sinon il en a plusieurs : il en choisi une a montrer
        {
            m_alleg.rectfont(page, langue, lumin, false, false, rec[4][0], rec[4][1], rec[4][2], rec[4][3], rec[4][0], rec[4][1], rec[4][2], rec[4][3]);//fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt[5][0], rec[4][0], rec[4][1], txt[5][1], rec[4][0], rec[4][1]);//texte

            for(unsigned int i=0; i<getNbCards(); i++)//affiche toutes les cartes du joueur
            {
                m_cartes[i].lire(page, lumin, posepqt[0]+165*i, posepqt[1]);//affiche la carte face visible

                if(m_outils.verifclick(0, frond, 1, posepqt[0]+165*i, posepqt[1], posepqt[2]+165*i, posepqt[3], (m_cartes[i].getNom()==txtcds[tab[0]] || m_cartes[i].getNom()==txtcds[tab[1]] || m_cartes[i].getNom()==txtcds[tab[2]])) && (m_cartes[i].getNom()==txtcds[tab[0]] || m_cartes[i].getNom()==txtcds[tab[1]] || m_cartes[i].getNom()==txtcds[tab[2]]))//click gauche sur une des cartes liées a l'hypothese ?
                    turn[1]=2+i;//cette carte sera montree
            }
        }
    }
    else//le joueur qui a emis l'hypothese voit la carte
    {
        //affichage du texte et des rectangles
        for(int i=0; i<3; i++)
        {
            m_alleg.rectfont(page, langue, lumin, i==2, false, rec3[i][0], rec3[i][1], rec3[i][2], rec3[i][3], rec3[i][0], rec3[i][1], rec3[i][2], rec3[i][3]);//fond du texte
            m_alleg.txtlangue(page, langue, lumin, txt3[i][0], posetxt3[i][0], posetxt3[i][1], txt3[i][1], posetxt3[i][0], posetxt3[i][1]);//texte
        }

        m_cartes[turn[1]-2].lire(page, lumin, 420, 350);//affichage de la carte

        if(m_outils.verifclick(0, frond, 1, rec3[2][0], rec3[2][1], rec3[2][2], rec3[2][3], 1))//click gauche sur le rectangle pour passer a la suite
        {
            //le joueur sauegarde la carte vue
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
