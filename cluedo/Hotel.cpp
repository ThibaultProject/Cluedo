#include "Hotel.h"

//constructeur et destructeur
//constructeur par defaut
Hotel::Hotel(){
    init_all();//initialise le Hotel
    init_all_img();//charge toutes les images
    m_souris.init_souris();//initialise la souris
    m_plat.init();//initialise le plateau
}

//destructeur
Hotel::~Hotel(){
    //on sort d'allegro
    m_alleg.myallegro_exit();
}

//initialise tout le jeu
void Hotel::init_all()
{
    srand(time(NULL));//initialise l'aléatoire
    init_allegro();//initialise allegro
    init_sound();//initialise le son
}

//detruit les elements de l'hotel
void Hotel::detruire()
{
    //detruit toutes les images
    m_alleg.mydestroy_bitmap(m_page);

    for(int i=0; i<5; i++)
    {
        m_alleg.mydestroy_bitmap(m_fond[i]);
    }
    for(int i=0; i<12; i++)
    {
        m_alleg.mydestroy_bitmap(m_img_param[i]);
    }
    m_souris.detruire();//detruit les images de la souris
    m_music.detruire();//detruit les musiques
    m_outils.detruire();//detruit les sons de l'outil
    m_plat.detruire();//détruit les images du plateau
    m_clavier.detruire();//détruit les sons du clavier
    //detruit tous les joueurs
    for(unsigned int i=0; i<m_joueurs.size(); i++)
    {
        m_joueurs[i]->detruire();
    }
}

//source du sous programme v_init_allegro : https://drive.google.com/file/d/19n9Itt_EVLrJ71etpWq2t6_5lwdjHdyY/view
//initialise allegro
void Hotel::init_allegro()
{
    //initialisation d'allegro
    allegro_init();

    install_mouse();//initialisation de la souris
    install_keyboard();//initialisation du clavier

    set_color_depth(desktop_color_depth());//mode graphique

    if(0 != set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 800, 0, 0))//erreur de création du mode graphique ?
    {
        m_alleg.myallegro_message("Probleme de gfx !");//message erreur
        m_alleg.myallegro_exit();//on arrete allegro
        m_alleg.myexit();//on sort du programme
    }
}

void Hotel::init_sound()
{
    install_sound(DIGI_AUTODETECT, MIDI_NONE, 0);//initialise le son

    //existence du son ?
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) != 0) {
        m_alleg.myallegro_message("Echec de l'installation du son !");//message erreur
        m_alleg.myallegro_exit();//on quitte allegro
        m_alleg.myexit();//on sort du programme
    }
}

//charge toutes les images
void Hotel::init_all_img()
{
    //Déclaration des ressourves
    char chemin[5][50]={"images/fond/ecran_titre.bmp","images/fond/parametres.bmp","images/fond/demarrage.bmp","images/fond/aide_statut.bmp","images/fond/menu_pause.bmp"};
    char chemin3[6][50]={"images/parametres/fleche.bmp","images/parametres/fleche2.bmp","images/parametres/jauge.bmp","images/parametres/curseur.bmp","images/parametres/sound.bmp","images/parametres/choice.bmp"};

    //charge la page d'affichage
    m_alleg.create_page(m_page, m_alleg.getSCREEN_W(), m_alleg.getSCREEN_H(), makecol(0,0,0));

    //charge les fonds
    for(int i=0; i<5; i++)
    {
        m_fond[i]=m_alleg.load_img(chemin[i]);
    }

    //charge les images des parametres
    for(int i=0; i<5; i++)
    {
        m_img_param[i]=m_alleg.load_img(chemin3[i]);
    }
    //cree les images des differents luigis
    for(int i=0; i<7; i++)
    {
        m_img_param[i+5]=m_alleg.load_img(chemin3[5]);//charge l'image
        //on change les couleurs a partir du 2eme luigi
        if(i!=0)
        {
            change_luigi(i);//changement de couleur
        }
    }
}

//modifie la couleur des luigis
void Hotel::change_luigi(int i)
{
    //Déclaration des resssources
    int color[6][3]={{48,157,59} , {237,28,36} , {255,128,0} , {255,201,14} , {26,82,230} , {162,69,169}};
    int receveur;

    for(int y=0; y<m_img_param[i+5]->h; y++)
    {
        for(int x=0; x<m_img_param[i+5]->w; x++)
        {
            //on récolte les couleurs du pixel
            receveur=getpixel(m_img_param[i+5], x, y);
            //couleur grise pour modification ?
            if(((113 == getr(receveur)) && (142 == getg(receveur)) && (138 == getb(receveur))))
            {
                putpixel(m_img_param[i+5], x, y, makecol(color[i-1][0], color[i-1][1], color[i-1][2]));//changement de couleur !
            }
        }
    }
}

//on affiche les deux flèches
int Hotel::print_fleches(int myfront, int mygoto[3], int validite, int cdt)
{
    //Déclaration des ressources
    int value=mygoto[0];

    //creation des 2 rectangles avec leur fleche
    for(int i=0; i<2; i++)
    {
        if((i==0 && validite) || (i==1 && cdt))//si c'est fleche precedent ou fleche suivant avec condition valide
        {
            affichage_fleche(i);//affichage fleche
            if(m_outils.verifclick(0, myfront, 1, 140+640*i, 680, 220+640*i, 750, 1))//click gauche (front montant) sur fleche ?
                value=mygoto[i+1];//changement de page
        }
    }

    return value;//retourne la nouvelle page
}

//on affiche une fleche avec son rectangle
void Hotel::affichage_fleche(int x)
{
    //Déclaration des ressources
    int cte=m_alleg.colorcte(getLuminosite(), 0);
    int valid=m_alleg.collimouse(140+640*x, 680, 220+640*x, 750);
    int color[3]={(230+cte)*(1-valid)+(190+cte)*(valid), (230+cte)*(1-valid)+(190+cte)*(valid), (230+cte)*(1-valid)+(190+cte)*(valid)};

    //on dessine les rectangles
    m_alleg.myrectfill(m_page, 140+640*x, 680, 220+640*x, 750, color[0], color[1], color[2]);
    m_alleg.myrect(m_page, 140+640*x, 680, 220+640*x, 750, 190+cte, 190+cte, 190+cte);

    //on affiche la flèche
    m_alleg.luminosite(m_page, m_img_param[x], getLuminosite(), 150+640*x, 690);
}

