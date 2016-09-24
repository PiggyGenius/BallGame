#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#define WINDOW_WIDTH 600
#define WINDOW_LENGTH 500

/*Permet d'analyser où l'utilisateur a cliquer dans le menu principal.*/
int Clicker_Analiser(void)
{
    couleur c=CouleurParNom("red");
    ChoisirCouleurDessin(c);
    if(SourisCliquee()==1)
    {
        if(_Y>=59 && _Y<=109 && _X>=170 && _X<=420)
            return 1;
        else if(_Y>=159 && _Y<=218 && _X>=170 && _X<=420)
            return 2;
        else if(_Y>=268 && _Y<=327 && _X>=170 && _X<=420)
            return 3;
        else if(_Y>=377 && _Y<=436 && _X>=170 && _X<=420)
            return 0;
    }
    return 4;
}

/*Permet d'afficher le menu.*/
int Menu_Printer(void)
{
    int page_loader;
    int difficulty=3;
    int x_start=WINDOW_WIDTH/4+25;
    int y_start=WINDOW_LENGTH/10;
    int y_increment=110;
    couleur wall=CouleurParComposante(25,25,25);
    ChoisirCouleurDessin(wall);
    RemplirRectangle(0,0,WINDOW_WIDTH,WINDOW_LENGTH);
    ChargerImage("./images/Menu_Jouer.jpg",x_start,y_start,0,0,250,59);
    ChargerImage("./images/Menu_Charger.jpg",x_start,y_start+y_increment,0,0,250,59);
    ChargerImage("./images/Menu_Score.jpg",x_start,y_start+y_increment*2,0,0,250,59);
    ChargerImage("./images/Menu_Quitter.jpg",x_start,y_start+y_increment*3,0,0,250,59);
}

