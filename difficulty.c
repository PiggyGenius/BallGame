#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/*Permet d'analyser sur quelle case l'utilisateur a cliqué, chaque case correspond a une difficulté.*/
int Difficulty_Pick_Analyser(void)
{
    if(SourisCliquee()==1)
    {
        if (_X>=350 && _X<=600 && _Y>=441 && _Y<=500)
            exit(1);
        else if(_X>=290 && _X<=336 && _Y>=75 && _Y<=117)
            return 1;
        else if(_X>=370 && _X<=416 && _Y>=75 && _Y<=117)
            return 2;
        else if(_X>=450 && _X<=496 && _Y>=75 && _Y<=117)
            return 3;
        else if(_X>=530 && _X<=576 && _Y>=75 && _Y<=117)
            return 4;
        else if(_X>=130 && _X<=176 && _Y>=150 && _Y<=192)
            return 5;
        else if(_X>=210 && _X<=256 && _Y>=150 && _Y<=192)
            return 6;
        else if(_X>=290 && _X<=336 && _Y>=150 && _Y<=192)
            return 7;
        else if(_X>=370 && _X<=416 && _Y>=150 && _Y<=192)
            return 8;
        else if(_X>=450 && _X<=496 && _Y>=150 && _Y<=192)
            return 9;
    }
    return 10;
}

/*Permet de charger les images de difficulté et de renvoyer le niveau de difficulté choisit par l'utilisateur.*/
int Difficulty_Pick_Printer(void)
{
    int difficulty=10;
    couleur wall=CouleurParComposante(25,25,25);
    ChoisirCouleurDessin(wall);
    RemplirRectangle(0,0,600,600);
    ChargerImage("./images/Difficulte.png",75,75,0,0,189,44);
    ChargerImage("./images/Difficulty_Pick_1.jpg",290,75,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_2.jpg",370,75,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_3.jpg",450,75,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_4.jpg",530,75,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_5.jpg",130,150,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_6.jpg",210,150,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_7.jpg",290,150,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_8.jpg",370,150,0,0,46,42);
    ChargerImage("./images/Difficulty_Pick_9.jpg",450,150,0,0,46,42);
    ChargerImage("./images/Menu_Quitter.jpg",350,441,0,0,250,59);
    while(difficulty==10)
        difficulty=Difficulty_Pick_Analyser();
    return difficulty;
}

