// class derived from cp264 implementations


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

Process* CreateProcess(int pid, int arrival, int run, int blocks[])
{
	Process* p = (Process*)malloc(sizeof(Process));
	if (run <= 0)
	{ fprintf(stderr,"Error invalid time");
	p-> runTime = 0;
	}
	else
	{
		p->runTime = run;
	}
	if(arrival< 0)
	{
		fprintf(stderr,"Error invalid time");
		p->arrival = 0;
	}
	else{
		p->arrival = arrival;
	}
	p->PID = pid;
	p->interupts = blocks;
	p->waitTime = 0;
	p->currentWaitTime = 0;
	p->readyTime = 0;
	p->currentReadyTime = 0;
	p->totalRunTime = 0;

	return p;
}
Process* copy_process(Process* p){
	Process* p2 = (Process*)malloc(sizeof(Process));
	p2->PID = p->PID;
	p2->arrival = p->arrival;
	return &p2;
}
