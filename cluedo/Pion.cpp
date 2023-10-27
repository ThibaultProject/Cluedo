#include "Pion.h"

//constructeur et destructeur
//constructeur par defaut
Pion::Pion(){}

//constructeur surcharge
Pion::Pion(string _name):m_name(_name)
{
    load_img_pion();//charge les images du pion
    load_sound_pion();//charge le son du pion
    init_depart();//initialise le depart du pion
}

//destructeur
Pion::~Pion(){
    //detruit les images
    for(unsigned int j=0; j<m_img_pion.size(); j++)
    {
        m_alleg.mydestroy_bitmap(m_img_pion[j]);
    }
    m_alleg.mydestroy_sample(m_sound);
}

//charge le son du pion
void Pion::load_sound_pion()
{
    //Declaration des ressources
    char chemin[100];
    string txt="musiques/pions/"+m_name+".WAV";

    //conversion : str en char*
    m_alleg.myStrToChar(chemin, txt);

    //charge le son
    m_alleg.load_one_sound(m_sound, chemin);
}

//charge les images
void Pion::load_img_pion()
{
    //chaque pion a un nombre d'images differents
    if("ectochien" == getName())//si c'est l'ectochien
        setMax(6);//max de 6 images
    else if("roi_boo" == getName())//si c'es le roi boo
        setMax(7);//max de 7 images
    else if(("mario" == getName()) || ("luigi" == getName()) || ("gluigi" == getName()) || ("prof" == getName()))//si c'est un autre pion existant
        setMax(3);//max de 3 images
    else//sinon
        setMax(0);//0 images

    //on s"assure que les tableaux d'images est vide
    while(m_img_pion.empty() == 0)
    {
        m_alleg.mydestroy_bitmap(m_img_pion[m_img_pion.size()-1]);//detruit les images des pions
        m_img_pion.pop_back();
    }
    while(m_img_logo.empty() == 0)
    {
        m_alleg.mydestroy_bitmap(m_img_logo[m_img_logo.size()-1]);//detruit les images des logos
        m_img_logo.pop_back();
    }

    //charge les images
    for(int i=0; i<getMax(); i++)
    {
        m_img_pion.push_back(charge_pion(i));
    }
}

//initialise le depart du pion
void Pion::init_depart()
{
    //initialise le depart en fonction du nom du pion
    if("ectochien" == getName())
        setDepart(9,0);
    else if("roi_boo" == getName())
        setDepart(14,0);
    else if("mario" == getName())
        setDepart(23,19);
    else if("luigi" == getName())
        setDepart(23,6);
    else if("gluigi" == getName())
        setDepart(7,24);
    else if("prof" == getName())
        setDepart(0,17);
    else
        setDepart(0,0);

    //initialise la place actuelle du pion
    setPoseX(m_depart[0]);
    setPoseY(m_depart[1]);
}

//charge une bitmap et la retourne
BITMAP *Pion :: charge_pion(int i)
{
    //declaration des ressources
    string txt="images/animations/";
    BITMAP *image, *img_grand;
    char chemin[50];
    unsigned int j;

    //ecriture du chemin
    for(unsigned int j=0; j<getName().size(); j++)
        txt += getName()[j];

    txt+="/";//suite du chemin
    txt+=to_string(i+1);//rang de l'image
    txt+=".bmp";//format de l'image

    //conversion string en char*
    for(j=0; j<txt.size(); j++)
        chemin[j] = txt[j];
    chemin[j]='\0';//fin du chemin

    image=m_alleg.load_img(chemin);//chargement de l'image

    m_alleg.create_page(img_grand, 120, 120, makecol(255,0,255));//cree le double buffer
    m_alleg.mystretch_sprite(img_grand, image, 0, 0, 120, 120);//agrandissement de l'image !
    m_img_logo.push_back(img_grand); //ajout de l'image grande

    //retourne l'image petite
    return image;
}

//lance l'effet sonore
void Pion::effet_sonore()
{
    m_alleg.myplay_sample(m_sound, 255, 128, 1000, 0);//son
}

//affiche un pion sur le plateau
void Pion::affiche_pion(BITMAP *&page, int lumin)
{
    //D"claration des ressources
    int depX=125;
    int depY=-5;
    int pasX=31;
    int pasY=32;

    //affiche le pion
    m_alleg.luminosite(page, getImgPion(4), lumin, depX+getPoseX()*pasX, depY+getPoseY()*pasY);
}

