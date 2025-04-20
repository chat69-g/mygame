# Kompilator
CXX = g++

# SDL2 poti (prilagodi glede na tvojo namestitev)
SDL2_INC = -IC:/SDL2/SDL2-2.32.4/include
SDL2_LIB = -LC:/SDL2/SDL2-2.32.4/lib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lmingw32

# Izvorne datoteke (dodaj vse potrebne .cpp)
SRC = src/main.cpp src/Game.cpp src/Player.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = MYGAME_Bikec.exe

# Prevajalne zastavice
CXXFLAGS = -std=c++17 -Wall $(SDL2_INC)
LDFLAGS = $(SDL2_LIB)

# Pravila
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(subst /,\,$(OBJ)) $(TARGET) 2> nul

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run