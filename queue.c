/* MARDALE Andrei-Iulian - 311CB */
#include "queue.h"

AQueue initQ (size_t dim) {
	AQueue aQ = malloc(sizeof(TQueue));
	if (!aQ) return NULL;
	
	aQ->first = NULL;
	aQ->last = NULL;
	aQ->dim = dim;
	
	return aQ;
}

//ae is allocated elsewhere
//aux is allocated and the data is copied to it
//then add to list
int intrQ (AQueue aQ, void *ae, TFcmp cmp) {	
	void *aux = malloc(aQ->dim);
	if (!aux) return 0;
	
	memcpy(aux, ae, aQ->dim);
	
	int r = 0; //return value
	
	//if empty then update first and last with same value
	//if not then add ordered, and update last value if needed
	if (EMPTY_QUEUE(aQ)) {
		r = addFirst(&aQ->first, aux);
		aQ->last = aQ->first;
	} else {
		r = addO(&aQ->first, aux, cmp, &aQ->last);
	}
	
	return r;
}
		
int extrQ (AQueue aQ, void *ae) {
	if (EMPTY_QUEUE(aQ)) return 0;
	
	//copy element
	memcpy(ae, aQ->first->inf, aQ->dim);
	
	//delete first value
	TList aux = aQ->first;
	
	
	if (aQ->first == aQ->last) {
		aQ->first = NULL;
		aQ->last = NULL;
	} else {
		aQ->first = aQ->first->next;
	}
	
	free(aux->inf);
	free(aux);
	
	return 1;
}

void printQ (AQueue aQ, TFwork print, FILE *out) {
	printL(aQ->first, print, out);
}

void destroyQ (AQueue *aQ) {
	destroyL(&(*aQ)->first);
	free(*aQ);
	*aQ = NULL;
}
