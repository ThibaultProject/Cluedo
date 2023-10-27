#include "allegfct.h"

//constructeur et destructeur
//constructeur par defaut
Allegfct::Allegfct(){}

//destructeur
Allegfct::~Allegfct(){}

//cree un bitmap
BITMAP *Allegfct::mycreate_bitmap(int width, int height)
{
    return create_bitmap(width, height);
}

//effacer un bitmap
void Allegfct::myclear_to_color(BITMAP *&bitmap, int color)
{
    clear_to_color(bitmap, color);
}

//sortir d'allegro
void Allegfct::myallegro_exit()
{
    allegro_exit();
}

//sortie avec erreur
void Allegfct::myexit()
{
    exit(EXIT_FAILURE);
}

//message allegro
void Allegfct::myallegro_message(const char* message)
{
    allegro_message(message);
}

//afficher une image
void Allegfct::myblit(BITMAP *source, BITMAP *&dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height)
{
    blit(source, dest, source_x, source_y, dest_x, dest_y, width, height);
}

//pause pendant un temps donne
void Allegfct::myrest(unsigned int tyme)
{
    rest(tyme);
}

//dessine l'interieur dun rectangle
void Allegfct::myrectfill(BITMAP *&dest, int x1, int y1, int x2, int y2, int red, int green, int blue)
{
    rectfill(dest, x1, y1, x2, y2, makecol(red, green, blue));
}

//dessine les contours d'un rectangle
void Allegfct::myrect(BITMAP *&dest, int x1, int y1, int x2, int y2, int red, int green, int blue)
{
    rect(dest, x1, y1, x2, y2, makecol(red, green, blue));
}

//detruit musique
void Allegfct::mydestroy_sample(SAMPLE *&s)
{
    try{
        myplay_sample(s, 0, 0, 0, 0);
        mystop_sample(s);

        if(!s)//si la musique n'existe pas
            throw string("Destruction d'une musique inexistante");
        destroy_sample(s);//destruction de la musique
    }
    catch(string e){
        cerr << e << endl;//message erreur
    }

}

//detruit image
void Allegfct::mydestroy_bitmap(BITMAP *&s)
{
    try{
        if(!s->w)//si l'image n'existe pas
            throw string("Destruction d'une musique inexistante");
        destroy_bitmap(s);//destruction de l'image
    }
    catch(string e){
        cerr << e << endl;//message erreur
    }
}

//ecrire du texte
void Allegfct::mytextout_ex(BITMAP *&page, FONT *font, char *txtfr, int xfr, int yfr, int color)
{
    textout_ex(page, font, txtfr, xfr, yfr, color, -1);
}

//jouer une musique
void Allegfct::myplay_sample(const SAMPLE* spl, int vol, int pan, int freq, int loop)
{
    play_sample(spl, vol, pan, freq, loop);
}

//arreter une musique
void Allegfct::mystop_sample(const SAMPLE* spl)
{
    stop_sample(spl);
}

//modifie la taille d'une image
void Allegfct::mystretch_sprite(BITMAP *&arrivee, BITMAP *depart, int x, int y, int w, int h)
{
    stretch_sprite(arrivee, depart, x, y, w, h);
}

//charge une musique
void Allegfct::load_one_sound(SAMPLE *&musique, char *chemin)
{
    //charge la musique
    musique=load_wav(chemin);

    ///existence de la musique ?
    if (!musique)
    {
        //blindage
        myallegro_message("musique non trouve");//message erreur
        myallegro_message(chemin);//suite du message erreur : affichage du chemin ou se produit l'erreur
        myallegro_exit();//on quitte allegro
        //on sort du programme
        myexit();
    }
}

//charge une image
BITMAP *Allegfct::load_img(char *chemin)
{
    //Déclaration des ressources
    BITMAP *img;

    //charge l'image
    img=load_bitmap(chemin, NULL);

    ///existence de l'image ?
    if(NULL == img)
    {
        myallegro_message("Erreur de chargement d'une image !");//message erreur
        myallegro_message(chemin);
        myallegro_exit();                                       //on quitte allegro
        myexit();                                               //on sort du programme
    }
    return img; //on retourne l'image
}

//cree la page d'affichage
void Allegfct::create_page(BITMAP *&page, int x, int y, int color)
{
    //Declaration des ressources
    Allegfct alleg;

    //creation du buffer
    page=alleg.mycreate_bitmap(x, y);

    ///existence du buffer ?
    if(NULL == page)
    {
        alleg.myallegro_message("Erreur de creation de double buffer !"); //message erreur
        alleg.myallegro_exit(); //on sort d'allegro
        alleg.myexit(); //on sort du programme
    }

    //on met tout à 0
    alleg.myclear_to_color(page, color);
}

