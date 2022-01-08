CC = gcc
FLAGS = -g -Wall
.PHONY: clean

all: graph

graph: main.o graphAlgo.so graph.so
	$(CC) $(FLAGS) -o graph main.o ./graphAlgo.so ./graph.so

tests: tests.o graphAlgo.so graph.so
	$(CC) $(FLAGS) -o tests tests.o ./graphAlgo.so ./graph.so

main.o: main.c graphAlgo.h graph.h
	$(CC) $(FLAGS) -c main.c

tests.o: tests.c graphAlgo.h graph.h
	$(CC) $(FLAGS) -c tests.c

graphAlgo.so: graphAlgo.o
	$(CC) $(FLAGS) -shared -o graphAlgo.so graphAlgo.o  

graph.so: graph.o
	$(CC) $(FLAGS) -shared -o graph.so graph.o  

graph.o: graphClass.c graphAlgo.h
	$(CC) $(FLAGS) -c graphClass.c -o graph.o

graphAlgo.o: graphAlgo.c graph.h
	$(CC) $(FLAGS) -c graphAlgo.c


clean:
	rm -f *.o *.a *.so graph tests