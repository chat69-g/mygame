#pragma once
#include <SDL2/SDL.h>       // Za SDL_Renderer
#include <SDL2/SDL_ttf.h>   // Za TTF_Font
#include <vector>
#include <string>

using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class ScoreManager {
private:
    vector<pair<string, double>> scores; // Seznam rezultatov (ime, čas)

public:
    void addScore(const string& name, double time); // Dodaj rezultat
    void saveScores(const string& filename) const; // Shrani rezultate v datoteko
    void loadScores(const string& filename); // Naloži rezultate iz datoteke
    void displayTopScores(SDL_Renderer* renderer, TTF_Font* font) const; // Prikaži top 5 rezultatov
};