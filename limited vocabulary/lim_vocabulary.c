#include "lim_vocabulary.h"

voc* file2voc(FILE* f_voc){
	voc* voc_from_file = malloc(1*sizeof(voc));
	words* keys = malloc(1*sizeof(words));
	char buffer[MAX_WORD_LEN];
	int num_keys = 0;
	int len = 0;
	int i;
	int c;
	while(EOF != (c = fgetc(f_voc))){
		/*saving the key word in the buffer*/
		while(c != ':'){
			buffer[len] = c;			
			++len;
			c = fgetc(f_voc);
		}
		buffer[len] = 0;
		keys = realloc(keys,(num_keys + 1)*sizeof(words));
		keys[num_keys].w = (char*)malloc(strlen(buffer));
		/*copying the buffer to the word array*/
		strcpy(keys[num_keys].w,buffer);
		
		keys[num_keys].num_trans = 0;
		keys[num_keys].translations = (char**)malloc(sizeof(char*));
		/*scanning the chars of the translation words*/
		while(EOF != (c = fgetc(f_voc))){
			len = 0;
			++keys[num_keys].num_trans;
			keys[num_keys].translations = (char**)realloc(keys[num_keys].translations,keys[num_keys].num_trans*sizeof(char*));
			/*saving the alternative word in the buffer*/
			while(c != '\n' && c != ','){
				buffer[len] = c;
				++len;
				c = fgetc(f_voc);	
			}
			buffer[len] = 0;
			keys[num_keys].translations[keys[num_keys].num_trans - 1] = (char*)malloc(strlen(buffer)+1);
			/*copying the buffer to the translations array*/
			strncpy(keys[num_keys].translations[keys[num_keys].num_trans - 1],buffer,strlen(buffer));
			if('\n' == c){
				break;			
			}
		}
		++num_keys;
		len = 0;
	}
	/*saving the vocabulary*/
	voc_from_file->vocabulary = keys;
	voc_from_file->num_words = num_keys; 
	return voc_from_file;
}

char* check_word(voc* v,char* word){
	int i;
	int r;
	/*if we got no word, just return*/
	if(strlen(word) == 0){
		return;
	}
	for(i=0;i<v->num_words;++i){
		if(strncmp(v->vocabulary[i].w,word,strlen(word))==0){
			/*if there is only one translation to the word return it*/			
			if(v->vocabulary[i].num_trans == 1){
				return v->vocabulary[i].translations[0];
			}
			
			/*if there is more than one translation choose one randomly*/
			r = rand()%(v->vocabulary[i].num_trans);
			return v->vocabulary[i].translations[r];
		}
	}
	return word;
}


void print_voc(voc* v){

	int i,j;
	printf("The vocabulary is:\n");
	for(i=0;i<v->num_words;++i){
		printf("word = %s ",v->vocabulary[i].w);
		for(j=0;j<v->vocabulary[i].num_trans;++j){
			printf("translation = %s ",v->vocabulary[i].translations[j]);
		}
		printf("\n");
	}
	return;
}

int updatef(char* fname,voc* v)
{
	FILE* fr = NULL;
	int c;
	int i;
	int len=0;
	char buffer[MAX_WORD_LEN];
	/*the word we write to the file*/
	char* wr;
	/*opening files*/
	FILE* temp = fopen("temp_file.txt","w+");
	/*using this to ensure the randomness of the translation word*/
	srand(time(NULL));	
	if(temp == NULL){
		printf("Could not open a temporary file to store the new text.\n");
		return ERR_OPENING;
	}
	fr = fopen(fname,"r");
	if(fr == NULL){
		printf("Could not open the text file.\n");
		return ERR_OPENING;
	}
	while(EOF != (c = fgetc(fr))){
		/*saving the word in the buffer*/
		while(c != '\n' && c != ' ' && c !='.' && c !=',' && c != EOF){
			buffer[len] = c;
			++len;
			c = fgetc(fr);
		}
		/*if we read a word and the last char is unique ('\n','.',',',' ') we store it and continue*/
		if(len == 0){
			fputc(c,temp);
			continue;
		}
		buffer[len] = 0;
		wr = (char*)malloc(strlen(buffer)+1);
		/*copy the buffer to string 'wr'*/
		strcpy(wr,buffer);
		/*store the word in the file, but first check if there is a translation word*/
		fputs(check_word(v,wr),temp);
		free(wr);
		/*saving one more character('\n','.',',',' ')*/
		fputc(c,temp);
		len = 0;
	}
	/*close files*/
	if(0!= fclose(temp)){
		printf("Couldn't close a temporary file.\n");
		return ERR_CLOSING;	
	}
	if(0!= fclose(fr)){
		printf("Couldn't close the text file.\n");
		return ERR_CLOSING;	
	}
	
	/*open files in different mode*/
	temp = fopen("temp_file.txt","r");	
	if(temp == NULL){
		printf("Could not open a temporary file to read the stored text.\n");
		return ERR_OPENING;
	}
	fr = fopen(fname,"w+");
	if(fr == NULL){
		printf("Could not open the text file in order to change it.\n");
		return ERR_OPENING;
	}
	/*copying the temporary file into the text file*/
	copy2files(temp,fr);
	/*closing the files*/
	if(0!= fclose(temp)){
		printf("Couldn't close a temporary file.\n");
		return ERR_CLOSING;	
	}
	if(0!= fclose(fr)){
		printf("Couldn't close the text file.\n");
		return ERR_CLOSING;	
	}
	if(0 != remove("temp_file.txt")){
		printf("Couldn't remove the temporary file.\n");
		return ERR_REMOVING;
	}
	return SUCCESS;
}

void delvoc(voc* v){
	int i,j;
	for(i=0;i<v->num_words;++i){
		for(j=0;j<v->vocabulary[i].num_trans;++j){
			/*free translation strings*/
			free(v->vocabulary[i].translations[j]);
		}
		/*free word string*/
		free(v->vocabulary[i].w);
	}
	/*free words struct*/
	free(v->vocabulary);
	/*free voc struct*/
	free(v);
	return;
}

static void copy2files(FILE* f1,FILE* f2){
	int c;
	/*copy content*/
	while(EOF != (c = fgetc(f1))){
		fputc(c,f2);
	}
	return;
}


