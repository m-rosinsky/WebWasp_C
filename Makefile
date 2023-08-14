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
	@echo "Creating subdirectories..."

	@mkdir -p $(OBJS)
	@echo "  [+] Created $(OBJS)"

	@mkdir -p $(BINS)
	@echo "  [+] Created $(BINS)"

	@echo "done"

compile:
	@echo "Compiling source files..."

# Common sources
	@$(CC) $(CFLAGS) -o $(OBJS)/vector.o -c src/common/vector.c
	@echo "  [+] Compiled object $(OBJS)/vector.o"

	@$(CC) $(CFLAGS) -o $(OBJS)/string_utils.o -c src/common/string_utils.c
	@echo "  [+] Compiled object $(OBJS)/string_utils.o"

# Command sources
	@$(CC) $(CFLAGS) -o $(OBJS)/node.o -c src/command/node.c
	@echo "  [+] Compiled object $(OBJS)/node.o"

	@$(CC) $(CFLAGS) -o $(OBJS)/command_ast.o -c src/command/command_ast.c
	@echo "  [+] Compiled object $(OBJS)/command_ast.o"

# Console sources
	@$(CC) $(CFLAGS) -o $(OBJS)/history.o -c src/console/history.c
	@echo "  [+] Compiled object $(OBJS)/history.o"

	@$(CC) $(CFLAGS) -o $(OBJS)/console.o -c src/console/console.c
	@echo "  [+] Compiled object $(OBJS)/console.o"
	
	@echo "done"

link: setup compile
	@echo "Linking binaries..."

	@$(CC) $(CFLAGS) -o $(BINS)/$(RELEASE) src/main.c $(OBJS)/*.o
	@echo "  [+] Linked binary $(OBJS)/$(RELEASE)"
	
	@echo "done"

clean:
	@echo "Cleaning..."

	@$(RM) -rf $(OBJS)
	@echo "  [-] Removed $(OBJS)"

	@$(RM) -rf $(BINS)
	@echo "  [-] Removed $(BINS)"

	@echo "done"