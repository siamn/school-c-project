CC = gcc

all: main.o userinput.o filehandler.o
	$(CC) $^ -o all

main.o:	main.c header.h
	$(CC) -c main.c

userinput.o: userinput.c header.h
	$(CC) -c userinput.c

filehandler.o: filehandler.c header.h
	$(CC) -c filehandler.c

clean:
	rm *.o all 