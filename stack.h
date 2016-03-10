/* MARDALE Andrei-Iulian - 311CB */
#include "list.h"

#ifndef _STACK_
#define _STACK_

#define EMPTY_STACK(s) ((s)->top == NULL)

typedef struct {
	size_t dim;
	TList top;
} TStack, *AStack;

//allocates memory for stack
AStack initStack (size_t dim);

int push (AStack aS, void *ae);
int pop (AStack aS, void *ae);

//prist stack top->bottom
void printS (AStack aS, TFwork print, FILE *out);

//destroy stack
void destroyS (AStack *aS);

	
#endif
