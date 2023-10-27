#include "Plateau.h"

//constructeur et destructeur
//constructeur par defaut
Plateau::Plateau(){}

//destructeur
Plateau::~Plateau(){
}

//detruit les elements
void Plateau::detruire()
{
    int taille=m_cartes.size();

    m_alleg.mydestroy_bitmap(m_img_plat);//Detruit l'image du plateau
    m_alleg.mydestroy_bitmap(m_img_pause);//Detruit l'image du bloc
    m_outils.detruire();//detruit les sons des outils
    m_env.detruire();//detruit les images des enveloppes

    for(int i=0; i<3; i++)
        m_des[i].detruire();//detruit les images des des

    //detruit toutes les cases
    for(int i=0; i<24*25; i++)
    {
        //cout << i << endl;
        auto it = m_cases.find(0);

        if(it != m_cases.end())//existence de la case
        {
            it->second->detruire();//destruction de la case
        }
    }

    ///detruit les cartes
    m_small_c.detruire();//detruit les images de la carte
    for(int i=0; i<taille; i++)
    {
        m_cartes[i].detruire();
    }
}

//charge les images de l'enveloppe et du plateau
void Plateau::init()
{
    //Déclaration des ressources
    char chemin[3][30]={"images/Plateau.bmp","images/cartes/dos.bmp","images/Plateau/bloc.bmp"};

    m_env.init();//charge les images de l'enveloppe
    m_img_plat=m_alleg.load_img(chemin[0]);//charge l'image du plateau
    m_img_pause=m_alleg.load_img(chemin[2]);//charge l'image du bloc menu pause

    m_small_c.setImg_carte(m_small_c.charge_cartes(chemin[1], 108, 156, "none"));//charge l'image du dos de carte
    m_small_c.setDos(m_small_c.charge_cartes(chemin[1], 108, 156, "none"));//charge l'image du dos de carte

    for(int i=0; i<3; i++)//initialise les 3 des
        m_des[i].init();
}

//permet de creer l'enveloppe et de tout melanger
void Plateau::init_cards(Ppiece &pieces, Pperso &persos, Parme &armes)
{
    //Déclaration des ressources
    vector<Carte> all;
    int rang;

    //on s'assure que le paquet du tableau est vide
    while(0 == m_cartes.empty())
        m_cartes.pop_back();

    //les paquets de cartes sont deja melanges : on les place dans l'enveloppe
    m_env.creation(pieces, armes, persos);

    //on reunit toutes les cartes
    for(unsigned int i=0; i<8; i++)
        pieces.piocher(all);//on reunit celles du paquet des armes
    for(unsigned int i=0; i<5; i++)
        persos.piocher(all);//celles des personnages
    for(unsigned int i=0; i<5; i++)
        armes.piocher(all);//et celles des armes

    //melange toutes les cartes dans le paquet
    while(0 == all.empty())
    {
        //case aleatoire du tableau compris dans l'intervalle souhaité
        rang=rand()%(all.size());

        //met la carte dans le paquet
        m_cartes.push_back(all[rang]);

        //enleve la case concernee
        all.erase(all.begin()+rang);
    }
}

//cree toutes les cases
void Plateau::init_cases(int diff, bool load_create, int tab[60])
{
    //Declaration des ressources
    int portes[11]={172,201,206,138,390,438,419,420,233,400,497};
    int dep[6]={9,14,167,479,408,583};

    //on s'assure que la map est vide
    m_cases.clear();

    cases_coin();//cree toutes les cases pieces coin
    pieces_autre();//cree toutes les cases pieces autre
    pieceCentre();//cree la case piece centre

    //cree toutes les portes
    for(int i=0; i<11; i++)
        m_cases.insert(pair<int , Abstract_Case*>(portes[i],creer_case_porte()));

    //les cases departs sont des cases neutres
    for(int i=0; i<6; i++)
        m_cases.insert(pair<int , Abstract_Case*>(dep[i],creer_case_neutre()));

    //cree les cases speciales en fonction du niveau de difficulte
    create_cases(diff, load_create, tab);

    //cree toutes les cases neutres
    for(int i=0; i<600; i++)
    {
        auto it = m_cases.find(i);//cherche la case concernee
        if(it == m_cases.end())//case non trouvee ?
            m_cases.insert(pair<int , Abstract_Case*>(i,creer_case_neutre()));//on pose une case neutre
    }

    //initialise les murs
    init_murs();

    //attribue a chaque case son numero
    for(int i=0; i<600; i++)
    {
        m_cases[i]->setNumero(i);
    }
}

