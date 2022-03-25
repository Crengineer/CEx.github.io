#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

#define MAX 50


bool isParenthesisBalanced(char * word){
	int count=0,i=0;
	while(word[i] != '\n'){
		if(word[i] == '('){
			count++;
		} else if(word[i] == ')'){
			count--;
		}
		i++;
	}
	if(count == 0){
		return true;
	} else {
		return false;
	}
}


void main(){
	char word[MAX];
	printf("\nWrite down a sentence; the program will check the balance of open / closed parenthesis:\n");
	gets(word);
	if(isParenthesisBalanced(word)){
		printf("\nThe sentence is parenthesis balanced.\n");
	} else {
		printf("\nThe sentence is not parenthesis balanced.\n");
	}
	
	
	return;
}
