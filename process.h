// class derived from cp264 implementations
#ifndef PROCESS_H_
#define PROCESS_H_
#define True 1
#define False 0
typedef struct
{
	int PID; //process ID
	int totalRunTime;
	int runTime; //requested process time
	int arrival; //arrival time
	int interupts;//array of interrupts
	int waitTime;
	int currentWaitTime;
	int readyTime;
	int currentReadyTime;
}	Process;
Process* CreateProccess(int PID, int arrival, int runtime, int interupts[]);
Process* copy_process(Process* p);
#endif /* PROCESS_H_ */
