#include<stdio.h>
#include<math.h>
#include<stdbool.h>

/*
	Write a number and check if it a prime number
*/

bool prime(int number);

// Functions
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


void main(){
	int number;
	printf("Write a number in the next line and press Enter after the digitation:\n");
	scanf("%d", &number);
	if(number <= 1 ){
		printf("\nInvalid number.");
	} else if(prime(number)){
		printf("The number is prime.\n");
	} else {
		printf("The number is not prime.\n");
	}
	return;
}
