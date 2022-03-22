#include<stdio.h>
#include<math.h>
#include<stdbool.h>

// Function that asks a number as input, and determines if there exist two numbers
// that, elevated to square and sum together, are equal to the number


void main(){
	int number;
	int i, j, count = 0; // i,j indexes for loops; count is used to check if the number has no sum squared
	
	printf("Enter an integer number and press Enter: \n");
	scanf("%d", &number);
	if(number < 0){
		printf("\nInvalid number inserted.");
		return;
	} else {
		printf("%d is the sum of the following square numbers: \n", number);
		for(i=1;i<=number;i++){
			for(j=1; j<=i; j++){
				if(((i*i) + (j*j)) == number){
					printf("\n%d ^2 + %d ^2 = %d\n", i, j, number);
					count++;
				}
			}
		}
		if(count==0){
				printf("\nThere are no squared numbers sum that are equal to the number.");
			}
		return;
	}
}
