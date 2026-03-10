SRC_DIR = src
BIN_DIR = bin
INC_DIR = include
TARGET = $(BIN_DIR)/tests

CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -g

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

all: $(TARGET)

clean:
	rm -f $(BIN_DIR)/*

run: all
	./$(TARGET)

.PHONY: all