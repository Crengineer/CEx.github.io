#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

#define MAX 10


double average(int * array){
	int i;
	double avg, sum=0, count = 0;
	for(i=0;i<MAX;i++){
		sum += array[i];
		count++;
	}
	return avg=sum/count;
}

int maxValue(int * array){
	int i, max=array[0];
	for(i=0;i<MAX;i++){
		if(array[i] >= max){
			max = array[i];
		}
	}
	return max;
}

int minValue(int * array){
	int i, min=array[0];
	for(i=0;i<MAX;i++){
		if(array[i] <= min){
			min = array[i];
		}
	}
	return min;
}


void main(){
	int seq[MAX], i;
	
	printf("\nInsert a sequence of %d elements: \n", MAX);
	for(i=0;i<MAX;i++){
		scanf("%d", &seq[i]);
	}
	
	//printf("\n%lf", average(seq));
	//printf("\n%d", maxValue(seq));
	//printf("\n%d", minValue(seq));
	
	return;
}
