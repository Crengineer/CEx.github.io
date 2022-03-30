#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>


// Function that modify a matrix from a cell if it, restarting the count after the chosen cell
int **initializeMatrix( int dim);
int getSize(int * array);
int *passElements(int * array, int * array2, int dim);

void printArray(int * array, int dim);
void printMatrix( int ** matrix, int dim);

bool checkCell(int dim, int ** matrix, int value);
int * indexesCheck(int dim, int ** matrix, int value);
int ** increaseValues(int **m, int * ind, int dim);


// Get the size of an array

int getSize(int * array){
	return (int)sizeof(array)/sizeof(array[0]);
}

//copy line of a matrix inside an array
int *passElements(int * array, int * array2, int dim){
	int i;
	//int * pointer;
	for(i=0; i<dim; i++){
		array[i] = array2[i];
	}
	//printArray(array, dim);
	return array;
}


//Functions that create a matrix composed of incremental numbers, starting from 1
int **initializeMatrix(int dim){
	int i=0, j=0, count = 1, num_rows = dim, num_cols = dim;
	int **m = (int **)malloc(sizeof(int *) * dim);         //Declaration of the pointer to matrix, where we allocate a vector of array pointers
	for(i=0; i<dim; i++){                                  //In this cycle, we allocate the lines of the matrix
		m[i] = (int *) malloc(sizeof(int) * dim);         
	}
	for(i=0;i<num_rows; i++){                 //We initialize the matrix with 1, 2, etc.
		for(j=0; j<num_cols; j++){
			m[i][j] = count;
			count++;
		}
	}
	return m;
}

// Function that increments the values after the element chosen
int ** increaseValues(int **m, int * ind, int dim){
	int indX = ind[0], indY = ind[1], i=0, j=0, ref, count=0;
	
	// This cycle put every cell after the position [indX,indY] from 0 and incremented by 1 at every cycle
	for(i=indX; i<dim; i++){
		for(j=indY+1;j<dim;j++){
			m[i][j] = count;
			count++;
			if((i==dim-1) && (j==dim-1)){
				ref = m[indX][indY];            //ref is set as the chosen element
			}
		}
	}
	// This cycle put every cell from the first to the one [indX,indY] incremented by the last element of the matrix
	for(i=0; i<indX; i++){
		for(j=0;j<indY;j++){
			if(m[i][j] < m[indX][indY]){
				m[i][j]+= ref; 
			}
			
		}
	}
	
	//This cycle put at the same value all the elements present in the same line or row of the element chosen
	for(i=0; i<dim; i++){
		for(j=0;j<dim;j++){
			if(i==indX || j == indY){
				m[i][j] = m[indX][indY];
			}
		}
	}
	return m;
}

//Print array elements

void printArray(int * array, int dim){
	int i;
	printf("\n");
	for(i=0; i<dim; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	return;
}


//Print the matrix passed by parameter

void printMatrix(int ** matrix, int dim){
	int i, j, num_rows = dim, num_cols = dim;
	printf("\n     ");
	for(i=0;i<num_rows; i++){
		printf("%d    ", i);
	}
	printf("\n");
	for(i=0;i<num_rows; i++){
		printf("\n%d    ", i);
		for(j=0; j<num_cols; j++){
			printf("%d   ", matrix[i][j]);
		}
		//printf("\n");
	}
		return;
}

// function that checks out the presence of a value inside a matrix

bool checkCell(int dim, int ** matrix, int value){
	int i, j;
	for(i=0;i<dim; i++){
		for(j=0; j<dim; j++){
			if(matrix[i][j] == value){
				return true;
			}
		}
	}
	return false;
}

// Function that returns the position of the element chosen by user

int * indexesCheck(int dim, int ** matrix, int value){
	int i, j;
	int *ind = (int *)malloc(sizeof(int) * 2);
	for(i=0;i<dim; i++){
		for(j=0; j<dim; j++){
			if(matrix[i][j] == value){
				ind[0] = i;
				ind[1] = j;
				return ind;
			}
		}
	}
	return NULL;
}


void main(){
	//Variable declaration
	int number, cellValue=0, ** matrixPointer;
	bool validity=false;
	
	// Matrix Initialisation
	printf("To start the program, provide a dimension of the matrix, to initialize it:\n");
	scanf("%d", &number);
	matrixPointer = initializeMatrix(number);
	printMatrix(matrixPointer, number);
	
	//Select number inside the matrix
	printf("\nSelect a number present in the previous matrix:\n");
	scanf("%d", &cellValue);
	while(!validity){
		validity = checkCell(number, matrixPointer, cellValue);
		if(validity){
			printf("\nThe number is present!");
			break;
		} else {
			printf("\nThe number is not present!");
		}
		printf("\nSelect a number present in the previous matrix:\n");
		scanf("%d", &cellValue);
	}
	// Find out the indexes of the number chosen in the matrix
	int * indexes;
	indexes = indexesCheck(number, matrixPointer, cellValue);
	printf("\nThe indexes of the element chosen: \n");
	printArray(indexes, 2);
	printf("\nThe program would increment the values of cells after the previous one chosen.");
	printf("\nAt the end of the matrix, the increase will restart from the first element till the chosen one before.");
	printf("\nAll the elements in the line or column of the chosen element are set to the element.\n");
	
	matrixPointer = increaseValues(matrixPointer, indexes, number);
	printMatrix(matrixPointer, number);
	
	
	return;
}