//permet de modifier la luminosité d'une image
void Allegfct::luminosite(BITMAP *&page, BITMAP *const&picture, int lumin, int posex, int posey)
{
    //Déclaration des ressources
    int x, y, color, red, green, blue;

    //on parcours l'image pour l'afficher avec assombrissement
    for(y=0; y<picture->h; y++)
    {
        for(x=0; x<picture->w; x++)
        {
            //on récolte les couleurs du pixel
            color=getpixel(picture, x, y);

            //si ce n'est pas la couleur de transparence(255, 0, 255) et qu'on dans l'ecran, on affiche
            if(((255 != getr(color)) || (0 != getg(color)) || (255 != getb(color))) &&((0 <= posex+x) && (SCREEN_W >= posex+x) && (0 <= posey+y) && (SCREEN_H >= posey+y)))
            {
                //changement de couleur : assombrissement
                //composante rouge
                red=getr(color)+lumin;
                change_rvb(red);

                //composante verte
                green=getg(color)+lumin;
                change_rvb(green);

                //composante bleue dans l'intervalle
                blue=getb(color)+lumin;
                change_rvb(blue);

                //on affiche la couleur correspondante
                putpixel(page, posex+x, posey+y, makecol(red, green, blue));
            }
        }
    }
}

//couleur doit etre entre 0 et 255
void Allegfct::change_rvb(int &color)
{
    //minimum 0
    if (0 > color)
        color=0;
    //maximum 255
    else if (255 < color)
        color=255;
}

//converti string en char*
void Allegfct::myStrToChar(char txt[100], string str)
{
    //conversion : copie du str dans char*
    for(unsigned int i=0; i<str.size()+1; i++)
        txt[i]=str[i];
}

//converti char* en string
void Allegfct::myCharToStr(string &str, char txt[100])
{
    //Declaration des ressources
    int i;

    //conversion : copie du char* dans str
    for(i=0; txt[i]!='\0'; i++)
        str[i]=txt[i];

    str[i]='\0';//caractere de fin de mot
}

//verifie si un nom n'a pas deja ete saisi
int Allegfct::verifpseudo(char *txt1, char *txt2)
{
    //Déclaration des ressources
    int taille=0;
    int presence=0;//on verifie si ce pseudo a ete deja saisi

    for(int j=0; txt1[j]!='\0'; j++)//parcours de tous les caracteres du premier texte
    {
        if(txt1[j] == txt2[j])//meme caractere ?
        {
            taille++;//1 caractere en commun en plus
            if((taille == j+1) && (txt1[j+1]=='\0') && (txt2[j+1]=='\0'))//meme taille ?
            {
                presence=1;//ce pseudo a deja ete saisi !
            }
        }
    }

    //retourne le resultat
    return presence;
}

//permet d'afficher le texte correspondant au chois de la langue
void Allegfct::txtlangue(BITMAP *&page, int langue, int lumin, char *txtfr, int xfr, int yfr, char *txteng, int xeng, int yeng)
{
    //Déclaration des ressources
    int c=colorcte(lumin, 150);
    int color=makecol(c, c, c);

    //0 : texte en français
    if(0 == langue)
    {
        mytextout_ex(page, font, txtfr, xfr+5, yfr+5, color);//texte
    }
    //1 : anglais
    else
    {
        mytextout_ex(page, font, txteng, xeng+5, yeng+5, color);//texte
    }
}

//permet de calculer la luminosité d'un texte et de son rectangle, dont l'écart reste le même (max 255)
int Allegfct::colorcte(int lumin, int color)
{
    //on retourne le résultat
    return color+(lumin)*(1-(lumin+100)/125);
}

//contour ou rectangle plein en fonction de la souris et de la demande
void Allegfct::drawrect(BITMAP *&page, int lumin, bool demande, bool force, int x1, int y1, int x2, int y2)
{
    //Déclaration des ressources
    int cte=colorcte(lumin, 0);
    int color=230+cte;

    //si la souris est en collision avec le rectangle ou si on force l'affichage, on affiche le rectangle plein
    if(((1 == collimouse(x1, y1, x2, y2)) && (true == demande)) || (true == force))
        color=190+cte;

    myrectfill(page, x1, y1, x2, y2, color, color, color);//contour du ectangle
    myrect(page, x1, y1, x2, y2, 190+cte, 190+cte, 190+cte);//interieur du rectangle
}

//rectangle de position differentes en fonction de la langue
void Allegfct::rectfont(BITMAP *&page, int langue, int lumin, bool demande, bool force, int xf1, int yf1, int xf2, int yf2, int xe1, int ye1, int xe2, int ye2)
{
    //0 : texte en français
    if(0 == langue)
    {
        drawrect(page, lumin, demande, force, xf1, yf1, xf2, yf2);//rectangle de fond
    }
    //1 : anglais
    else
    {
        drawrect(page, lumin, demande, force, xe1, ye1, xe2, ye2);//rectangle de fond
    }
}

//permet d'observer une collision de la souris avec un rectangle 0:non 1:oui
int Allegfct::collimouse(int x1, int y1, int x2, int y2)
{
    //collision ?
    if((getMouseX()>=x1) && (getMouseX()<x2) && (getMouseY()>=y1) && (getMouseY()<y2))
    {
        return 1;//presence de collision
    }
    else
    {
        return 0;//absence de collision
    }
}

/*template <typename T>
//echange deux valeurs
void Allegfct::echange(T &a, T &b)
{
    //Declaration des ressources
    T c;

    //echange
    c=a;
    a=b;
    b=c;
}*/

//getter
int Allegfct::getMouseX() const{ return mouse_x; }
int Allegfct::getMouseY() const{return mouse_y; }
int Allegfct::getSCREEN_W() const{ return SCREEN_W; }
int Allegfct::getSCREEN_H() const{ return SCREEN_H; }
