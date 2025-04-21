CXXFLAGS = -std=c++17 -Wall -Wextra -Iinc -IC:/SDL2/include
LDFLAGS = -LC:/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,obj/%.o,$(SRC))
EXE = bin/mygame.exe

all: $(EXE)

$(EXE): $(OBJ)
	@mkdir -p bin
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj bin

.PHONY: all clean