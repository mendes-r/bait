IDIR=../include

CC=gcc
CFLAGS=-I$(IDIR) -Wall -pedantic -std=c99
DEPS=$(IDIR)/. 
OBJ=bait.c display.c
EXEC=bait
DEST=/usr/local/bin
BASHRC=~/.bashrc

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

h: run
	@./$(EXEC) -h

install: run
	strip --strip-all ./$(EXEC)
	mv ./$(EXEC) $(DEST) 
#	echo "# Bait environment variable" >> $(BASHRC)
#	echo "# max value = 10" >> $(BASHRC)
#	echo "export BAIT_LIST_SIZE=5" >> $(BASHRC)
#	echo "alias bait=\"source $(EXEC)\"" >> $(BASHRC)
