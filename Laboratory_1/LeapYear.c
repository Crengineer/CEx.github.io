#include<stdio.h>
#include<math.h>
#include<stdbool.h>

/*
	Write a program that determines if a year is a leap year or not
*/

//Functions
bool gregorian_calendar(int year);  //Check if the year is equal or over 1582
bool leap_year_check(int year);     //Check if the year is a leap year

// Implementations
bool gregorian_calendar(int year){
	if(year >= 1582){
		return true;
	}
	else {
		return false;
	}
}

bool leap_year_check(int year){
	if((!(year % 100 == 0) && (year % 4 == 0)) || (year % 400 == 0)){
		return true;
	}
	else {
		return false;
	}
}



// MAIN
void main(){
	int year;
	printf("Write a year and press Enter to validate your insert:\n");
	scanf("%d", &year);
	
	if(!gregorian_calendar(year)){
		printf("\nUnvalid year.\n");
		return;
	} else {
		if(leap_year_check(year)){
			printf("\nThe year is a Leap year.");
		} else {
			printf("\nThe year is not a Leap year.");
		}
	}
	return;
}