//la fonction principale
void Hotel::thegame()
{
    //Déclaration des ressources
    int tab[6];

    //tant qu'on ne demande pas de sortir du Hotel
    while(-1 != getCurseur())
    {
        //on va a la fonction associee en fonction de la page
        if(0 == getCurseur())
        {
            ecran_titre(getCurseur());//ecran titre
        }
        else if(1 == getCurseur())
        {
            menu_principal(getCurseur());//menu principal
            setNbPlayer(0);//le nombre de joueur n'est pas encore choisi
        }
        else if(2 == getCurseur())
        {
            parametres(getCurseur(),1);//parametres
        }
        else if(3 == getCurseur())
        {
            afficher_statuts(getCurseur(),1);//affiche les stats des joueurs
        }
        else if(4 == getCurseur())
        {
            load_game();//charge une partie sauvegardee
        }
        else if(5 == getCurseur())
        {
            saisie_nbjh(getCurseur());//choix du nombre de joueurs
            setNbOrdi(0);//le nombre d'ordinateurs n'est pas encore choisi
            if(6 != getNbPlayer())// Si on est 6 joueurs, pas besion de saisir le nombre d'ordis
                setNbOrdi(-1);//le nombre d'ordinateurs n'est pas encore choisi
        }
        else if(6 == getCurseur())
        {
            saisie_nbordi(getCurseur());//choix du nombre d'ordinateurs
        }
        else if(7 == getCurseur())
        {
            print_choix_joueur(getCurseur());//affiche la saisie du choix du nombre de joueurs
        }
        else if((8 <= getCurseur()) && (13 >= getCurseur()))
        {
            saisir_pseudo(getCurseur());//saisie du pseudo des joueurs
        }
        else if(14 == getCurseur())
        {
            print_choix_pseudo(getCurseur());//affiche les pseudos des joueurs
            for(int i=0; i<6; i++)
                tab[i]=-1;//initialise le tableau
        }
        else if((15 <= getCurseur()) && (20 >= getCurseur()))
        {
            saisir_pion(getCurseur(), tab);//saisie du pion des joueurs
        }
        else if(21 == getCurseur())
        {
            print_choix_pion(getCurseur());//affiche les pseudos et les pions associés aux joueurs
            if(getCurseur() == 15)//si on choisi de retourner en arriere
            {
                for(int i=0; i<6; i++)
                    tab[i]=-1;//reinitialise le tableau
            }
        }
        else if(22 == getCurseur())
        {
            choix_difficulte(getCurseur());//choix de la difficulte
        }
        else if(23 == getCurseur())
        {
            creation_env(getCurseur());//creation de l'enveloppe
        }
        else if(24 == getCurseur())
        {
            distribution_cartes(getCurseur());//distribution des cartes
        }
        else if((25 <= getCurseur()) && (30 >= getCurseur()))
        {
            print_choix_carte(getCurseur());//affiche les cartes des joueurs
        }
        else if(31 == getCurseur())
        {
            time_to_play(getCurseur());//les joueurs jouent !
        }
        else if(32 == getCurseur())
        {
            menu_pause(getCurseur());//le menu pause
        }
        else if(33 == getCurseur())
        {
            save_game();//sauvegarde la partie
        }
        else if(34 == getCurseur())
        {
            regles_jeu(getCurseur());//les regles du jeu
        }
        else if(35 == getCurseur())
        {
            collection(getCurseur());//la collection de cartes
        }
        else if(36 == getCurseur())
        {
            afficher_statuts(getCurseur(),32);//affiche les stats des joueurs
        }
        else if(37 == getCurseur())
        {
            parametres(getCurseur(),32);//parametres
        }
    }
}

//ecran titre
void Hotel::ecran_titre(int page)
{
    //Déclaration des ressources
    char texte[2][2][50]={{"Cluedo : version Luigi's Mansion 3","Cluedo : Luigi's Mansion 3's version"},{"Appuyez sur Enter pour commencer de jouer.","Press Enter to begin to play."}};
    //lance la musique de l'ecran titre
    m_music.play_ecran_titre(getSon());

    //on continue tant qu'on n'appiue pas sur echap
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[0], getLuminosite(), 0, 0);

        //affiche du texte et leur fond
        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 360, 230, 640, 245, 350, 230, 650, 245);
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[0][0], 360, 230, texte[0][1], 350, 230);
        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 330, 600, 670, 615, 380, 600, 620, 615);
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[1][0], 330, 600, texte[1][1], 380, 600);

        //reactualise l'ecran
        refresh_game();

        //appui sur enter pour passer a la suite
        if(key[KEY_ENTER])
            setCurseur(getCurseur()+1);//page suivante
    }
}

//menu principal
void Hotel::menu_principal(int page)
{
    //Déclaration des ressources
    char texte[5][2][50]={{"Menu principal", "Main menu"},{"Lancer une nouvelle partie","Play a new game"},{"Charger une partie","Load a game"},{"Statistiques", "Statistics"},{"Parametres", "Parameters"}};
    int posRecFr[5][4]={{436,100,564,115} , {380,200,620,300} , {380,340,620,440} , {380,480,620,580} , {380,620,620,720}};
    int posRecEn[5][4]={{460,100,540,115} , {380,200,620,300} , {380,340,620,440} , {380,480,620,580} , {380,620,620,720}};
    int posTexte[5][4]={{440,100,460,100} , {392,242,440,242} , {428,382,455,382} , {452,522,460,522} , {460,662,460,662}};
    bool valid[5]={false, true, true, true, true};

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[0], getLuminosite(), 0, 0);

        //affiche du texte et leur font et click gauche
        for(int i=0; i<5; i++)
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), valid[i], false, posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], posRecEn[i][0], posRecEn[i][1], posRecEn[i][2], posRecEn[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posTexte[i][0], posTexte[i][1], texte[i][1], posTexte[i][2], posTexte[i][3]);//texte
            if(m_outils.verifclick(0, m_souris.getFront(0), 1, posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], i!=0) && i!=0)//click gauche (front montant) sur un rectangle autre que le texte menu principal
            {
                setCurseur(6-i);//on change de page
            }
        }

        //reactualise l'ecran
        refresh_game();
    }

    //arrete la musique de l'ecran titre
    m_music.stop_ecran_titre();
    if(5 == getCurseur())//lance la musique de démarrage
        m_music.play_demarrage(getSon());
}

//affiche les statuts de tous les joueurs
void Hotel::afficher_statuts(int page, int page_avant)
{
    //Déclaration des ressources
    char texte[3][2][50]={{"Statistiques","Statistics"} , {"Aucun compte n'a ete cree.","No account has been created."} , {"Retourner au menu","Return to menu"}};
    int posRecFr[5][4]={{448,100,552,115} , {391,390,609,405} , {400,650,600,750}};
    int posRecEn[5][4]={{456,100,544,115} , {383,390,617,405} , {400,650,600,750}};
    int posTexte[5][4]={{448,100,456,100} , {391,390,383,390} , {427,693,439,693}};
    int value[3];
    vector<Compte> tab;
    string txtfr="", txten="";
    char txtfr2[100], txten2[100];
    int current=0;
    int taille;

    load_all_statut(tab,0); //chargement des statuts
    taille=tab.size(); //sauvegarde de la taille du tableau

    //lance la musique
    m_music.play_demarrage(getSon());

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affichage
        m_alleg.luminosite(m_page, m_fond[3], getLuminosite(), 0, 0); //affiche l'image de fond

        //affichage des textes
        for(int i=0; i<3; i++)
        {
            if(i!=1 || taille==0)
            {
                m_alleg.rectfont(m_page, getLangue(), getLuminosite(), int(i/2), false, posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], posRecEn[i][0], posRecEn[i][1], posRecEn[i][2], posRecEn[i][3]); //fond du texte
                m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posTexte[i][0], posTexte[i][1], texte[i][1], posTexte[i][2], posTexte[i][3]);//texte
            }
            value[i]=current-1*(i==1)+1*(i==2);//page possible pour affichage
        }

        //affichage des stats
        for(int i=current*10; i<(current+1)*10 && i<taille; i++)
        {
            txtfr="";//reset des textes
            txten="";

            //creation du texte en francais et anglais
            for(unsigned int j=0; (tab[i].getNom())[j]!='\0'; j++)//ecriture du nom : char* en string
            {
                txtfr+=(tab[i].getNom())[j];
                txten+=(tab[i].getNom())[j];
            }//suite de l'ecriture

            txtfr+=" a joue "+to_string(tab[i].getPjouees())+" match(s) et en a gagne "+to_string(tab[i].getPgagnees())+" : c'est un "+tab[i].getStatut()+".";
            txten+=" played "+to_string(tab[i].getPjouees())+" game(s) and won "+to_string(tab[i].getPgagnees())+" : he's a "+tab[i].getStatut()+".";

            for(int i=0; i<100; i++)//converti string en char*
            {
                txtfr2[i]=txtfr[i];
                txten2[i]=txten[i];
            }

            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 140, 160+45*(i-current*10), 860, 175+45*(i-current*10), 140, 160+45*(i-current*10), 860, 175+45*(i-current*10)); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), txtfr2, 140, 160+45*(i-current*10), txten2, 140, 160+45*(i-current*10));//texte
        }

        //reactualise la page des stats s'il y en a beaucoup
        current=print_fleches(m_souris.getFront(0), value, current!=0, (current+1)*10<taille);

        if(m_outils.verifclick(0, m_souris.getFront(0), 1, 400,650,600,750, 1))//click gauche sur revenir au menu ?
            setCurseur(page_avant);//on revient a la page precendete

        refresh_game();//reactualise l'ecran
    }

    //arrete la musique et en lance une autre
    m_music.stop_demarrage();
    if(page_avant==1)//retour a l'ecran titre ?
        m_music.play_ecran_titre(getSon());//on lance la musique de l'ecran titre
}

