// class derived from cp264 implementations

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <assert.h>
#include "linkedList.h"


/**
 * Parameters: 	a data item (Data*)
 * Returns: 	A Node (Node*)
 * Description:	Creates a new node using the given data
 * 				asserts given data is not NULL
 */
Node* create_node(Data* d){
	assert(d!=NULL);
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = copy_data(d);
	node->next = NULL;
	return node;
}

/**
 * Parameters: 	a Node (Node*)
 * Returns: 	none
 * Description:	prints the contents of a node
 * 				invokes print_data
 * 				does not print next pointer
 */
/**
 * Parameters: 	a Node (Node*)
 * Returns: 	a copy of given node (Node*)
 * Description:	Creates a copy of the given node
 * 				The new copy has a copy version of the data
 * 				the next pointer points to the same node as the original node's next
 */
Node* copy_node(Node* n){
	assert(n!=NULL);
	Node* n2 = create_node(n->data);
	n2->next = n->next;
	return n2;
}

/**
 * Parameters:  a Node (Node**)
 * Returns: 	none
 * Description:	destroys a node by:
 * 				- destroy the encompassed data
 * 				- setting next to NULL
 * 				- free the node pointer
 */
void destroy_node(Node** n){
	assert(n!=NULL);
	(*n)->data = NULL;
	(*n)->next = NULL;
	free(*n);
	return;
}

/**
 * Parameters: 	None
 * Returns: 	A pointer to linked list (LinkedList*)
 * Description:	Creates an empty linked list
 * 				head is set to NULL and size to 0
 * 				Returns a pointer to the newly created linked list
 */
LinkedList* create_linkedList(){
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->size = 0;
	return list;
}

/**
 * Parameters: 	A pointer to a linked list (LinkedList*)
 * Returns: 	True(1)/False(0)
 * Description:	Check if LinkedList is empty
 * 				linked list is empty if head points to NULL
 * 				asserts list pointer is not NULL
 */
int isEmpty_linkedList(LinkedList* list){
	assert(list!=NULL);
	return(list->head==NULL);
}

/**
 * Parameters: 	Pointer to a linked list (LinkedList*)
 * 				Pointer to a data item (Data*)
 * Returns: 	None
 * Description:	asserts linked list is not NULL
 * 				appends the given data item to the trail of the linked list
 * 				The append operation:
 * 				- updates next pointer for last node
 * 				- increments size
 * 				- updates head pointer, if linked list was empty
 */
