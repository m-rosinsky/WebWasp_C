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

	@echo "   done"

link: setup compile
	@echo -n "Linking binaries..."
	@$(CC) $(CFLAGS) -o $(BINS)/$(RELEASE) src/main.c # $(OBJS)/*.o
	@echo "   done"

clean:
	@$(RM) -rf $(OBJS) $(BINS)
