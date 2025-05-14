#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class ReplayManager {
private:
    vector<pair<int, int>> movements; // Seznam premikov igralca

public:
    void recordMovement(int x, int y); // Zabeleži premik igralca
    void saveReplay(const string& filename) const; // Shrani replay v datoteko
    void loadReplay(const string& filename); // Naloži replay iz datoteke
    void displayReplay(SDL_Renderer* renderer, TTF_Font* font) const; // Prikaži replay na zaslonu
};