CC = gcc
CFLAGS = -Wall -Werror -Wshadow -g
DEPS = $(HEADERS)

ODIR=../obj
MAPDIR=../map
QUERYDIR=../QUERY
DEPDIR := .d

$(shell mkdir -p $(ODIR) >/dev/null)
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

HEADERS = graph.h fileio.h
CSOURCE = graph.c fileio.c main.c
COBJ = $(CSOURCE:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(COBJ))

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

.PHONY:clean cleanAll all ca usa 5x5

all: shortestpath

$(ODIR)/%.o: %.c
$(ODIR)/%.o: %.c $(DEPDIR)/%.d
	$(COMPILE.c) -o $@ $< $(CFLAGS)
	$(POSTCOMPILE)

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

cleanAll:clean
	rm -f $(ODIR)/*

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(CSOURCE))))
