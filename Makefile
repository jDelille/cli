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

# Compile CLI
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Test files
TEST_SRC = $(shell find tests -name '*.c')
TEST_TARGET = run_tests

# Compile and run tests
$(TEST_TARGET): $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) -o $(TEST_TARGET) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build
clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all clean test