//verifie si on peut deplacer le pion
int Pion::test_deplacement(map<int , Abstract_Case*> const&cases, int x, int y, int pionsPl[6][2])
{
    //Declaration des ressources
    int pionsPl2[6][2];
    int presence=0;
    int reussite=0;
    int a=0, b=0, rang=0;
    BITMAP *page;

    //demande de deplacement ?
    if(x!=0 || y!=0)
    {
        for(int i=0; i<6; i++)
        {
            if((pionsPl[i][0]==getPoseX()+x) && (pionsPl[i][1]==getPoseY()+y))//se dirige sur une case d'un adversaire ?
                presence=1;//presence d'un pion sur la case de destination
            if((pionsPl[i][0]==getPoseX()) && (pionsPl[i][1]==getPoseY()))//est-ce le joueur actuel ?
                rang=i;//rang du joueur actuel
        }

        if((getPoseX()+x!=-1) && (getPoseX()+x!=24) && (getPoseY()+y!=-1) && (getPoseY()+y!=25) && (0 == presence))//on n'est pas en dehors du plateau et case libre ?
        {
            auto it = cases.find(24*getPoseY()+getPoseX());//cherche la case concernee
            auto it2 = cases.find(24*(getPoseY()+y)+getPoseX()+x);//cherche la case concernee

            if((it != cases.end()) && (it2 != cases.end()))//cases trouvee ?
            {
                if(it->second->getNom()=="piece")//dans une piece ?
                {
                    sortir(x, y);//on sort de la piece
                    reussite=1;//deplacement reussi
                }
                else if(it->second->getNom()=="coin")
                {
                    if(secret(x,y))//si le deplacement par passage secret est fait
                    {
                        reussite=2;//on a reussi et fini le deplacement
                    }
                    else//sinon on sort de la piece
                    {
                        sortir(x, y);//on sort de la piece
                        reussite=1;//deplacement reussi
                    }
                }
                else if(it->second->getNom()=="centre")//sinon si c'est la piece centrale
                {
                    reussite=2;//on a fini le deplacement
                }
                else if(it->second->getNom()=="porte" && (it2->second->getNom()=="coin" || it2->second->getNom()=="piece"))//sinon si on entre dans une piece
                {
                    //teleportation et le joueur ne bouge plus
                    it->second->effect(page, 0, 0, 0, a, b, pionsPl2, rang, 1);//chargement de la case de teleportation
                    deplacer_pion2(pionsPl2[rang][0], pionsPl2[rang][1]);//le joueur se teleporte
                    reussite=2;//on a reussi et fini le deplacement
                }
                else if((-1==x && 0==it->second->getMur(3)) || (1==y && 0==it->second->getMur(2)) || (1==x && 0==it->second->getMur(1)) || (-1==y && 0==it->second->getMur(0)))//absence de mur ?
                {
                    deplacer_pion1(x, y);//deplacement du pion
                    reussite=1;//deplacement reussi
                }
            }
        }
    }

    return reussite;//on retourne si le deplacement est reussi
}

//le pion prend un passage secret ?
int Pion::secret(int x, int y)
{
    //Declaration des ressources
    int valid=1;

    //deplacement en fonction de la piece actuelle
    if(getPoseX()<10 && getPoseY()<10 && (x==-1 || y==-1))
    {
        deplacer_pion2(497%24, int(497/24));
    }
    else if(getPoseX()>10 && getPoseY()<10 && (x==1 || y==-1))
    {
        deplacer_pion2(438%24, int(438/24));
    }
    else if(getPoseX()<10 && getPoseY()>10 && (x==-1 || y==1))
    {
        deplacer_pion2(138%24, int(138/24));
    }
    else if(getPoseX()>10 && getPoseY()>10 && (x==1 || y==1))
    {
        deplacer_pion2(172%24, int(172/24));
    }
    else
        valid=0;//pas de deplacement

    return valid;//retourne le resultat
}

//le pion sort de la piece
void Pion::sortir(int x, int y)
{
    //deplacement en fonction de la piece actuelle
    if(getPoseX()<6 && getPoseY()<7)
    {
        deplacer_pion2(172%24, int(172/24));//deplacement du pion
    }
    else if(getPoseX()>17 && getPoseY()<6)
    {
        deplacer_pion2(138%24, int(138/24));//deplacement du pion
    }
    else if(getPoseX()>16 && getPoseY()>20)
    {
        deplacer_pion2(497%24, int(497/24));//deplacement du pion
    }
    else if(getPoseX()<7 && getPoseY()>18)
    {
        deplacer_pion2(438%24, int(438/24));//deplacement du pion
    }
    else if(getPoseX()<8)
    {
        deplacer_pion2(390%24, int(390/24));//deplacement du pion
    }
    else if(getPoseX()>17 && getPoseY()<13)
    {
        deplacer_pion2(233%24, 233/24);//deplacement du pion
    }
    else if(getPoseX()>16)
    {
        deplacer_pion2(400%24, 400/24);//deplacement du pion
    }
    else if(getPoseY()>14)
    {
        deplacer_pion2(419%24+(x==1), 419/24);//deplacement du pion
    }
    else if(getPoseY()<15)
    {
        deplacer_pion2(201%24+5*(x==1), 201/24);//deplacement du pion
    }
}

