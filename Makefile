CC = gcc -c
LD = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

build: tema2

tema2: main.o proc.o queue.o stack.o list.o
	$(LD) $(CFLAGS) $^ -o $@

main.o: main.c proc.h queue.h list.h
	$(CC) $(CFLAGS) $< -o $@

proc.o: proc.c proc.h queue.h list.h
	$(CC) $(CFLAGS) $< -o $@
	
queue.o: queue.c queue.h list.h
	$(CC) $(CFLAGS) $< -o $@

stack.o: stack.c stack.h list.h
	$(CC) $(CFLAGS) $< -o $@
	
list.o: list.c list.h
	$(CC) $(CFLAGS) $< -o $@
	
	
clean:
	rm -f tema2
	rm -f *.o
	rm -f *~
