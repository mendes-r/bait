IDIR=../include
BIN=../bin/

CC=gcc
CFLAGS=-I$(IDIR) -Wall -pedantic -std=c99
DEPS=$(IDIR)/. 
OBJ=bait.c content.c plotter.c
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
	echo "alias bait='eval $$(bait 3>&1 1>&2 2>&3)'" >> ~/.bashrc
