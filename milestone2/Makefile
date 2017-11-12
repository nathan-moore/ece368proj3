CC := gcc
CFLAGS := -Wall -Werror -Wshadow -g

TARGET = adjacent

ODIR :=../obj
MAPDIR :=../map
QUERYDIR :=../query

$(shell mkdir -p $(ODIR) >/dev/null)

CSOURCE = $(wildcard *.c)
COBJ = $(CSOURCE:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(COBJ))

COMPILE.c = $(CC) $(CFLAGS) -c

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

all: $(TARGET)

$(ODIR)/%.o: %.c
	$(COMPILE.c) -o $@ $< $(CFLAGS)

$(TARGET):$(OBJ)
	gcc -o $@ $^

ca:$(TARGET) $(MAPDIR)/roadCA.txt 
	./$(TARGET) $(MAPDIR)/roadCA.txt 

usa:$(TARGET) $(MAPDIR)/usa.txt 
	./$(TARGET) $(MAPDIR)/usa.txt 

5x5:$(TARGET) $(MAPDIR)/map5x5.txt
	valgrind ./$(TARGET) $(MAPDIR)/map5x5.txt 

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





