CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/kellerautomat

SRC = $(SRC_DIR)/kellerautomat.c $(SRC_DIR)/linkedstack.c
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/linkedstack.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJ) $(TARGET) $(BIN_DIR)/kellerautomat_tests

test: $(BIN_DIR)/kellerautomat_tests
	./$(BIN_DIR)/kellerautomat_tests

$(BIN_DIR)/kellerautomat_tests: test/test_kellerautomat.c $(SRC_DIR)/kellerautomat.c $(SRC_DIR)/linkedstack.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -DKELLERAUTOMAT_NO_MAIN $^ -o $@