void Hotel::parametres(int page, int page_avant)
{
    //Déclaration des ressources
    char texte[11][2][50]={{"Parametres","Parameters"} , {"Choix de la luminosite des images","Choice of pictures' brightness"} , {"Choix de l'image de la souris","Choice of mouse's picture"} , {"Choix du son","Choice of sound"} , {"Choix de la langue","Choice of language"} , {"Confirmer","Confirm"} , {"francais","french"} , {"anglais","english"} , {"standard","standard"} , {"pioche","pick"} , {"marteau","hammer"}};
    int posRecFr[11][4]={{450,95,550,110} , {365,205,635,220} , {48,355,285,370} , {446,355,554,370} , {757,355,907,370} , {400,650,600,750} , {732,440,932,490} , {732,530,932,580} , {66,430,266,470} , {66,490,266,530} , {66,550,266,590}};
    int posRecEn[11][4]={{450,95,550,110} , {375,205,625,220} , {63,355,270,370} , {426,355,574,370} , {757,355,907,370} , {400,650,600,750} , {732,440,932,490} , {732,530,932,580} , {66,430,266,470} , {66,490,266,530} , {66,550,266,590}};
    int posTexte[11][4]={{455,95,455,95}  , {365,205,375,205} , {48,355,63,355}  , {447,355,435,355} , {757,355,757,355} , {459,695,467,695} , {797,455,805,455} , {802,545,802,545} , {129,445,134,445} , {137,505,145,505} , {133,565,137,565}};
    int x=0, saisie=0;

    //lance la musique
    m_music.play_demarrage(getSon());

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affichage
        m_alleg.luminosite(m_page, m_fond[1], getLuminosite(), 0, 0); //affiche l'image de fond
        m_alleg.luminosite(m_page, m_img_param[2], getLuminosite(), 248, 256);//affiche le curseur
        m_alleg.luminosite(m_page, m_img_param[4], getLuminosite(), 470, 430);//affiche le choix du son

        //affichage du curseur
        if(1 == saisie)//curseur saisie ?
        {
            x=m_alleg.getMouseX()-10; //la position du curseur depend de celle de la souris
            x=x*((x+500)/740 && 1-(x/740))+(1-((x+800)/1040))*240 + (x/741)*740; //x est compris dans l'intervalle [240, 740]
        }
        else//sinon le curseur n'est pas saisie
            x=490+getLuminosite()*2.5;//sa position depend de la luminosite des images
        m_alleg.luminosite(m_page, m_img_param[3], getLuminosite(), x, 261);//affiche le choix du son

        //creation et commande des differents rectangles
        for(int i=0; i<11; i++)
        {
            //affichage
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), int((i+3)/8), (((i==6 || i==7) && getLangue()==i-6) || ((i>=8 || i<=10) && m_souris.getType()==i-8)), posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], posRecEn[i][0], posRecEn[i][1], posRecEn[i][2], posRecEn[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posTexte[i][0], posTexte[i][1], texte[i][1], posTexte[i][2], posTexte[i][3]);//texte
            //commande : click gauche sur rectangle ?
            if(m_outils.verifclick(0, m_souris.getFront(0), 1, posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], i>4) && i>4)//click gauche (front montant) sur un rectangle autre que les titres
            {
                if(i==5)
                    setCurseur(page_avant);//on retourne a la page precedente
                else if(i==6 || i==7)
                    setLangue(i-6);//change la langue
                else
                    m_souris.setType(i-8);//change l'image du curseur
            }
        }

        //commande de la saisie du curseur
        if(m_outils.verifclick(0, m_souris.getFront(0), 1, 490+getLuminosite()*2.5, 261, 490+getLuminosite()*2.5+20, 297, 1))//si on clique gauche sur le curseur
            saisie=1;//on saisit le curseur
        else if((3 == m_souris.getFront(0)) && (1 == saisie))//sinon si on n'appuie pas sur le bouton gauche et qu'on saisissait le curseur : front descendant
        {
            setLuminosite((((x-230)/25)-10)*10); //on réactualise la luminosité : 1 barre correspond à un changement de 10 en couleur
            saisie=0; //on ne saisit plus le curseur
        }

        //affichage et commande du son
        for(int i=0; i<8; i++)
        {
            if((getSon()-10)/35 >= i)//bon nombre de bars pour le son ?
                m_alleg.myrectfill(m_page, 472, 565-i*19, 527, 581-i*19, 50, 216, 100);//affichage
            if(m_outils.verifclick(0, m_souris.getFront(0), 1, 472, 565-i*19, 527, 581-i*19, 1))//click gauche sur l'un des rectangles ?
                setSon(10+35*i);//on change le son !
        }

        refresh_game();//reactualise l'ecran
    }

    //arrete la musique et en lance une autre
    m_music.stop_demarrage();
    if(page_avant==1)//retour a l'ecran titre ?
        m_music.play_ecran_titre(getSon());//on lance la musique de l'ecran titre
}

//affichage des regles du Hotel
void Hotel::regles_jeu(int page)
{
    //Déclaration des ressources
    char texte[2][2][50]={{"Regles du jeu", "Rules of the game"} , {"Retourner au menu","Return to menu"}};
    int rec[2][4]={{427,80,573,95} , {400,700,600,760}};
    int pose[2][4]={{443,80,427,80} , {427,722,439,722}};

    //lance la musique des regls du jeu = demarrage
    m_music.play_demarrage(getSon());

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[3], getLuminosite(), 0, 0);

        for(int i=0; i<2; i++)//affiche des textes et rectangle de fond
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), i!=0, false, rec[i][0], rec[i][1], rec[i][2], rec[i][3], rec[i][0], rec[i][1], rec[i][2], rec[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], pose[i][0], pose[i][1], texte[i][1], pose[i][2], pose[i][3]);//texte
        }

        if(m_outils.verifclick(0, m_souris.getFront(0), 1, rec[1][0], rec[1][1], rec[1][2], rec[1][3], 1))//click gauche sur le rectangle pour revenir au menu ?
            setCurseur(32);

        m_regles.display(m_page, getLangue(), getLuminosite());//affiche la feuille des regles

        refresh_game();//reactualise l'ecran
    }

    //arrete la musique du demarrage
    m_music.stop_demarrage();
}

//affichage de toutes les cartes
void Hotel::collection(int page)
{
    //Déclaration des ressources
    char texte[2][2][50]={{"Collection", "Collection"} , {"Retourner au menu","Return to menu"}};
    int rec[2][4]={{455,80,545,95} , {400,700,600,760}};
    int pose[2][4]={{455,80,455,80} , {427,722,439,722}};
    char txt2[3][2][50]={{"Cartes lieux", "Places' cards"} , {"Cartes personnages","Characters' cards"} , {"Cartes armes","Weapons' cards"}};
    int rect2[3][4]={{447,140,553,155} , {423,140,577,155} , {439,140,561,155}};
    vector< vector <Carte>> cards;
    int value[3]={0,0,1};
    int current=0;
    Carte c;

    c.rassembler_cartes(cards);//on rassemble toutes les cartes pour la collection

    m_music.play_demarrage(getSon());//lance la musique de la collection = demarrage

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[3], getLuminosite(), 0, 0);

        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, rect2[current][0], rect2[current][1], rect2[current][2], rect2[current][3], rect2[current][0], rect2[current][1], rect2[current][2], rect2[current][3]); //fond du texte
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), txt2[current][0], rect2[current][0], rect2[current][1], txt2[current][1], rect2[current][0], rect2[current][1]);//texte

        for(int i=0; i<2; i++)//affiche des textes et rectangle de fond
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), i!=0, false, rec[i][0], rec[i][1], rec[i][2], rec[i][3], rec[i][0], rec[i][1], rec[i][2], rec[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], pose[i][0], pose[i][1], texte[i][1], pose[i][2], pose[i][3]);//texte
        }

        for(int i=0; i<9-3*((current+1)/2); i++)//affiche les cartes
        {
            cards[current][i].lire(m_page, getLuminosite(), 5+166*i-996*int(i/6), 200+250*int(i/6));
        }

        if(m_outils.verifclick(0, m_souris.getFront(0), 1, rec[1][0], rec[1][1], rec[1][2], rec[1][3], 1))//click gauche sur le rectangle pour revenir au menu ?
            setCurseur(32);

        current=print_fleches(m_souris.getFront(0), value, current!=0, current!=2);//affiche les fleches et chagne la page d'affichage des cartes
        value[0]=current;//Reactualise les pages
        value[1]=current-1;//arriere
        value[2]=current+1;//avant

        refresh_game();//reactualise l'ecran
    }

    //arrete la musique du demarrage
    m_music.stop_demarrage();
}

