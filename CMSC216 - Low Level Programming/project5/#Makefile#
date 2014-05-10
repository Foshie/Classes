CC = gcc
CFLAGS = -ansi -pedantic-errors -c -Wall -Werror
all: mysh

parser.o: parser.h
execute.o: execute.h wait.h
mysh.o: parser.h execute.h

mysh: parser.o mysh.o execute.o

clean:
	rm -f *.o mysh