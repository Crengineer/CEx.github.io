#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

// Padovan number succession: determine if a number is in Padovan succession


int PadovanSuccession(int n){	
	if(n==0 || n==1 || n==2){
		return 1;
	} else {
		return PadovanSuccession(n-2) + PadovanSuccession(n-3);  //rule of the Padovan succession: Padovan(n) = Padovan(n-2) + Padovan(n-3)
	}
}

bool checkPadovan(int n){
	int i = 0, check;
	check = PadovanSuccession(i);
	while(check <= n){
		if(check == n){
			return true;
		}
		i++;
		check = PadovanSuccession(i);
	}
	return false;
}


void main(){
	//Internal Variables
	int i;
	int number;
	
	// Padovan Succession based on indexing
	printf("Insert a number that represents the index of the succession: \n");
	scanf("%d", &number);
	printf("\nIndexes: \n");
	for(i=0;i<=number; i++){
		printf("%d ", i);
	}
	printf("\n");
	for(i=0;i<=number; i++){
		printf("| ");
	}
	printf("\n");
	for(i=0;i<=number; i++){
		printf("%d ", PadovanSuccession(i));
	}
	// Padovan succession: check if the inserted number is inside the succession
	printf("\nEnter a number and it will be checked if it is Padovan succession:\n");
	scanf("%d", &number);
	if(checkPadovan(number)){
		printf("\nThe number is present in Padovan succession.\n");
	} else {
		printf("\nThe number is not present in Padovan succession.\n");
	}
	return;
}
