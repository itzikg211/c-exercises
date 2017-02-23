#include "a_star.h"

cell** read_map(FILE* map_f) {
	int i, j;
	int k = 0;
	char c;
	char buffer[SIZE_BUFFER];
	/*allocate memory for the map*/
	cell** map = malloc(sizeof(cell*)*NUM_ROWS);
	for (i = 0; i<NUM_ROWS; ++i) {
		map[i] = malloc(sizeof(cell)*NUM_COLS);
	}
	/*initialize the map*/
	for (i = 0; i<NUM_ROWS; ++i) {
		for (j = 0; j<NUM_COLS; ++j) {
			map[i][j].row = i;
			map[i][j].col = j;
			map[i][j].distance = MAX_DISTANCE;
			while ((EOF != (c = fgetc(map_f))) && (' ' != c) && ('\n' != c) && k<SIZE_BUFFER) {
				buffer[k] = c;
				k++;
			}
			buffer[k] = 0;
			k = 0;
			/*coverting the string read from the to an integer*/
			map[i][j].weight = str2int(buffer);
			map[i][j].came_from = NULL;
		}
	}
	/*updating only the distance of the first neighbors*/
	map[1][0].distance = map[0][0].weight + map[1][0].weight;
	map[0][1].distance = map[0][0].weight + map[0][1].weight;
	map[1][0].came_from = &map[0][0];
	map[0][1].came_from = &map[0][0];
	return map;

}

int str2int(char* str) {
	int i;
	int num = 0;
	int digit;
	/*run through 'str' and save each digit of the number*/
	for (i = 0; i<strlen(str); ++i) {
		digit = *(str + i) - '0';
		num += digit;
		if (i != strlen(str) - 1) {
			num *= 10;
		}
	}
	return num;
}

void print_map(cell** map) {
	int i, j;
	printf("map is:\n");
	for (i = 0; i<NUM_ROWS; ++i) {
		for (j = 0; j<NUM_COLS; ++j) {
			printf("%d ", map[i][j].weight);
		}
		printf("\n");
	}
}

void del_map(cell** map) {
	int i;
	for (i = 0; i<NUM_ROWS; ++i) {
		free(map[i]);
	}
	free(map);
}

void a_star(cell** map) {
	int** openset;
	int** closedset;
	cell* start = &map[0][0];
	cell* c = NULL;
	/*creating an openset and a closedset*/
	openset = empty_set();
	closedset = empty_set();
	/*inserting the starting cell to the openset*/
	openset[0][0] = 1;
	start->distance = start->weight;
	/*while openset is not empty*/
	while (is_empty_set(openset) == 1) {
		/*c = the node in openset having the lowest f function value*/
		c = open_set_lowest_f(map, openset);
		/*check if got to the final cell*/
		if (c->row == NUM_ROWS - 1 && c->col == NUM_COLS - 1) {
			printf("The cells we actually visited:\n");
			print_set(closedset);
			printf("The shortest path is:\n");
			print_path(c);
			printf("finished! Total distance is: %d\n", len_path(c));
			break;
		}
		
		/*removing c from open set*/
		openset[c->row][c->col] = 0;
		/*adding c to closed set*/
		closedset[c->row][c->col] = 1;
		/*update the distance of the neighbors*/
		update_neighbor_cells(map, c, openset);
	}
	/*free allocated memory*/
	free_set(openset);
	free_set(closedset);
	return;
}

int is_empty_set(int **set) {
	int i, j;
	for (i = 0; i<NUM_ROWS; ++i) {
		for (j = 0; j<NUM_COLS; ++j) {
			if (set[i][j] == 1) {
				return 1;
			}
		}
	}
	return 0;
}

int** empty_set() {
	int i, j;
	int** set = (int**)malloc(sizeof(int*)*NUM_ROWS);
	for (i = 0; i<NUM_ROWS; ++i) {
		set[i] = (int*)malloc(sizeof(int)*NUM_COLS);
		for (j = 0; j<NUM_COLS; ++j) {
			set[i][j] = 0;
		}
	}
	return set;
}

