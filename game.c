#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/*Fonction permettant de déterminer si l'utilisateur a cliquer sur une bille ou non.Renvoi 1 si oui, 4 si non.*/
int Game_Start_Clicker_Analizer(int* ball_x,int* ball_y)
{
    if(SourisCliquee()==1)
    {
        *ball_x=_X/40;
        *ball_y=_Y/40;
        if(*ball_x<15 && *ball_y<10)
            return 1;
    }
    return 4;
}

/*Fonction permettant de déterminer si la bille est seul ou si elle appartient a un groupe, renvoi 0 si oui
et 0 si non.*/
int Ball_Approval(int x,int y,int ball_value,int grid[10][15])
{
    if(ball_value==10)
        return 0;
    if(x>0 && ball_value==grid[x-1][y])
        return 1;
    if(x<9 && ball_value==grid[x+1][y])
        return 1;
    if(y>0 && ball_value==grid[x][y-1])
        return 1;
    if(y<9 && ball_value==grid[x][y+1])
        return 1;
    return 0;
}

/*Cette fonction test chaque bille en appellant Ball_Approval, si le end teller ne change jamais de valeur
cela signifie que la partie est perdu.*/
int Check_End_Game(int grid[10][15])
{
    int i, j, end_teller=0;
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            end_teller=Ball_Approval(i,j,grid[i][j],grid);
            if(end_teller==1)
                return 0;
        }
    }
    return 1;
}

/*La procédure Grid_Updater lorsque elle doit seulement afficher les groupes de billes en surbrillance et non
les supprimer change la valeur à 11 de chaque bille appartenant au groupe que l'utilisateur sélectionne avec
son curseur, cette fonction permet de restaurer la vrai valeur de chaque bille après que le groupe ai été 
afficher graphiquement en surbrillance.*/
void Grid_Restore(int ball_value,int grid[10][15])
{
    int i, j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            if(grid[i][j]==11)
                grid[i][j]=ball_value;
        }
    }
}

/*Cette fonction récursive permet d'effectuer les modification nécessaire afin de décaler chaque bille dans
le tableau grid pour qu'il n'y ai aucun trou en dessous et a gauche de chaque bille.C'est la variable 
modification qui va indiquer si la fonction doit continuer de vérifier si il y a un trou.*/
void Grid_Fixer(int grid[10][15])
{
    int i, j, modification=0;
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            if(grid[i][j]==10 && i!=0 && grid[i-1][j]!=10)
            {
                grid[i][j]=grid[i-1][j];
                grid[i-1][j]=10;
                modification=1;
            }
            if(grid[i][j]==10 && j!=14 && grid[i][j+1]!=10)
            {
                grid[i][j]=grid[i][j+1];
                grid[i][j+1]=10;
                modification=1;
            }
        }
    }
    if(modification==1)
        Grid_Fixer(grid);
}

/*Permet d'afficher l'image de victoire ou de défaite graphiquement pendant une courte période.*/
void End_Game_Display(char* image)
{
    unsigned long time_waster, cycle=1500000L;
    time_waster=Microsecondes()+cycle;
    couleur wall=CouleurParComposante(25,25,25);
    while(Microsecondes()<time_waster)
            ;
    cycle=3000000L;
    time_waster=Microsecondes()+cycle;
    if(image=="lost")
    {
        ChoisirCouleurDessin(wall);
        RemplirRectangle(0,0,600,500);
        ChargerImage("./images/Lost.jpg",0,0,0,0,600,500);
        while(Microsecondes()<time_waster)
            ;
    }
    else if(image=="victory")
    {
        ChoisirCouleurDessin(wall);
        RemplirRectangle(0,0,600,500);
        ChargerImage("./images/Victory.jpg",0,0,0,0,600,500);
        while(Microsecondes()<time_waster)
            ;
    }
}

/*Permet d'indiquer au End_Game_Display si il doit afficher l'image de victoire ou de défaite.*/
int End_Game_Launcher(int grid[10][15])
{
    if(grid[9][0]==10)
    {
        End_Game_Display("victory");
        return 1;
    }
    else if(Check_End_Game(grid)==1)
    {
        End_Game_Display("lost");
        return -1;
    }
    return 0;
}

/*Permet d'appeller toutes les fonctions devant l'être lorsque l'utilisateur clique sur une bille.*/
int Mouse_Clicked_Manager(int grid[10][15], int difficulty)
{
    int ball_x, ball_y, real_score=0, ball_value, score=0;
    ball_x=_Y/40;
    ball_y=_X/40;
    if(ball_x<10 && ball_y<15)
    {
        if(Ball_Approval(ball_x,ball_y,grid[ball_x][ball_y],grid)==1 && grid[ball_x][ball_y]!=10)
        {
            Grid_Updater(ball_x,ball_y,grid[ball_x][ball_y],1,&score,grid);
            Grid_Fixer(grid);
            Grid_Ball_Loader(difficulty,1,grid);
            real_score=(score-2)*(score-2);
            ChargerImage("./images/Game_Score.jpg",230,405,0,0,150,55);
        }
    }
    return real_score;
}

/*Permet d'appeller toutes les fonctions devant l'être lorsque l'utilisateur bouge le curseur.*/
int Mouse_Position_Manager(int grid[10][15], int difficulty)
{
    int ball_x, ball_y, ball_score=0, ball_value, score=0;
    SourisPosition();
    ball_x=_Y/40;
    ball_y=_X/40;
    if(ball_x<10 && ball_y<15)
    {
        ball_value=grid[ball_x][ball_y];
        Grid_Updater(ball_x,ball_y,grid[ball_x][ball_y],2,&score,grid);
        Grid_Ball_Loader(difficulty,1,grid);
        ball_score=(score-2)*(score-2);
        Grid_Restore(ball_value,grid);
    }
    return ball_score;
}

/*Fonction générale ayant pour rôle de diriger les autres fonctions selon les actions de l'utilisateur.*/
int Game_Start(int difficulty, char* string_score, int grid[10][15], int real_score)
{
    int game_manager=4, score=0, end_check;
    char ball_string_score[5]={'\0','\0','\0','\0'};
    Score_Display(real_score,273,483,265,460,80,60,string_score);
    while(game_manager==4)
    {
        if(SourisCliquee()==0)
        {
            score=Mouse_Position_Manager(grid,difficulty);
            Score_Display(score,65,430,55,405,80,30,ball_string_score);    
        }
        if(SourisCliquee()==1)
        {
            real_score=real_score+Mouse_Clicked_Manager(grid,difficulty);
            Score_Display(real_score,273,483,265,460,80,60,string_score);
            end_check=End_Game_Launcher(grid);
            if(end_check==1)
                return real_score;
            else if(end_check==-1)
                return -1;
        }
        game_manager=Save_And_Quit(grid,string_score);
    }
    return game_manager;
}

