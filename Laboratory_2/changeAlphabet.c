#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100


void fairyLanguage(char * string){
	int i = 0;
	printf("\nThe Fairy translation is: \n");
	while(string[i] != '\0'){
		if(string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u'){
			printf("f%c", string[i]);
		} else {
			printf("%c", string[i]);
		}
		i++;
	}
	printf("\n");
	return;
}


void florenceDialectVariant(char * string){
	int i = 0;
	printf("\nThe Florentine translation is: \n");
	while(string[i] != '\0'){
		if(string[i] == 'c'){
			printf("h");
		} else {
			printf("%c", string[i]);
		}
		i++;
	}
	printf("\n");
	return;
}

void shoutVersion(char * string){
	int i = 0;
	printf("\nThe Shout translation is: \n");
	while(string[i] != '\0'){
		if(string[i] >= 'A' && string[i] <= 'Z' || string[i] == ' '){
			printf("%c", string[i]);
		} else {
			printf("%c", string[i]-25);
		}
		i++;
	}
	printf("\n");
	return;
}



void main(){
	char word[MAX];
	printf("Write a sentence: it would be translated in fairy language!\n");
	gets(word);
	fairyLanguage(word);
	florenceDialectVariant(word);
	shoutVersion(word);
	return;
}
