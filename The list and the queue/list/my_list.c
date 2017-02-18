#include "my_list.h"

list* my_list_ctor(int val){
	/*allocating memory for the list and the first node*/
	list* lst = malloc(1*sizeof(list));
	node* head = malloc(1*sizeof(node));
	head->val = val;
	head->next = NULL;
	head->prev = NULL;
	/*setting the list's first and last nodes.*/
	lst->first = head;
	lst->last = head;
	/*updating the list's number of nodes and the total sum of their values.*/
	lst->num_of_nodes = 1;
	lst->total_sum = head->val;
	return lst;
}

void my_list_dtor(list* lst){
	node* nxt = NULL;
	/*checking if the list is empty*/
	if(lst->first == NULL){
		printf("The list is empty! Nothing was deleted.\n");
		return;	
	}
	/*freeing each node*/
	while(!(lst->first==NULL)){
		free(lst->first);
		nxt = lst->first->next;
		lst->first = nxt;
	}
	/*freeing the whole list*/
	free(lst);
	printf("The list is now empty!!\n");
	return;
}

void delete_node(list* lst,node* nd){

	/*check if the node we want to delete is our head*/
	if(nd->prev == NULL){
		lst->first = nd->next;
		/*make sure the new head's previous node is NULL*/
		if(!(lst->first == NULL)){
			lst->first->prev = NULL;
		}
		--lst->num_of_nodes;
		lst->total_sum -= nd->val;
		free(nd);
		printf("Deleted the head of the list\n");
		return;
	}
	/*check if the node we want to delete is our last node*/
	if(nd->next == NULL){
		node* prev = nd->prev;
		prev->next = NULL;
		lst->last = prev;
		--lst->num_of_nodes;
		lst->total_sum -= nd->val;
		free(nd);
		return;
	}
	/*deleting a node from the list which is not the head or the last node*/
	nd->prev->next = nd->next;
	nd->next->prev = nd->prev;
	--lst->num_of_nodes;
	lst->total_sum -= nd->val;
	free(nd);
	return;
}


void add_node(list* lst,int val){
	/*creating a new node*/
	node* new_node = malloc(1*sizeof(node));
	new_node->val = val;
	/*updating the previous and next nodes of the new node and the last node of list-'lst'*/
	new_node->prev = lst->last;
	lst->last->next = new_node;
	new_node->next = NULL;
	lst->last = new_node;
	++lst->num_of_nodes;
	lst->total_sum += val;
	printf("Added a new node with %d value\n",val);
	return;

}


int get_list_len(list* lst)
{
	return lst->num_of_nodes;
}


node* get_head(list* lst){
	return lst->first;
}
node* get_last(list* lst){
	return lst->last;
}

node* get_next(node* nd){
	if(!(nd->next == NULL)){
		return nd->next;
	}
	else{
		printf("There is no next node...");
		return NULL;
	}
}
node* get_prev(node* nd){
	if(!(nd->prev == NULL)){
		return nd->prev;
	}
	else{
		printf("There is no prev node...");
		return NULL;
	}
}

int get_val(node* nd){
	return nd->val;

}

double get_avg(list* lst){
	/*making sure that the returned value is double*/
	double ret_val = (lst->total_sum*1.0)/lst->num_of_nodes;
	return ret_val;

}
