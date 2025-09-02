# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Linker flags
LDFLAGS = -lncurses

# Source files (recursive)
SRC = $(shell find src -name '*.c')

# Object files
OBJ = $(SRC:.c=.o)

# Executable
TARGET = cli

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

# Pattern rule to compile .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test files
TEST_SRC = $(shell find tests -name '*.c')
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = run_tests

$(TEST_TARGET): $(TEST_OBJ) src/commands.o
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) src/commands.o $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJ) $(TEST_OBJ)

.PHONY: all clean test