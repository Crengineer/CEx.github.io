<<<<<<< HEAD
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

// This function checks out if a letter in the first word is not contained in the second one
// If both words have the same length but they differ from n characters, they cannot be anagrams
bool letterCheck(char * first, char * second){
	int i, j;
	char value;
	bool check=false;
	for(i=0;i<strlen(first);i++){
		value = first[i];
		check=false;
		for(j=0; j<strlen(second); j++){
			if(second[j] == value){
				check = true;
			}
		}
		if(!check){
			return check;
		}
	}
	return check;
}


bool checkAnagram(char * first, char * second){
	int i, j, count=0;
	char reference[strlen(first)];
	bool check;
	if((strlen(first) != strlen(second)) || !(letterCheck(first, second)) || !(letterCheck(second, first))){  //Check if the 2 words have the same length and they have the same letters
		return false;
	} else {
		
		for(i=0;i<strlen(reference); i++){
			reference[i] = '*';
		}
		
		for(i=0; i<strlen(first); i++){
			check = false;
			for(j=0; j<strlen(second); j++){
				if(first[i] == second[j]){
					second[j]='*';
					check = true;
				}
			}
		//printf("\n%s", second);
		}
		if(strcmp(reference, second) == 0){
			return false;
		} else {
			return true;
		}
		
	}
}


void main(){
	char word1[MAX], word2[MAX];
	bool result;
	printf("\nThis is a program that checks if two inserted words are one the anagram of the other.\n");
	printf("\nInsert the first word: \n");
	gets(word1);
	printf("\nInsert the second word: \n");
	gets(word2);
	result = checkAnagram(word1, word2);
	if(result){
		printf("\nThe two words are anagrams each other.");
	} else {
		printf("\nThe two words are not anagrams each other.");
	}
	return;
}
=======
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

// This function checks out if a letter in the first word is not contained in the second one
// If both words have the same length but they differ from n characters, they cannot be anagrams
bool letterCheck(char * first, char * second){
	int i, j;
	char value;
	bool check=false;
	for(i=0;i<strlen(first);i++){
		value = first[i];
		check=false;
		for(j=0; j<strlen(second); j++){
			if(second[j] == value){
				check = true;
			}
		}
		if(!check){
			return check;
		}
	}
	return check;
}


bool checkAnagram(char * first, char * second){
	int i, j, count=0;
	char reference[strlen(first)];
	bool check;
	if((strlen(first) != strlen(second)) || !(letterCheck(first, second)) || !(letterCheck(second, first))){  //Check if the 2 words have the same length and they have the same letters
		return false;
	} else {
		
		for(i=0;i<strlen(reference); i++){
			reference[i] = '*';
		}
		
		for(i=0; i<strlen(first); i++){
			check = false;
			for(j=0; j<strlen(second); j++){
				if(first[i] == second[j]){
					second[j]='*';
					check = true;
				}
			}
		//printf("\n%s", second);
		}
		if(strcmp(reference, second) == 0){
			return false;
		} else {
			return true;
		}
		
	}
}


void main(){
	char word1[MAX], word2[MAX];
	bool result;
	printf("\nThis is a program that checks if two inserted words are one the anagram of the other.\n");
	printf("\nInsert the first word: \n");
	gets(word1);
	printf("\nInsert the second word: \n");
	gets(word2);
	result = checkAnagram(word1, word2);
	if(result){
		printf("\nThe two words are anagrams each other.");
	} else {
		printf("\nThe two words are not anagrams each other.");
	}
	return;
}
>>>>>>> 2f8dcec944728e424cf3e8559cbe9742e1284121
