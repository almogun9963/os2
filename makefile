CC= gcc -pthread

all: q1_1 q1_2 q2_1 q2_2 q3_1 q3_2

q1_1: 2_1_1.c
	$(CC)  2_1_1.c -g -o 2_1_1
q1_2: 2_1_2.c
	$(CC)  2_1_2.c -g -o 2_1_2
q2_1: 2_2_1.c
	$(CC)  2_2_1.c -g -o 2_2_1
q2_2: 2_2_2.c
	$(CC)  2_2_2.c -g -o 2_2_2
q3_1: 2_3_1.c
	$(CC)  2_3_1.c -g -o 2_3_1
q3_2: 2_3_2.c
	$(CC)  2_3_2.c -g -o 2_3_2



.PHONY: clean all
clean:
	rm -f *.o 2_1_1 2_1_2 2_2_1 2_2_2 2_3_1 2_3_2