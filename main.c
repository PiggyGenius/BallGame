#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#define WINDOW_WIDTH 600
#define WINDOW_LENGTH 500

/*Le main ne fait que gérer les appels de fonction, c'est le squeulette du programme.*/
int main(int argc, char** argv)
{
    int difficulty, page_loader=4, game_score, score=0;
    int grid[10][15];
    char string_score[5]={'\0','\0','\0','\0','\0'};
    InitialiserGraphique();
    CreerFenetre(0,0,WINDOW_WIDTH,WINDOW_LENGTH);
    Menu_Printer();
    while(page_loader!=0)
    {
        page_loader=Clicker_Analiser();
        if(page_loader==1)
        {
            difficulty=Difficulty_Pick_Printer()+1;
            Grid_Loader();
            Grid_Ball_Loader(difficulty,42,grid);
            game_score=Game_Start(difficulty,string_score,grid,score);
            if(game_score!=-1)
                Hall_Of_Fame(string_score,game_score);
            score=0;
            Menu_Printer();
        }
        else if(page_loader==2)
        {
            if(argc==2)
            {
                Grid_Loader();
                Manual_Grid_Ball_Loader(argv[1],grid);
                score=Score_Loader(string_score);
                game_score=Game_Start(difficulty,string_score,grid,score);
                if(game_score!=-1)
                    Hall_Of_Fame(string_score,game_score);
                score=0;
                Menu_Printer();
            }
            else
                printf("Aucun nom de fichier valable rentré en argument, impossible de charger une partie.\n");
        }
        else if(page_loader==3)
        {
           Hall_Of_Fame_Printer();
           Menu_Printer();
        }
    }
    return 0;
}
