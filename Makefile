# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Linker flags
LDFLAGS = -lncurses

# Source files
SRC = $(wildcard src/*.c)

# Executable
TARGET = cli

# Default target
all: $(TARGET)

# Compile all sources into one executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean build
clean:
	rm -f $(TARGET)

.PHONY: all clean