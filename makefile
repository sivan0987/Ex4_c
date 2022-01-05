CC = gcc
AR = ar -rcs
FLAGS = -Wall -g
all: graph

main.o: main.c
	$(CC) $(FLAGS) -c main.c

graph: main.o
	$(CC) $(FLAGS) main.o -o graph

clean:
	rm -f *.o *.a *.so graph