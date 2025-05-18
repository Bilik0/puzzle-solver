CC = g++
CFLAGS = -Iinclude -Isrc -std=c++17 -Wall -Wextra
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/puzzle_solver

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: directories $(TARGET)
	@echo "Build complete. Executable is located at $(TARGET)"
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(dir $(OBJS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all directories clean