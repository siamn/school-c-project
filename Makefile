CC = gcc

all: main.o userinput.o
	$(CC) main.o userinput.o -o all

main.o:	main.c header.h
	$(CC) -c main.c

userinput.o: userinput.c header.h
	$(CC) -c userinput.c

clean:
	rm *.o all 