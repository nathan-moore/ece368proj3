CC = gcc
CFLAGS = -Wall -Werror -Wshadow -g
DEPS = $(HEADERS)

ODIR=../obj
MAPDIR=../map
QUERYDIR=../QUERY

HEADERS = graph.h fileio.h
CSOURCE = graph.c fileio.c main.c
COBJ = $(CSOURCE:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(COBJ))

.PHONY:clean all ca usa 5x5

all: shortestpath

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shortestpath:$(OBJ)
	gcc -o $@ $^

ca:shortestpath 
	valgrind ./shortestpath $(MAPDIR)/roadCA.txt $(QUERYDIR)/usa10.txt

usa:shortestpath
	./shortestpath $(MAPDIR)/usa.txt $(QUERYDIR)/usa10.txt

5x5:shortestpath
	valgrind ./shortestpath $(MAPDIR)/5x5.txt $(QUERYDIR)/5x5query.txt

clean:
	rm -f *~
	rm -f shortestpath
	rm -f $(ODIR)/*.o
