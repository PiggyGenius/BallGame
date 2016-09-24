#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/*Cette procédure a pour but d'écrire le fichier Hall_Of_Fame.txt de manière qu'il contienne le score et le
nom du joueur, tout en recopiant les scores et nom qui doivent rester dans le fichier et en insérant le score
du joueur à la bonne ligne.*/
void Hall_Of_Fame_File_Writer(char name[3], char* string_score, int line_mark)
{
    FILE* temporary_hall_of_fame;
    FILE* hall_of_fame;
    char hall_line[13];
    int i;
    if(temporary_hall_of_fame=fopen("Temporary_Hall_Of_Fame.txt","w"))
    {
        if(hall_of_fame=fopen("Hall_Of_Fame.txt","r"))
        {
            for(i=0;i<line_mark;i++)
            {
                fscanf(hall_of_fame,"%12s",hall_line);
                fprintf(temporary_hall_of_fame,"%12s%c",hall_line,'\n');
            }
            fprintf(temporary_hall_of_fame,"%d:%c%c%c-->%c%c%c%c%c",line_mark,name[0],name[1],name[2],string_score[0],string_score[1],string_score[2],string_score[3],'\n');
            for(i=0;i<10-line_mark-1;i++)
            {
                fscanf(hall_of_fame,"%12s",hall_line);
                hall_line[0]=(char) (int) hall_line[0]+1;
                fprintf(temporary_hall_of_fame,"%12s%c",hall_line,'\n');
            }
            fclose(hall_of_fame);
        }
        fseek(temporary_hall_of_fame,0,SEEK_SET);
        fclose(temporary_hall_of_fame);
        remove("Hall_Of_Fame.txt");
        rename("Temporary_Hall_Of_Fame.txt", "Hall_Of_Fame.txt");
        remove("Temporary_Hall_of_Fame.txt");
    }
}

/*Cette procédure a pour but d'indiquer a Hall_Of_Fame_Writer le numéro de la ligne où il faudra écrire le
score du joueur ainsi que son nom ainsi que d'indiquer graphiquement à l'utilisateur les lettres qu'il écrit.*/
void Hall_Of_Fame(char* string_score,int game_score)
{
    int letter_1, letter_2, letter_3, line_mark, hall_integer_score, hall_save_decider=4;
    FILE* hall_of_fame;
    char hall_junk[8];
    char hall_character_score[4];
    char name[3]="\0\0\0";
    couleur wall=CouleurParComposante(25,25,25);
    couleur writing=CouleurParNom("white");
    ChoisirCouleurDessin(writing);
    ChargerImage("./images/Hall_Of_Fame.png",0,0,0,0,600,500);
    EcrireTexte(260,290,string_score,2);
    ChoisirCouleurDessin(wall);
    RemplirRectangle(325,260,40,60);
    ChoisirCouleurDessin(writing);
    ChargerImage("./images/Save_And_Quit_Menu_Quitter.jpg",406,441,0,0,194,59);
    ChargerImage("./images/Save_And_Quit_Menu_Sauver.jpg",0,441,0,0,195,59);
    letter_1=Touche();
    name[0]=letter_1;
    EcrireTexte(270,215,name,2);
    letter_2=Touche();
    name[1]=letter_2;
    EcrireTexte(270,215,name,2);
    letter_3=Touche();
    name[2]=letter_3;
    name[3]='\0';
    EcrireTexte(270,215,name,2);
    while(hall_save_decider==4)
    {
        hall_save_decider=Save_And_Quit_Click_Analizer();
        if(hall_save_decider==0)
            return ;
    }
    letter_1=(char) letter_1;
    letter_2=(char) letter_2;
    letter_3=(char) letter_3;
    if(hall_of_fame=fopen("Hall_Of_Fame.txt","r"))
    {
        for(line_mark=0;line_mark<10;line_mark++)
        {
            fscanf(hall_of_fame,"%8s",hall_junk);
            fscanf(hall_of_fame,"%4s",hall_character_score);
            hall_integer_score=((int) hall_character_score[0]-48)*1000+((int) hall_character_score[1]-48)*100+((int) hall_character_score[2]-48)*10+(int) hall_character_score[3]-48;
            if(game_score>hall_integer_score)
            {
                close(hall_of_fame);
                Hall_Of_Fame_File_Writer(name,string_score,line_mark);
                break;
            }
        }
    }
}

/*Cette procédure écrit graphiquement le fichier Hall_Of_Fame.txt afin que l'utilisateur consulte le fichier
sans avoir a quitter le jeu.*/
void Hall_Of_Fame_Printer(void)
{
     FILE* hall_of_fame;
     char hall_line[13];
     int line_mark, x=75, y=200, y_increment=60;
     unsigned long time_waster, cycle=4000000L;
     time_waster=Microsecondes()+cycle;
     couleur wall=CouleurParComposante(25,25,25);
     couleur writing=CouleurParNom("white");
     ChoisirCouleurDessin(wall);
     RemplirRectangle(0,0,600,500);
     ChoisirCouleurDessin(writing);
     ChargerImage("./images/Fame_Print.jpg",90,30,0,0,436,116);
     if(hall_of_fame=fopen("Hall_Of_Fame.txt","r"))
     {
         for(line_mark=0;line_mark<10;line_mark++)
         {
             fscanf(hall_of_fame,"%12s",hall_line);
             if(line_mark==5)
             {
                 x=350;
                 y=200;
             }
             EcrireTexte(x,y,hall_line,2);
             y=y+y_increment;
         }
         close(hall_of_fame);
     }
     while(Microsecondes()<time_waster)
         ;
}
