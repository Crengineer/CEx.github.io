#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#define N 3
#define MAX 40

/*
	TIC TAC TOE GAME
*/

//type definition

typedef char Grid[N][N];
typedef struct{
	char name[MAX+1];
	bool turn;
	char element;
} player;

/*
	Functions list
*/

void initializeGrid();



/*
	Function implementation
*/
void initializeGrid(){
	int i, j, k;
	printf("\nEmpty grid:\n");
	printf("---", i+1);
	for(i=0; i<N; i++){
		printf("--%d--", i+1);
	}
	printf("\n");
	for(i=0; i<N; i++){
		printf("%d  ", i+1);
		for(j=0;j<N;j++){
			printf("|    ");
		}
		printf("|\n");
		printf("   ", i+1);
		for(j=0;j<N;j++){
			printf("-----");
		}
		printf("\n");
	}
	
}

//Player Data insert

void insertDataPlayers(player p1, player p2){
	
	//Player 1 Initialization
	strcpy(p1.name, "");           //Initialized to a 'NULL' value for convenience
	while(strcmp(p1.name,"") == 0){
		printf("\nPlayer 1 name:\n");
		gets(p1.name);
	}
	fflush(stdin);
	while(p1.element != 'X' && p1.element != 'O'){
		printf("\nPlayer 1 symbol:\n");
		scanf("%s", &p1.element);
	}
	fflush(stdin);
	
	//Player 2 Initialization             
	strcpy(p2.name, "");                       //Initialized to a 'NULL' value for convenience
	while(strcmp(p2.name,"") == 0){
		printf("\nPlayer 2 name:\n");
		gets(p2.name);
	}
	fflush(stdin);
	while(p2.element != 'X' && p2.element != 'O'){
		printf("\nPlayer 2 symbol:\n");
		scanf("%s", &p2.element);
		while(p2.element == p1.element){
			fflush(stdin);
			printf("\nPlayer 2 symbol:\n");
			scanf("%s", &p2.element);
		}
	}
	fflush(stdin);
	
	return;
}

void showPlayers(player p1, player p2){
	printf("\nPlayer 1:\n %s \n %c \n", p1.name, p1.element);
	printf("\nPlayer 2:\n %s \n %c \n", p2.name, p2.element);
	return;
}

void main(){
	player p1, p2;
	printf("Welcome to TicTacToe!\nPut your name and choose the sign you want: X or O.\n");
	insertDataPlayers(p1, p2);
	printf("\n%s", p1.name);
	//showPlayers(p1, p2);
	initializeGrid();
	
	
	return;
}
