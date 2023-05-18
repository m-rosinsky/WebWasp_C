# Compiler selection.
CC=gcc

# Compiler flags.
CFLAGS=-Wall -Wextra -pedantic

# Object directory
OBJS=objs

# Binary directory
BINS=bins

# Binary names
RELEASE=webwasp
DEBUG=webwasp-db

################################################################################

all: setup compile link

setup:
	@echo -n "Creating subdirectories..."
	@mkdir -p $(OBJS) $(BINS)
	@echo "   done"

compile:
	@echo -n "Compiling source files..."

# Utility sources
	@$(CC) $(CFLAGS) -o $(OBJS)/queue.o -c src/utils/queue.c
	@$(CC) $(CFLAGS) -o $(OBJS)/history.o -c src/utils/history.c

# Src sources
	@$(CC) $(CFLAGS) -o $(OBJS)/console.o -c src/console.c
	@$(CC) $(CFLAGS) -o $(OBJS)/command.o -c src/command.c
	@$(CC) $(CFLAGS) -o $(OBJS)/parser.o -c src/parser.c
	@$(CC) $(CFLAGS) -o $(OBJS)/http.o -c src/http.c

# Command sources
	@$(CC) $(CFLAGS) -o $(OBJS)/command_show.o -c src/commands/command_show.c
	
	@echo "   done"

link: setup compile
	@echo -n "Linking binaries..."
	@$(CC) $(CFLAGS) -o $(BINS)/$(RELEASE) src/main.c $(OBJS)/*.o
	@echo "   done"

clean:
	@$(RM) -rf $(OBJS) $(BINS)
