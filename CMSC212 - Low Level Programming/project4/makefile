CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g

all: all1 all2 all3

all1: public01.x public02.x public03.x public04.x public05.x
all2: public06.x public07.x public08.x public09.x public10.x
all3: public11.x public12.x public13.x public14.x public15.x

clean:
	rm -f *.x *.o *.gch *~


filesystem.o: filesystem.c filesystem.h
	$(CC) $(CFLAGS) -c filesystem.c

public01.o: public01.c filesystem.h
	$(CC) $(CFLAGS) -c public01.c
public01.x: public01.o filesystem.o
	$(CC) -o public01.x public01.o filesystem.o

public02.o: public02.c filesystem.h
	$(CC) $(CFLAGS) -c public02.c
public02.x: public02.o filesystem.o
	$(CC) -o public02.x public02.o filesystem.o

public03.o: public03.c filesystem.h
	$(CC) $(CFLAGS) -c public03.c
public03.x: public03.o filesystem.o
	$(CC) -o public03.x public03.o filesystem.o

public04.o: public04.c filesystem.h
	$(CC) $(CFLAGS) -c public04.c
public04.x: public04.o filesystem.o
	$(CC) -o public04.x public04.o filesystem.o

public05.o: public05.c filesystem.h
	$(CC) $(CFLAGS) -c public05.c
public05.x: public05.o filesystem.o
	$(CC) -o public05.x public05.o filesystem.o

public06.o: public06.c filesystem.h
	$(CC) $(CFLAGS) -c public06.c
public06.x: public06.o filesystem.o
	$(CC) -o public06.x public06.o filesystem.o

public07.o: public07.c filesystem.h
	$(CC) $(CFLAGS) -c public07.c
public07.x: public07.o filesystem.o
	$(CC) -o public07.x public07.o filesystem.o

public08.o: public08.c filesystem.h
	$(CC) $(CFLAGS) -c public08.c
public08.x: public08.o filesystem.o
	$(CC) -o public08.x public08.o filesystem.o

public09.o: public09.c filesystem.h
	$(CC) $(CFLAGS) -c public09.c
public09.x: public09.o filesystem.o
	$(CC) -o public09.x public09.o filesystem.o
public10.o: public10.c filesystem.h
	$(CC) $(CFLAGS) -c public10.c
public10.x: public10.o filesystem.o
	$(CC) -o public10.x public10.o filesystem.o

public11.o: public11.c filesystem.h
	$(CC) $(CFLAGS) -c public11.c
public11.x: public11.o filesystem.o
	$(CC) -o public11.x public11.o filesystem.o

public12.o: public12.c filesystem.h
	$(CC) $(CFLAGS) -c public12.c
public12.x: public12.o filesystem.o
	$(CC) -o public12.x public12.o filesystem.o

public13.o: public13.c filesystem.h
	$(CC) $(CFLAGS) -c public13.c
public13.x: public13.o filesystem.o
	$(CC) -o public13.x public13.o filesystem.o

public14.o: public14.c filesystem.h
	$(CC) $(CFLAGS) -c public14.c
public14.x: public14.o filesystem.o
	$(CC) -o public14.x public14.o filesystem.o

public15.o: public15.c filesystem.h
	$(CC) $(CFLAGS) -c public15.c
public15.x: public15.o filesystem.o
	$(CC) -o public15.x public15.o filesystem.o