//cree les cases evenements
void Plateau::create_cases(int diff, bool load_create, int tab[60])
{
    //Declaration des ressources
    int bon, essai;

    //cree les cases secretes de teleportation
    for(int i=0; i<30; i++)
    {
        bon=0;
        if(false == load_create)//creation d'un nouveau plateau ?
        {
            do{//recherche une case vide
                essai=rand()%600;
                auto it = m_cases.find(essai);

                if(it == m_cases.end())//case vide ?
                    bon=1;
            }while(0==bon);
        }
        else//chaargement d'un ancien plateau
            essai=tab[i];

        if(diff==1)
            m_cases.insert(pair<int , Abstract_Case*>(essai,creer_case_telep()));//cree la case teleportation
        else if(diff==2)
            m_cases.insert(pair<int , Abstract_Case*>(essai,creer_case_verte()));//cree la case verte
        else
            m_cases.insert(pair<int , Abstract_Case*>(essai,creer_case_rouge()));//cree la case rouge
    }
}

//cree toutes les cases coin
void Plateau::cases_coin()
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
            m_cases.insert(pair<int , Abstract_Case*>(i+j*24,creer_piece_coin()));
    }

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(j!=5 || (i!=0 && i!=5))
                m_cases.insert(pair<int , Abstract_Case*>(18+i+j*24,creer_piece_coin()));
        }
    }

    for(int i=0; i<7; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(j!=5 || i!=6)
                m_cases.insert(pair<int , Abstract_Case*>(i+(j+19)*24,creer_piece_coin()));
        }
    }

    for(int i=0; i<7; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(j!=3 || i!=0)
                m_cases.insert(pair<int , Abstract_Case*>(17+i+(j+21)*24,creer_piece_coin()));
        }
    }
}

//cree les pieces autres
void Plateau::pieces_autre()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<2; j++)
        {
            m_cases.insert(pair<int , Abstract_Case*>(10+i+(j)*24,creer_piece_autre()));
        }
    }

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<6; j++)
        {
            m_cases.insert(pair<int , Abstract_Case*>(8+i+(j+2)*24,creer_piece_autre()));
        }
    }

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(j!=0 || i<5)
                m_cases.insert(pair<int , Abstract_Case*>(i+(j+9)*24,creer_piece_autre()));
        }
    }

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<5; j++)
        {
            m_cases.insert(pair<int , Abstract_Case*>(18+i+(j+8)*24,creer_piece_autre()));
        }
    }

    for(int i=0; i<7; i++)
    {
        for(int j=0; j<5; j++)
        {
            if((j!=0 && j!=4) || (i!=0 && i!=6))
                m_cases.insert(pair<int , Abstract_Case*>(17+i+(j+14)*24,creer_piece_autre()));
        }
    }

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            m_cases.insert(pair<int , Abstract_Case*>(9+i+(j+18)*24,creer_piece_autre()));
        }
    }
}

//cree les cases piece centre
void Plateau::pieceCentre()
{
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<7; j++)
        {
            m_cases.insert(pair<int , Abstract_Case*>(10+i+(j+10)*24,creer_piece_centre()));
        }
    }
}

//cree une case porte
Abstract_Case* Plateau::creer_case_porte()
{
    //Declaration des ressources
    Abstract_Case *c = new Porte();
    return c;//retourne la case porte
}

//cree une case neutre
Abstract_Case* Plateau::creer_case_neutre()
{
    //Declaration des ressources
    Abstract_Case *c = new CaseNeutre();
    return c;//retourne la case neutre
}

//cree une case piece coin
Abstract_Case* Plateau::creer_piece_coin()
{
    //Declaration des ressources
    Abstract_Case *c = new PieceCoin();
    return c;//retourne la case coin
}

//cree une case piece autre
Abstract_Case* Plateau::creer_piece_autre()
{
    //Declaration des ressources
    Abstract_Case *c = new PieceAutre();
    return c;//retourne la case autre
}

//cree une case piece centre
Abstract_Case* Plateau::creer_piece_centre()
{
    //Declaration des ressources
    Abstract_Case *c = new PieceCentre();
    return c;//retourne la case centre
}

//cree une case teleportation
Abstract_Case* Plateau::creer_case_telep()
{
    //Declaration des ressources
    Abstract_Case *c = new Case_telep();
    return c;//retourne la case centre
}

//cree une case verte
Abstract_Case* Plateau::creer_case_verte()
{
    //Declaration des ressources
    Abstract_Case *c = new Case_verte();
    return c;//retourne la case centre
}

//cree une case rouge
Abstract_Case* Plateau::creer_case_rouge()
{
    //Declaration des ressources
    Abstract_Case *c = new Case_rouge();
    return c;//retourne la case centre
}

