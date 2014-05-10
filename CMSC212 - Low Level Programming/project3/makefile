CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g

all: all1 all2 all3

all1: public01.x public02.x public03.x public04.x public05.x
all2: public06.x public07.x public08.x public09.x public10.x
all3: public11.x public12.x public13.x public14.x public15.x

clean:
	rm -f *.x *.o *.gch *~

polynomial.o: polynomial.c polynomial.h
	$(CC) $(CFLAGS) -c polynomial.c

public01.o: public01.c polynomial.h
	$(CC) $(CFLAGS) -c public01.c
public01.x: public01.o polynomial.o
	$(CC) -o public01.x public01.o polynomial.o

public02.o: public02.c polynomial.h
	$(CC) $(CFLAGS) -c public02.c
public02.x: public02.o polynomial.o
	$(CC) -o public02.x public02.o polynomial.o

public03.o: public03.c polynomial.h
	$(CC) $(CFLAGS) -c public03.c
public03.x: public03.o polynomial.o
	$(CC) -o public03.x public03.o polynomial.o

public04.o: public04.c polynomial.h
	$(CC) $(CFLAGS) -c public04.c
public04.x: public04.o polynomial.o
	$(CC) -o public04.x public04.o polynomial.o

public05.o: public05.c polynomial.h
	$(CC) $(CFLAGS) -c public05.c
public05.x: public05.o polynomial.o
	$(CC) -o public05.x public05.o polynomial.o

public06.o: public06.c polynomial.h
	$(CC) $(CFLAGS) -c public06.c
public06.x: public06.o polynomial.o
	$(CC) -o public06.x public06.o polynomial.o

public07.o: public07.c polynomial.h
	$(CC) $(CFLAGS) -c public07.c
public07.x: public07.o polynomial.o
	$(CC) -o public07.x public07.o polynomial.o

public08.o: public08.c polynomial.h
	$(CC) $(CFLAGS) -c public08.c
public08.x: public08.o polynomial.o
	$(CC) -o public08.x public08.o polynomial.o

public09.o: public09.c polynomial.h
	$(CC) $(CFLAGS) -c public09.c
public09.x: public09.o polynomial.o
	$(CC) -o public09.x public09.o polynomial.o
public10.o: public10.c polynomial.h
	$(CC) $(CFLAGS) -c public10.c
public10.x: public10.o polynomial.o
	$(CC) -o public10.x public10.o polynomial.o

public11.o: public11.c polynomial.h
	$(CC) $(CFLAGS) -c public11.c
public11.x: public11.o polynomial.o
	$(CC) -o public11.x public11.o polynomial.o

public12.o: public12.c polynomial.h
	$(CC) $(CFLAGS) -c public12.c
public12.x: public12.o polynomial.o
	$(CC) -o public12.x public12.o polynomial.o

public13.o: public13.c polynomial.h
	$(CC) $(CFLAGS) -c public13.c
public13.x: public13.o polynomial.o
	$(CC) -o public13.x public13.o polynomial.o

public14.o: public14.c polynomial.h
	$(CC) $(CFLAGS) -c public14.c
public14.x: public14.o polynomial.o
	$(CC) -o public14.x public14.o polynomial.o

public15.o: public15.c polynomial.h
	$(CC) $(CFLAGS) -c public15.c
public15.x: public15.o polynomial.o
	$(CC) -o public15.x public15.o polynomial.o
