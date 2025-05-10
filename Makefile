# Makefile za SDL2 projekt z avtomatiziranim kopiranjem DLL

# Nastavitve prevajalnika
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Iinc -Iinclude -Isrc -DSDL_MAIN_HANDLED
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows

# Poti
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .
MINGW_BIN = /mingw64/bin

# Seznam vseh potrebnih DLL datotek
DLLS = SDL2.dll SDL2_image.dll SDL2_ttf.dll SDL2_mixer.dll \
       libpng16-16.dll zlib1.dll libfreetype-6.dll

# Vse izvorne datoteke
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET = $(BIN_DIR)/game.exe

# Privzeta pravila
all: $(TARGET) copy_dlls

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Pravilo za kopiranje DLL datotek
copy_dlls: $(TARGET)
	@echo "Kopiram potrebne DLL datoteke..."
	@for dll in $(DLLS); do \
		if [ -f $(MINGW_BIN)/$$dll ]; then \
			cp $(MINGW_BIN)/$$dll $(BIN_DIR) && echo "Kopiral $$dll"; \
		else \
			echo "Opozorilo: $$dll ni bil najden v $(MINGW_BIN)"; \
		fi \
	done
	@echo "Vse DLL datoteke so pripravljene"

run: $(TARGET) copy_dlls
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	rm -f $(foreach dll,$(DLLS),$(BIN_DIR)/$(dll))

.PHONY: all run clean copy_dlls