/*
dispatcher.c

Student Name : ....
Student ID # : ....

Dispatch Algorithm : ....
 */

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 100

#include "process.h"
#include "queueLinked.h"

void dispatcher(FILE *fd, int quantum, int harddrive){

	Queue* ready = create_queue();
	Queue* block = create_queue();
	Queue* complete = create_queue();
	Queue* temp = create_queue();
	int dif;
	int time = 0;

	char line_buffer[MAX_LINE_LENGTH];
	int start_time, run_time, process_id, num_exchanges, exchange_time;
	char *token;

	//Process simulation input line by line
	while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n'){
		//intQueue* tempArray = create_intQueue();
		token = strtok(line_buffer, " ");
		sscanf(token, "%d",&start_time);


		token = strtok(NULL, " ");
		sscanf(token, "%d",&process_id);

		token = strtok(NULL, " ");
		sscanf(token, "%d",&run_time);

		num_exchanges = 0;
		token = strtok(NULL, " ");
		while ( token != NULL ){
			//enintQueue(tempArray,token);
			num_exchanges += sscanf(token, "%d",&exchange_time);
			token = strtok(NULL, " ");
		}
		//Process* p = CreateProcess(process_id, start_time, run_time,tempArray);
		//enqueue(temp, p);
		printf("Process %3d wants to start at %6dms and run for %6dms and has %3d hard drive exchanges\n",  process_id, start_time, run_time, num_exchanges);
	}

	Process* p = CreateProcess(0,0, 0,NULL);
	en_queue(complete,p);

	while(!isEmpty_queue(temp) && !isEmpty_queue(ready)&&!isEmpty_queue(block))
	{

		if(isEmpty_queue(ready)&& !isEmpty_queue(temp))
		{
			for (int cnt = 0; cnt < getSize_queue(block)-1; cnt++)
			{
				Process* temp = de_queue(block);
				temp->currentWaitTime+=front_queue(temp)-> arrival-time;
				en_queue(block,temp);
			}
			front_queue(complete)->runTime += (front_queue(temp)-> arrival - time);
			time = front_queue(temp)-> arrival;
			en_queue(ready,de_queue(temp));

		}
		/*
		else
		{
			for (int cnt = 0; cnt < getSize_queue(block)-1; cnt++)
			{
				Process* temp = dequeue(block);
				temp->currentWaitTime+=front_queue(ready)-> arrival-time;
				enqueue(block,temp);
			}
			time = front_queue(ready)->arrival;
		}

		 */
		Process* p = de_queue(ready);
		p->readyTime += p->currentReadyTime;
		p->currentReadyTime = 0;

		if(p->runTime < quantum && p->totalRunTime + p->runTime< front_intQueue(p->interupts))
		{
			p->totalRunTime += p-> runTime;
			time += p->runTime;
			for (int cnt = 0; cnt < getSize_queue(block)-1; cnt++)
			{
				Process* tempP = de_queue(block);
				tempP->currentWaitTime+=p->runTime;
				en_queue(block,temp);
			}
			for (int cnt = 0; cnt < getSize_queue(ready)-1; cnt++)
			{
				Process* tempP = de_queue(ready);
				tempP->currentReadyTime+=p->runTime;
				en_queue(ready,temp);
			}
			en_queue(complete,p);
		}

		if(quantum < p->runTime &&  quantum< front_intQueue(p->interupts) - p->totalRunTime)
		{

			p->totalRunTime += quantum;
			p-> runTime = p-> runTime - quantum;
			time += quantum;
			p-> arrival = time;
			for (int cnt = 0; cnt < getSize_queue(block)-1; cnt++)
			{
				Process* temp = de_queue(block);
				temp->currentWaitTime+=quantum;
				en_queue(block,temp);
			}
			for (int cnt = 0; cnt < getSize_queue(ready)-1; cnt++)
			{
				Process* temp = de_queue(ready);
				temp->currentReadyTime+=quantum;
				en_queue(ready,temp);
			}
			en_queue(ready,p);
		}

		if(front_intQueue(p->interupts) - p-> totalRunTime < quantum )
		{
			dif = front_intQueue(p->interupts) - p-> totalRunTime;
			dif += dif;
			p->totalRunTime += dif;
			p->runTime -= dif;
			p-> arrival  = time + harddrive;
			for (int cnt = 0; cnt < getSize_queue(block)-1; cnt++)
			{
				Process* temp = de_queue(block);
				temp->currentWaitTime+=dif;
				en_queue(block,temp);
			}
			for (int cnt = 0; cnt < getSize_queue(ready)-1; cnt++)
			{
				Process* temp = de_queue(ready);
				temp->currentReadyTime+=dif;
				en_queue(ready,temp);
			}
			de_intQueue(p->interupts);
			en_queue(block,p);
		}

		if(front_queue(block)->currentWaitTime > harddrive)
		{
			int dif = front_queue(block)->currentWaitTime - harddrive;
			front_queue(block)->currentWaitTime -= dif;
			front_queue(block)->arrival=time - dif;
			front_queue(block)-> waitTime += front_queue(block)->currentWaitTime;
			en_queue(ready,de_queue(block));
			front_queue(block)-> waitTime += front_queue(block)->currentWaitTime;
			front_queue(block)->currentWaitTime = 0;

		}

		else if(front_queue(block)->currentWaitTime == harddrive)
		{
			front_queue(block)->waitTime += front_queue(block)->currentWaitTime;
			front_queue(block)->arrival=time;
			en_queue(ready,de_queue(block));
			front_queue(block)-> waitTime += front_queue(block)->currentWaitTime;
			front_queue(block)->currentWaitTime = 0;
		}
		else if(front_queue(block)->currentWaitTime < harddrive && isEmpty_queue(ready) && isEmpty_queue(temp))
		{
			dif =  harddrive - front_queue(block)->currentWaitTime ;
			time += dif;
			for (int cnt = 0; cnt < getSize_queue(block)-1; cnt++)
			{
				Process* temp = de_queue(block);
				temp->currentWaitTime+=dif;
				en_queue(block,temp);
			}
			front_queue(block)-> waitTime += front_queue(block)->currentWaitTime;
			en_queue(ready,de_queue(block));
			front_queue(block)-> waitTime += front_queue(block)->currentWaitTime;
			front_queue(block)->currentWaitTime = 0;

		}
	}
}