//saisie du nombre de joueurs humains
void Hotel::saisie_nbjh(int page)
{
    //Déclaration des ressources
    char texte[2][50]={"Choix du nombre de joueurs", "Choice of the number of players"};
    int value[3]={getCurseur(), 1, getCurseur()+1+int(getNbPlayer()/6)};

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 391, 100, 609, 115, 371, 100, 629, 115); //fond du texte
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[0], 391, 100, texte[1], 371, 100);//texte

        //rectangle pour choix du nombre de joueurs
        for(int i=0; i<6; i++)
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), true, (i+1)==getNbPlayer(), 100+450*(int(i/3)), 200+150*i-450*(int(i/3)), 450+450*(int(i/3)), 290+150*i-450*(int(i/3)), 100+450*(int(i/3)), 200+150*i-450*(int(i/3)), 450+450*(int(i/3)), 290+150*i-450*(int(i/3))); //rectangle
            if(m_outils.verifclick(0, m_souris.getFront(0), 1, 100+450*(int(i/3)), 200+150*i-450*(int(i/3)), 450+450*(int(i/3)), 290+150*i-450*(int(i/3)), 1))//click gauche (front montant) sur un rectangle autre que le titre ?
            {
                setNbPlayer(i+1);//changement du nombre de joueurs
                value[2]=getCurseur()+1+int(getNbPlayer()/6);//changement de la prochaine page
            }

            for(int j=0; j<i+1; j++)//affiche les luigi
                m_alleg.luminosite(m_page, m_img_param[6+j], getLuminosite(), 101+450*(int(i/3))+j*58, 216+150*i-450*(int(i/3)));
        }

        setCurseur(print_fleches(m_souris.getFront(0), value, true, getNbPlayer()!=0));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }

    if(1 == getCurseur())//retour a l'ecran titre
    {
        m_music.stop_demarrage();//arrete la musique actuelle
        m_music.play_ecran_titre(getSon());//remet la musique de l'ecran titre
    }
}

//saisie du nombre d'oedinateur
void Hotel::saisie_nbordi(int page)
{
    //Déclaration des ressources
    char texte[2][50]={"Choix du nombre d'ordinateurs", "Choice of the number of computers"};
    int value[3]={getCurseur(), getCurseur()-1, getCurseur()+1};

    setNbOrdi(-1);//le nombre d'ordinateurs n'est pas encore choisi

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 379, 100, 621, 115, 367, 100, 633, 115); //fond du texte
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[0], 379, 100, texte[1], 367, 100);//texte

        //rectangle pour choix du nombre d'ordinateurs
        for(int i=0; i<7-getNbPlayer(); i++)
        {
            if(getNbPlayer()+i > 2)//minimum 3 joueurs
            {
                m_alleg.rectfont(m_page, getLangue(), getLuminosite(), true, i==getNbOrdi(), 100+450*(int(i/3)), 200+150*i-450*(int(i/3)), 450+450*(int(i/3)), 290+150*i-450*(int(i/3)), 100+450*(int(i/3)), 200+150*i-450*(int(i/3)), 450+450*(int(i/3)), 290+150*i-450*(int(i/3))); //rectangle
                if(m_outils.verifclick(0, m_souris.getFront(0), 1, 100+450*(int(i/3)), 200+150*i-450*(int(i/3)), 450+450*(int(i/3)), 290+150*i-450*(int(i/3)), 1))//click gauche (front montant) sur un rectangle autre que le titre ?
                {
                    setNbOrdi(i);//changement du nombre d'ordinateurs
                }

                for(int j=0; j<i; j++)//affiche les ordi
                    m_alleg.luminosite(m_page, m_img_param[5], getLuminosite(), 101+450*(int(i/3))+j*58, 216+150*i-450*(int(i/3)));
            }
        }
        setCurseur(print_fleches(m_souris.getFront(0), value, true, getNbOrdi()!=-1));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }
}

//affichage de la selection des joueurs
void Hotel::print_choix_joueur(int page)
{
    //Déclaration des ressources
    char texte[2][50]={"Confirmation de la selection", "Confirmation of selection"};
    int value[3]={getCurseur(), getCurseur()-1-int(getNbPlayer()/6), getCurseur()+1};

    //reset des joueurs : on vide les vecteurs de players et d'ordis
    while(!m_joueurs.empty())
        m_joueurs.pop_back();

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 383, 100, 617, 115, 395, 100, 605, 115); //fond du texte
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[0], 383, 100, texte[1], 395, 100);//texte

        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 325, 350, 675, 440, 325, 350, 675, 440);//rectangle
        for(int i=0; i < (getNbPlayer()+getNbOrdi()) ; i++)//affiche les luigis (humains et ordis)
            m_alleg.luminosite(m_page, m_img_param[5+(1+i)*(1-int((i+10)/(getNbPlayer()+10)))], getLuminosite(), 326+i*58, 366);

        setCurseur(print_fleches(m_souris.getFront(0), value, true, true));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }

    //creation des joueurs : on remplit les vecteurs de players et d'ordis
    for(int i=0; i<getNbPlayer(); i++)
    {
        create_player();//creation d'un joueur
        m_joueurs[i]->setNom("                    ");//reinitialise le pseudo
        m_joueurs[i]->setDernier(0);//reinitialise le rang du dernier caractere du pseudo
    }
    for(int i=getNbPlayer(); i<getNbPlayer()+getNbOrdi(); i++)
    {
        create_ordi();//creation d'un ordi
        m_joueurs[i]->setNom("                    ");//reinitialise le pseudo
        m_joueurs[i]->setDernier(12);//reinitialise le rang du dernier caractere du pseudo
    }
}

//saisie des pseudos
void Hotel::saisir_pseudo(int page)
{
    //Déclaration des ressources
    int value[3]={getCurseur(), getCurseur()-1, getCurseur()+1};
    int rang=page-8;
    int presence=0;

    //m_clavier.setFrappe(0);//on n'a frappe sur aucune touche

    if(rang < getNbPlayer()+getNbOrdi()) //joueur ?
    {
        //tant qu'on reste dans cette page
        while(page == getCurseur())
        {
            //affiche l'image de fond
            m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

            presence=verifpseudo(rang);//on verifie si le pseudo a deja ete saisi

            m_joueurs[rang]->saisir_pseudo(m_page, getLangue(), getLuminosite(), presence, page);//le joueur saisi son pseudo

            if(rang < getNbPlayer())//joueur humain ?
            {
                setCurseur(print_fleches(m_souris.getFront(0), value, true, ((0 != m_joueurs[rang]->getDernier()) && (0 == presence))));//affiche les fleches et chagne la page
                refresh_game();//reactualise l'ecran
            }
            else//ordi
                setCurseur(getCurseur()+1);//on change de page
        }
    }
    else//sinon c'est fini
    {
        setCurseur(getCurseur()+1);//on change de page
    }
}

//affiche le choix des pseudos des joueurs
void Hotel::print_choix_pseudo(int page)
{
    //Déclaration des ressources
    char texte[2][2][50]={{"Confirmation de la selection", "Confirmation of selection"} , {"Joueur _ :","Player _ :"}};
    int value[3]={getCurseur(), 8, getCurseur()+1};
    int i;

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

        m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 383, 100, 617, 115, 395, 100, 605, 115); //fond du titre
        m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[0][0], 383, 100, texte[0][1], 395, 100);//titre

        //affiche tous les pseudos
        for(i=0; i<getNbPlayer()+getNbOrdi(); i++)
        {
            texte[1][0][7]=49+i;//change le numero du joueur
            texte[1][1][7]=49+i;
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 370, 240+i*60, 630, 255+i*60, 370, 240+i*60, 630, 255+i*60); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[1][0], 370, 240+i*60, texte[1][1], 370, 240+i*60);//titre

            if(i<getNbPlayer())
                m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), m_joueurs[i]->getNom(), 460, 240+i*60, m_joueurs[i]->getNom(), 460, 240+i*60);//pseudo du joueur humain
            else
                m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), m_joueurs[i]->getNom(), 460, 240+i*60, m_joueurs[i]->getNom(), 460, 240+i*60);//pseudo du joueur ordi
        }

        setCurseur(print_fleches(m_souris.getFront(0), value, true, true));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }
}

