#if !defined(_LIM_VOCABULARY_H_)
#define _LIM_VOCABULARY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 16
#define SUCCESS	0
#define WRONG_NUM_ARG -1
#define ERR_OPENING -2
#define ERR_CLOSING -3
#define ERR_REMOVING -4

/*Struct that contains words and their translation.
 *This struct actually stores the data from the vocabulary*/
typedef struct words{
	char* w;
	char** translations;
	int num_trans;
}words;

/*Struct that contains all the words in the vocabulary file*/
typedef struct voc{
	struct words* vocabulary;
	int num_words;
}voc;

/*The function converts the vocabulary file into a 'voc' structure*/
voc* file2voc(FILE* f_voc);
/*The function checks if the word is in the dictionary - if it does than it returns a translation of the word*/
char* check_word(voc* v,char* word);
/*The function prints the vocabulary*/
void print_voc(voc* v);
/*The function updates a file using the vocabulary*/
int updatef(char* fname,voc* v);
/*The function frees all the memory allocated for the vocabulary*/
void delvoc(voc* v);
/*This function copies file 'f1' into file 'f2'*/
static void copy2files(FILE* f1,FILE* f2);


#endif
