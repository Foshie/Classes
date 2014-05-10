CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g

all: 	all1 all2
all1:	public01.x public02.x public03.x public04.x public05.x\
	public06.x public07.x public08.x public09.x public10.x\
	public11.x public12.x public13.x public14.x 

all2:	secret01.x secret02.x secret03.x secret04.x secret05.x\
	secret06.x secret07.x secret08.x secret09.x secret10.x\
	secret11.x secret12.x secret13.x secret14.x 

clean:
	rm -f *.x *.o *.gch *~

array-hash-map.o: array-hash-map.c hash-map.h hash-map-implementation.h
	$(CC) $(CFLAGS) -c array-hash-map.c

linked-hash-map.o: linked-hash-map.c hash-map.h hash-map-implementation.h
	$(CC) $(CFLAGS) -c linked-hash-map.c

public01.o: public01.c hash-map.h
	$(CC) $(CFLAGS) -c public01.c
public01.x: public01.o array-hash-map.o
	$(CC) -o public01.x public01.o array-hash-map.o

public02.o: public02.c hash-map.h
	$(CC) $(CFLAGS) -c public02.c
public02.x: public02.o linked-hash-map.o
	$(CC) -o public02.x public02.o linked-hash-map.o

public03.o: public03.c hash-map.h
	$(CC) $(CFLAGS) -c public03.c
public03.x: public03.o array-hash-map.o
	$(CC) -o public03.x public03.o array-hash-map.o

public04.o: public04.c hash-map.h
	$(CC) $(CFLAGS) -c public04.c
public04.x: public04.o linked-hash-map.o
	$(CC) -o public04.x public04.o linked-hash-map.o

public05.o: public05.c hash-map.h
	$(CC) $(CFLAGS) -c public05.c
public05.x: public05.o array-hash-map.o
	$(CC) -o public05.x public05.o array-hash-map.o

public06.o: public06.c hash-map.h
	$(CC) $(CFLAGS) -c public06.c
public06.x: public06.o linked-hash-map.o
	$(CC) -o public06.x public06.o linked-hash-map.o

public07.o: public07.c hash-map.h
	$(CC) $(CFLAGS) -c public07.c
public07.x: public07.o array-hash-map.o
	$(CC) -o public07.x public07.o array-hash-map.o

public08.o: public08.c hash-map.h
	$(CC) $(CFLAGS) -c public08.c
public08.x: public08.o linked-hash-map.o
	$(CC) -o public08.x public08.o linked-hash-map.o

public09.o: public09.c hash-map.h
	$(CC) $(CFLAGS) -c public09.c
public09.x: public09.o array-hash-map.o
	$(CC) -o public09.x public09.o array-hash-map.o
public10.o: public10.c hash-map.h
	$(CC) $(CFLAGS) -c public10.c
public10.x: public10.o linked-hash-map.o
	$(CC) -o public10.x public10.o linked-hash-map.o

public11.o: public11.c hash-map.h
	$(CC) $(CFLAGS) -c public11.c
public11.x: public11.o array-hash-map.o
	$(CC) -o public11.x public11.o array-hash-map.o

public12.o: public12.c hash-map.h
	$(CC) $(CFLAGS) -c public12.c
public12.x: public12.o linked-hash-map.o
	$(CC) -o public12.x public12.o linked-hash-map.o

public13.o: public13.c hash-map.h
	$(CC) $(CFLAGS) -c public13.c
public13.x: public13.o array-hash-map.o
	$(CC) -o public13.x public13.o array-hash-map.o

public14.o: public14.c hash-map.h
	$(CC) $(CFLAGS) -c public14.c
public14.x: public14.o linked-hash-map.o
	$(CC) -o public14.x public14.o linked-hash-map.o

secret01.o: secret01.c hash-map.h
	$(CC) $(CFLAGS) -c secret01.c
secret01.x: secret01.o array-hash-map.o
	$(CC) -o secret01.x secret01.o array-hash-map.o

secret02.o: secret02.c hash-map.h
	$(CC) $(CFLAGS) -c secret02.c
secret02.x: secret02.o linked-hash-map.o
	$(CC) -o secret02.x secret02.o linked-hash-map.o

secret03.o: secret03.c hash-map.h
	$(CC) $(CFLAGS) -c secret03.c
secret03.x: secret03.o array-hash-map.o
	$(CC) -o secret03.x secret03.o array-hash-map.o

secret04.o: secret04.c hash-map.h
	$(CC) $(CFLAGS) -c secret04.c
secret04.x: secret04.o linked-hash-map.o
	$(CC) -o secret04.x secret04.o linked-hash-map.o

secret05.o: secret05.c hash-map.h
	$(CC) $(CFLAGS) -c secret05.c
secret05.x: secret05.o array-hash-map.o
	$(CC) -o secret05.x secret05.o array-hash-map.o

secret06.o: secret06.c hash-map.h
	$(CC) $(CFLAGS) -c secret06.c
secret06.x: secret06.o linked-hash-map.o
	$(CC) -o secret06.x secret06.o linked-hash-map.o

secret07.o: secret07.c hash-map.h
	$(CC) $(CFLAGS) -c secret07.c
secret07.x: secret07.o array-hash-map.o
	$(CC) -o secret07.x secret07.o array-hash-map.o

secret08.o: secret08.c hash-map.h
	$(CC) $(CFLAGS) -c secret08.c
secret08.x: secret08.o linked-hash-map.o
	$(CC) -o secret08.x secret08.o linked-hash-map.o

secret09.o: secret09.c hash-map.h
	$(CC) $(CFLAGS) -c secret09.c
secret09.x: secret09.o array-hash-map.o
	$(CC) -o secret09.x secret09.o array-hash-map.o
secret10.o: secret10.c hash-map.h
	$(CC) $(CFLAGS) -c secret10.c
secret10.x: secret10.o linked-hash-map.o
	$(CC) -o secret10.x secret10.o linked-hash-map.o

secret11.o: secret11.c hash-map.h
	$(CC) $(CFLAGS) -c secret11.c
secret11.x: secret11.o array-hash-map.o
	$(CC) -o secret11.x secret11.o array-hash-map.o

secret12.o: secret12.c hash-map.h
	$(CC) $(CFLAGS) -c secret12.c
secret12.x: secret12.o linked-hash-map.o
	$(CC) -o secret12.x secret12.o linked-hash-map.o

secret13.o: secret13.c hash-map.h
	$(CC) $(CFLAGS) -c secret13.c
secret13.x: secret13.o array-hash-map.o
	$(CC) -o secret13.x secret13.o array-hash-map.o

secret14.o: secret14.c hash-map.h
	$(CC) $(CFLAGS) -c secret14.c
secret14.x: secret14.o linked-hash-map.o
	$(CC) -o secret14.x secret14.o linked-hash-map.o
