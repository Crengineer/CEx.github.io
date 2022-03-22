#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

int numero[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1}; //numero di parole disponibili
int valore[26] = {1,2,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; //punteggio per lettera

int punteggio(char * s){
	
	return 0;
}

int valida(char * s){
	int i,j, diff=0, count=0;
	char ref;
	for(i=0;i<strlen(s);i++){
		ref = s[i];
		diff = ref - 'a';
		count = numero[diff];
		for(j=i;j<strlen(s);j++){
			if(s[j] == s[i]){
				count--;
				if(count < 0){
					return 0;
				}
			}
		}
	}
	return 1;
}

void main(){
	int i;
	printf("%d", valida("cab"));
	
	
	
	
	
	
	
	
	
	return;
}
