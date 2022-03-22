#include<stdio.h>
#include<math.h>
#include<stdbool.h>

/*
	Write two numbers and check if they are prime numbers each other
*/

//bool prime(int number);
int checkGreaterNumber(int number1, int number2);
// Functions
/*
bool prime(int number){
	int count=0, i;
	for(i=1; i<=number; i++){
		if(number % i ==0){
			count++;
		}
	}
	if(count == 2){ //if count = 2, just 1 and the number itself are the divisors
		return true;
	} else {
		return false;
	}
}
*/
int checkGreaterNumber(int number1, int number2){
	if(number1>=number2){
		return number1;
	} else {
		return number2;
	}
}

void main(){
	int number1, number2; // numbers to be inserted
	int i, j;
	printf("Write two numbers in the next line and press Enter after the digitation:\n");
	scanf("%d %d", &number1, &number2);
	if((number1 <= 1) || (number2 <= 1)){
		printf("\nInvalid number.");
	} else{
		for(i=2; i<=checkGreaterNumber(number1, number2); i++){
			if((number1 % i == 0) && (number2 % i == 0)){
				printf("\nThe two numbers are not prime between them.");
				return;
			}
		}
		printf("\nThe two numbers are prime between them.");
	}
	return;
}