//saisie du pion des joueurs
void Hotel::saisir_pion(int page, int tab[6])
{
    //Declaration des ressources
    int value[3]={getCurseur(), getCurseur()-1, getCurseur()+1};
    string name[6]={"mario","luigi","gluigi","prof","ectochien","roi_boo"};
    int rang=page-15;
    int valid=-1, saisie;
    Pion p[6];

    //initialise les 6 pions
    for(int i=0; i<6; i++)
    {
        p[i].setName(name[i]);
        p[i].load_img_pion();
        p[i].load_sound_pion();
    }

    if(rang < getNbPlayer()+getNbOrdi()) //joueur devant saisir pion ?
    {
        //tant qu'on reste dans cette page
        while(page == getCurseur())
        {
            //affiche l'image de fond
            m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

            m_joueurs[rang]->saisir_pion(m_page, getLangue(), getLuminosite(), tab, p, rang, valid, m_souris.getFront(0));//saisie du pion du joueur

            //pion saisie ?
            saisie=0;
            for(int j=0; j<6; j++)//on verifie s'il a choisi un pion
            {
                if(tab[j]==rang)//pion saisi ?
                    saisie=1;//pion saisi !
            }

            if(rang < getNbPlayer())//joueur humain
            {
                setCurseur(print_fleches(m_souris.getFront(0), value, true, (valid!=-1 || saisie==1)));//affiche les fleches et chagne la page
                refresh_game();//reactualise l'ecran
            }
            else//ordi
                setCurseur(getCurseur()+1);//on change de page
        }

        //si on choisi un pion et qu'on decide d'avancer d'une page pour validation du choix
        if(valid!=-1 && getCurseur()==page+1)
        {
            m_joueurs[rang]->create_pion(name[valid]);//cree le pion
            tab[valid]=rang; //ce pion est pris !
        }
    }
    else//sinon c'est fini
    {
        setCurseur(getCurseur()+1);//on change de page
    }
}

//affiche le choix des pseudos et pions des joueurs
void Hotel::print_choix_pion(int page)
{
    //Déclaration des ressources
    char texte[3][2][60]={{"Confirmation de la selection", "Confirmation of selection"} , {"Lorsque vous validerez ces parametres, les comptes","When you validate these settings, the accounts"} , {"seront crees ou charges s'ils existent.","will be created or loaded if they exist."}};
    int posRecFr[4][4]={{383,100,617,115} , {300,180,705,195} , {300,210,705,225} , {20,300,140,420}};
    int posRecEn[3][4]={{395,100,605,115} , {316,180,689,195} , {316,210,689,225}};
    int value[3]={getCurseur(), getCurseur()-6, getCurseur()+1};

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0);

        for(int i=0; i<3; i++)//affichage du texte
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, posRecFr[i][0], posRecFr[i][1], posRecFr[i][2], posRecFr[i][3], posRecEn[i][0], posRecEn[i][1], posRecEn[i][2], posRecEn[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posRecFr[i][0], posRecFr[i][1], texte[i][1], posRecEn[i][0], posRecEn[i][1]);//texte
        }

        //affiche tous les pseudos avec leur pion
        for(int i=0; i<getNbPlayer()+getNbOrdi(); i++)
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, posRecFr[3][0]+333*i-(int(i/3))*999, posRecFr[3][1]+(int(i/3))*180, posRecFr[3][2]+333*i-(int(i/3))*999, posRecFr[3][3]+(int(i/3))*180, posRecFr[3][0]+333*i-(int(i/3))*999, posRecFr[3][1]+(int(i/3))*180, posRecFr[3][2]+333*i-(int(i/3))*999, posRecFr[3][3]+(int(i/3))*180); //rectangle du pion

            if(i<getNbPlayer())
            {
                m_alleg.luminosite(m_page, m_joueurs[i]->timer_logo(2), getLuminosite(), posRecFr[3][0]+333*i-(int(i/3))*999, posRecFr[3][1]+(int(i/3))*180);//affichage du logo
                m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180, 133+5+m_joueurs[i]->getDernier()*8+posRecFr[3][0]+333*i-(int(i/3))*999, 48+15+posRecFr[3][1]+(int(i/3))*180, 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180, 133+5+m_joueurs[i]->getDernier()*8+posRecFr[3][0]+333*i-(int(i/3))*999, 48+15+posRecFr[3][1]+(int(i/3))*180); //rectangle du pseudo
                m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), m_joueurs[i]->getNom(), 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180, m_joueurs[i]->getNom(), 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180);//pseudo du joueur humain
            }
            else
            {
                m_alleg.luminosite(m_page, m_joueurs[i]->timer_logo(2), getLuminosite(), posRecFr[3][0]+333*i-(int(i/3))*999, posRecFr[3][1]+(int(i/3))*180);//affichage du logo
                m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180, 133+5+m_joueurs[i]->getDernier()*8+posRecFr[3][0]+333*i-(int(i/3))*999, 48+15+posRecFr[3][1]+(int(i/3))*180, 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180, 133+5+m_joueurs[i]->getDernier()*8+posRecFr[3][0]+333*i-(int(i/3))*999, 48+15+posRecFr[3][1]+(int(i/3))*180); //rectangle du pseudo
                m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), m_joueurs[i]->getNom(), 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180, m_joueurs[i]->getNom(), 133+posRecFr[3][0]+333*i-(int(i/3))*999, 48+posRecFr[3][1]+(int(i/3))*180);//pseudo du joueur humain
            }
        }

        setCurseur(print_fleches(m_souris.getFront(0), value, true, true));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }
}

//permet le choix du niveau de difficulte
void Hotel::choix_difficulte(int page)
{
    //Déclaration des ressources
    char texte[4][2][50]={{"Choix du niveau de difficulte", "Choice of level of difficulty"} , {"Facile","Easy"} , {"Moyen","Medium"} , {"Difficile","Hard"}};
    int posRec[4][4]={{379,100,621,115} , {400,210,600,310} , {400,360,600,460} , {400,510,600,610}};
    int postxt[4][4]={{379,100,379,100} , {471,250,479,250} , {475,400,471,400} , {459,550,479,550}};
    int value[3]={getCurseur(), getCurseur(), getCurseur()+1}, tab[60];

    //reinitialise le niveau de difficulte
    setDiff(0);

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0); //affiche l'image de fond

        for(int i=0; i<4; i++) //affiche tous les textes
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), i!=0, (i==getDiff() && i!=0), posRec[i][0], posRec[i][1], posRec[i][2], posRec[i][3], posRec[i][0], posRec[i][1], posRec[i][2], posRec[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], postxt[i][0], postxt[i][1], texte[i][1], postxt[i][2], postxt[i][3]);//texte

            if(m_outils.verifclick(0, m_souris.getFront(0), 1, posRec[i][0], posRec[i][1], posRec[i][2], posRec[i][3], 0!=i) && 0!=i)//click gauche sur un rectangle de selection ?
                setDiff(i);//difficulte choisi !
        }

        setCurseur(print_fleches(m_souris.getFront(0), value, false, getDiff()!=0));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }

    //initialise les cases du plateau a partir du niveau de difficulte
    m_plat.init_cases(getDiff(), false, tab);
}

