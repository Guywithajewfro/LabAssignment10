/*
	Edited by Daniel Nunez
	4/18/2024
	CS1 Lab Assignment 10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct trie {
	int isWord;
	struct trie *next[26];
} Trie;

// Inserts the word to the trie structure
void insert(Trie *pTrie, char *word) {
	if (strlen(word) == 0) {
		pTrie->isWord = 1;
		return;
	}
}

// computes the number of occurances of the word
int numberOfOccurances(Trie *pTrie, char *word) {
	if (strlen(word) == 0) return pTrie->isWord;
	int i=0;
	int nextIndex = word[i] - 'a';
	for (i=0; i<strlen(word); i++) {
		if (pTrie->next[nextIndex] == NULL) return 0;
		pTrie = pTrie->next[nextIndex];
	}
	return numberOfOccurances(pTrie->next[nextIndex], word);
}

// deallocate the trie structure
Trie *deallocateTrie(Trie *pTrie) {
	if (pTrie) {
		for (int i=0; i<26; i++) {
			if (pTrie->next[i]) deallocateTrie(pTrie->next[i]);
		}
		free(pTrie);
	}
}

// Initializes a trie structure
Trie *createTrie() {
	Trie *myTrie = (Trie *) malloc(sizeof(Trie));
	myTrie->isWord = 0;
	for (int i=0; i<26; i++) myTrie->next[i] = NULL;
	return myTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
	FILE *inFile = fopen(filename, "r");
	int dataSize = 0;
	char buffer[256];

	if (!inFile) {
		printf("Failed to open file %s\n", filename);
		exit(1);
	}

	while (fgets(buffer, sizeof(buffer), inFile)) {
		buffer[strcspn(buffer, "\n")] = 0;
		pInWords[dataSize] = strdup(buffer);
		dataSize++;
	}
	fclose(inFile);
	return dataSize;
}

int main() {
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0; i<numWords; ++i) printf("%s\n",inWords[i]);

	Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++) insert(pTrie, inWords[i]);
	
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0; i<5; i++) printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)  printf("There is an error in this program\n");
	return 0;
}