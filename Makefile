# Makefile za SDL2 projekt na Windowsu

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Iinc -Iinclude -Isrc
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows  # Dodajte -mwindows za Windows aplikacijo

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET = $(BIN_DIR)/game.exe

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)

.PHONY: all run clean