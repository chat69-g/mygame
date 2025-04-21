# Vaš obstoječi Makefile z minimalnimi spremembami
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Iinc -IC:/SDL2/include
CXXFLAGS += -Wno-delete-incomplete 
LDFLAGS = -LC:/SDL2/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lmingw32 -mwindows

SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Dodajte TextureManager.cpp k SOURCES
SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(SRCDIR)/TextureManager.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/mygame.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean