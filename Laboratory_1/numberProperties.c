#include<stdio.h>
#include<math.h>
#include<stdbool.h>

/*
	In a sequence of numbers provided by the user, show the maximum, minimum, odd and non odd numbers. The sequence must be ended by a zero
*/

//Functions
bool evenNumber(int number); //determines if a number is even or not

//Function implementation
bool evenNumber(int number){
	if(number % 2 == 0){
		return true;
	} else {
		return false;
	}
}




void main(){
	int number, evenNum = 0, oddNum = 0; //number to be inserted, and counters for odd and not odd numbers
	double count=0, average=0, sum = 0; //
	int max, min;
	printf("Insert a sequence of positive numbers, ended by a 0:\n");
	scanf("%d", &number);
	while(number > 0){
		count++;
		if(count==1){   //at firts iteration, the maximun and minumum coincides
			max=number;
			min=number;
			average = number;
		}
		if(evenNumber(number)){
			evenNum++;
		} else  {
			oddNum++;
		}
		if(number >= max){
			max = number;
		}
		if(number <= min){
			min = number;
		}
		sum += number;
		average = sum / count;
		printf("\n");
		scanf("%d", &number);
	}
	printf("The number of even numbers is: %d\nThe number of odd numbers is: %d\n", evenNum, oddNum);
	printf("The maximum number is: %d\nThe minimum number is: %d\n", max, min);
	printf("The number of inserted number is: %f\nThe average is: %f\n", count, average);
	return;
}
