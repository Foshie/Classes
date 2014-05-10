CC = gcc
CFLAGS = -Wall -ansi -pedantic-errors -Werror -g

all: all1 all2 all3

all1: public01.x public02.x public03.x public04.x public05.x public06.x
all2: public07.x public08.x public09.x public10.x public11.x public12.x
all3: public13.x public14.x public15.x

clean:
	rm -f *.x machine.o public01.o public-2.o public03.o public04.o public05.o public06.o public07.o public08.o public09.o public10.o public11.o public12.o public13.o public14.o public15.o *.gch *~

machine.o: machine.c machine.h
	$(CC) $(CFLAGS) -c machine.c machine.h

public01.o: public01.c machine.h
	$(CC) $(CFLAGS) -c public01.c
public01.x: public01.o machine.o
	$(CC) -o public01.x public01.o machine.o assembler.o

public02.o: public02.c machine.h
	$(CC) $(CFLAGS) -c public02.c
public02.x: public02.o machine.o
	$(CC) -o public02.x public02.o machine.o assembler.o

public03.o: public03.c machine.h
	$(CC) $(CFLAGS) -c public03.c
public03.x: public03.o machine.o
	$(CC) -o public03.x public03.o machine.o assembler.o

public04.o: public04.c machine.h
	$(CC) $(CFLAGS) -c public04.c
public04.x: public04.o machine.o
	$(CC) -o public04.x public04.o machine.o assembler.o

public05.o: public05.c machine.h
	$(CC) $(CFLAGS) -c public05.c
public05.x: public05.o machine.o
	$(CC) -o public05.x public05.o machine.o assembler.o

public06.o: public06.c machine.h
	$(CC) $(CFLAGS) -c public06.c
public06.x: public06.o machine.o
	$(CC) -o public06.x public06.o machine.o assembler.o

public07.o: public07.c machine.h
	$(CC) $(CFLAGS) -c public07.c
public07.x: public07.o machine.o
	$(CC) -o public07.x public07.o machine.o assembler.o

public08.o: public08.c machine.h
	$(CC) $(CFLAGS) -c public08.c
public08.x: public08.o machine.o
	$(CC) -o public08.x public08.o machine.o assembler.o

public09.o: public09.c machine.h
	$(CC) $(CFLAGS) -c public09.c
public09.x: public09.o machine.o
	$(CC) -o public09.x public09.o machine.o assembler.o

public10.o: public10.c machine.h
	$(CC) $(CFLAGS) -c public10.c
public10.x: public10.o machine.o
	$(CC) -o public10.x public10.o machine.o assembler.o

public11.o: public11.c machine.h
	$(CC) $(CFLAGS) -c public11.c
public11.x: public11.o machine.o
	$(CC) -o public11.x public11.o machine.o assembler.o

public12.o: public12.c machine.h
	$(CC) $(CFLAGS) -c public12.c
public12.x: public12.o machine.o
	$(CC) -o public12.x public12.o machine.o assembler.o

public13.o: public13.c machine.h
	$(CC) $(CFLAGS) -c public13.c
public13.x: public13.o machine.o
	$(CC) -o public13.x public13.o machine.o assembler.o

public14.o: public14.c machine.h
	$(CC) $(CFLAGS) -c public14.c
public14.x: public14.o machine.o
	$(CC) -o public14.x public14.o machine.o assembler.o

public15.o: public15.c machine.h
	$(CC) $(CFLAGS) -c public15.c
public15.x: public15.o machine.o
	$(CC) -o public15.x public15.o machine.o assembler.o