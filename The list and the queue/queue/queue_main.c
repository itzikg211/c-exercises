#include "my_queue.h"

/*main function to test the queue's module*/
int main(void){

	queue* my_q = my_queue_ctor(211);
	printf("The value of the first variable is: %d\n",*(my_q->qq));
	my_queue_add(my_q,48);
	my_queue_add(my_q,1);
	my_queue_add(my_q,2);
	my_queue_add(my_q,3);
	printf("The value of the second variable is: %d\n",*((my_q->qq)+1));
	print(my_q);
	printf("Removing the first value = %d\n ",my_queue_remove1(my_q));
	print(my_q);
	printf("The new length of the queue is: %d\n",my_queue_length(my_q));
	printf("Now, The value of the first variable is: %d\n",my_queue_get1(my_q));
	printf("Removing the first value = %d\n ",my_queue_remove1(my_q));
	print(my_q);
	printf("Now, The value of the first variable is: %d\n",my_queue_get1(my_q));
	my_queue_dtor(my_q);
	return 0;
}