//permet la creation de l'enveloppe
void Hotel::creation_env(int page)
{
    //Déclaration des ressources
    char texte[3][2][60]={{"Creation de l'enveloppe", "Creation of the envelope"} , {"Cliquez sur les trois paquets pour placer une carte","Click on the three packages to put a card"} , {"piece, personnage et arme dans l'enveloppe.","location, character and weapon in the envelope."}};
    int posfr[3][4]={{403,90,597,105} , {291,140,709,155} , {323,170,677,185}};
    int poseng[3][4]={{399,90,601,105} , {331,140,669,155} , {307,170,693,185}};
    int value[3]={getCurseur(), getCurseur(), getCurseur()+1};
    bool retour[3]={false, false, false};
    Ppiece pieces;
    Parme armes;
    Pperso persos;

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0); //affiche l'image de fond

        pieces.display(m_page, getLuminosite(), 200, 220);//affiche les dos des cartes
        armes.display(m_page, getLuminosite(), 420, 220);//affiche les dos des cartes
        persos.display(m_page, getLuminosite(), 640, 220);//affiche les dos des cartes

        for(int i=0; i<3; i++) //affiche tous les textes et images
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, posfr[i][0], posfr[i][1], posfr[i][2], posfr[i][3], poseng[i][0], poseng[i][1], poseng[i][2], poseng[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posfr[i][0], posfr[i][1], texte[i][1], poseng[i][0], poseng[i][1]);//texte

            if(m_outils.verifclick(0, m_souris.getFront(0), 1, 200+220*i, 220, 360+220*i, 449, false==retour[i]))//click gauche sur un dos de paquet de carte ?
                retour[i]=true;//carte mise dans l'enveloppe
        }

        m_plat.display_env(m_page, getLuminosite(), 1, 175, 470);//Affiche l'enveloppe (fond)

        if(true == retour[0])//carte mise dans l'enveloppe .
            pieces.display(m_page, getLuminosite(), 250, 557);//affiche les dos des cartes +75 + 87
        if(true == retour[1])//carte mise dans l'enveloppe .
            armes.display(m_page, getLuminosite(), 410, 557);//affiche les dos des cartes +75 + 87
        if(true == retour[2])//carte mise dans l'enveloppe .
            persos.display(m_page, getLuminosite(), 570, 557);//affiche les dos des cartes +75 + 87

        m_plat.display_env(m_page, getLuminosite(), 2, 175, 470);//Affiche l'enveloppe (couche)

        setCurseur(print_fleches(m_souris.getFront(0), value, false, ((true == retour[0]) && (true == retour[1]) && (true == retour[2]))));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }

    //creation de l'enveloppe
    m_plat.init_cards(pieces, persos, armes);
}

//permet la distribution des cartes
void Hotel::distribution_cartes(int page)
{
    //Déclaration des ressources
    char texte[2][2][60]={{"Distribution des cartes", "Distribution of cards"} , {"Cliquez sur le paquet pour distribuer les cartes.","Click on the package to distribute the cards."}};
    int posfr[2][4]={{403,90,597,105} , {299,140,701,155}};
    int poseng[2][4]={{411,90,589,105} , {315,140,675,155}};
    int value[3]={getCurseur(), getCurseur(), getCurseur()+1};
    unsigned int reste=18%(getNbPlayer()+getNbOrdi());
    int maxi=18-reste;
    int posee=0;

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0); //affiche l'image de fond

        for(int i=0; i<2; i++) //affiche tous les textes
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), false, false, posfr[i][0], posfr[i][1], posfr[i][2], posfr[i][3], poseng[i][0], poseng[i][1], poseng[i][2], poseng[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posfr[i][0], posfr[i][1], texte[i][1], poseng[i][0], poseng[i][1]);//texte
        }

        if(posee!=maxi)//si on n'a pas pose toutes les cartes
            m_plat.display_dos_carte(m_page, getLuminosite(), 420, 200); //affiche le dos du paquet de cartes melanges
        else//lorsque tous les joueurs ont le meme nombre de cartes, les restantes sont retournées
        {
            for(unsigned int i=0; i<m_plat.getNbCards(); i++)
                m_plat.display_img_carte(m_page, getLuminosite(), i, 503-m_plat.getNbCards()*83+165*i, 200);
        }

        if(m_outils.verifclick(0, m_souris.getFront(0), 1, 420, 200, 580, 429, posee!=maxi) && (posee != maxi))//click gauche sur le dos de paquet de carte et paquet non fini ? ?
            m_plat.distribution_cards(m_joueurs, getNbPlayer(), getNbOrdi(), posee);//distribution d'une carte en plus

        //affichage des cartes distribuees
        for(int i=0; i<getNbPlayer()+getNbOrdi(); i++)//affiche celles des joueurs
        {
            for(unsigned j=0; j<m_joueurs[i]->getNbCards(); j++)//affiche tous les dos de cartes d'un joueur
                m_joueurs[i]->affiche_dos(m_page, getLuminosite(), j, 5+i*165, 500+j*40);
        }

        setCurseur(print_fleches(m_souris.getFront(0), value, false, posee==maxi));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }
}

//permet l'affichage des cartes de chaque joueur
void Hotel::print_choix_carte(int page)
{
    //Déclaration des ressources
    int rang=page-25;
    int value[3]={getCurseur(), getCurseur(), getCurseur()+1};
    bool affiche[6]={false, false, false, false, false, false};
    unsigned int nbretour=0;

    //si c'est un joueur humain, il visionne ces cartes
    if(rang < getNbPlayer())
    {
        //tant qu'on reste dans cette page
        while(page == getCurseur())
        {
            m_alleg.luminosite(m_page, m_fond[2], getLuminosite(), 0, 0); //affiche l'image de fond

            m_joueurs[rang]->retourner_cartes(m_page, getLangue(), getLuminosite(), affiche, nbretour, m_souris.getFront(0));//le joueur retourne ses cartes

            setCurseur(print_fleches(m_souris.getFront(0), value, false, nbretour==m_joueurs[rang]->getNbCards()));//affiche les fleches et chagne la page
            refresh_game();//reactualise l'ecran
        }
    }
    else//sinon on avance
    {
        setCurseur(getCurseur()+1);//on avance d'une page
    }

    //arrete la muqie de demarrage
    m_music.stop_demarrage();
    //reinitialise le chrono
    m_plat.initChrono();
    //reinitialise le plateau
    m_plat.reinit();
    //charge les status des joueurs
    demarrage_load_statut();
}

//les joueurs jouent
void Hotel::time_to_play(int page)
{
    //Declaration des ressources 21 23
    char txt[3][2][25]={{"Voulez-vous rejouer ?","Do you want to replay ?"},{"Oui","Yes"},{"Non","No"}};
    int rectxt[3][4]={{400,200,600,215}, {400,400,600,455}, {400,500,600,555}};
    int postxt[3][4]={{411,200,403,200}, {483,420,483,420}, {483,520,487,520}};
    int hyp[3], turn[4];

    //lance la musique de la partie
    m_music.play_partie(getSon());

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        m_alleg.luminosite(m_page, m_fond[0], getLuminosite(), 0, 0); //affiche l'image de fond

        if(m_plat.getTour()<getNbPlayer())//joueur humain ?
            m_joueurs[m_plat.getTour()]->display_enq(m_page, getLangue(), getLuminosite(), m_plat.getState());//affichage de la feuille d'enquete

        m_plat.time_to_play(m_page, getLangue(), getLuminosite(), m_joueurs, getNbPlayer(), getNbOrdi(), m_souris.getFront(0), hyp, turn);//affichages et physique du plateau

        display_enquete();//affiche la feuille d'enquete

        //collision le bloc de menu pause et aucune autre fenetre ouverte ?
        if(m_outils.verifclick(0, m_souris.getFront(0), 1, 20, 680, 110, 770, (0 == m_plat.getState())) && (0 == m_plat.getState()))
            setCurseur(getCurseur()+1);//on accede au menu pause

        if(turn[0]==100)
        {
            m_music.stop_partie();//arrete la musique de la partie
            m_music.play_victoire(getSon());//lance la musique de victoire
            turn[0]=101;
        }
        else if(turn[0]==102)
        {
            m_music.stop_victoire();//on arrete la musique
            turn[0]=103;//on va sauvegarder les stats des joueurs
        }
        else if(turn[0]==103)
        {
            for(int i=0; i<getNbPlayer(); i++)
            {
                m_joueurs[i]->setPjouees(m_joueurs[i]->getPjouees()+1);//tous les joueurs ont joue une partie de plus
                m_joueurs[i]->reecrit_statut();//reecrit le statut du joueur
            }

            save_all_statut();//sauvegarde des statuts des joueurs
            turn[0]=104;//on va demander aux joueurs s'ils veulent rejouer ou non
        }
        else if(turn[0]==104)
        {
            for(int i=0; i<3; i++) //affiche tous les textes
            {
                m_alleg.rectfont(m_page, getLangue(), getLuminosite(), i>0, false, rectxt[i][0], rectxt[i][1], rectxt[i][2], rectxt[i][3], rectxt[i][0], rectxt[i][1], rectxt[i][2], rectxt[i][3]); //fond du texte
                m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), txt[i][0], postxt[i][0], postxt[i][1], txt[i][1], postxt[i][2], postxt[i][3]);//texte

                if(i>0)
                {
                    if(m_outils.verifclick(0, m_souris.getFront(0), 1, rectxt[i][0], rectxt[i][1], rectxt[i][2], rectxt[i][3], 1))//click gauche sur un rectangle
                    {
                        if(i==2)//click gauche sur non ?
                            setCurseur(0);//retour a l'ecran titre
                        else//sinon click gauche sur oui
                        {
                            turn[0]=restart();//rejoue en changeant les cartes des joueurs et enveloppe (+reinitialisations)
                        }
                    }
                }
            }
        }

        refresh_game();//reactualise l'ecran
    }

    //arrete la musique de la partie
    m_music.stop_partie();
}

