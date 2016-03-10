/* MARDALE Andrei-Iulian - 311CB */
#include "queue.h"
#include "stack.h"

#ifndef _PROC_
#define _PROC_

#define MAXLEN 100 //input buffer size

typedef struct {
	size_t id;
	size_t priority;
	size_t step;
} TProcess;

//parse commands and calls function accordingly
int parse (FILE *in, FILE *out);

//creates stacks for events
AStack * initEvents (size_t n);

//creates process, adds it in queue
int start (size_t id, size_t priority, size_t step, AQueue aQ);

//add process to event stack
int wait (size_t evNo, size_t id, AQueue *aQ, AStack *Events);

//produces event, processes go to queue
int event (size_t evNo, AQueue aQ, AStack *Events);

//ends a process removing it from queue
int end (size_t id, AQueue *aQ);

//prints data
void printEnv (size_t step, int n, AQueue aQ, AStack *Events, FILE *out);


#endif
