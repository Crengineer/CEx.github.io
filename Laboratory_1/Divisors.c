#include<stdio.h>
#include<math.h>

/*
	Write a number, and all the divisor greater than 1 and lower than the number will be displayed
*/

void main(){
	int number;
	int i;
	printf("Write an integer number, greater than 1:\n");
	scanf("%d", &number);
	if(number <= 1){
		printf("\nInvalid number.");
	} else {
		for(i=2; i<number; i++){
			if(number % i == 0){
				printf("%d ", i);
			}
		}
	}
	return;
}
