projet : grid.o difficulty.o game.o score.o save_and_quit.o menu.o hall_of_fame.o main.o
	gcc -o projet grid.o difficulty.o game.o score.o save_and_quit.o menu.o hall_of_fame.o main.o -lgraph -Wall -ansi -pedantic

grid : grid.c
	gcc -c grid.c

difficulty : difficulty.c
	gcc -c difficulty.c

game : game.c save_and_quit.h
	gcc -c game.c

score : score.c
	gcc -c score.c

save : save_and_quit.c menu.h
	gcc -c save_and_quit.c

menu : menu.c
	gcc -c menu.c

hall : hall_of_fame.c
	gcc -c hall_of_fame.c

main : main.c hall_of_fame.h.h menu.h save_and_quit.h score.h game.h difficulty.h grid.h
	gcc -c main.c
