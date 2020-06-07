CC = gcc
AR = ar -rcs
OBJECTS_MAIN = q1.o
FLAGS = -Wall


all: q1

q1: q1.o
	$(CC) $(FLAGS) -o q1 $(OBJECTS_MAIN)

q1.o: q1.c
	$(CC) $(FLAGS) -c q1.c


.PHONY: clean all q1

clean:
	rm -f *.o q1