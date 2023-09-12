CC = gcc

all: main.o userinput.o userfunctions.o filehandler.o
	$(CC) $^ -o all

main.o:	main.c userfunctions.h userinput.h
	$(CC) -c main.c

userinput.o: userinput.c userinput.h
	$(CC) -c userinput.c

userfunctions.o: userfunctions.c userfunctions.h
	$(CC) -c userfunctions.c

filehandler.o: filehandler.c header.h
	$(CC) -c filehandler.c

clean:
	rm *.o all 