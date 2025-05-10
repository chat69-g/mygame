# Makefile za mygame projekt - popravljena različica

# Prevajalnik
CC = g++

# Opcije za prevajanje
CFLAGS = -Wall -Wextra -std=c++17 -Iinc -Iinclude -Isrc
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system

# Imeniki
SRC_DIR = src
INC_DIRS = inc include src
OBJ_DIR = obj
BIN_DIR = .

# Vse izvorne datoteke
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Dodaj vse imenike z headerji kot -I zastavice
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

# Izhodna datoteka
TARGET = $(BIN_DIR)/game.exe

# Privzeta pravila
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)

.PHONY: all run clean