//rejoue une partie
int Hotel::restart()
{
    //declaration des ressoruces
    Ppiece pieces;
    Parme armes;
    Pperso persos;
    int posee=0, maxi=18-18%(getNbPlayer()+getNbOrdi());//aucune carte distribuée

    //reinitialisation de tous les joueurs
    for(int i=0; i<getNbOrdi()+getNbPlayer(); i++)
    {
        m_joueurs[i]->reinit();
    }

    m_music.stop_victoire();//arrete la muqie de victoire
    m_music.play_partie(getSon());//lance la musique de la partie
    m_plat.initChrono();//reinitialise le chrono
    m_plat.reinit();//reinitialise le plateau

    //creation de l'enveloppe
    m_plat.init_cards(pieces, persos, armes);

    while(posee!=maxi)//distribution des cartes
        m_plat.distribution_cards(m_joueurs, getNbPlayer(), getNbOrdi(), posee);//distribution d'une carte en plus

    return 0;//reussite
}

//affiche la feuille d'enquete d'un joueur
void Hotel::display_enquete()
{
    //click gauche sur la feuille d'enquete ?
    if(m_outils.verifclick(0, m_souris.getFront(0), 1, 24, 492, 106, 590, (0==m_plat.getState() || 2==m_plat.getState()) && (m_plat.getTour()<getNbPlayer())) && (0==m_plat.getState() || 2==m_plat.getState()) && (m_plat.getTour()<getNbPlayer()))
        m_plat.setState(2-m_plat.getState());

    if(2==m_plat.getState() && m_plat.getTour()<getNbOrdi() && getNbPlayer()<=m_plat.getTour())//si c'est un ordi
        m_plat.setState(0);//cache sa feuille d'enquete

    //affichage d'un joueur humain ?
    if(m_plat.getTour()<getNbPlayer())
    {
        if(2 == m_plat.getState())//affichage de la feuille d'enquete ?
        {
            for(int x=0; x<6; x++)//click gauche sur un rectngle de l'enquete ?
            {
                for(int y=0; y<21; y++)
                {
                    if(m_outils.verifclick(0, m_souris.getFront(0), 1, 430+x*50, 150+y*25, 480+x*50, 175+y*25, 1))//click gauche sur rectangle ?
                        m_joueurs[m_plat.getTour()]->setTab(x, y, 1-m_joueurs[m_plat.getTour()]->getTab(x, y));//changement de la valeur de la case
                }
            }
        }
    }
}

//le menu pause
void Hotel::menu_pause(int page)
{
    //Déclaration des ressources
    char texte[7][2][50]={{"Menu pause", "Pause menu"},{"Sauvegarder la partie","Save the game"},{"Regles du jeu","Rules of the game"},{"Voir la collection","See the collection"},{"Statistiques", "Statistics"},{"Parametres", "Parameters"},{"Retourner a l'ecran titre","Return to the main menu"}};
    int posRec[7][4]= {{455,80,545,95} , {380,160,620,235} , {380,260,620,335} , {380,360,620,435} , {380,460,620,535} , {380,560,620,635} , {380,660,620,735}};
    int posTexte[7][4]={{455,80,455,80} , {413,190,443,190} , {443,290,427,290} , {423,390,423,390}, {447,490,455,490} , {460,590,460,590} , {395,690,403,690}};
    int value[3]={getCurseur(), getCurseur()-1, getCurseur()+1};

    //lance la musique du menu pause
    m_music.play_menu_pause(getSon());

    //tant qu'on reste dans cette page
    while(page == getCurseur())
    {
        //affiche l'image de fond
        m_alleg.luminosite(m_page, m_fond[4], getLuminosite(), 0, 0);

        //affiche du texte et leur font et click gauche
        for(int i=0; i<7; i++)
        {
            m_alleg.rectfont(m_page, getLangue(), getLuminosite(), i!=0, false, posRec[i][0], posRec[i][1], posRec[i][2], posRec[i][3], posRec[i][0], posRec[i][1], posRec[i][2], posRec[i][3]); //fond du texte
            m_alleg.txtlangue(m_page, getLangue(), getLuminosite(), texte[i][0], posTexte[i][0], posTexte[i][1], texte[i][1], posTexte[i][2], posTexte[i][3]);//texte
            if(m_outils.verifclick(0, m_souris.getFront(0), 1, posRec[i][0], posRec[i][1], posRec[i][2], posRec[i][3], i!=0) && i!=0)//click gauche (front montant) sur un rectangle autre que le texte menu principal
            {
                setCurseur(page+i);//on change de page
                if(i==6)//si on retourne a l'ecran titre
                    setCurseur(0);//page de l'ecran titre
                value[0]=getCurseur();//reactualise la nouvelle page de destination
            }
        }

        setCurseur(print_fleches(m_souris.getFront(0), value, true, false));//affiche les fleches et chagne la page
        refresh_game();//reactualise l'ecran
    }

    //arrete la musique du menu pause
    m_music.stop_menu_pause();
    if(page-1 == getCurseur())//si on retourne sur l'ecran de partie
        m_music.play_partie(getSon());//on lance la musique de la partie
}

