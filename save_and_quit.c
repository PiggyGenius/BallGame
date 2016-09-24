#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/*Cette fonction indique à Save_And_Quit si l'utilisateur a cliquer sur le bouton sauver ou quitter.*/
int Save_And_Quit_Click_Analizer(void)
{
    if(SourisCliquee()==1)
    {
        if(_X>=0 && _X<=195 && _Y>=441)
            return -1;
        else if(_X>=406 && _Y>=441)
            return 0;
    }
    return 4;
}

/*Cette procédure écrit le fichier save.txt de manière qu'il puisse être charger si l'utilisateur le souhaite
par le Manual_Grid_Loader(section game).Enregstre �galement le score.*/
void Game_Saver(int grid[10][15], char* string_score)
{
    FILE* save=NULL;
    FILE* score=NULL;
    int i, j;
    char character_grid[11]={'r','b','y','g','e','m','o','p','k','l','w'};
    if(save=fopen("save.txt", "w"))
    {
        for(i=0;i<10;i++)
        {
            for(j=0;j<15;j++)
                fprintf(save,"%c",character_grid[grid[i][j]]);
            fprintf(save,"%c",'\n');
        }
        fseek(save,0,SEEK_SET);
        close(save);
    }
    if(score=fopen("score.txt", "w"))
    {
        fprintf(score,"%s",string_score);
        fseek(score,0,SEEK_SET);
        close(score);
    }
}

/*Cette fonction affiche graphiqument le bouton quitter et sauver, elle appelle si nécessaire Game_Saver, 
son analyseur de clique lui indiquera si Game_Saver doit être appellé.*/
int Save_And_Quit(int grid[10][15], char* string_score)
{
    int clicked=4;
    ChargerImage("./images/Save_And_Quit_Menu_Quitter.jpg",406,441,0,0,194,59);
    ChargerImage("./images/Save_And_Quit_Menu_Sauver.jpg",0,441,0,0,195,59);
    clicked=Save_And_Quit_Click_Analizer();
    if(clicked==-1)
        Game_Saver(grid,string_score);
    else if(clicked==0)
    {
        Menu_Printer();
        return -1;
    }
    return clicked;
}
