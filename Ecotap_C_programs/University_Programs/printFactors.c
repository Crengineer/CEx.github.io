#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

// Write a function that calculates the prime factor of a number, with their elevation to power

void printFactors(int n){
	int i, count = 0;  // count is the counter of the power of a factor, while i is the index used for factor 
	printf("\n%d: 1 ", n);
	for(i=2; i<=n; i++){
		while(n % i == 0){
			count++;
			n /= i;
		}
		if(count>1 ){
			printf(" %d^%d ", i, count);
		} else if(count == 1){
			printf(" %d ", i);
		}
		count = 0;    //reset count to 0 every cycle for starting out the next power
	}
}



void main(){
	int number;
	
	printf("Write a integer positive number and press Enter:\n");
	scanf("%d", &number);
	printf("\nThe prime factors of %d are:\n", number);
	printFactors(number);
	
	return;
}
