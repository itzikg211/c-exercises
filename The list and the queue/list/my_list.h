#if !defined(_MY_LIST_H_)
#define _MY_LIST_H
#include <stdio.h>
#include <stdlib.h>


/*A struct that defines a node - an element in the list*/
typedef struct node{

/*The value of the node*/
int val;
/*A pointer to the next element*/
struct node* next;
/*A pointer to the previous element*/
struct node* prev;

}node;


/*A struct that defines a list. It contains a pointer to the head of the list,
* a pointer to the tail of the list,
* the amount of nodes in the list,
* and the total sum of the list's variables.*/
typedef struct list{
	node* first;
	node* last;
	int num_of_nodes;
	int total_sum;
}list;

/*The function creates a new list and returns a pointer to it's head. The head's value is 'val'.*/
list* my_list_ctor(int val);
/*The function destroys the list, it frees the list and all it's elements.*/
void my_list_dtor(list* lst);
/*The function adds a node that contains 'val' to the list.*/
void add_node(list* lst,int val);
/*The function deletes node-'nd' from list-'lst'.*/
void delete_node(list* lst,node* nd);
/*The function returns the number of elements in the list-'lst'.*/
int get_list_len(list* lst);
/*The function returns the head of the list-'lst'*/
node* get_head(list* lst);
/*The function returns the last element of the list-'lst'*/
node* get_last(list* lst);
/*The function returns the next node of 'nd'*/
node* get_next(node* nd);
/*The function returns the prevoius node tof 'nd'*/
node* get_prev(node* nd);
/*The function returns the value inside node-'nd'*/
int get_val(node* nd);
/*The function returns the average of all the node's values.*/
double get_avg(list* lst);



#endif
