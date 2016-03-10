#processPlanifier
My second Data Structures homework

A C process planifier which simulates the way an operating system handles running processes with a given priority and the events on which a process may depend. It uses the (priority) queue and stack data structures in order to achieve this functionality.

#Context
Each process has a given priority and they are kept in a priority queue. At any time an event may occur and some processes may depend on this event. In this case they are removed from the queue and added to a stack associated with this event. When the event finishes, the stack is emptied and the processes are added back to the queue.

The stack and queue are implemented using single linked lists.

As a constraint, the number of possible events is given at the beginning of the program.

#How to compile
Run "make build"

#How to run
Use the syntax: "./tema2 data.in data.out" where:
* data.in - input file
* data.out - output file

#Input data syntax
N - event number, followed by any of the given actions:
* start X Y - starts process X with priority Y
* wait E X - process X will have to wait for event E
* event E - event E will finish and it's stack will be emptied
* end X - process X will finish, and will be removed

#Output data syntax
* n -current action
* X_1 X_2 ... X_n - process queue with processes sorted by order (decreasing)
* K_i : X_i1 X_i2 ... X_in - event K_i and the processes which are waiting for it to finish
