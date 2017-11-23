CC := gcc
CFLAGS := -Wall -Werror -Wshadow -g

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
TESTS := priorityqueue.c
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


.PHONY:clean cleanAll all ca usa 5x5

all: shortestpath
	echo " $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))"

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
	gcc -o $@ $^

pqueuetest:$(ODIR)/utility.o $(ODIR)/priorityqueue.o
	gcc -o $@ $^

ca:shortestpath $(MAPDIR)/roadCA.txt $(QUERYDIR)/usa10.txt
	valgrind ./shortestpath $(MAPDIR)/roadCA.txt $(QUERYDIR)/usa10.txt

usa:shortestpath $(MAPDIR)/usa.txt $(QUERYDIR)/usa10.txt
	./shortestpath $(MAPDIR)/usa.txt $(QUERYDIR)/usa10.txt

5x5:shortestpath ./shortestpath $(MAPDIR)/5x5.txt $(QUERYDIR)/5x5query.txt
	valgrind ./shortestpath $(MAPDIR)/5x5.txt $(QUERYDIR)/5x5query.txt

clean:
	rm -f *~
	rm -f shortestpath

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
