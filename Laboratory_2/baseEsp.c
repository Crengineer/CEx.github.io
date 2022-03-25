#include<stdio.h>
#include<math.h>
#include<stdlib.h>



void main(){
	int base, esp, i, j;
	printf("Enter a base and and exponent to calculate the power: \n");
	printf("\nBase: ");
	scanf("%d", &base);
	fflush(stdin);
	printf("\nExponent: ");
	scanf("%d", &esp);
	fflush(stdin);
	printf("\nThe powers, in order, of %d till %d", base, esp);
	// More exercise solution
	for(i=0;i<=esp;i++){
		if(i==0){
			j = 1;
		}
		else {
			j *= base;
		}
		printf("\n%d ^ %d = %d", base, i, j);
	}
	/*
	for(i=0; i<=esp; i++){
		printf("\n%d ^ %d = %d", base, i, (int) pow((double )base, (double) i));
	}
	*/
	return;
}
