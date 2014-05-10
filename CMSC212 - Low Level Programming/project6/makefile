CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g
LIBFLAGS = -nostdlib -shared -fPIC -Wl,-soname,libhash-map.so

all:	libhash-map.so public01.x public02.x public03.x public04.x \
	public05.x public06.x public07.x public08.x public09.x public10.x\
	public11.x public12.x public13.x public14.x 

clean:
	rm -f *.x *.o *.so

libhash-map.so: liblinked-hash-map.so libarray-hash-map.so
	ln -sf libarray-hash-map.so libhash-map.so

array-iterator.o: array-iterator.c iterator.h array-iterator.h types.h
	$(CC) $(CFLAGS) -c -fPIC array-iterator.c

linked-iterator.o: linked-iterator.c iterator.h linked-iterator.h types.h
	$(CC) $(CFLAGS) -c -fPIC linked-iterator.c

libarray-hash-map.so:	array-hash-map.o array-iterator.o
	$(CC) $(LIBFLAGS) array-hash-map.o array-iterator.o -o $@

liblinked-hash-map.so:	linked-hash-map.o linked-iterator.o
	$(CC) $(LIBFLAGS) linked-hash-map.o linked-iterator.o -o $@

array-hash-map.o: array-hash-map.c hash-map.h array-hash-map.h
	$(CC) $(CFLAGS) -fPIC -c array-hash-map.c

linked-hash-map.o: linked-hash-map.c hash-map.h linked-hash-map.h
	$(CC) $(CFLAGS) -fPIC -c linked-hash-map.c

public01.o: public01.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public01.c
public01.x: public01.o
	$(CC) -o public01.x public01.o -L. -lhash-map

public02.o: public02.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public02.c
public02.x: public02.o
	$(CC) -o public02.x public02.o -L. -lhash-map

public03.o: public03.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public03.c
public03.x: public03.o
	$(CC) -o public03.x public03.o -L. -lhash-map

public04.o: public04.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public04.c
public04.x: public04.o
	$(CC) -o public04.x public04.o -L. -lhash-map

public05.o: public05.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public05.c
public05.x: public05.o
	$(CC) -o public05.x public05.o -L. -lhash-map

public06.o: public06.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public06.c
public06.x: public06.o
	$(CC) -o public06.x public06.o -L. -lhash-map

public07.o: public07.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public07.c
public07.x: public07.o
	$(CC) -o public07.x public07.o -L. -lhash-map

public08.o: public08.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public08.c
public08.x: public08.o
	$(CC) -o public08.x public08.o -L. -lhash-map

public09.o: public09.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public09.c
public09.x: public09.o
	$(CC) -o public09.x public09.o -L. -lhash-map

public10.o: public10.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public10.c
public10.x: public10.o
	$(CC) -o public10.x public10.o -L. -lhash-map

public11.o: public11.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public11.c
public11.x: public11.o
	$(CC) -o public11.x public11.o -L. -lhash-map

public12.o: public12.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public12.c
public12.x: public12.o
	$(CC) -o public12.x public12.o -L. -lhash-map

public13.o: public13.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public13.c
public13.x: public13.o
	$(CC) -o public13.x public13.o -L. -lhash-map

public14.o: public14.c hash-map.h iterator.h types.h
	$(CC) $(CFLAGS) -c public14.c
public14.x: public14.o
	$(CC) -o public14.x public14.o -L. -lhash-map 