#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <time.h>

/*Grid_updater est une fonction récursive permettant de calculer les groupes de billes à supprimer, à afficher
en surbrillance, calculer le nombre de billes par groupe.L'option détermine si elle doit supprimer les billes
ou simplement les afficher d'une couleur différente pour indiquer la surbrillance.*/
void Grid_Updater(int x, int y, int ball_value, int option,int* score,int grid[10][15])
{
    if(ball_value==10)
        return ;
    if(grid[x][y]==ball_value)
    {
        if(option==1)
        {
            grid[x][y]=10;
            *score+=1;
        }
        else
        {
            grid[x][y]=11;
            *score+=1;
        }
        if(x<9)
            Grid_Updater(x+1,y,ball_value,option,score,grid);
        if(x>0)
            Grid_Updater(x-1,y,ball_value,option,score,grid);
        if(y<14)
            Grid_Updater(x,y+1,ball_value,option,score,grid);
        if(y>0)
            Grid_Updater(x,y-1,ball_value,option,score,grid);
    }
}

/* Cette fonction permet de remplir un tableau de couleur, chaque indice du tableau correspond à la valeur
de la couleur, l'argument color_pick va donc déterminer quelle couleur la fonction doit renvoyer.*/
couleur Color_Value(int color_pick)
{
    couleur red=CouleurParNom("red");
    couleur blue=CouleurParNom("blue");
    couleur yellow=CouleurParNom("yellow");
    couleur green=CouleurParNom("green");
    couleur grey=CouleurParNom("grey");
    couleur maroon=CouleurParNom("maroon");
    couleur orange=CouleurParNom("orange");
    couleur purple=CouleurParNom("purple");
    couleur pink=CouleurParNom("pink");
    couleur lightgreen=CouleurParComposante(128,255,128);
    couleur wall=CouleurParComposante(25,25,25);
    couleur selected=CouleurParComposante(10,10,10);
    couleur color[12]={red,blue,yellow,green,grey,maroon,orange,purple,pink,lightgreen,wall,selected};
    return color[color_pick];
}

/*Cette preocédure permet d'afficher les billes de couleur dans la grille, l'argument option va déterminer si
la couleur des billes doit être aléatoire, cela corresspond a un utilisateur ayant cliqué sur jouer, ou si
elle doit respecter la grille qui aura été remplie par le fichier en argument de l'éxecutable, cela corresspond
a un utilisateur ayant cliqué sur chager.*/
void Grid_Ball_Loader(int difficulty,int option,int grid[10][15])
{
    int i, j;
    int color_pick;
    int x_start=5, y_start=5, x_incrementation=0, y_incrementation=0;
    srand((unsigned int) time(NULL));
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            if(option==42)
            {
                color_pick=rand()%difficulty;
                grid[i][j]=color_pick;
            }
            else
                color_pick=grid[i][j];
            ChoisirCouleurDessin(Color_Value(color_pick));
            RemplirArc(x_start+x_incrementation,y_start+y_incrementation,30,30,360,360);
            x_incrementation+=40;
        }
        x_incrementation=0;
        y_incrementation+=40;
    }
}
/*Procédure permettant de tracer la grille à l'écran.*/
void Grid_Loader(void)
{
    int i, j;
    int x_line_begin=0, x_line_end=600, y_line_begin=0, y_line_end=400;
    int x_incrementation=0;
    int y_incrementation=0;
    couleur white=CouleurParNom("white");
    couleur wall=CouleurParComposante(25,25,25);
    ChoisirCouleurDessin(wall);
    RemplirRectangle(0,0,600,600);
    ChoisirCouleurDessin(white);
    for(i=0;i<=15;i++)
    {
            DessinerSegment(x_line_begin+x_incrementation,y_line_begin,x_line_begin+x_incrementation,y_line_end);
            x_incrementation+=40;
    }
    for(j=0;j<=10;j++)
    {
            DessinerSegment(x_line_begin,y_line_begin+y_incrementation,x_line_end,y_line_begin+y_incrementation);
            y_incrementation+=40;
    }
}
/*Permet de charger la grille avec les valeurs du fichiers en arguments de l'executable, chaque char correspond
a une valeur, la preocédure Grid_Ball_Loader remplira ensuite chaque bille en fonction de la valeur du tableau
grid dont l'indice correspond a la case de la grille.Cette precédure n'est appellé que si l'utilisateur clique
sur charger dans le menu et si il a indiquer un fichier en argument de l'executable.*/
void Manual_Grid_Ball_Loader(char* color_file,int grid[10][15])
{
    FILE* file=NULL;
    char color_character;
    int color_pick, i=0, j=0, k=0;
    char color_pick_character[11]={'r','b','y','g','e','m','o','p','k','l','w'};
    if(file=fopen(color_file,"r"))
    {
        while(fscanf(file,"%c",&color_character)!=EOF)
        {
            if(color_character!='\n')
            {
                if(j==15)
                {
                    i=i+1;
                    j=0;
                }
                for(k=0;k<11;k++)
                {
                    if(color_character==color_pick_character[k])
                    {
                        color_pick=k;
                        break;
                    }
                 }
                 grid[i][j]=color_pick;
                 j=j+1;
            }
        }
        fclose(file);
    }
    Grid_Ball_Loader(42,2,grid);
}

