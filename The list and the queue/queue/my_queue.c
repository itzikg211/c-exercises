#include "my_queue.h"

queue* my_queue_ctor(int val){
	/*allocating memory for the queue and for the integer array inside*/
	queue* q = malloc(1*sizeof(queue));
	q->qq = (int*)malloc(1*sizeof(int));
	*(q->qq) = val;
	/*setting the length of the new queue*/
	q->length = 1;
	/*making sure that 'first' will point the queue*/
	q->first = q->qq;
	return q;
}

void my_queue_dtor(queue* q){
	/*freeing the memory of the integer array.
	Actually 'first' contains the address of the whole variables that were in the queue*/
	free(q->first);
	/*freeing the memory of the struct*/
	free(q);
	return;
}

void my_queue_add(queue* q, int val){
	/*checking if 'q' was not created*/
	if(q == NULL){
		printf("You should create the queue first!\n");
		return;
	}
	/*reallocating the size of the integer array inside 'q', icreasing the length and storing 'val'*/
	q->qq = (int*)realloc(q->qq,(++(q->length))*sizeof(int));
	*((q->qq)+(q->length)-1) = val;
	return;
}

int my_queue_remove1(queue* q){
	/*checking if 'q' was not created*/
	if(q == NULL){
		printf("You should create the queue first!\n");
		return;
	}
	/*storing the head of the queue so later we can return it*/
	int ret_val = *(q->qq);
	/*checking if removing the only variable in the queue.*/
	if(q->length == 1){
		q->qq = NULL;
	}
	else{
	/*changing 'qq' pointer to start from the next variable.*/
	q->qq = q->qq+1;
	}
	/*decreasing the length*/
	--q->length;
	return ret_val;
}
int my_queue_length(queue* q){
	return q->length;
}

int my_queue_get1(queue* q){
	return *q->qq;
}

void print(queue *q)
{
	int i;
	for(i=0;i<q->length;i++){
		printf("%d = %d ",i+1,*((q->qq)+i));
	}
	printf("\n");
}
