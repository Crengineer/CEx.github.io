#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


void  main(){
	int number, curr, count=0, fixed=1;
	
	printf("\nInsert a series of number, terminated by 0,\n and the program would show up the maximum series of consecutive numbers.\n");
	scanf("%d", &number);
	curr = number;
	while(number != 0){
		if(number >= curr){
			count++;
		} else {
			count = 1;
		}
		if(count > fixed){
			fixed = count;
		}
		curr = number;
		scanf("%d", &number);
	}
	printf("\nThe maximum sequence of consecutive numbers is: %d", fixed);
	return;
}
