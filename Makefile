CC = gcc

all: main.o
	$(CC) main.o -o all

main.o:	main.c
	$(CC) -c main.c

clean:
	rm *.o all 