// class derived from cp264 implementations

#include "queueLinked.h"

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

/**
 * Parameters: 	queue length (int)
 * Returns: 	A pointer to a Queue
 * Description:	Creates a new empty queue
 * 				Initializes size to 0
 * 				front and rear are set to -1
 * 				if given length is <1 --> through an error and set length to 10
 */
Queue* create_queue(){
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->length = 100;
	q->size = 0;
	q->list = create_linkedList();
	q->front = NULL;
	q->rear = NULL;
	return q;
}

/**
 * Parameters: 	A pointer to Queue (Queue*)
 * Returns: 	number of items in queue (int)
 * Description:	return number of items in queue
 */
int getSize_queue(Queue* q){
	assert(q!=NULL);
	return q->size;
}

/**
 * Parameters: 	A pointer to Queue (Queue*)
 * Returns: 	True(1)/False(0)
 * Description:	Check if queue is empty
 * 				queue is empty if size = 0
 */
int isEmpty_queue(Queue* q){
	assert(q!=NULL);
	return (q->size==0);
}


int getLength_queue(Queue* q){
	assert(q!=NULL);
	return q->length;
}
/**
 * Parameters: 	A pointer to Queue (Queue*)
 * Returns: 	True(1)/False(0)
 * Description:	Check if queue is full
 * 				queue is full if size == length
 */
int isFull_queue(Queue* q){
	assert(q!=NULL);
	return (q->size == q->length);
}
/**
 * Parameters: 	A pointer to a Queue (Queue*)
 * 				A pointer to a data item (Data*)
 * Returns: 	True/False
 * Description:	Insert a Data item into the queue
 * 				if queue is full - print error and return False
 */
int en_queue(Queue* q, Data* d){
	assert(q!=NULL && d!=NULL);
	if (isFull_queue(q)){
		fprintf(stderr, "Error (en_queue): queue is full\n");
		return False;
	}
	append_linkedList(q->list, d);
	if(q->size == 0){
		q->front = q->list->head;
		q->rear = q->list->head;
	} else {
		q->rear = q->rear->next;
	}
	q->size++;
	return True;
}

/**
 * Parameters: 	A pointer to a Queue (Queue*)
 * Returns: 	item on front of queue (int)
 * Description:	returns first item in the queue
 * 				if queue is empty: print error message and return a NULL pointer
 */
Data* front_queue(Queue* q){
	assert(q!=NULL);
	if (isEmpty_queue(q)){
		fprintf(stderr, "Error (front_queue): Queue is empty\n");
		Data* d = NULL;
		return d;
	}
	return getData_linkedList(q->list, 0);
	//return copy_data(q->front->data);
}

/**
 * Parameters: 	A pointer to a Queue (Queue*)
 * Returns: 	Last item in queue (Data*)
 * Description:	returns first item in the queue
 * 				if queue is empty: print error message and return a NULL pointer
 */
Data* rear_queue(Queue* q){
	assert(q!=NULL);
	if (isEmpty_queue(q)){
		fprintf(stderr, "Error (rear_queue): Queue is empty\n");
		Data* d = NULL;
		return d;
	}
	//return copy_data(q->rear->data);
	return getData_linkedList(q->list, q->size - 1);
}

/**
 * Parameters: 	A pointer to a Queue (Queue*)
 * Returns: 	first item in queue (int)
 * Description:	returns the first item in queue and remove it from queue
 * 				sets previous array value to 0, and increment top
 * 				If queue is full: print error message and return -1
 */
Data* de_queue(Queue* q){
	assert(q!=NULL);
	Data* d = NULL;
	if (isEmpty_queue(q)){
		fprintf(stderr,"Error (de_queue): queue is empty\n");
		return d;
	}

	d = getData_linkedList(q->list, 0);
	deleteNode_linkedList(q->list, 0);

	q->size--;

	if(q->size == 0){ //if queue becomes empty
		q->front = NULL;
		q->rear = NULL;
	}
	return d;
}


void destroy_queue(Queue** q){
	assert(q!= NULL);
	destroy_linkedList(&((*q)->list));
	(*q)->length = 0;
	(*q)->front = NULL;
	(*q)->rear = NULL;
	(*q)->size = 0;
	free(*q);
	*q = NULL;
	return;
}
