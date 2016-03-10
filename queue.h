/* MARDALE Andrei-Iulian - 311CB */
#include "list.h"

#ifndef _QUEUE_
#define _QUEUE_

#define EMPTY_QUEUE(Q) ((Q)->first == NULL && (Q)->last == NULL)

typedef struct {
	size_t dim;
	TList first, last;
} TQueue, *AQueue;

//allocates memory for queue
AQueue initQ (size_t dim);

int intrQ (AQueue aQ, void *ae, TFcmp cmp);
int extrQ (AQueue aQ, void *ae);

//prints queue first to last (by priority)
void printQ (AQueue aQ, TFwork print, FILE *out);

//destroys Queue
void destroyQ (AQueue *aQ);

#endif
