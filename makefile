CFLAGS = -Wall -g
CC = gcc
AR = ar

all: graph

graph: main.o nodes.o algo.o
	$(CC) $(CFLAGS) -o graph nodes.o main.o algo.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

nodes.o: nodes.c
	$(CC) $(CFLAGS) -c nodes.c -o nodes.o

algo.o: algo.c
	$(CC) $(CFLAGS) -c algo.c -o algo.o

.PHONY: clean all

clean: 
	rm -f *.o graph
