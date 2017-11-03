CC = gcc
CFLAGS = -Wall -Werror -Wshadow 

HEADERS = graph.h #fileio.h
CSOURCE = graph.c fileio.c main.c
COBJ = $(CSOURCE:.c=.o)

all:$(COBJ) $(HEADERS)
	gcc -o shortestpath $(COBJ)

clean:
	rm -f *.o
	rm -f *~
