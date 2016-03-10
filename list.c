/* MARDALE Andrei-Iulian - 311CB */
#include "list.h"

TList newCell (void *ae) {
	TList r = malloc(sizeof(TCell));
	if (!r) return NULL;
	
	r->inf = ae;	
	r->next = NULL;
	
	return r;
}

int addFirst (AList aL, void *ae) {
	TList aux = newCell(ae);
	if (!aux) return 0;
	
	aux->next = *aL;
	*aL = aux;
	
	return 1;
}

int addO (AList aL, void *ae, TFcmp cmp, AList last) {
	TList aux = newCell(ae);
	if (!aux) return 0;
	
	while (*aL && cmp(ae, (*aL)->inf) > 0) {
		aL = &(*aL)->next;
	}
	
	//if end of list reached, update last pointer
	if (*aL == NULL && last != NULL) {	
		*last = aux;
	}
	
	aux->next = *aL;
	*aL = aux;
	
	return 1;
}

void printL (TList L, TFwork print, FILE *out) {
	while (L) {
		print(L->inf, out);
		L = L->next;
	}
}

void destroyL (AList aL) {
	TList l = *aL, aux = NULL;
	
	while (l) {
		aux = l;
		l = l->next;
		
		free(aux->inf);
		free(aux);
	}
	
	*aL = NULL;
}
