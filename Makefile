CC = g++
CFLAGS = -Iinclude -Isrc -std=c++17 -Wall -Wextra
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/puzzle_solver

# Рекурсивный поиск всех .cpp файлов в директории src и поддиректориях
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
# Создание списка объектных файлов из исходников
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: directories $(TARGET)

# Создание всех необходимых директорий
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