#if !defined(_MY_QUEUE_H)
#define _MY_QUEUE_H
#include <stdio.h>
#include <stdlib.h>

/*A struct that contains a dynamic integer array,
* the amount of variables in the queue,
  and a pointer to the beginning of the queue.*/
typedef struct queue{
	/*qq -> the queue itself*/
	int* qq;
	/*length -> the length of the queue*/
	int length;
	/*first -> a pointer to the head of the queue.
	* This variable is essential for freeing the queue in the end*/
	int* first;
}queue;

/*The function creates a new q, the head of the queue will contain 'val'.
* It returns a pointer for the new queue.*/
queue* my_queue_ctor(int val);
/*The function destroys the queue by freeing it.*/
void my_queue_dtor(queue* q);
/*The function adds 'val' to the queue-'q'.*/
void my_queue_add(queue* q, int val);
/*The function removes the head of the queue-'q'.*/
int my_queue_remove1(queue* q);
/*The function returns the length of the queue-'q', which means the amount of variables in it.*/
int my_queue_length(queue* q);
/*The function returns the head of the queue.*/
int my_queue_get1(queue* q);
/*The function prints the queue-'q'. NOTE: this function actually contains a loop
  but it is OK since the function is extra.*/
void print(queue *q);


#endif
