CC = gcc
CFLAGS = -g -pedantic -I./include

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
INCLUDE_DIR = include

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Main program sources
MAIN_SRCS = src/main.c

# Library module sources
LIB_SRCS = src/expr.c \
	src/lexer.c \
	src/parser.c \
        src/printer.c

# Test sources
TEST_SRCS = tests/expr_test.c \
	tests/lexer_test.c \
	tests/parser_test.c \
	tests/evaluation_test.c

# Object files
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Program binaries
PROGRAMS = $(MAIN_SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

# Test binaries
TEST_PROGRAMS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(BIN_DIR)/%)

all: $(PROGRAMS) $(TEST_PROGRAMS)

# Library object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Main programs (depend on library objects)
$(BIN_DIR)/%: $(SRC_DIR)/%.c $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Test programs (depend on library objects)
$(BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_PROGRAMS)
	@echo "Running all tests..."
	@for test in $(TEST_PROGRAMS); do \
		echo "Running $$test"; \
		$$test || exit 1; \
	done
	@echo "All tests passed!"

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: all test clean
