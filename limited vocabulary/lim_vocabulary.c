#include "lim_vocabulary.h"

voc* file2voc(FILE* f_voc){
	voc* voc_from_file = malloc(1*sizeof(voc));
	words* keys = malloc(1*sizeof(words));
	int num_keys = 0;
	int len = 0;
	int i;
	int c;
	while(EOF != (c = fgetc(f_voc))){
		/*calculating the length of the key word*/
		while(c != ':'){
			++len;
			c = fgetc(f_voc);	
		}
		keys = realloc(keys,(num_keys + 1)*sizeof(words));
		keys[num_keys].w = (char*)malloc(len+1);
		/*going back 'len' chars so we can save the word*/
		fseek(f_voc,-(len+1),SEEK_CUR);
		/*saving the key word*/
		for(i=0;i<len;++i){
			c = fgetc(f_voc);
			keys[num_keys].w[i] = tolower(c);
		}
		/*inserting NULL termination char*/
		keys[num_keys].w[len] = 0;
		/*reading ':' character*/
		c = fgetc(f_voc);
		keys[num_keys].num_trans = 0;
		keys[num_keys].translations = (char**)malloc(sizeof(char*));
		/*scanning the chars of the translation words*/
		while(EOF != (c = fgetc(f_voc))){
			len = 1;
			++keys[num_keys].num_trans;
			keys[num_keys].translations = (char**)realloc(keys[num_keys].translations,keys[num_keys].num_trans*sizeof(char*));
			/*calculating the length of the alternative word*/
			while(c != '\n' && c != ','){
				++len;
				c = fgetc(f_voc);	
			}
			
			keys[num_keys].translations[keys[num_keys].num_trans - 1] = (char*)malloc(len);
			/*going back 'len' chars so we can save the translation word*/
			fseek(f_voc,-len,SEEK_CUR);
			/*stroing the translation in the right place*/
			for(i=0;i<len;++i){
				if(',' != (c = fgetc(f_voc)) && c != '\n'){
					keys[num_keys].translations[keys[num_keys].num_trans - 1][i] = tolower(c);
				}
			}
			/*inserting NULL termination char*/
			keys[num_keys].translations[keys[num_keys].num_trans - 1][len] = 0;
			/*check if finished going through translations and can go to the next word*/
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
	/*calculating the length of the word*/
		while(c != '\n' && c != ' ' && c !='.' && c !=',' && c != EOF){
			++len;
			c = fgetc(fr);
		}
		/*if we read a word and the last char is unique ('\n','.',',',' ') we store it and continue*/
		if(len == 0){
			fputc(c,temp);
			continue;
		}
		wr = (char*)malloc(len+1);
		/*going back 'len' chars so we can save the word*/
		fseek(fr,-(len+1),SEEK_CUR);
		/*saving the chars of the word*/
		for(i=0;i<len;++i){
			c = fgetc(fr);
			wr[i] = c;
		}
		wr[len] = 0;
		/*storing the word in the temporary file after checking if there is a translation*/
		fputs(check_word(v,wr),temp);
		free(wr);
		/*reading one more character('\n','.',',',' ')*/
		c = fgetc(fr);
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


