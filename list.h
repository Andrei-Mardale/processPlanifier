/* MARDALE Andrei-Iulian - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _LIST_
#define _LIST_

typedef int (*TFcmp) (const void *, const void*); //usually compares 2 elements
typedef void (*TFwork) (const void *, const void *); //performs operation on element

typedef struct cell {
	struct cell *next;
	void *inf;
} TCell, *TList, **AList;

//creates new cell with inf ae
//ae is allocated elsewhere
TList newCell (void *ae);

//adds element to list in first position
/*if end of list is reached and parameter is given it will
update last element pointer - to be used with priority queues*/
int addFirst (AList aL, void *ae);

//adds element to list in order given by cmp
int addO (AList aL, void *ae, TFcmp cmp, AList last);

//prints all elements in list
void printL (TList L, TFwork print, FILE *out);

//destroys list
void destroyL (AList aL);

#endif