//initialise les murs
void Plateau::init_murs()
{
    //Declaration des ressources
    int cases[16][4]={{1,0,1,0} , {1,0,0,0} , {0,1,0,0} , {0,0,1,0} , {0,0,0,1} , {1,1,0,0} , {0,1,1,0} , {0,0,1,1} , {1,0,0,1} , {1,1,1,0} , {1,1,0,1} , {1,0,1,1} , {0,1,1,1}};
    int angleHG[14]={0,6,10,14,18,56,168,210,216,354,377,384,441,456};
    int angleHD[15]={5,9,13,17,23,63,220,215,247,335,358,383,446,449,527};
    int angleBG[16]={38,114,144,176,192,221,306,360,425,432,450,569,576,585,591,594};
    int angleBD[18]={33,119,126,142,149,183,191,311,367,353,431,454,503,558,581,584,590,599};
    int libreH[1]={359};
    int libreD[1]={582};
    int libreB[2]={143,455};
    int libreG[1]={593};
    int seulH[52]={ 57, 62,138,163,164,165,166,169,170,171,173,200,202,203,204,205,207,217,218,219,245,246,355,356,357,385,386,387,388,389,391,211,212,213,214,442,445,457,458,459,460,461,474,475,476,477,478,522,523,524,525,526};
    int seulD[50]={ 29, 37, 53, 77,101,125, 55, 79,103,127,151,159,175, 87,111,135,159, 17, 41, 65, 89,113,271,295,319,343,209,257,281,305,376,424,462,486,510,534,440,464,488,512,536,560,470,494,518,542,566,520,544,568};
    int seulB[49]={145,146,147, 32, 39,178,179,180,181,139,140,141,193,194,195,196,222,223,186,187,188,189,190,307,308,309,310,361,362,363,364,365,451,452,453,417,418,421,422,433,434,435,436,437,498,499,500,501,502};
    int seulG[47]={ 30, 54, 78,102,126,150, 34, 80,104,128,160,152, 64, 88,112,136,159,184,258,282, 42, 66, 90,248,272,296,320,344,368,463,487,511,535,559,465,489,513,537,561,447,471,495,519,543,567,521,545};
    int hautbas[5]={330,331,332,333,334};

    //remplit toutes les cases
    remplir_cases(cases, angleHG, 14, 8);
    remplir_cases(cases, angleHD, 15, 5);
    remplir_cases(cases, angleBG, 16, 7);
    remplir_cases(cases, angleBD, 18, 6);
    remplir_cases(cases, libreH, 1, 12);
    remplir_cases(cases, libreD, 1, 11);
    remplir_cases(cases, libreB, 2, 10);
    remplir_cases(cases, libreG, 1, 9);
    remplir_cases(cases, seulH, 52, 1);
    remplir_cases(cases, seulD, 50, 2);
    remplir_cases(cases, seulB, 49, 3);
    remplir_cases(cases, seulG, 47, 4);
    remplir_cases(cases, hautbas, 5, 0);

}

//remplit les murs des cases
void Plateau::remplir_cases(int cases[16][4], int *tab, int place, int rang)
{
    //cree les murs des cases
    for(int i=0; i<place; i++)
    {
        auto it = m_cases.find(tab[i]);//recherche de la case
        if(it != m_cases.end())//case bien trouve ?
        {
            it->second->init(cases[rang]);//initialise la case
        }
    }
}

//permet de recuperer une carte du paquet
void Plateau::distribution_cards(vector<Abstract_Joueur*> &joueurs, int lenP, int lenO, int &posee)
{
    joueurs[posee%(lenP+lenO)]->recuperer_carte(m_cartes);//une carte donee a un joueur

    posee++;//une carte de posee en plus
}

//affiche l'enveloppe
void Plateau::display_env(BITMAP *&page, int lumin, int rang, int x, int y)
{
    m_env.display(page, lumin, rang, x ,y);//affiche l'enveloppe
}

//affiche le dos d'une carte
void Plateau::display_dos_carte(BITMAP *&page, int lumin, int x, int y)
{
    //affiche le dos d'une carte du paquet
    if(0 == m_cartes.empty())//paquet pas vide ?
        m_cartes[0].affiche_dos(page, lumin, x ,y);//affichage carte
}

//affiche le dos d'une petite carte
void Plateau::display_petit_dos(BITMAP *&page, int lumin)
{
    m_small_c.affiche_dos(page, lumin, 10, 40);//affiche le petit dos de carte
}

//affiche la face d'une carte
void Plateau::display_img_carte(BITMAP *&page, int lumin, unsigned int rang, int x, int y)
{
    if(0<=rang && rang<m_cartes.size())//rang pointant sur une carte existante ?
        m_cartes[rang].lire(page, lumin, x ,y);//affiche la face d'une carte
}

//affiche le chrono
void Plateau::print_chrono(BITMAP *&page, int lumin)
{
    m_chrono.print_chrono(page, lumin);//affiche le chrono
}

