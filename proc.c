/* MARDALE Andrei-Iulian - 311CB */
#include "proc.h"

int cmp (const void *a, const void *b) {
	TProcess *A = (TProcess *) a;
	TProcess *B = (TProcess *) b;
	int pdiff = B->priority - A->priority; //decreasing by order
	
	if (pdiff == 0) {
		return A->step - B->step; //increasing by steps
	}
	
	return pdiff;
}

void print (const void *a, const void *b) {
	TProcess *A = (TProcess *) a;
	FILE *out = (FILE *) b;
	fprintf(out, "%zu ", A->id);
}
			

int parse (FILE *in, FILE *out) {
	char *input = malloc(MAXLEN);
	char *test = fgets(input, MAXLEN, in);
	
	size_t n = atoi(test); //number of events
	size_t step = 1; //current step;
	
	//create Events stacks
	AStack *Events = initEvents(n);
	if (!Events) {
		return 1;
	}
	
	//create process queue
	AQueue aQ = initQ(sizeof(TProcess));
	
	int check = 1; //used for checking function output
	
	test = fgets(input, MAXLEN, in);
	while (test != NULL && test[0] != '\n') {
		//tokenize input 
		char *cmd[3] = {0};
		int i = 0;
		char *aux = strtok(test, " \n");
		while (aux != NULL) {
			cmd[i] = aux;
			++i;
			aux = strtok(NULL, " \n");
		}
		
		if (cmd[0] != NULL) {
			//call function accordingly
			if (!strcmp(cmd[0], "start")) {
				check = start(atoi(cmd[1]), atoi(cmd[2]), step, aQ);
			} else if (!strcmp(cmd[0], "wait")) {
				check = wait(atoi(cmd[1]), atoi(cmd[2]), &aQ, Events);
			} else if (!strcmp(cmd[0], "event")) {
				check = event(atoi(cmd[1]), aQ, Events);
			} else if (!strcmp(cmd[0], "end")) {
				check = end(atoi(cmd[1]), &aQ);
			}
		}
		
		//if some of the functions encountered problems exit loop (and program)
		//most probably will not happen
		if (check != 1) {
			for (size_t i = 0; i < n; i++) {
				destroyS(&Events[i]);
			}
			free(Events);
			destroyQ(&aQ);
			free(input);
			return check;
		}
		
		printEnv(step, n, aQ, Events, out);
		test = fgets(input, MAXLEN, in);
		++step;
	}	
	
	//free what needs to be freed
	for (size_t i = 0; i < n; i++) {
		destroyS(&Events[i]);
	}
	free(Events);
	destroyQ(&aQ);
	free(input);
	return 1;
}

AStack * initEvents(size_t n) {
	AStack *Events = malloc(n * sizeof(AStack));
	if (!Events) return NULL;
	
	for (size_t i = 0; i < n; ++i) {
		Events[i] = initStack(sizeof(TProcess));
		
		if (!Events[i]) {
			for (size_t j = 0; j < i; ++j) {
				free(Events[j]);
			}
			free(Events);
			return NULL;
		}
	}	
	
	return Events;
}

//creates process, then adds it to queue
int start (size_t id, size_t priority, size_t step, AQueue aQ) {
	TProcess P = {id, priority, step};
	
	return intrQ(aQ, &P, cmp);
}

//receives pointer to AQueue - does not copy the values back in the original queue
//just copies everything except the waiting process and then replaces the old queue with the new one
int wait (size_t evNo, size_t id, AQueue *aQ, AStack *Events) {
	TProcess *ae = malloc(sizeof(TProcess));
	if (!ae) return 0;
	
	AQueue aux = initQ(sizeof(TProcess));
	if (!aux) {
		free(ae);
		return 0;
	}
	
	int check = 0;
	
	while(!EMPTY_QUEUE(*aQ)) {
		extrQ(*aQ, ae);
		if (ae->id != id) {
			check = intrQ(aux, ae, cmp);
		} else {
			check = push(Events[evNo], ae);
		}
	
		if (check == 0) return 0;
	}
	
	free(ae);
	free(*aQ); //frees memory
	
	*aQ = aux; //more efficient than copying the data back
	
	return 1;
}

//just pops that stack and add elements to queue
int event (size_t evNo, AQueue aQ, AStack *Events) {
	TProcess *ae = malloc(sizeof(TProcess));
	if (!ae) return 0;
	
	int check = 0;
	while (!EMPTY_STACK(Events[evNo])) {
		pop(Events[evNo], ae);
		check = intrQ(aQ, ae, cmp);
		if (check == 0) {
			free(ae);
			return 0;
		}
	}
	
	free(ae);
	return 1;
}

//copies everything except the terminated process to a new queue
//then replaces the old queue with the new one
int end (size_t id, AQueue *aQ) {
	TProcess *ae = malloc(sizeof(TProcess));
	if (!ae) return 0;
	
	AQueue aux = initQ(sizeof(TProcess));
	if (!aux) {
		free(ae);
		return 0;
	}
	
	int check = 0;
	while (!EMPTY_QUEUE(*aQ)) {
		extrQ(*aQ, ae);
		if (ae->id != id) {
			check = intrQ(aux, ae, cmp);
			if (!check) {
				free(ae);
				destroyQ(&aux);
				return 0;
			}
		}
	}
	
	free(ae);
	free(*aQ); //frees memory
	
	*aQ = aux; //more efficient than copying the data back
	
	return 1;
}
	
	

void printEnv (size_t step, int n, AQueue aQ, AStack *Events, FILE *out) {
	fprintf(out, "%zu\n", step);
	
	printQ(aQ, print, out);
	fprintf(out, "\n");
	
	for (int i = 0; i < n; ++i) {
		if (!EMPTY_STACK(Events[i])) {
			fprintf(out, "%d: ", i);
			printS(Events[i], print, out);
			fprintf(out, "\n");
		}
	}
	
	fprintf(out, "\n");
}
	
	
	
	