//detecte la position du pion dans une piece donnée
int Pion::position()
{
    //Declaration des ressources
    int value=-1;

    //deplacement en fonction de la piece actuelle
    if(getPoseX()<6 && getPoseY()<7)
    {
        value=0;
    }
    else if(getPoseX()>17 && getPoseY()<6)
    {
        value=2;
    }
    else if(getPoseX()>16 && getPoseY()>20)
    {
        value=8;
    }
    else if(getPoseX()<7 && getPoseY()>18)
    {
        value=6;
    }
    else if(getPoseX()<8)
    {
        value=3;
    }
    else if(getPoseX()>17 && getPoseY()<13)
    {
        value=4;
    }
    else if(getPoseX()>16)
    {
        value=5;
    }
    else if(getPoseY()>17)
    {
        value=7;
    }
    else if(getPoseY()<9)
    {
        value=1;
    }

    //retourne le resultat
    return value;
}

//deplacement du pion 1
void Pion::deplacer_pion1(int x, int y)
{
    setPoseX(getPoseX()+x);//deplacement en x
    setPoseY(getPoseY()+y);//deplacement en y
}

//deplacement du pion 2
void Pion::deplacer_pion2(int x, int y)
{
    setPoseX(x);//deplacement en x
    setPoseY(y);//deplacement en y
}

//sauvegarde du pion
void Pion::save(ofstream &file)
{
    //sauegarde des elemnts du pion
    file << getTimer() << endl << getMax() << endl << getPoseX() << endl << getPoseY() << endl << getDepartX() << endl << getDepartY() << endl << getName() << endl;
}

//charge les elemnts du pion
void Pion::load(ifstream &file, string &receveur)
{
    //Declaration des ressources
    int numero, n2;

    //chargement des elemnts du pion
    file >> receveur;
    numero=stoi(receveur);//converti str en int
    setTimer(numero);

    file >> receveur;
    numero=stoi(receveur);//converti str en int
    setMax(numero);

    file >> receveur;
    numero=stoi(receveur);//converti str en int
    setPoseX(numero);//position en x

    file >> receveur;
    numero=stoi(receveur);//converti str en int
    setPoseY(numero);//position en y

    file >> receveur;
    numero=stoi(receveur);//converti str en int
    file >> receveur;
    n2=stoi(receveur);//converti str en int
    setDepart(numero, n2);//depart du pion

    file >> receveur;
    setName(receveur);//pseudo

}

// Accesseurs
// Getter
int Pion :: getTimer() const{ return m_timer; }
int Pion :: getMax() const{ return m_max; }
int Pion :: getPoseX() const{ return m_pose[0]; }
int Pion :: getPoseY() const{ return m_pose[1]; }
int Pion :: getDepartX() const{ return m_depart[0]; }
int Pion :: getDepartY() const{ return m_depart[1]; }
string Pion :: getName() const{ return m_name; }

BITMAP *Pion::getImgPion(int speed)
{
    //compteur d'affichage +1
    setTimer(speed);
    //retourne l'image
    return m_img_pion[int(getTimer()/speed)];
}

BITMAP *Pion::getImgLogo(int speed)
{
    //compteur d'affichage +1
    setTimer(speed);
    //retourne l'image
    return m_img_logo[int(getTimer()/speed)];
}

// Setter
void Pion :: setTimer(int speed)
{
    m_timer++;//set timer
    //max atteint ?
    if(getMax()*speed <= m_timer)
        m_timer=0;//reset
}
void Pion :: setMax(int _max){ m_max = _max;}
void Pion :: setPoseX(int _pose_x){ m_pose[0] = _pose_x;}
void Pion :: setPoseY(int _pose_y){ m_pose[1] = _pose_y;}
void Pion :: setName(string _name){ m_name = _name; }
void Pion :: setDepart(int x, int y)
{
    m_depart[0]=x;
    m_depart[1]=y;
}
