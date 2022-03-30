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
	int seq[MAX], i,j, min, max;
	
	//Keyboard insert
	printf("\nInsert a sequence of %d elements: \n", MAX);
	for(i=0;i<MAX;i++){
		scanf("%d", &seq[i]);
	}
	
	//Min e Max
	min=minValue(seq);
	max=maxValue(seq);
	
	if(!(min< 0)){
		min =0;
	}
	if(!(max > 0)){
		max =0;
	}
	for(i=0; i<MAX; i++){
		printf("---");
	}
	printf("\n");
	for(i=max; i>=min; i--){
		if(i<10){
			printf("%d  |", i);
		} else {
			printf("%d | ", i);
		}
		
		for(j=0;j<10;j++){
			if(seq[j] >= 0 && i >= 0){
				if(i == (int)average(seq) || i==0){
				printf("---");
			} else if(seq[j] >= i){
				printf(" * ");
			} else {
				printf("   ");
			}
			} else if(seq[j] < 0 && i <= 0) {
			if(i == (int)average(seq) || i==0){
				printf("---");
			} else if(seq[j] <= i){
				printf(" * ");
			} else {
				printf("   ");
			}
			}
			
		}
		printf("\n");
	}
	printf("    ");
	for(i=0; i<MAX; i++){
		printf("---");
	}
	printf("\n");
	max=0;
	for(i=0; i<2; i++){
		printf("   ");
		for(j=0;j<MAX;j++){
			if(i==0){
				max++;
				printf(" %d ", max);
			}
			if(i==1){
				printf(" %d ", seq[j]);
			}
		}
		printf("\n");
	}
	
	
	
	//printf("\n%lf", average(seq));
	//printf("\n%d", maxValue(seq));
	//printf("\n%d", minValue(seq));
	
	return;
}
