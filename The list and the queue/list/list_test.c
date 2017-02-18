#include "my_list.h"

/*main function to test the list's module*/
int main(void){
	list* l = my_list_ctor(211);
	printf("The value of the first variable is: %d\n",l->first->val);
	add_node(l,45);
	add_node(l,48);
	printf("The length of the list is: %d\n",get_list_len(l));
	delete_node(l,get_next(get_head(l)));
	printf("And now, The length of the list is: %d\n",get_list_len(l));
	printf("The avg of the values in the list is: %f\n",get_avg(l));
	printf("The value of the second node is: %d\n",get_val(get_next(get_head(l))));
	my_list_dtor(l);	
	return 0;
}


