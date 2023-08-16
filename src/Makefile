IDIR=../include

CC=gcc
CFLAGS=-I$(IDIR) -Wall -pedantic -std=c99
DEPS=$(IDIR)/. 
OBJ=bait.c display.c fileio.c
EXEC=bait
DEST=/usr/local/bin
BASHRC=~/.bashrc
BIN=../bin/

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
	strip --strip-all ./$(EXEC)
	mv ./$(EXEC) $(DEST) 
#	echo "# Bait environment variable" >> $(BASHRC)
#	echo "# max value = 10" >> $(BASHRC)
#	echo "export BAIT_LIST_SIZE=5" >> $(BASHRC)
#	echo "alias bait=\"source $(EXEC)\"" >> $(BASHRC)
