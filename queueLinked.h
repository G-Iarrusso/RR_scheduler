// class derived from cp264 implementations

#ifndef QUEUELINKED_H_
#define QUEUELINKED_H_

# include "data.h"
# include "linkedList.h"

# define True 1
# define False 0

typedef struct {
	LinkedList* list; 	//array containing data items
	Node* front;		//pointer to first item in Queue
	Node* rear;		//pointer to last item in Queue
	int size;		//number of elements in Queue
	int length;		//maximum queue length
}Queue;

Queue* create_queue();
int isEmpty_queue(Queue* q);
int getSize_queue(Queue* q);
int getLength_queue(Queue* q);
int isFull_queue(Queue* q);
int en_queue(Queue* q, Data* d);
Data* front_queue(Queue* q);
Data* rear_queue(Queue* q);
Data* de_queue(Queue* q);
void destroy_queue(Queue** q);
void print_queue(Queue* q);

#endif /* QUEUELINKED_H_ */
