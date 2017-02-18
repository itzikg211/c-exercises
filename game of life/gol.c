#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define INIT_NUM_ROWS 5
#define INIT_NUM_COLS 5
#define ENLARGE 1
#define REMAIN_THE_SAME 0
typedef enum state{DEAD,LIVE} state;

/*This struct contains the board of the game which contains states of cells
 * and the number of columns and rows in the board.*/
typedef struct board{
	state ** cells;
	int rows;
	int cols;

}board;

/*The functions checks the neighbors of a cell and returns it's new state*/
state check_neighbors(board* b,int row,int col);
/*The function prints the current board*/
void print_board(board* b);
/*The functions gets a number of rows and a number of columns and returns a board*/
board* init(int rows,int cols); 
/*The function plays the game of life*/
void play(board* b);
/*The function takes the board and makes it larger, it return the new board*/
board* enlarge(board* b);
/*The function checks if we should enlarge the board*/
int check_size(board* b);
/*The function checks if all the cells are dead*/
int check_all_dead(board* b);
/*The function deletes a board*/
void del_board(board* b);



int main(void)
{
	/*initialize a board*/
	board * b = init(INIT_NUM_ROWS,INIT_NUM_COLS);
	print_board(b);
	/*play the game*/
	play(b);
	return 0;
}

board* init(int rows,int cols){
	int i,j;
	/*allocating memory for the board*/
	board * b = malloc(sizeof(board));
	b->rows = rows;
	b->cols = cols;
	b->cells = (state**)malloc(sizeof(state*)*rows);
	for(i=0;i<rows;++i){
		b->cells[i] = (state*)malloc(sizeof(state)*cols);
		for(j=0;j<cols;j++){
			b->cells[i][j] = DEAD;
		}
	}
	/*setting the beginning of the board. NOTE: change this to play the game of life with other starting points*/
	b->cells[0][0] = LIVE;
	b->cells[1][0] = LIVE;
	b->cells[1][2] = LIVE;
	b->cells[2][1] = LIVE;
	b->cells[3][1] = LIVE;
	b->cells[4][1] = LIVE;

	return b;
}

board* enlarge(board* b){
	int i,j;
	/*initializing new board*/
	board* new_b = malloc(sizeof(board));
	new_b->rows = b->rows + 2;
	new_b->cols = b->cols + 2;
	new_b->cells = (state**)malloc(sizeof(state*)*(new_b->rows));
	for(i=0;i<new_b->rows;++i){
		new_b->cells[i] = (state*)malloc(sizeof(state)*new_b->cols);
		for(j=0;j<new_b->cols;j++){
			new_b->cells[i][j] = DEAD;
		}
	}
	/*copying the old board to the new one*/
	for(i=0;i<b->rows;++i){
		for(j=0;j<b->cols;j++){
			if(b->cells[i][j] == LIVE){
				new_b->cells[i+1][j+1] = LIVE;
			}
		}
	}
	/*free memory of old board*/
	del_board(b);
	return new_b;
}

void del_board(board* b){
	int i;
	/*free allocated memory*/
	for(i=0;i<b->rows;++i){
		free(b->cells[i]);
	}
	free(b->cells);
	free(b);
}

int check_all_dead(board* b){
	int i,j;	
	for(i=0;i<b->rows;++i){
		for(j=0;j<b->cols;j++){
			if(b->cells[i][j] == LIVE){
				return 1;
			}
		}
	}
	return 0;
}

void play(board* b){
	int i,j;
	board* new_b;
	/*play while there are live cells*/
	while(check_all_dead(b) != 0){
		/*check if need to enlarge the board*/
		if(check_size(b) == ENLARGE){
			b = enlarge(b);
		}
		/*initializing a new board*/
		new_b = malloc(sizeof(board));
		new_b->rows = b->rows;
		new_b->cols = b->cols;
		new_b->cells = (state**)malloc(sizeof(state*)*(b->rows));
		for(i=0;i<new_b->rows;++i){
			new_b->cells[i] = (state*)malloc(sizeof(state)*b->cols);
			for(j=0;j<new_b->cols;j++){
				/*checking the neighbors of each cell*/
				new_b->cells[i][j] = check_neighbors(b,i,j);
			}
		}
		/*deleting the old board*/
		del_board(b);
		b = new_b;
		print_board(b);
		/*sleeping for 1 second so we can see the changes apply*/
		sleep(1);
	}
	del_board(b);
	printf("Game is finished, all dead :(\n");

}

