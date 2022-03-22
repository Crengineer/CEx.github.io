#include<stdio.h>
#include<math.h>

#define MAX_LENTH 10

/*
	User must provide 2 integer numbers and the program must display a grid of multiples
*/


void main(){
	int rows, columns; //parameters
	int i, j; //loop counters
	printf("Insert two numbers in the nexr line, divided by space, as in the example: 6 8\n");
	printf("Maximum value to be inserted for both numbers: %d\nThe first number will be the number of rows, the other the number of columns\n", MAX_LENTH);
	scanf("%d %d", &rows, &columns);
	
	// Grid print with multiples
	
	//first line with the column indexes
	printf("\n      ");
	for(j=1; j<=columns; j++){
		printf("%d    ", j);
	}
	printf("\n      ");
	for(j=1; j<=columns; j++){
		printf("-----", j);
	}
	printf("\n");
	//Grid with row indexes and multiplications between indexes
	for(i=1; i<=rows; i++){
		if(i<10){
			printf("\n%d|    ", i);
		}
		if(i>=10){
			printf("\n%d|   ", i);
		}
		
		for(j=1;j<=columns;j++){
			if((i*j) <=9){
				printf("%d    ", i*j);
			}
			if(((i*j) >=10) && ((i*j)<=100)){
				printf("%d   ", i*j);
			}
		}
		printf("\n");
	}
	return;
}
