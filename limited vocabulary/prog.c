#include "lim_vocabulary.h"


int main(int argc, char* argv[])
{
	/*'voc' stores the vocabulary file*/
	voc* v = NULL;
	FILE* f_voc = NULL;
	/*check number of arguments*/
	if(argc!=3){
		printf("Wrong number of arguments, usage: ./program_name txt_file vocabulary_file");
		return WRONG_NUM_ARG;
	}
	f_voc = fopen(argv[2],"r");
	if(f_voc == NULL){
		printf("Could not open the vocabulary file.\n");
		return ERR_OPENING;
	}
	v = file2voc(f_voc);
	print_voc(v);
	if(updatef(argv[1],v) < 0){
		printf("ERROR!\n");
		return -1;
	}
	delvoc(v);
	printf("finished successfuly!\n");
	return SUCCESS;
}
