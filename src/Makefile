IDIR=../include
BIN=../bin/

CC=gcc
CFLAGS=-I$(IDIR) -Wall -pedantic -std=c99
DEPS=$(IDIR)/. 
OBJ=bait.c plotter.c content.c
EXEC=bait
DEST=/usr/local/bin
BASHRC=~/.bashrc

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	@mkdir -p $(BIN)
	@$(CC) -o $(BIN)$(EXEC) $^ $(CFLAGS)

g: run
	@$(BIN)$(EXEC) -g

r: run
	@$(BIN)$(EXEC) -r

c: run
	@$(BIN)$(EXEC)

h: run
	@$(BIN)$(EXEC) -h

install: run
	@strip --strip-all ./$(EXEC)
	mv ./$(EXEC) $(DEST) 
