#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#define N 7

/*
	Write a program than reordinates the strings of an elencation of them
*/

/*
	Type definitions
*/

typedef char word[20];
typedef word elencation[N];

// Functions

void printSet(elencation set);
void insertStrings(elencation set);
elencation *reorderSet(elencation set);

//Function that prints the element of the set
void printSet(elencation set){
	int i;
	printf("\nThe words in the set are:\n");
	for(i=0; i<sizeof(set); i++){
			printf("\n%s", set[i]);
	}
}

// Function that enables the insertion of words into the set
void insertStrings(elencation set){
	int i=0;
	word insWord;
	printf("\nInsert a maximum of %d words, enter '-1' to terminate before the end:\n", N);
	while(i<sizeof(set)){
		gets(insWord);
		if(strcmp(insWord, "-1") == 0){
			break;
		}
		strcpy(set[i], insWord);
		i++;
	}
	return;
}

//Function that reordinates the elements of the set
elencation *reorderSet(elencation set){
	int i=0,j;
	word sub, temp;
	while(i<sizeof(set)){
		strcpy(sub, set[i]);
		for(j=i;j<sizeof(set); j++){
			if(strcmp(set[j], sub) < 0){
				strcpy(temp, set[j]);
				strcpy(set[j], sub);
				strcpy(sub, temp);
			}
		}
		strcpy(set[i], sub);
		i++;
	}
	return set;
}


void main(){
	elencation wordSet = {};
	elencation * point;
	insertStrings(wordSet);
	printSet(wordSet);
	point = &wordSet;
	point = reorderSet(wordSet);
	printf("\nThe set has been reordered by alphabetic criteria. Here is the elencation:\n");
	printSet(point);
	return;
}
