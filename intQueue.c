// class derived from cp264 implementations

#include "intQueue.h"

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

intQueue* create_intQueue()
{
	intQueue* q = (intQueue*)malloc(sizeof(intQueue)*(100));
	q->front = 0;
	q->rear = 0;
	q->array[0] = NULL;
	return q;
}
int front_intQueue(intQueue* q)
{
	assert(q->array != NULL);
	return (q->array[0]);
}
void en_intQueue(intQueue* q, int i)
{
	q->array[q->rear] = i;
	q->rear+=1;
}
int de_intQueue(intQueue* q)
{
	int temp = q->array[q->front];
	q->front -=1;
	return temp;
}
