# Compiler selection.
CC=gcc

# Compiler flags.
CFLAGS=-Wall -Wextra -pedantic -Werror

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

# Common sources
	@$(CC) $(CFLAGS) -o $(OBJS)/vector.o -c src/common/vector.c

# Command sources
	@$(CC) $(CFLAGS) -o $(OBJS)/node.o -c src/command/node.c
	@$(CC) $(CFLAGS) -o $(OBJS)/command_ast.o -c src/command/command_ast.c

# Console sources
	@$(CC) $(CFLAGS) -o $(OBJS)/history.o -c src/console/history.c
	@$(CC) $(CFLAGS) -o $(OBJS)/console.o -c src/console/console.c
	@$(CC) $(CFLAGS) -o $(OBJS)/parser.o -c src/console/parser.c
	
	@echo "   done"

link: setup compile
	@echo -n "Linking binaries..."
	@$(CC) $(CFLAGS) -o $(BINS)/$(RELEASE) src/main.c $(OBJS)/*.o
	@echo "   done"

# Test deletion for github action validation.
	@$(RM) -rf $(OBJS) $(BINS)

clean:
	@$(RM) -rf $(OBJS) $(BINS)