state check_neighbors(board* b,int row,int col){
	int counter = 0;
	/*check boundaries*/
	/*cell in first row*/
	if(row==0){
		/*cell in first column*/
		if(col==0){
			if(b->cells[row][col+1] == LIVE){++counter;}
			if(b->cells[row+1][col+1] == LIVE){++counter;}
			if(b->cells[row+1][col] == LIVE){++counter;}
		}
		else{
			/*cell in last cloumn*/
			if(col==b->cols-1){
				if(b->cells[row][col-1] == LIVE){++counter;}
				if(b->cells[row+1][col-1] == LIVE){++counter;}
				if(b->cells[row+1][col] == LIVE){++counter;}
			}
			else{
				if(b->cells[row+1][col] == LIVE){++counter;}
				if(b->cells[row][col-1] == LIVE){++counter;}
				if(b->cells[row+1][col-1] == LIVE){++counter;}
				if(b->cells[row][col+1] == LIVE){++counter;}
				if(b->cells[row+1][col+1] == LIVE){++counter;}

			}
		}
	}
	else{
		/*cell in last row*/
		if(row==b->rows-1){
			/*cell in first column*/
			if(col==0){
				if(b->cells[row-1][col] == LIVE){++counter;}
				if(b->cells[row-1][col+1] == LIVE){++counter;}
				if(b->cells[row][col+1] == LIVE){++counter;}
			}
			else{
				/*cell in last column*/
				if(col==b->cols-1){
					if(b->cells[row-1][col-1] == LIVE){++counter;}
					if(b->cells[row-1][col] == LIVE){++counter;}
					if(b->cells[row][col-1] == LIVE){++counter;}
				}
				else{
					if(b->cells[row][col-1] == LIVE){++counter;}
					if(b->cells[row-1][col-1] == LIVE){++counter;}
					if(b->cells[row-1][col] == LIVE){++counter;}
					if(b->cells[row-1][col+1] == LIVE){++counter;}
					if(b->cells[row][col+1] == LIVE){++counter;}

				}
			}
		}

		/*every cell which is not on border*/
		else{
			if(b->cells[row-1][col-1] == LIVE){++counter;}
			if(b->cells[row-1][col] == LIVE){++counter;}
			if(b->cells[row-1][col+1] == LIVE){++counter;}
			if(b->cells[row][col+1] == LIVE){++counter;}
			if(b->cells[row][col-1] == LIVE){++counter;}
			if(b->cells[row+1][col-1] == LIVE){++counter;}
			if(b->cells[row+1][col] == LIVE){++counter;}
			if(b->cells[row+1][col+1] == LIVE){++counter;}
		}
	}
	/*applying the rules of the game*/
	if(counter == 3 && b->cells[row][col] == DEAD){return LIVE;}
	if((counter == 2 || counter == 3) && b->cells[row][col] == LIVE){return LIVE;}
	return DEAD;

}



int check_size(board* b){
	
	int i;
	/*check if there is a live cell in the borders*/
	for(i=0;i<b->rows;++i){
		if(b->cells[i][0] == LIVE || b->cells[i][b->cols-1] == LIVE){
			return ENLARGE;
		}
	}
	for(i=0;i<b->cols;++i){
		if(b->cells[0][i] == LIVE){
			return ENLARGE;
		}
	}
	for(i=0;i<b->cols;++i){
		if(b->cells[b->rows-1][i] == LIVE){
			return ENLARGE;
		}
	}
	return REMAIN_THE_SAME;

}

void print_board(board* b){

	int i,j;
	for(j=0;j<b->cols+2;++j){
		printf("_");
	}
	printf("\n");
	for(i=0;i<b->rows;++i){
		printf("|");
		for(j=0;j<b->cols;++j){
			if(b->cells[i][j] == LIVE){
				printf("*");
			}
			else{
				printf("~");
			}
		}
		printf("|\n");
	}
	printf("\n");

}
