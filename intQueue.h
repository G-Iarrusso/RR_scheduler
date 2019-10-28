// class derived from cp264 implementations

#ifndef INTQUEUE_H_
#define INTQUEUE_H_
typedef struct
{
	int array[100];
	int front;
	int rear;
}	intQueue;
intQueue* create_intQueue();
int front_intQueue(intQueue* q);
void en_intQueue(intQueue* q, int i);
int de_intQueue(intQueue* q);
#endif /* INTQUEUE_H_ */
