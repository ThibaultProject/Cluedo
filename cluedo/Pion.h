#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Paquet.h"
#include "Allegfct.h"
#include "Abstract_Case.h"

//classe pion
class Pion{
private:
    //attributs
    Allegfct m_alleg;               //les fonctions allegro
    SAMPLE *m_sound;                //le son du pion
    vector<BITMAP *> m_img_pion;    //l'image du pion
    vector<BITMAP *> m_img_logo;    //l'image du logo
    string m_name="";               //le nom
    int m_timer=0;                  //le timer d'affichage
    int m_max;                      //le max du timer d'affichage
    int m_pose[2]={0,0};            //position du pion
    int m_depart[2]={0,0};          //la case depart du pion

public:
    //constructeur et destructeur
    Pion();
    Pion(string _name);
    ~Pion();

    //methodes
    void load_sound_pion();//charge le son du pion
    void load_img_pion();//charge les images
    BITMAP *charge_pion(int i);//charge une bitmap et la retourne
    void init_depart();//initialise le depart du pion
    void effet_sonore();//lance l'effet sonore
    void affiche_pion(BITMAP *&page, int lumin);//affiche un pion sur le plateau
    int test_deplacement(map<int , Abstract_Case*> const&cases, int x, int y, int pionsPl[6][2]);//verifie si on peut deplacer le pion
    int secret(int x, int y);//le pion prend un passage secret ?
    void sortir(int x, int y);//le pion sort de la piece
    int position();//detecte la position du pion dans une piece donnée
    void deplacer_pion1(int x, int y);//deplacement du pion 1
    void deplacer_pion2(int x, int y);//deplacement du pion 2
    void save(ofstream &file);//sauvegarde du pion
    void load(ifstream &file, string &receveur);//charge les elements du pion

    /// Accesseur
    // Getter
    int getTimer() const;
    int getMax() const;
    int getPoseX() const;
    int getPoseY() const;
    int getDepartX() const;
    int getDepartY() const;
    string getName() const;
    BITMAP *getImgPion(int speed);
    BITMAP *getImgLogo(int speed);

    // Setter
    void setTimer(int speed);
    void setMax(int _max);
    void setPoseX(int _pose_x);
    void setPoseY(int _pose_y);
    void setName(string _name);
    void setDepart(int x, int y);
};

#endif // PION_H_INCLUDED
