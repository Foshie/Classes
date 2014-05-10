CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g -DNUM_BUCKETS=5
PROGS = hashtester public00 public01 public02 \
	public03 public04 public05

.PHONY: all clean

all: $(PROGS)

clean:
	rm -f *.o $(PROGS)

$(PROGS): hashtable.o
hashtester: hashtester.o
public%: public%.o

hashtester.o: hashtable.h
hashtable.o: hashtable.h
public%.o: hashtable.h
