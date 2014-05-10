CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g
LDFLAGS = -lpthread
PROGS = mergetest   public00 public01 public02 \
        public03 public04 public05

.PHONY: all clean

all: $(PROGS)

clean:
	rm -f *.o $(PROGS)

$(PROGS): mergesort.o
mergetest: mergetest.o
public%: public%.o

mergetest.o: mergesort.h
mergesort.o: mergesort.h
public%.o: mergesort.h
