CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -pedantic
LDLIBS = -lm

# Find all .c files
SOURCES = $(wildcard *.c)

# Create executable names (remove .c extension)
EXECUTABLES = $(SOURCES:.c=)

# Default target - build all executables
all: $(EXECUTABLES)

# Pattern rule: compile each .c file into its own executable
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

# Clean up
clean:
	rm -f $(EXECUTABLES)

.PHONY: all clean