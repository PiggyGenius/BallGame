#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/*Permet d'afficher le score de l'utilisateur graphiquement.*/
void Score_Display(int score, int x, int y, int rect_x, int rect_y, int l, int h,char* string_score)
{
    couleur wall=CouleurParComposante(25,25,25);
    couleur writing=CouleurParNom("white");
    couleur writing_Bscore=CouleurParNom("black");
    if(score<10)
    {
        string_score[0]='0';
        string_score[1]='0';
        string_score[2]='0';
        string_score[3]=((char) score)+48;
    }
    else if(score<100 && score>9)
    {
        string_score[3]=((char) score%10)+48;
        string_score[2]=((char) score/10)+48;
        string_score[1]='0';
        string_score[0]='0';
    }
    else if(score<1000 && score>99)
    {
        string_score[3]=((char) (score%10)+48);
        string_score[2]=((char) ((score/10)%10)+48);
        string_score[1]=((char) (((score/100)%10))+48);
        string_score[0]='0';
    }
    else if(score<10000 && score>999)
    {
        string_score[3]=((char) (score%10)+48);
        string_score[2]=((char) ((score/10)%10)+48);
        string_score[1]=((char) ((score/100)%10)+48);
        string_score[0]=((char) (((score/1000)%10))+48);
    }
    ChoisirCouleurDessin(wall);
    RemplirRectangle(rect_x,rect_y,l,h);
    if(rect_x==265)
        ChoisirCouleurDessin(writing);
    else
        ChoisirCouleurDessin(writing_Bscore);
    EcrireTexte(x,y,string_score,2);
    ChoisirCouleurDessin(wall);
    RemplirRectangle(335,460,40,60);
}

int Score_Loader(char* string_score)
{
    FILE* score_txt;
    int score;
    if(score_txt=fopen("score.txt","r"))
    {
        fscanf(score_txt,"%4s",string_score);
        score=((int) string_score[0]-48)*1000+((int) string_score[1]-48)*100+((int) string_score[2]-48)*10+(int) string_score[3]-48;
        close(score_txt);
        return score;
    }
}
