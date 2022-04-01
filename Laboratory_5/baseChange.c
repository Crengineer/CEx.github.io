<<<<<<< HEAD
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

//this program translate a number from a base different from 10 to its decimal version
double baseChange(int number, int sourceBase, int destBase){
	int i=0, rest, count=0, baseTenNumber=0;
	while(number>0){
		rest = number % 10;
		baseTenNumber += rest*pow((double)sourceBase,(double)count);
		//printf("\n%lf", baseTenNumber);
		count++;
		number /= 10;
	}
	number = 0;
	count = 0;
	int newBaseNumber =(int) baseTenNumber;
	
	while(newBaseNumber>0){
		rest = newBaseNumber % destBase;
		number += rest*pow(10,count);
		printf("\n%d", number);
		count++;
		newBaseNumber /= destBase;
	}
	return (int)number;
}


void main(){
	int base1, base2, num;
	
	printf("\nInsert the base of the first number; it has to be between 2 and 10:\n");
	scanf("%d", &base1);
	while(!(base1>=2 && base1<=10)){
		printf("\nInsert the base of the number; it has to be between 2 and 10:\n");
		scanf("%d", &base1);
	}
	printf("\nInsert the destination base of the number; it has to be between 2 and 10:\n");
	scanf("%d", &base2);
	while(!(base2>=2 && base2<=10)){
		printf("\nInsert the destination base of the number; it has to be between 2 and 10:\n");
		scanf("%d", &base2);
	}
	printf("\nInsert the number:\n");
	scanf("%d", &num);
	
	printf("%d", baseChange(num, base1, base2));
	
	
	
	return;
}
=======
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

//this program translate a number from a base different from 10 to its decimal version
double baseChange(int number, int sourceBase, int destBase){
	int i=0, rest, count=0, baseTenNumber=0;
	while(number>0){
		rest = number % 10;
		baseTenNumber += rest*pow((double)sourceBase,(double)count);
		//printf("\n%lf", baseTenNumber);
		count++;
		number /= 10;
	}
	number = 0;
	count = 0;
	int newBaseNumber =(int) baseTenNumber;
	
	while(newBaseNumber>0){
		rest = newBaseNumber % destBase;
		number += rest*pow(10,count);
		printf("\n%d", number);
		count++;
		newBaseNumber /= destBase;
	}
	return (int)number;
}


void main(){
	int base1, base2, num;
	
	printf("\nInsert the base of the first number; it has to be between 2 and 10:\n");
	scanf("%d", &base1);
	while(!(base1>=2 && base1<=10)){
		printf("\nInsert the base of the number; it has to be between 2 and 10:\n");
		scanf("%d", &base1);
	}
	printf("\nInsert the destination base of the number; it has to be between 2 and 10:\n");
	scanf("%d", &base2);
	while(!(base2>=2 && base2<=10)){
		printf("\nInsert the destination base of the number; it has to be between 2 and 10:\n");
		scanf("%d", &base2);
	}
	printf("\nInsert the number:\n");
	scanf("%d", &num);
	
	printf("%d", baseChange(num, base1, base2));
	
	
	
	return;
}
>>>>>>> 2f8dcec944728e424cf3e8559cbe9742e1284121
