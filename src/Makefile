# Makefile za mygame projekt

# Prevajalnik
CC = g++

# Opcije za prevajanje
CFLAGS = -Wall -Wextra -std=c++17

# Knjižnice
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Izvorna datoteka
SRC = main.cpp

# Izhodna datoteka
TARGET = game.exe

# Privzeta ciljna pravila
all: $(TARGET)

# Pravilo za prevajanje
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Pravilo za zagon
run: $(TARGET)
	./$(TARGET)

# Pravilo za čiščenje
clean:
	rm -f $(TARGET)