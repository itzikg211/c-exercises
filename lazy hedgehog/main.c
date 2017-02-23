#include "a_star.h"

int main(int argc, char* argv[])
{
	FILE* map_f = NULL;
	cell** map = NULL;

	/*check argument count*/
	if (argc != 2) {
		printf("Wrong number of arguments, usage: ./program_name world_map_file");
		return WRONG_NUM_ARGS;
	}
	/*open file containing map*/
	map_f = fopen(argv[1], "r");
	if (map_f == NULL) {
		printf("ERR opening file\n");
		return -1;
	}
	/*store the map from the file*/
	map = read_map(map_f);
	/*print the map*/
	print_map(map);
	/*run A STAR algorithm on the map*/
	a_star(map);
	/*free alocated memory*/
	del_map(map);
	/*closing file*/
	if (0 != fclose(map_f)) {
		printf("ERR closing file\n");
		return ERR_CLOSING_F;
	}
	return SUCCESS;
}

