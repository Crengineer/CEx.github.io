#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>

// Function that modify a matrix from a cell if it, restarting the count after the chosen cell
void initializeMatrix(int dim, int matrix[dim][dim]);
void printMatrix(int dim, int matrix[dim][dim]);

//Functions that create a matrix composed of incremental numbers, starting from 1
void initializeMatrix(int dim, int matrix[dim][dim]){
	int i, j, count = 1;
	//int mat[dim][dim] = matrix;
	for(i=1;i<=dim; i++){
		for(j=1; j<=dim; j++){
			matrix[i][j] = count;
			count++;
		}
	}
	printMatrix(dim, matrix);
}

//Print the matrix set in the 

void printMatrix(int dim, int matrix[dim][dim]){
	int i, j;
	for(i=1;i<=dim; i++){
		for(j=1; j<=dim; j++){
			printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
		
	}

// function that checks out the presence of a value inside a matrix
bool checkCell(int dim, int matrix[dim][dim], int value){
	int i, j;
	for(i=1;i<=dim; i++){
		for(j=1; j<=dim; j++){
			if(matrix[i][j] == value){
				return true;
			}
			}
			
		}
		return false;
}


void main(){
	int number, cellValue;
	bool validity=false;
	printf("To start the program, provide a dimension of the matrix, to initialize it:\n");
	scanf("%d", &number);
	int matrix[number][number];
	initializeMatrix(number, matrix);
	printf("\nSelect a number present in the previous matrix:\n");
	scanf("%d", &cellValue);
	while(validity==false){
		printf("\nSelect a number present in the previous matrix:\n");
		scanf("%d", &cellValue);
		validity = checkCell(number, matrix, cellValue);
	}
	
	return;
}