void print_set(int** set) {
	int i, j;
	for (i = 0; i<NUM_ROWS; ++i) {
		for (j = 0; j<NUM_COLS; ++j) {
			printf("%d ",set[i][j]);
		}
		printf("\n");
	}
	return;
}


cell* open_set_lowest_f(cell** map, int** set) {
	int i, j;
	int h;
	int min_distance = MAX_DISTANCE;
	cell* to_return = NULL;
	/*finding the visited cell with the shortest distance from the start*/
	for (i = 0; i<NUM_ROWS; ++i) {
		for (j = 0; j<NUM_COLS; ++j) {
			if (set[i][j] == 1) {
				h = h_function(map,&map[i][j]);
				/*f = g + h = (distance from start to cell)*(heuristic function)*/
				if (map[i][j].distance + h < min_distance) {
					min_distance = map[i][j].distance + h;
					to_return = &map[i][j];
				}
			}
		}
	}
	return to_return;

}

void update_neighbor_cells(cell** map, cell* c, int** set) {

	int row, col;
	cell* curr;
	int temp_weight = 0;
	row = c->row;
	col = c->col;
	/*neighbor up*/
	if (row - 1 >= 0 && col >= 0) {
		curr = &map[row - 1][col];
		/*calculating distance from start going through c*/
		temp_weight = c->distance + curr->weight;
		/*check if the new distance is shorter than original and the neighbor is unvisited*/
		if (temp_weight <= curr->distance && set[row - 1][col] == 0)
		{
				curr->came_from = c;
				curr->distance = temp_weight;
				set[row - 1][col] = 1;
		}
	}
	/*neighbor down*/
	if (row + 1 < NUM_ROWS && col >= 0) {
		curr = &map[row + 1][col];
		/*calculating distance from start going through c*/
		temp_weight = c->distance + curr->weight;
		/*check if the new distance is shorter than original and the neighbor is unvisited*/
		if (temp_weight <= curr->distance && (set[row + 1][col] == 0))
		{
				curr->came_from = c;
				curr->distance = temp_weight;
				set[row + 1][col] = 1;
		}
	}
	/*neighbor left*/
	if (row >= 0 && col - 1 >= 0) {
		curr = &map[row][col - 1];
		/*calculating distance from start going through c*/
		temp_weight = c->distance + curr->weight;
		/*check if the new distance is shorter than original and the neighbor is unvisited*/
		if (temp_weight <= curr->distance && (set[row][col - 1] == 0))
		{
				curr->came_from = c;
				curr->distance = temp_weight;
				set[row][col - 1] = 1;
		}
	}
	/*neighbor right*/
	if (row >= 0 && col + 1 < NUM_COLS) {
		curr = &map[row][col + 1];
		/*calculating distance from start going through c*/
		temp_weight = c->distance + curr->weight;
		/*check if the new distance is shorter than original and the neighbor is unvisited*/
		if (temp_weight <= curr->distance && (set[row][col + 1] == 0))
		{
				curr->came_from = c;
				curr->distance = temp_weight;
				set[row][col + 1] = 1;
		}
	}

}



void print_path(cell* final) {
	if (final->row == 0 && final->col == 0) {
		printf("(%d,%d)\n", final->row, final->col);
		return;
	}
	/*going to the "father" of the cell so we could print it*/
	print_path(final->came_from);
	printf("(%d,%d)\n", final->row, final->col);
}

int len_path(cell* final) {
	if (final->row == 0 && final->col == 0) {
		return final->weight;
	}
	/*going to the "father" of the cell and summing up the weights on the path*/
	return len_path(final->came_from) + final->weight;
}

void free_set(int** set) {
	int i;
	for (i = 0; i<NUM_ROWS; ++i) {
		free(set[i]);
	}
	free(set);
}

int h_function(cell** map, cell* c){
	int min = MAX_DISTANCE;
	int i,j;
	/*find minimum weight*/
	for(i=0;i<NUM_ROWS;++i){
		for(j=0;j<NUM_COLS;++j){
			if(map[i][j].weight < min){
				min = map[i][j].weight;
			}
		}
	}
	/*return (manhattan distance)*(min weight)*/
	return (NUM_ROWS - c->row - 1)*(NUM_COLS - c->col - 1)*min;
}
