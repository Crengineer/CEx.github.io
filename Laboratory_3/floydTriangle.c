#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

#define MAX 50


void floydTriangle(int n){
	int i, j, count = 0;
	for(i=0; i<n; i++){
		for(j=0;j<n; j++){
			
			if(j<=i){
				count ++;
				printf("%d ", count);
			}
		}
		printf("\n");
	}
}

void reversedFloydTriangle(int n){
	int i, j, count = 0, prev;
	for(i=0; i<n; i++){
		for(j=0;j<n; j++){
			if(j>=i){
				count ++;
			}
		}
	}
	for(i=n; i>0; i--){
		for(j=0;j<n; j++){
			if(i>j){
				printf("%d ", count-i+1+j);
			}
		}
		count -= i;
		printf("\n");
	}
}


void main(){
	int number;
	printf("\nWrite down a number: the program will display the consequent number of lines of Floyd triangle: \n");
	scanf("%d", &number);
	printf("\n");
	floydTriangle(number);
	printf("\n");
	reversedFloydTriangle(number);
	
	
}