void append_linkedList(LinkedList* list, Data* d){
	assert(list!=NULL);
	Node* new_node = create_node(d);
	if(isEmpty_linkedList(list))
		list->head = new_node;
	else{
		Node* current_node = list->head;
		while(current_node->next!=NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	list->size++;
	return;
}

/**
 * Parameters: 	Pointer to a linked list (LinkedList*)
 * Returns: 	size of linked list (int)
 * Description:	asserts linked list is not NULL
 * 				linked list size = Number of nodes in a linked list
 */
int getSize_linkedList(LinkedList* list){
	assert(list!=NULL);
	return list->size;
}

/**
 * Parameters: 	Pointer to a linked list (LinkedList*)
 * Returns: 	None
 * Description:	traverse through all nodes
 * 				uses print_node(Node*) to print contents of nodes
 * 				starting from list head to tail
 * 				prints <Empty linked list> if isEmpty_linkedList is True
 * 				asserts list is not NULL
 */
void print_linkedList(LinkedList* list){
	assert(list!=NULL);
	if(list->head == NULL){
		printf("<Empty linked list>\n");
		return;
	}
	//Node* current_node = (Node*)malloc(sizeof(Node));
	Node* current_node = list->head;
	while(current_node!=NULL){
		printf("\n");
		current_node = current_node->next;
	}
	return;
}

/**
 * Parameters: 	Pointer to a linked list (LinkedList*)
 * 				Node index (int)
 * Returns: 	Pointer to Data at node #index
 * Description:	returns the data object at given index
 * 				invokes: getNode_linkedList function
 * 				All assertions and error checking is done at getNode
 */
Data* getData_linkedList(LinkedList* list, int index){
	return getNode_linkedList(list,index)->data;
}

/**
 * Parameters: 	An array of data (Data*)
 * 				size of array (const int)
 * Returns: 	a linked list (LinkedList*)
 * Description:	Creates a linked list from the given array items
 * 				if given size is < 0 --> through an error, return NULL
 * 				asserts given array pointer is not Null
 */
LinkedList* array_to_linkedList(Data* array, const int size){
	assert(array!=NULL);
	LinkedList* list = NULL;

	if(size<=0){
		fprintf(stderr, "Error (array_to_linkedList): invalid array size - return NULL\n");
		return list;
	}
	list = create_linkedList();

	int i;
	for(i=0;i<size;i++)
		append_linkedList(list,&array[i]);

	return list;
}

/**
 * Parameters: 	a linkedList (LinkedList*)
 * 				a node index (int)
 * Returns: 	a Node (Node*)
 * Description:	Returns a copy of the Node at the given index
 * 				if given index is out of range --> print an error and return NULL;
 * 				asserts given array pointer is not Null
 */
Node* getNode_linkedList(LinkedList* list, int index){
	assert(list!=NULL);
	Node* n = NULL;
	if(index <0 || index>=getSize_linkedList(list)){
		fprintf(stderr,"Error (getINode_linkedList): index out of range\n");
		return n;
	}
	Node* current_node = list->head;
	int i = 0;
	while(i<index){
		current_node = current_node->next;
		i++;
	}
	return copy_node(current_node);
}

/**
 * Parameters: 	a linkedList (LinkedList*)
 * 				a data item (Data*)
 * 				an index (int)
 * Returns: 	True/False
 * Description:	Inserts the given data item at position (index) at the linked list
 * 				if given index is out of range --> print an error and return NULL
 * 				Updates the following:
 * 				- structure of list (how nodes are connected)
 * 				- increments size
 * 				- head pointer (if list was empty)
 * 				asserts given array and data pointers are not Null
 */
int insert_linkedList(LinkedList* list, Data* d, int index){
	assert(list!=NULL && d!=NULL);
	int size = getSize_linkedList(list);

	//Case 0: An error
	if( index <0 || (index>size)){
		fprintf(stderr,"Error (insert_linkedList): index out of range\n");
		return False;
	}
	Node* new_node = create_node(d);

	//Case 1: Inserting at the head
	if(index == 0){
		if(isEmpty_linkedList(list)== False)
			new_node->next = list->head;
		list->head = new_node;
	}
	//Case 2: Inserting anywhere after the head
	else{
		int i=0;
		Node* current_node = list->head;
		while(i++<index-1)
			current_node = current_node->next;
		new_node->next = current_node->next;
		current_node->next = new_node;
	}
	list->size++;
	return True;
}

/**
 * Parameters: 	a linkedList (LinkedList*)
 * 				an index (int)
 * Returns: 	True/False
 * Description:	deletes the node at position (index) at the linked list
 * 				if given index is out of range --> print an error and return False
 * 				if given linkked list is empty --> print an error and return False
 * 				Updates the following:
 * 				- structure of list (how nodes are connected)
 * 				- increments size
 * 				- head pointer (if list has only one item)
 * 				- deleted node is destroyed
 * 				asserts given linked list is not Null
 */
int deleteNode_linkedList(LinkedList* list, int index){
	assert(list!=NULL);
	int size = getSize_linkedList(list);

	//Case 0: An empty list
	if( isEmpty_linkedList(list)){
		fprintf(stderr,"Error (deleteNode_linkedList): Can not delete from an empty list\n");
		return False;
	}

	//Case 1: index out of range
	if( index <0 || (index>=size)){
		fprintf(stderr,"Error (deleteNode_linkedList): index out of range\n");
		return False;
	}

	Node* del_node;
	//Case 2: delete first node
	if (index == 0){
		del_node = list->head;
		list->head = list->head->next;
	}

	//Case 3: delete other nodes
	else{
		Node* current_node = list->head;
		Node* previous_node = NULL;
		int i=0;
		while (current_node->next !=NULL && i<index){
			previous_node = current_node;
			current_node = current_node->next;
			i++;
		}
		previous_node->next = current_node->next;
		del_node = current_node;
	}
	list->size--;
	destroy_node(&del_node);
	return True;
}

/**
 * Parameters: 	a linkedList (LinkedList**)
 * Returns: 	None
 * Description:	Destroys a given linked list
 * 				Deletes all nodes (which takes care of destroying data)
 * 				set head to NULL and size to 0
 * 				free list pointer
 * 				asserts given linked list is not Null
 */
void destroy_linkedList(LinkedList** list){
	while(!isEmpty_linkedList(*list))
		deleteNode_linkedList(*list,0);
	(*list)->head = NULL;
	(*list)->size = 0;
	free(*list);
	return;
}

//-------------------------- L8: LinkedLists ----------------------


/**
 * Parameters: 	a linkedList (LinkedList*)
 * 				start index [inclusive] (int)
 * 				end index [inclusive] (int)
 * Returns: 	a linkedList
 * Description:	Constructs a linkedList with elements from index start to end (inclusive both ends)
 * 				Updates nothing of the input list
 * 				asserts given linked list is not NULL
 * 				if given list is empty, return an empty list
 *				if given start or end indices are out of range --> print an error and return an empty list
 *				The new list should maintain the order of nodes as they appear in the original list
 */
LinkedList* getList_linkedList(LinkedList* list, int start, int end){
	assert(list!=NULL);
	LinkedList* new_list = create_linkedList();
	if(start < 0){
		printf("Error (getList_linkedList): Invalid start value\n");
		return new_list;
	} else if(end >= getSize_linkedList(list) || start > end){
		printf("Error (getList_linkedList): Invalid end value\n");
		return new_list;
	}
	for(int i = start; i <= end; i++)
		append_linkedList(new_list, getData_linkedList(list,i));
	return new_list;
}

/**
 * Parameters: 	a linkedList (LinkedList*)
 * 				start index [inclusive] (int)
 * 				end index [inclusive] (int)
 * Returns: 	True/False
 * Description:	deletes items from the list from index start to end (inclusive both ends)
* 				May update the following:
 * 				- head pointer
 * 				- structure of list (how nodes are connected)
 * 				- size
 * 				asserts given linked list is not NULL
 * 				if given list is empty, print error and return False
 *				if given start or end indices are out of range --> print an error and return False
 *				Whenever the cut operation is successful the function returns True
 */
int cut_linkedList(LinkedList* list, int start, int end){
	assert(list!=NULL);
	if(start < 0){
		printf("Error (getList_linkedList): Invalid start value\n");
		return False;
	} else if(end >= getSize_linkedList(list) || start > end){
		printf("Error (getList_linkedList): Invalid end value\n");
		return False;
	}
	for(int i = start; i <= end; i++)
		deleteNode_linkedList(list, start);
	return True;
}

/**
 * Parameters: 	a linkedList (LinkedList*)
 * Returns: 	None
 * Description:	Reverses a linked list
 * 				Updates the following:
 * 				- head pointer
 * 				- structure of list (how nodes are connected)
 * 				size is not changed
 * 				asserts given linked list is not Null
 */
void reverse_linkedList(LinkedList* list){
	assert(list!=NULL);
	if(getSize_linkedList(list) == 0)
		return;
	Node* curr = list->head;
	Node* prev = NULL;
	Node* next = curr->next;
	while(curr->next !=NULL){
		next = curr->next;
		prev = curr;
		curr->next = prev;
		curr = next;
	}
	return;
}
