IDIR=../include

CC=gcc
CFLAGS=-I$(IDIR) -Wall -pedantic -std=c99
DEPS=$(IDIR)/. 
OBJ=bait.c display.c
EXEC=bait.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	@$(CC) -o $(EXEC) $^ $(CFLAGS)

g: run
	@./$(EXEC) -g

r: run
	@./$(EXEC) -r

c: run
	@./$(EXEC)
