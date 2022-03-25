#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

#define MAX 100


void caesarCiphers(char * word, int n){
	int i;
	printf("\n");
	for(i=0; i<=strlen(word); i++){
			if( word[i] == ' ' ||  word[i] == '.' || word[i] == ',' || word[i] == ';' || word[i] == '!' || word[i] == '?'){  //Characters not letters are not delayed
			printf("%c", word[i]);
		} else if( word[i] >= 'A' && word[i] <= 'Z'){   // Upper case letters
			if((word[i] + n) > 'Z'){
				printf("%c", word[i] + n -26);  //Characters after Z are not upper case letters, we restart the count from A
			} else {
				printf("%c", word[i] + n);
			}
		} else if( word[i] >= 'a' && word[i] <= 'z'){  //Lower case letters
			if((word[i] + n) > 'z'){
				printf("%c", word[i] + n -26);   //Characters after z are not upper case letters, we restart the count from a
			} else {
				printf("%c", word[i] + n);
			}
	}
}
}


void main(){
	char word[MAX];
	int delay;
	printf("\nWrite down a sentence; the program will apply the Caesar ciphrarium:\n");
	gets(word);
	printf("\nDecide a delay number for the code:\n");
	scanf("%d", &delay);
	caesarCiphers(word, delay);
	
	
	return;
}
