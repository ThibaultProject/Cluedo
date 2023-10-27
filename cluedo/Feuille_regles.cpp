#include "Feuille_regles.h"

//constructeur et destructeur

//constructeur par defaut
Feuille_regles::Feuille_regles()
{
    //Declaration des ressources
    char txt[34][2][100]={{"Introduction :","Introduction :"},{" "," "},{"A l'issue d'une invitation dans un hotel de luxe, les amis de luigi","After an invitation to a luxury hotel, luigi's friends"},{"ont ete kidnappe et retenu pris au piege dans le musee du manoir.","have been kidnapped and held trapped in the mansion museum."},{" "," "},{"But du jeu :","Goal of the game :"},{" "," "},{"Resoudre, par deductions, l'enigme posee par ce crime.","Solve, by deduction, the enigma posed by this crime."},{" "," "},{"Gagnant :","Winner :"},{" "," "},{"Celui qui tourve le meutrier, l'arme et le lieu du crime le premier.","The one who is the first to identify the murderer, the weapon and the place."},{" "," "},{"Materiel :","Material:"},{" "," "},{"- 21 cartes :","- 21 cards:"},{"- 6 cartes 'Suspects' : Luigi, Gluigi, Roi Boo, Ectochien, Mario, Prof K.Tastroff","- 6 'Suspects' cards: Luigi, Gluigi, King Boo, Ectochien, Mario, Prof K. Tastroff"},{"- 6 cartes 'Armes' : Lampe torche, Ectoblast, Ventouse, Bombe, Aspira'coeur, Reveloscope","- 6 'Weapons' cards: Flashlight, Ectoblast, Suction cup, Bomb, Aspira'coeur, Reveloscope"},{"- 9 cartes 'Lieux' : Cuisine, Reception, Hall d'entree, Balcon, Bibliotheque,","- 9 'Places' cards: Kitchen, Reception, Entrance hall, Balcony, Library,"},{"                     Chambre, Salon, Salle de billard, Salle de bain","                    Bedroom, Living room, Billiard room, Bathroom"},{"- 2 des"," - 2 dices"},{"- 1 enveloppe pour inserer les 3 cartes de l'enigme"," - 1 envelope to insert the 3 puzzle cards"},{"- 1 carnet de notes ou les joueurs inscrivent les resultats de leurs investigations"," - 1 notebook where the players write down the results of their investigations"},{" "," "},{"Deplacement :","Shift :"},{" "," "},{"- cases occupees : il n'est pas autorise s'arreter sur une case occupee","- occupied squares: it is not allowed to stop on an occupied square "},{"                   ni de sauter au dessus d'un pion adverse","                    or to jump over an opponent's pawn"},{"- passages secrets : Les pieces de chaque coin sont reliees par des passages secrets souterrains","- secret passages: The rooms in each corner are connected by secret underground passages"},{"                     permettent de passer a la piece opposee sans lancer les des","                   allow you to switch to the opposite room without throwing the dice"},{"- entrer dans une piece : Les pieces sont absorbantes, donc si un joueur passe","- enter a room: The rooms are absorbent, so if a player passes"},{"                          pres d'une porte, il va directement dans la piece","                near a door, he goes directly into the room"},{"- double 6 et double 1 : s'il fait un double 6 ou un double 1,","- double 6 and double 1: if it makes a double 6 or a double 1,"},{"                         il va directement dans la piece choisie","                         it goes directly to the chosen room"}};
    int i, j, k;

    //ecriture de tous les textes
    for(i=0; i<34; i++)
    {
        for(j=0; j<2; j++)//ecriture du texte en anglais et francais
        {
            for(k=0; txt[i][j][k]!='\0'; k++)//ecriture du texte
                m_txt[i][j][k]=txt[i][j][k];//copie !

            m_txt[i][j][k]='\0';//caratere de fin de mot
        }
    }
}

//destructeur
Feuille_regles::~Feuille_regles(){}

//methodes
//affiche les regles du jeu
void Feuille_regles::display(BITMAP *&page, int langue, int lumin)
{
    //trace le rectangle de fond de texte
    m_alleg.rectfont(page, langue, lumin, false, false, 100, 140, 900, 660, 100, 140, 900, 660); //fond du texte

    //affichage de toutes les lignes de texte
    for(int i=0; i<34; i++)
        m_alleg.txtlangue(page, langue, lumin, m_txt[i][0], 100, 140+15*i, m_txt[i][1], 100, 140+15*i);//texte
}
