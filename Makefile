CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -g
OBJS = main.o mazegen.o mazeplay.o utility.o

MazeRunner:	$(OBJS)
	$(CC)	$(CFLAGS) -o MazeRunner	$(OBJS)

main.o: main.c mazegen.h mazeplay.h utility.h
	$(CC)	$(CFLAGS) -c main.c

mazegen.o: mazegen.c mazegen.h utility.h
	$(CC)	$(CFLAGS) -c mazegen.c

mazeplay.o: mazeplay.c mazeplay.h utility.h
	$(CC)	$(CFLAGS) -c mazeplay.c

utility.o: utility.c utility.h
	$(CC)	$(CFLAGS) -c utility.c

clean:
	rm -f *.o MazeRunner