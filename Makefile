CC = gcc
OBJS = RLEList.o main.o
EXEC = AsciiArtTool
COMP_FLAG = -std=c99 -Wall -Werror
OTHERDIR = tool

$(EXEC) : $(OBJS)
	$(CC) $(COMP_FLAG) RLEList.o main.o -o $@

RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(COMP_FLAG) $*.c

main.o : $(OTHERDIR)/main.c RLEList.h $(OTHERDIR)/AsciiArtTool.h
	$(CC) -c $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)