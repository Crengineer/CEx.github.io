#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

//Function that check if the number is repetitive or not

bool checkRepetitive(int n){
	int i, sup;
	if(n <= 0){
		return false;
	}
	while(n>0){
		i=n%10;
		sup = n/10;
		while(sup>0){            // This cycle analyse number by number by right hand to left hand
			if((sup%10) == i){
				return true;     //if the last right number is equal to the previous one extracted, there is a repetition
			} else {
				sup/=10;
			}
		}
		n/=10;     //part of the problem that reduce the number at each iteration
	}
	return false;
}



void main(){
	int number;
	bool rep;
	printf("\nInsert a number, the program will check if it is repetitive or various:\n");
	scanf("%d", &number);
	if(rep=checkRepetitive(number) == true){
		printf("\nThe number is repetitive.\n");
	} else {
		printf("\nThe number is not repetitive.\n");
	}
	return;
}
