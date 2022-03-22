#include<stdio.h>
#include<math.h>
#include<stdbool.h>

#define MAX 100


// Exercises used for determination of close-knit numbers = pair of numbers different one from another
// and their sum is equal to the product of the digits that compose them

//Functions
int multiplicateDigits(int number1, int number2); //This function gives as result the multiplication of the digits of two number
void closeKnitNumbersTwoDigits();                 //This function calculates all numbers greater than 0 and lower than 100


int multiplicateDigits(int number1, int number2){ 
	int multResult =1;
	while(number1 > 0){
		multResult *= (number1%10);
		number1 /= 10;
	}
	while(number2 > 0){
		multResult *= (number2%10);
		number2 /= 10;
	}
	return multResult;
}

void closeKnitNumbersTwoDigits(){
	printf("\nThe close-knit numbers greater than zero and lower than 100 are:\n");
	int i, j;
	for(i=1; i<MAX; i++){
		for(j=1; j<MAX; j++){
			if((i+j) == multiplicateDigits(i,j)){
				printf("%d + %d = %d\n", i, j, (i+j));
			}
		}
	}
	return;
}






void main(){
	closeKnitNumbersTwoDigits();
	return;
}
