/* MARDALE Andrei-Iulian - 311CB */
#include "stack.h"

AStack initStack (size_t dim) {
	AStack s = malloc(sizeof(TStack));
	if (!s) return NULL;
	
	s->dim = dim;
	s->top = NULL;
	
	return s;
}

//ae allocated elswhere
//aux allocated here
//copy then add to list
int push (AStack aS, void *ae) {
	void *aux = malloc(aS->dim);
	if (!aux) return 0;
	memcpy(aux, ae, aS->dim); //copy inf
	
	return addFirst(&aS->top, aux); //add to list
}
	
int pop (AStack aS, void *ae) {
	if (EMPTY_STACK(aS)) return 0;
	
	//copy memory from top to ae
	memcpy(ae, aS->top->inf, aS->dim);
	
	//remove first element
	TList aux = aS->top;	
	aS->top = aS->top->next;
	free(aux->inf);
	free(aux);
	
	return 1;
}

void printS (AStack aS, TFwork print, FILE *out) {
	printL(aS->top, print, out);
}

void destroyS (AStack *aS) {
	destroyL(&(*aS)->top);
	free(*aS);
	*aS = NULL;
}

