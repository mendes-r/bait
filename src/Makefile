IDIR=../include
BIN=../bin/

CC=gcc
CFLAGS=-I$(IDIR) -Wall -pedantic -std=c99
DEPS=$(IDIR)/. 
OBJ=bait.c content.c plotter.c
EXEC=bait-tool
DEST=/usr/local/bin/
BASHRC=~/.bashrc

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	@mkdir -p $(BIN)
	@$(CC) -o $(BIN)$(EXEC) $^ $(CFLAGS)

run-debug: $(OBJ)
	@mkdir -p $(BIN)
	@$(CC) -D DEBUG=1 -o $(BIN)$(EXEC) $^ $(CFLAGS)

g: run
	@$(BIN)$(EXEC) g

r: run
	@$(BIN)$(EXEC) r

c: run
	@$(BIN)$(EXEC) c

h: run
	@$(BIN)$(EXEC) h

install: run
	@strip --strip-all $(BIN)$(EXEC)
	mv $(BIN)$(EXEC) $(DEST) 

install-debug: run-debug
	mv $(BIN)$(EXEC) $(DEST) 
