// class derived from cp264 implementations

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

# include "data.h"

# define True 1
# define False 0

# include "data.h"

typedef struct linkedListNode{
	Data* data; 					//data item
	struct linkedListNode* next; 	//Pointer to next node
}Node;

Node* create_node(Data* d);
void destroy_node(Node** n);
void print_node(Node* n);
Node* copy_node(Node* n);

typedef struct{
	Node* head;
	int size;
}LinkedList;

LinkedList* create_linkedList();
int isEmpty_linkedList(LinkedList* list);
void print_linkedList(LinkedList* head);
void append_linkedList(LinkedList* list, Data* d);
int getSize_linkedList(LinkedList* list);
Data* getData_linkedList(LinkedList* list, int index);
LinkedList* array_to_linkedList(Data* array, const int size);
Node* getNode_linkedList(LinkedList* list, int index);
int insert_linkedList(LinkedList* list, Data* d, int index);
int deleteNode_linkedList(LinkedList* list, int index);
void destroy_linkedList(LinkedList** list);

//to be implemented in L8
void reverse_linkedList(LinkedList* list);
LinkedList* getList_linkedList(LinkedList* list, int start, int end);
int cut_linkedList(LinkedList* list, int start, int end);


#endif /* LINKEDLIST_H_ */
