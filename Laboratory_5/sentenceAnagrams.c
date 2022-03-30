#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

// This function checks out if a letter in the first sentence is not contained in the second one
// If both sentences have the same length but they differ from n characters, they cannot be anagrams

bool letterCheck(char * first, char * second){
	int i, j;
	char value;
	bool check=false;
	for(i=0;i<strlen(first);i++){
		if((first[i] >= 'A' && first[i] <= 'Z') || (first[i] >= 'a' && first[i] <= 'z')){  //check if the value chosen in first sentence is a letter or upper case letter
			value = first[i];
		} else {
			continue;
		}
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

//Check if the 2 sentence have the same length and they have the same letters

bool checkSentenceAnagram(char * first, char * second){
	int i, j, count=0;
	char reference[strlen(first)];
	bool check;
	if((strlen(first) != strlen(second)) || !(letterCheck(first, second)) || !(letterCheck(second, first))){ 
		return false;
	} else {
		
		for(i=0;i<strlen(reference); i++){
			reference[i] = '*';
		}
		
		for(i=0; i<strlen(first); i++){
			check = false;
			for(j=0; j<strlen(second); j++){
				if(first[i] == second[j] || !((first[i] >= 'A' && first[i] <= 'Z') || (first[i] >= 'a' && first[i] <= 'z'))){
					second[j]='*';
					check = true;
				}
			}
		}
		if(strcmp(reference, second) == 0){
			return false;
		} else {
			return true;
		}
		
	}
}


void main(){
	char sentence1[MAX], sentence2[MAX];
	bool result;
	printf("\nThis is a program that checks if two inserted words are one the anagram of the other.\n");
	printf("\nInsert the sentence word: \n");
	gets(sentence1);
	printf("\nInsert the sentence word: \n");
	gets(sentence2);
	result = checkSentenceAnagram(sentence1, sentence2);
	if(result){
		printf("\nThe two sentence are anagrams each other.");
	} else {
		printf("\nThe two sentence are not anagrams each other.");
	}
	return;
}
