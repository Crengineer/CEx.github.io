#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

//Functions that checks if two numbers are anagrams or not each other

bool checkAnagramNumbers(int num1, int num2){
	double count=1;
	int sup=num1, power, ref, ref2;
	//Part of the code in which is stated the 10^(n-1) power 
	sup/=10;
	while(sup>=10){
		count++;
		sup/=10;
	}
	//Check the most significant position of first number with respect to the least significant one
	//of the second number
	while(num2>0){
		power=(int)pow(10,count);
		ref = num1/power;
		
		if((ref) != (num2%10)){   //if the comparison fails, the two number are not anagrams
			return false;
		} else {
			num1-=ref*power;      //At every cycle, we erase the most significant position for the first number
			num2/=10;		      //At every cycle, we erase the least significant position for the second number
			count--;
		}
	}
	return true;
}



void main(){
	int num1, num2;
	printf("\nInsert two numbers to check if they are anagrams each other:\n");
	printf("\nInsert the first number:\n");
	scanf("%d", &num1);
	printf("\nInsert the second number:\n");
	scanf("%d", &num2);
	if(checkAnagramNumbers(num1, num2) == true){
		printf("\nThe two numbers are anagrams each other.\n");
	} else {
		printf("\nThe two numbers are not anagrams each other.\n");
	}
	
	return;
}