//rafraichit l'ecran
void Hotel::refresh_game()
{
    //gère le click gauche et droite de la souris
    for(int i=1; i<3; i++)
        m_souris.gere_souris(i);

    //gere l'appui sur echap
    if(key[KEY_ESC])//on sort du jeu
        setCurseur(-1);

    //affiche la souris
    m_souris.display(m_page, getLuminosite());
    //affiche le tout
    m_alleg.myblit(m_page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    //pause de 10ms
    m_alleg.myrest(10);
}

//sauvegarde tous les statuts
void Hotel::save_all_statut()
{
    //Déclaration des ressources
    vector<Compte> all_statut;

    //charge les joueurs du fichier pour ne pas perdre les donnees
    load_all_statut(all_statut,0);

    //ouvre un fichier
    ofstream file("save/statistiques.txt");

    //existence du fichier ?
    if(!file)
    {
        //message erreur
        m_alleg.myallegro_message("Erreur d'ouverture du fichier !");
        m_alleg.myallegro_message("save/statistiques.txt");
    }
    else
    {
        //parcours du tableau charge pour voir si un joueur existe deja
        for(unsigned int i=0; i<all_statut.size(); i++)
        {
            //parcours du tableau des joueurs actuels
            for(int j=0; j<getNbPlayer(); j++)
            {
                //meme pseudo ?
                if(1 == m_alleg.verifpseudo(all_statut[i].getNom(), m_joueurs[j]->getNom()))
                {
                    //les anciennes donnees sont ecrasees
                    all_statut.erase(all_statut.begin()+i);
                }
            }
        }

        for(int j=0; j<getNbPlayer(); j++)
            all_statut.push_back(m_joueurs[j]->getCompte());//ajout du joueur dans le tableau chargee

        //sauvegarde des joueurs
        file << all_statut.size(); //sauvegarde du nombre de personnes sauvegardees
        file << endl;
        for(unsigned int i=0; i<all_statut.size(); i++)
        {
            all_statut[i].save_one_statut(file);//sauvegarde de tous les joueurs
        }

        //fermeture du fichier
        file.close();
        //message de reussite
        m_alleg.myallegro_message("La sauvegarde des statuts des joueurs est un succes !");
    }
}

//charge tous les statuts pour le demarrage
void Hotel::demarrage_load_statut()
{
    //Déclaration des ressources
    vector<Compte> all_statut;

    //charge les joueurs du fichier pour ne pas perdre les donnees
    load_all_statut(all_statut,0);

    //parcours du tableau charge pour voir si un joueur existe deja
    for(unsigned int i=0; i<all_statut.size(); i++)
    {
        //parcours du tableau des joueurs actuels
        for(int j=0; j<getNbPlayer(); j++)
        {
            //meme pseudo ?
            if(1 == m_alleg.verifpseudo(all_statut[i].getNom(), m_joueurs[j]->getNom()))
            {
                //copie des valeurs !
                m_joueurs[j]->setStatut(all_statut[i].getStatut());
                m_joueurs[j]->setPjouees(all_statut[i].getPjouees());
                m_joueurs[j]->setPgagnees(all_statut[i].getPgagnees());
            }
        }
    }
}

//verifie si un pseudo n'a pas deja ete saisi
int Hotel::verifpseudo(int rang)
{
    //Déclaration des ressources
    int taille=0;
    int presence=0;//on verifie si ce pseudo a ete deja saisi

    if(m_joueurs[rang]->getDernier() != 0)//on verfie si on a bien saisie une chaine
    {
        for(int i=0; i<getNbPlayer(); i++)//on regarde les pseudos saisis
        {
            if((m_joueurs[i]->getDernier() == m_joueurs[rang]->getDernier()) && (i != rang))//meme taille et different joueur ?
            {
                for(int j=0; j<m_joueurs[i]->getDernier(); j++)//parcours de tous les caracteres des pseudos
                {
                    if((m_joueurs[i]->getNom())[j] == (m_joueurs[rang]->getNom())[j])//meme caractere ?
                    {
                        taille++;//1 caractere en commun en plus
                        if(taille == m_joueurs[i]->getDernier())//meme taille ?
                            presence=1;//ce pseudo a deja ete saisi !
                    }
                }
                taille=0; //reset de la taille
            }
        }
    }
    //retourne le resultat
    return presence;
}

//charge tous les statuts
void Hotel::load_all_statut(vector<Compte> &tab, bool afficher)
{
    //Déclaration des ressources
    ifstream file("save/statistiques.txt");
    string receveur="";
    int maxi=0, i=-1;

    //existence du fichier ?
    if(!file)
    {
        //message erreur si on demande de l'afficher
        if(afficher)
        {
            m_alleg.myallegro_message("Erreur d'ouverture du fichier !");
            m_alleg.myallegro_message("save/statistiques.txt");
        }
    }
    else
    {
        file >> receveur; //lit le nombre de personnes a charger
        maxi=stoi(receveur); //converti le texte en nombre entier

        for(i=0; i<maxi; i++)//charge toutes les personnes
            tab.push_back(create_personne(file, receveur));//ajoute une personne

        file.close();//fermeture du fichier
    }
}

//cree une personne
Compte Hotel::create_personne(ifstream &file, string &receveur)
{
    Compte p;//Déclaration des ressources
    p.load_one_statut(file, receveur);//charge une persone
    return p;//retourne la personne
}

//cree une personne
Compte Hotel::create_personne(string _nom, string _statut, int _p_jouees, int _p_gagnees)
{
    Compte p(_nom, _statut, _p_jouees, _p_gagnees);//Déclaration des ressources
    return p;//retourne la personne
}

//crée un joueur
void Hotel::create_player()
{
    Abstract_Joueur *p = new Player();//Déclaration des ressources : creation du joueur
    m_joueurs.push_back(p);//ajout du joueur dans le tableau dynamique
}

//crée un ordi
void Hotel::create_ordi()
{
    Abstract_Joueur *o = new Ordi();//Déclaration des ressources : creation de l'ordinateur
    m_joueurs.push_back(o);//ajout de l'ordinateur dans le tableau dynamique
}

//sauvegarde la partie
void Hotel::save_game()
{
    //Declaration des ressources
    ofstream file("save/game.txt");//ouverture du fichier en ecriture

    //existence du fichier ?
    if(!file)
    {
        //message erreur
        m_alleg.myallegro_message("Erreur d'ouverture du fichier de sauvegarde...");
    }
    else
    {
        //sauvegarde tout
        file << int(getLangue()) << endl << getLuminosite() << endl << getSon() << endl << getCurseur() << endl << getNbPlayer() << endl << getNbOrdi() << endl << getDiff() << endl;

        m_souris.save(file);//sauvegarde la souris
        m_plat.save(file);//sauvegarde le plateau

        //sauvegarde les joueurs
        for(int i=0; i<getNbPlayer()+getNbOrdi(); i++)
            m_joueurs[i]->save_one_joueur(file);

        m_alleg.myallegro_message("La sauvegarde des donnees est un succes !");//message de reussite
        file.close();//fermeture du fichier
    }

    setCurseur(32);//retour au menu pause
}

//charge la partie
void Hotel::load_game()
{
    //Declaration des ressources
    ifstream file("save/game.txt");//ouverture du fichier en ecriture
    string receveur="";
    int numero;

    //existence du fichier ?
    if(!file)
    {
        //message erreur
        m_alleg.myallegro_message("Erreur d'ouverture du fichier de sauvegarde...");

        setCurseur(1);//retour au menu principal
    }
    else
    {
        //charge tout
        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setLangue(numero);    //ecriture de la donnee

        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setLuminosite(numero);    //ecriture de la donnee

        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setSon(numero);    //ecriture de la donnee

        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setCurseur(numero);    //ecriture de la donnee

        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setNbPlayer(numero);    //ecriture de la donnee

        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setNbOrdi(numero);    //ecriture de la donnee

        file >> receveur;      //chargement
        numero=stoi(receveur); //convertion str en int
        setDiff(numero);    //ecriture de la donnee

        m_souris.load(file, receveur);//sauvegarde la souris
        m_plat.load(file, receveur, getDiff());//sauvegarde le plateau

        //creation des joueurs : on remplit les vecteurs de players et d'ordis
        for(int i=0; i<getNbPlayer(); i++)
        {
            create_player();//creation d'un joueur
            m_joueurs[i]->load_one_joueur(file, receveur);//charge le joueur
        }

        for(int i=getNbPlayer(); i<getNbPlayer()+getNbOrdi(); i++)
        {
            create_ordi();//creation d'un ordi
            m_joueurs[i]->load_one_joueur(file, receveur);//charge le joueur
        }

        m_alleg.myallegro_message("Le chargement des donnees un succes !");//message de reussite
        file.close();//fermeture du fichier

        setCurseur(31);//on se dirige directement vers la partie lancee
    }
}

/// Accesseur
// Getter
bool Hotel :: getLangue()const { return m_langue; }
int Hotel :: getLuminosite()const { return m_luminosite; }
int Hotel :: getSon() const { return m_son; }
int Hotel :: getCurseur() const { return m_curseur; }
int Hotel :: getNbPlayer() const{ return m_nb_players; }
int Hotel :: getNbOrdi() const{ return m_nb_ordis; }
int Hotel :: getDiff() const{ return m_diff; }
Souris Hotel :: getSouris() const{ return m_souris; }

// Setter
void Hotel :: setLangue(bool language) { m_langue=language; }
void Hotel :: setLuminosite(int lux) { m_luminosite = lux; }
void Hotel :: setSon(int son) { m_son=son; }
void Hotel :: setCurseur(int curseur) { m_curseur=curseur; }
void Hotel :: setNbPlayer(int nb){ m_nb_players=nb; }
void Hotel :: setNbOrdi(int nb){ m_nb_ordis=nb; }
void Hotel :: setDiff(int diff){ m_diff=diff; }
