all: ; mkdir -p obj bin && g++ -std=c++17 -Wall -Wextra -Werror -Iinc -IC:/SDL2/include -LC:/SDL2/lib -o bin/mygame.exe src/*.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lmingw32 -mwindows

clean: ; rm -rf obj bin

.PHONY: all clean