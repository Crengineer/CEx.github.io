#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


void fullFormAsteriscs(int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf(" * ");
		}
		printf("\n");
	}
	return;
}

void emptyFormAsteriscs(int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==0 || i==(n-1)){
				printf(" * ");
			} else 
			if(!(i==0 || i==(n-1)) && !(j!=0 && j!=(n-1))){
				printf(" * ");
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}
	return;
}

void triangle(int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i>=j){
				printf(" * ");
			}
		}
		printf("\n");
	}
	return;
}

void triangleAndPlus(int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i>=j){
				printf(" * ");
			}
			else {
				printf(" + ");
			}
		}
		printf("\n");
	}
	return;
}






void main(){
	int number, i, j;
	printf("\nChoose a number and a square NxN would appear: \n");
	scanf("%d", &number);
	fullFormAsteriscs(number);
	printf("\n");
	emptyFormAsteriscs(number);
	printf("\n");
	triangle(number);
	printf("\n");
	triangleAndPlus(number);
	return;
}
