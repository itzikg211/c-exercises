#if !defined(_A_STAR_H_)
#define _A_STAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SUCCESS 0
#define WRONG_NUM_ARGS -1
#define ERR_CLOSING_F -2
#define MAX_DISTANCE MAX_CELL_VALUE*NUM_ROWS*NUM_COLS
#define MAX_CELL_VALUE 1000 
#define SIZE_BUFFER 5
#define NUM_ROWS 5
#define NUM_COLS 5

/*Struct that defines a cell in the map*/
typedef struct cell {
	/*row(i),col(j) indexes in the map*/
	int row;
	int col;
	/*the minimum distance to this cell (g function)*/
	int distance;
	/*the weight of the cell*/
	int weight;
	/*the cell we came from in the shortest path*/
	struct cell* came_from;

}cell;

/*the function reads the map from a file and stores it in a cell array*/
cell** read_map(FILE* map_f);
/*The function convert a string to an integer*/
int str2int(char* str);
/*The function prints the map*/
void print_map(cell** map);
/*The function frees the allocated memory of the map*/
void del_map(cell** map);
/*The function implements a* algorithm and returns the shortest path from the starting point to the finish point
 *NOTE : the implementation is of 'a star' algorithm just as described in: https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode 
 * I implemented the function following the pseudo code*/
void a_star(cell** map);
/*The function updates the neighbors of the cell 'c' with the new distance*/
void update_neighbor_cells(cell** map, cell* c, int** set);
/*The function prints the path from start to finish*/
void print_path(cell* final);
/*The function returns the total length of the path*/
int len_path(cell* final);
/*The function frees the memory allocated for the set*/
void free_set(int** set);
/*The function allocates memory for a new set and fills it with 0s*/
int** empty_set();
/*The function check if the set is empty*/
int is_empty_set(int **set);
/*The function chooses the unvisited cell with the lowest f function value*/
cell* open_set_lowest_f(cell** map, int** set);
/*The function prints the set*/
void print_set(int** set);
/*The function return the 'manhattan' distance from the cell to the finish*/
int h_function(cell** map, cell* c);


#endif