//le coeur du jeu
void Plateau::time_to_play(BITMAP *&page, int langue, int lumin, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd, int frond, int hyp[3], int turn[4])
{
    //Declaration des ressources
    char names[21][21]={"Cuisine", "Hall_d_entree", "Balcon", "Chambre", "Salle_de_billard", "Bibliotheque", "Salon", "Reception", "Salle_de_bain", "Luigi", "Prof_K_Tastroff", "Ectochien", "Roi_Boo", "Mario", "Gluigi", "Ectoblast", "Aspira_coeur", "Reveloscope", "Ventouse", "Lampe_torche", "Bombe"};
    int nbdes=joueurs[getTour()]->getNbDes();//nombre de des du joueur
    int pionsPl[6][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
    int bonus=joueurs[getTour()]->getBonus();
    int fait=0;

    for(int i=0; i<lenPl+lenOrd; i++)//garde en memoire les places des differents pions
    {
        pionsPl[i][0]=joueurs[i]->getPionPoseX();
        pionsPl[i][1]=joueurs[i]->getPionPoseY();
    }

    lancer_all_dice(page, langue, lumin, nbdes, frond, lenPl, joueurs[getTour()]->getBonus());//lancer tous les des

    print_all(page, langue, lumin, nbdes, joueurs, lenPl, lenOrd, frond);//affiche tous les elements du plateau


    if(m_outils.verifclick(0, frond, 1, 10, 40, 118, 196, (2 > getState() && getTour()<lenPl)) && (2 > getState() && getTour()<lenPl))//collision avec la carte ?
        setState(1-getState());//change l'etat

    if(2 > getState() && getTour()<lenOrd && lenPl<=getTour())//si c'est un ordi
        setState(0);//retourne ses cartes

    if(getEtape()==1)//etape 2 : deplacement du pion
    {
        fait=joueurs[getTour()]->deplacer(m_cases, pionsPl);//deplacement du pion

        if(fait)//deplacement du pion ?
        {
            if(fait==1)//on se dirige vers une autre case ?
            {
                fait=0;//reinit de la valeur
                for(int i=0; i<joueurs[getTour()]->getNbDes() && fait==0; i++)//deplacement de 1 case donc on retranche de 1 la valeur d'un de
                {
                    if(m_des[i].getValue()!=0)//valeur existante du de ?
                    {
                        m_des[i].setValue(m_des[i].getValue()-1);//on retranche de 1 sa valeur
                        fait=1;//un deplacement de fait
                    }
                }
            }
            else//sinon on est rentre dans une piece
            {
                for(int i=0; i<joueurs[getTour()]->getNbDes(); i++)//deplacement de 1 case donc on retranche de 1 la valeur d'un de
                {
                    m_des[i].setValue(0);//on met à 0 les dés
                }
            }

            if(m_des[joueurs[getTour()]->getNbDes()-1].getValue()==0)//si tous les deplacements ont ete fait
            {
                if(joueurs[getTour()]->getBonus()!=4)//si on n'a pas un bonus de 4 cases
                {
                    setEtape(getEtape()+1);//on passe a l'etape suivante
                    m_cases[joueurs[getTour()]->getPionPoseX()+joueurs[getTour()]->getPionPoseY()*24]->setEtape(0);//reinit l'etape
                    m_cases[joueurs[getTour()]->getPionPoseX()+joueurs[getTour()]->getPionPoseY()*24]->setRoulette(0);//reinit la roulette
                    //reinitialise les bonus du joueur
                    if(joueurs[getTour()]->getBonus()!=-100)//si le joueur existe toujours (n'a pas emis d'accusation)
                    {
                        joueurs[getTour()]->setBonus(0);
                        joueurs[getTour()]->setNbDes(2);
                    }
                }
                else
                {
                    m_des[joueurs[getTour()]->getNbDes()-1].setValue(4);//+4 cases
                    joueurs[getTour()]->setBonus(0);//reinitialise le bonus
                }
            }
        }
    }
    else if(getEtape()==2)//etape 3 : effet de la case
    {
        setEtape(getEtape()+m_cases[joueurs[getTour()]->getPionPoseX()+joueurs[getTour()]->getPionPoseY()*24]->effect(page, langue, lumin, frond, nbdes, bonus, pionsPl, getTour(), lenPl));
        //reinit les hypotheses
        for(int i=0; i<3; i++){ hyp[i]=-1; }
        //reactualise les donnees du joueur
        joueurs[getTour()]->setNbDes(nbdes);
        joueurs[getTour()]->setBonus(bonus);

        if(pionsPl[getTour()][0]==-10)//si on retourne a la case depart
        {
            joueurs[getTour()]->retour_depart();//retour a la case depart
        }
        else
        {
            joueurs[getTour()]->setPionPoseX(pionsPl[getTour()][0]);//reactalisaton de la place du pion
            joueurs[getTour()]->setPionPoseY(pionsPl[getTour()][1]);
        }
    }
    else if(getEtape()==4)
    {
        joueurs[getTour()]->soupconner(page, langue, lumin, hyp, frond, m_etape);//accusation
        if(getEtape()!=4)//accuation faite ?
        {
            if(m_env.getLieuxName()==names[hyp[0]] && m_env.getSuspectName()==names[hyp[1]] && m_env.getArmeName()==names[hyp[2]])//le joueur a gagne ?
                turn[0]=100;//joueur a bien gagne
        }
    }
    else if(getEtape()==5)
    {
        //verification de l'accusation
        setEtape(joueurs[getTour()]->accuser(page, langue, lumin, turn, frond, turn[0]==101, names[hyp[0]], names[hyp[1]], names[hyp[2]], m_env));
    }
    else if(getEtape()==6)
    {
        joueurs[getTour()]->soupconner(page, langue, lumin, hyp, frond, m_etape);//hypothese
        turn[0]=1;//reinit du n ieme joueur a montrer ses cartes
        turn[1]=0;//reinit de l'etape intermediaire pour montrer les cartes
        turn[2]=lenPl+lenOrd;//nombre de joueurs a potentiellement montrer leurs cartes
    }
    else if(getEtape()==7)
    {
        joueurs[(turn[0]+getTour())%turn[2]]->montrer_carte(page, langue, lumin, hyp, frond, m_etape, turn);//les autres joueurs montrent leur cartes si c'est le cas

        if(turn[3]!=-1)
        {
            joueurs[getTour()]->setTab((turn[0]+getTour()-1)%turn[2]*(getTour()<lenPl),turn[3],true);//sauvegarde des cartes montrees
            turn[3]=-1;//la modif est faite
        }

        if(turn[0]==turn[2])//tous les joueurs ont montré une carte s'ils en avaient au moins une en possession ?
            setEtape(3);//on passe au tour du prochain joueur
    }
    else if(getEtape()==11)
    {
        setEtape(getEtape()+telep(page, langue, lumin, frond, nbdes, bonus, pionsPl, getTour(), lenPl));//teleportation
        joueurs[getTour()]->setPionPoseX(pionsPl[getTour()][0]);//reactualise la case du joueur
        joueurs[getTour()]->setPionPoseY(pionsPl[getTour()][1]);
    }
    else if(getEtape()==12)
    {
        echange_place(page, langue, lumin, frond, joueurs, lenPl, lenOrd);//echange de place avec un autre joueur
    }

    if(getEtape()==3)
    {
        setEtape(0);//on reinitialise l'etape intermediaire
        setTour((getTour()+1)%(lenPl+lenOrd));//on passe au prochain joueur

        if(joueurs[getTour()]->getBonus()==-5)//le joueur passe son tour ?
        {
            joueurs[getTour()]->setBonus(0);//le joueur vient de passer son tour
            setEtape(3);//on avance d'un tour
        }
        else if(joueurs[getTour()]->getBonus()==-100)//sinon si le joueur ne peux plus jouer
        {
            bonus=0;
            for(int i=0; i<lenPl+lenOrd; i++)//on compte le nombre de joeurs qui ont perdu
                bonus+=joueurs[i]->getBonus()==-100;

            if(bonus==lenPl+lenOrd)//si tous les joueurs ont perdu
            {
                m_alleg.myallegro_message("Vous avez tous perdu !");//message de défaite
                turn[0]=103;//sauvegarde des joueurs
            }
            else
            {
                setEtape(3);//on passe au joueur suivant
            }
        }
    }
/*
    fait=int((m_alleg.getMouseX()-130)/31)+int(m_alleg.getMouseY()/32)*24;
    if(m_outils.verifclick(0, frond, 1, 0, 0, 1000, 800, 1))
        cout << "value = " << fait << endl;*/

}

//echange la place de 2 joueurs
void Plateau::echange_place(BITMAP *&page, int langue, int lumin, int frond, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd)
{
    char texte[2][20]={"Echange de place", "Switch places"};
    int posfr[4] ={431,90,569,105};
    int x1, y1, x2, y2;

    m_alleg.rectfont(page, langue, lumin, false, false, posfr[0], posfr[1], posfr[2], posfr[3], posfr[0], posfr[1], posfr[2], posfr[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, texte[0], posfr[0], posfr[1], texte[1], posfr[0], posfr[1]);//texte

    for(int i=0; i<(lenPl+lenOrd); i++)
    {
        //collision avec un recntagle de joueur ?
        if(m_outils.verifclick(1, frond, 1, 5+870*(i!=0), 35+300*(i==0)+160*(i-1)*(i!=0), 120+5+870*(i!=0), 35+120+300*(i==0)+160*(i-1)*(i!=0) ,1) || getTour()>=lenPl)
        {
            joueurs[(getTour()+i)%(lenPl+lenOrd)]->PionEffetSonore();//joue l'effet sonore du pion

            if(i!=0)//si on demande d'echanger les places
            {
                //echange !
                x1=joueurs[getTour()]->getPionPoseX();
                y1=joueurs[getTour()]->getPionPoseY();
                x2=joueurs[(getTour()+i)%(lenPl+lenOrd)]->getPionPoseX();
                y2=joueurs[(getTour()+i)%(lenPl+lenOrd)]->getPionPoseY();
                joueurs[getTour()]->setPionPoseX(x2);
                joueurs[getTour()]->setPionPoseY(y2);
                joueurs[(getTour()+i)%(lenPl+lenOrd)]->setPionPoseX(x1);
                joueurs[(getTour()+i)%(lenPl+lenOrd)]->setPionPoseY(y1);
            }

            setEtape(3);//on passe au prochain joueur
        }
    }
}

//teleportation
int Plateau::telep(BITMAP *&page, int langue, int lumin, int frond, int &newNbDes, int &newBonus, int pionsPl[6][2], int rang, int lenPl)
{
    //Déclaration des ressources
    int tab[9][6][2]={{{1,1},{2,2},{3,1},{4,2},{1,3},{2,4}} , {{10,0},{11,0},{12,0},{10,1},{11,1},{12,1}} , {{19,1},{20,2},{21,1},{22,2},{19,3},{20,4}} , {{0,10},{1,10},{2,10},{3,10},{4,10},{5,10}} , {{18,8},{19,8},{20,8},{21,8},{22,8},{23,8}} , {{18,14},{19,14},{20,14},{21,14},{22,14},{23,15}} , {{1,20},{2,21},{3,20},{4,21},{5,20},{1,22}} , {{9,24},{10,24},{11,24},{12,24},{13,24},{14,24}} , {{18,22},{19,23},{20,22},{21,23},{22,22},{22,23}}};
    char texte[2][20]={"Teleportation", "Teleportation"};
    int posfr[4] ={443,90,557,105};
    char txt1[9][21]={"Cuisine", "Hall d'entree", "Balcon", "Chambre", "Salle de billard", "Bibliotheque", "Salon", "Reception", "Salle de bain"};
    int rec1[4]={270+150,150,430+150,175};
    int selec=-1, ret=0;
    int myrand=rand()%20;

    m_alleg.rectfont(page, langue, lumin, false, false, posfr[0], posfr[1], posfr[2], posfr[3], posfr[0], posfr[1], posfr[2], posfr[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, texte[0], posfr[0], posfr[1], texte[1], posfr[0], posfr[1]);//texte

    for(int i=0; i<9; i++)//affiche les noms de lieux
    {
        m_alleg.rectfont(page, langue, lumin, true, false, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i); //fond du texte
        m_alleg.txtlangue(page, langue, lumin, txt1[i], rec1[0]+5, rec1[1]+5+25*i, txt1[i], rec1[0]+5, rec1[1]+5+25*i);//texte
        if((m_outils.verifclick(1, frond, 1, rec1[0], rec1[1]+25*i, rec1[2], rec1[3]+25*i, rang<lenPl) && rang<lenPl) || (rang>=lenPl && !myrand))//click gauche sur l'un des pions possibles ?
        {
            selec=i;//selection faite
        }
    }

    //selection faite ?
    if(selec!=-1)
    {
        //on effectue la teleportation
        pionsPl[rang][0]=tab[selec][rang][0];
        pionsPl[rang][1]=tab[selec][rang][1];
        ret=-9;//teleportation effectuee : on change d'etape intermediaire

        for(int i=0; i<2; i++)//reinit les des
        {
            m_des[i].setValue(0);//on met à 0 les valeurs des dés
        }
    }

    return ret;//retourne la nouvelle etape intermediaire
}

//affiche tous les elements du plateau
void Plateau::print_all(BITMAP *&page, int langue, int lumin, int taille, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd, int frond)
{
    m_alleg.luminosite(page, getImgPlat(), lumin, 130, 0); //affiche le plateau
    print_cases(page, lumin);//affiche les cases du plateau
    print_chrono(page, lumin);//affiche le chrono
    display_petit_dos(page, lumin);//affiche le petit dos de carte
    print_des(page, lumin, taille); //affiche les des
    print_img_pause(page, lumin);//affiche le bloc de menu pause
    display_joueurs(page, langue, lumin, joueurs, lenPl, lenOrd, frond);//affiche tous les logos , statuts des joueurs
    display_etape(page, langue, lumin);//affiche l'etape actuelle
    joueurs[getTour()]->display_enq(page, langue, lumin, getState());//affichage de la feuille d'enquete
    affiche_cartes_j(page, langue, joueurs);//affiche toutes les cartes du joueur et celles defaussees
}

//affiche les cases du plateau
void Plateau::print_cases(BITMAP *&page, int lumin)
{
    //Declaration des ressources
    int color=200+m_alleg.colorcte(lumin, 0);

    //affiche toutes les cases vertes
    for(int i=0; i<600; i++)
    {
        auto it = m_cases.find(i);//cherche la case concernee
        if(it != m_cases.end())//case trouvee ?
        {
            if("verte"==it->second->getNom())//si on demande d'afficher la case verte
                m_alleg.myrectfill(page, 130+31*(i%24), 32*int(i/24), 31+130+31*(i%24), 32+32*int(i/24), 0, color, 0);//on cree un rectangle vert
        }
    }
}

//affiche le bloc menu pause
void Plateau::print_img_pause(BITMAP *&page, int lumin)
{
    m_alleg.luminosite(page, m_img_pause, lumin, 20, 680); //affiche le bloc menu pause
}

//reinitialise le chrono
void Plateau::initChrono()
{
    m_chrono.initChrono();//reinit le chrono
}

//lance un certain nombre de des
void Plateau::lancer_de(int nbdes)
{
    for(int i=0; i<nbdes; i++)//lance tous les des
        m_des[i].lancer();//lance un de
}

//affiche les des
void Plateau::print_des(BITMAP *&page, int lumin, int taille)
{
    //Declaration des ressources
    int mini[4]={0,45,17,3};
    int dec[4]={0,0,56,42};

    //affiche tous les des
    for(int i=0; i<taille; i++)
    {
        m_des[i].display(page, lumin, mini[taille]+i*dec[taille], 245);//affiche un de
    }
}

//reinitialise le plateau
void Plateau::reinit()
{
    m_tour=0;//reinitialise le tour du joueur
    m_etape=0;//reinitialise l'etape du tour du joueur
    m_state=0;//reinit la state actuelle
    for(int i=0; i<3; i++)//reinitialise les des
        m_des[i].setValue(0);
}

///lancer tous les des
void Plateau::lancer_all_dice(BITMAP *&page, int langue, int lumin, int nbdes, int frond, int nbplayer, int bonus)
{
    //Declaration des ressources
    char txt[2][20]={"Lancer les des","Roll the dice"};
    int rec[4]={5,210,125,235};

    m_alleg.rectfont(page, langue, lumin, true, false, rec[0], rec[1], rec[2], rec[3], rec[0], rec[1], rec[2], rec[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, txt[0], rec[0]-1, rec[1]+5, txt[1], rec[0]+7, rec[1]+5);//texte

    //collision avec le rectangle de lancer de des et on n'a pas ouvert d'autres onglets
    if((m_outils.verifclick(0, frond, 1, rec[0], rec[1], rec[2], rec[3], (0==getEtape() && 0==getState() && (getTour() < nbplayer))) && (0==getEtape()&& 0==getState() && (getTour() < nbplayer))) || (0==getEtape() && getTour()>=nbplayer))
    {
        setEtape(getEtape()+1);//changement d'etape
        lancer_de(nbdes);

        if(bonus==-2)//lancer divise par 2 ?
        {
            for(int i=0; i<nbdes; i++)
                m_des[i].setValue(int(m_des[i].getValue()/2));
        }

        if(nbdes==2 && ((m_des[0].getValue()==1 && m_des[1].getValue()==1) || (m_des[0].getValue()==6 && m_des[1].getValue()==6)))//double 1 ou double 6 ?
            setEtape(getEtape()+10);//changement d'etape
    }
}

//affiche les caracteristiques de tous les joueurs
void Plateau::display_joueurs(BITMAP *&page, int langue, int lumin, vector<Abstract_Joueur*> &joueurs, int lenPl, int lenOrd, int frond)
{
    //affichage de tous les joueurs
    for(int i=0; i<(lenPl+lenOrd); i++)
        display_joueur(page, langue, lumin, (getTour()+i)%(lenPl+lenOrd), 5+870*(i!=0), 300*(i==0)+160*(i-1)*(i!=0), joueurs, frond);
}

//affiche les caracteristiques d'un joueur sur le plateau
void Plateau::display_joueur(BITMAP *&page, int langue, int lumin, int rang, int x, int y, vector<Abstract_Joueur*> &joueurs, int frond)
{
    //Déclaration des ressources
    int pose[3][2]={{0,15} , {15,30} , {35,155}};
    char txt[100];

    //trace les rectangles de fond
    for(int i=0; i<3; i++)
        m_alleg.rectfont(page, langue, lumin, int(i/2), false, x, y+pose[i][0], x+120, y+pose[i][1], x, y+pose[i][0], x+120, y+pose[i][1]); //rectangle du pseudo

    m_alleg.txtlangue(page, langue, lumin, joueurs[rang]->getNom(), x+60-4*joueurs[rang]->getDernier(), y+pose[0][0], joueurs[rang]->getNom(), x+60-4*joueurs[rang]->getDernier(), y+pose[0][0]);//pseudo du joueur
    m_alleg.myStrToChar(txt, joueurs[rang]->getStatut());//ecrit le nom
    m_alleg.txtlangue(page, langue, lumin, txt, x+60-4*joueurs[rang]->getStatut().size(), y+pose[1][0], txt, x+60-4*joueurs[rang]->getStatut().size(), y+pose[1][0]);//statut du joueur
    m_alleg.luminosite(page, joueurs[rang]->timer_logo(4), lumin, x, y+pose[2][0]);//affichage du logo

    if(m_outils.verifclick(1, frond, 1, x, y+pose[2][0], x+120, y+pose[2][1], 1))//click gauche sur le pion ?
        joueurs[rang]->PionEffetSonore();//joue l'effet sonore du pion

    joueurs[rang]->affiche_pion(page, lumin);//affiche le pion du joueur

}

//affiche le texte pour l'etape actuelle
void Plateau::display_etape(BITMAP *&page, int langue, int lumin)
{
    //Déclaration des ressources
    char txt[3][2][50]={{"Lancer les des","Roll the dice"} , {"Deplacer le pion","Move the piece"} , {"Effet de la case","Box's effect"}};
    char etape[2][50]={"Etape _ :","Step _ :"};
    int rec[4]={1,620,129,650};
    int e;

    if(getEtape()<3)//etape inferieur a trois
        e=getEtape();//copie de l'etape
    else
        e=2;//ecriture du max inclus

    //ecriture de l'étape
    etape[0][6]=49+getEtape();
    etape[1][5]=49+getEtape();

    //affichage de l'etape
    m_alleg.rectfont(page, langue, lumin, false, false, rec[0], rec[1], rec[2], rec[3], rec[0], rec[1], rec[2], rec[3]); //fond du texte
    m_alleg.txtlangue(page, langue, lumin, etape[0], rec[0], rec[1], etape[1], rec[0], rec[1]);//texte 1
    m_alleg.txtlangue(page, langue, lumin, txt[e][0], rec[0]-5, rec[1]+15, txt[e][1], rec[0]-5, rec[1]+15);//texte 2

}

//affiche les cartes du joueur et celles defaussees
void Plateau::affiche_cartes_j(BITMAP *&page, int lumin, vector<Abstract_Joueur*> &joueurs)
{
    //Declaration des ressources
    unsigned int maxi;

    //si on demande d'afficher les cartes
    if((1 == getState()) && (getTour() < int(joueurs.size())))
    {
        for(unsigned int i=0; i<getNbCards(); i++)//affiche les cartes defaussees
            display_img_carte(page, lumin, i, 503-getNbCards()*83+165*i, 50);

        maxi=joueurs[getTour()]->getNbCards();
        for(unsigned int i=0; i<maxi; i++)//affiche toutes les cartes du joueur
            joueurs[getTour()]->lire(page, lumin, i, 503-maxi*83+165*i, 520);//affiche la carte face visible
    }
}

//sauvegarde du plateau
void Plateau::save(ofstream &file)
{
    //Declaration des ressources
    int nbcartes=getNbCards();

    m_chrono.save(file);//sauvegarde du chrono
    m_env.save(file);//sauvegarde du enveloppe

    //sauvegarde des elements du plateau
    file << getTour() << endl << getEtape() << endl << getState() << endl;

    //sauvegarde de ses cases
    for(int i=0; i<600; i++)
        m_cases[i]->save(file);

    //sauvegarde des cartes
    file << nbcartes << endl;//ecrit le nombre de cartes
    for(int i=0; i<nbcartes; i++)//sauvegarde de toutes les cartes
        m_cartes[i].save(file);
}

//charge les elements du plateau
void Plateau::load(ifstream &file, string &receveur, int diff)
{
    //Declaration des ressources
    int numero, tab[60];
    int nbcartes=getNbCards();
    Carte c;

    m_chrono.load(file, receveur);//charge le chrono
    m_env.load(file, receveur);//charge l'enveloppe

    //charge les elements du plateau
    file >> receveur;//ecriture de la donnee lue
    numero=stoi(receveur);//conversion str en int
    setTour(numero);//charge le tour

    file >> receveur;//ecriture de la donnee lue
    numero=stoi(receveur);//conversion str en int
    setEtape(numero);//charge l'etape

    file >> receveur;//ecriture de la donnee lue
    numero=stoi(receveur);//conversion str en int
    setState(numero);//charge le state

    //chargement de ses cases
    for(int i=0; i<30; i++)
        m_cases[0]->load(file, receveur, tab, i);

    //cartes
    file >> receveur;
    nbcartes=stoi(receveur);//converti str en int pour le nomre de cartes

    //chargement des cartes
    for(int i=0; i<nbcartes; i++)
        m_cartes.push_back(c.load(file, receveur));

    //creation du plateau
    init_cases(diff, true, tab);
}

//accesseurs
//getter
//retourne l'Enveloppe
Enveloppe Plateau::getEnv() const{ return m_env; }
BITMAP *Plateau::getImgPlat() const{ return m_img_plat; }
//taille du vecteur de cartes
unsigned int Plateau::getNbCards() const{ return m_cartes.size(); }
unsigned int Plateau::getNbDes() const{ return m_cartes.size(); }
int Plateau::getTour() const{ return m_tour; }
int Plateau::getEtape() const{ return m_etape; }
int Plateau::getState() const{ return m_state; }

//setter
void Plateau::setTour(int _tour){ m_tour = _tour; }
void Plateau::setEtape(int _etape){ m_etape = _etape; }
void Plateau::setState(int _state){ m_state = _state; }
