CC := gcc
CFLAGS := -Wall -Werror -Wshadow -Wextra -O3
LINKFLAGS := -lm

ODIR :=../obj
MAPDIR :=../map
QUERYDIR :=../query
DEPDIR := .d
TESTDIR := ../tests

$(shell mkdir -p $(ODIR) >/dev/null)
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(notdir $*).Td

HEADERS := graph.h fileio.h utility.h
CSOURCE := graph.c fileio.c main.c utility.c
TESTS := priorityqueue.c pqtest2.c walk.c
COBJ := $(CSOURCE:.c=.o)
OBJ := $(patsubst %,$(ODIR)/%,$(COBJ))
TEST := $(patsubst %,$(ODIR)/%,$(TESTS))
OBJTEST := $(TEST:.c=.o)

SOURCES = $(CSOURCE) $(patsubst %,_%,$(notdir $(TESTS)))

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -c
POSTCOMPILE = @mv -f $(DEPDIR)/$(notdir $(notdir $*)).Td $(DEPDIR)/$(notdir $*).d && touch $@

#gets given files if I don't currently have them
MAPFILES = map5x5.txt roadCA.txt usa.txt
QUERYFILES = query5x5.txt usa1.txt usa10.txt usa100.txt
PROVMAP = $(addprefix $(MAPDIR)/,$(MAPFILES))
PROVQUERY = $(addprefix $(QUERYDIR)/,$(QUERYFILES))


WGET = wget -A txt -m -p -E -k -K -mp
FILE = ftp.ecn.purdue.edu/xzl/inv/ece368-f17/proj3
SITE = ftp://$(FILE)
CLEANUP = rm -rf ftp.ecn.purdue.edu

GIVENBINARY = ../shortestpath

.PHONY:clean cleanAll all ca usa 5x5

all: shortestpath

.SECONDEXPANSION:
$(OBJTEST): $(TESTDIR)/$$(notdir $$(subst .o,.c,$$@))
$(OBJTEST): $(TESTDIR)/$$(notdir $$(subst .o,.c,$$@)) $(DEPDIR)/$$(notdir $$(subst .o,.d,$$@))
	cp $(TESTDIR)/$(notdir $<) $(notdir $<)
	$(COMPILE.c) -o $@ $(notdir $(subst .o,.c,$@))
	$(POSTCOMPILE)
	rm $(notdir $<) > /dev/null

$(ODIR)/%.o: %.c
$(ODIR)/%.o: %.c $(DEPDIR)/%.d
	$(COMPILE.c) -o $@ $<
	$(POSTCOMPILE)

shortestpath:$(OBJ)
	gcc -o $@ $^ $(LINKFLAGS)

pqueuetest:$(ODIR)/utility.o $(ODIR)/priorityqueue.o
	gcc -o $@ $^ $(LINKFLAGS)

pqtest2:$(ODIR)/utility.o $(ODIR)/pqtest2.o
	gcc -o $@ $^ $(LINKFLAGS)

ca:shortestpath $(MAPDIR)/roadCA.txt $(QUERYDIR)/usa10.txt
	./shortestpath $(MAPDIR)/roadCA.txt $(QUERYDIR)/usa10.txt > o1.txt
	$(GIVENBINARY) $(MAPDIR)/roadCA.txt $(QUERYDIR)/usa10.txt > o2.txt
	./walk $(MAPDIR)/roadCA.txt o1.txt o2.txt
	rm o1.txt o2.txt

usa1 usa10 usa100 usadb buggy:walk shortestpath $(MAPDIR)/usa.txt $(QUERYDIR)/$$@.txt
	time ./shortestpath $(MAPDIR)/usa.txt $(QUERYDIR)/$@.txt > o1.txt
	time $(GIVENBINARY) $(MAPDIR)/usa.txt $(QUERYDIR)/$@.txt > o2.txt
	./walk $(MAPDIR)/usa.txt o1.txt o2.txt $(QUERYDIR)/$@.txt
	rm o1.txt o2.txt

5x5:shortestpath walk $(MAPDIR)/map5x5.txt $(QUERYDIR)/query5x5.txt
	./shortestpath $(MAPDIR)/map5x5.txt $(QUERYDIR)/query5x5.txt > o1.txt
	$(GIVENBINARY) $(MAPDIR)/map5x5.txt $(QUERYDIR)/query5x5.txt > o2.txt
	./walk $(MAPDIR)/map5x5.txt o1.txt o2.txt $(QUERYDIR)/query5x5.txt
	rm o1.txt o2.txt

walk:$(ODIR)/fileio.o $(ODIR)/walk.o
	gcc -o walk $^ $(LINKFLAGS)

clean:
	rm -f *~
	rm -f shortestpath
	rm -f pqtest2
	rm -f pqueuetest
	rm -f walk

cleanAll:clean
	rm -f $(ODIR)/*

$(PROVMAP):
	$(WGET) $(SITE)/$(notdir $@)
	cp $(FILE)/$(notdir $@) $@
	$(CLEANUP)

$(PROVQUERY):
	$(WGET) $(SITE)/$(notdir $@)
	cp $(FILE)/$(notdir $@) $@
	$(CLEANUP)


$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))
